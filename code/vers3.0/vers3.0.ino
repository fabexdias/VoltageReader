int aprox = 0; // aprox pode tomar 3 valores:
// aprox = 0, para este caso não há qualquer aproximação;
// aprox = 1, para este caso há aproximação segundo os dados do MATLAB, para uma função de grau 1;
// aprox = 2, para este caso há aproximação segundo os dados do MATLAB, para uma função de grau 2;

double icc = 0.15; // icc pode tomar valores entre [0; +inf[, trata-se do índice de coeficiente de cagasso

int Pin[6]; // Valor lido pelo ADC (entre 0 e 1023)
double Vin[6]; // Valores de tensão referentes ao GND
double Vtotal; // Valor total do pack
double Vfloor[6]; // Valores de tensão de cada andar
double Vr[6]; // Valores de tensão retificados
double norm = (5.0 / 1023); // Constante de normalização

void setup() {
  // put your setup code here, to run once:

  // Inicialização do monitor
  Serial.begin(9600);
  // Inicialização dos pins usados
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Leitura de andar 1
  Pin[0] = analogRead(A5);
  Vin[0] = Pin[0] * norm; // Normalização

  // Leitura de andar 2
  Pin[1] = analogRead(A4);
  Vin[1] = Pin[1] * norm * 2; // x2 uma vez que se trata de um divisor de tensão com R_1 e R_2 iguais

  // Leitura de andar 3
  Pin[2] = analogRead(A3);
  Vin[2] = Pin[2] * norm * 3; // x3 uma vez que se trata de um divisor de tensão com R_1 = 10k e R_2 = 20k

  // Leitura de andar 4
  Pin[3] = analogRead(A2);
  Vin[3] = Pin[3] * norm * 6.1; // x6.1 uma vez que se trata de um divisor de tensão com R_1 = 10k e R_2 = 51k

  // Leitura de andar 5
  Pin[4] = analogRead(A1);
  Vin[4] = Pin[4] * norm * 6.1;

  // Leitura de andar 6
  Pin[5] = analogRead(A0);
  Vin[5] = Pin[5] * norm * 6.1;

  switch (aprox) {
    case 0:
      Vr[0] = Vin[0] - icc;
      Vr[1] = Vin[1] - icc;
      Vr[2] = Vin[2] - icc;
      Vr[3] = Vin[3] - icc;
      Vr[4] = Vin[4] - icc;
      Vr[5] = Vin[5] - icc;
    case 1:
      if (Vin[0] > 0.1 && Vin[1] > 0.1 && Vin[2] > 0.1 && Vin[3] > 0.1 && Vin[4] > 0.1 && Vin[5] > 0.1) {
        Vr[0] = Vin[0] * 1.064813067694310 - 0.046151742686869; // Ajuste do erro consuante calculos do MATLAB
        Vr[1] = Vin[1] * 1.020410287289550 + 0.030103119898705;
        Vr[2] = Vin[2] * 1.026701122174919 - 0.007965747012040;
        Vr[3] = Vin[3] * 1.029332050573825 + 0.051099729730813;
        Vr[4] = Vin[4] * 1.015451373069476 + 0.092686668819097;
        Vr[5] = Vin[5] * 1.020056451830968 + 0.064401035977903;
      } else {
        Vr[0] = Vin[0] - icc; // Ajuste para tensões negativas e bastante baixas
        Vr[1] = Vin[1] - icc;
        Vr[2] = Vin[2] - icc;
        Vr[3] = Vin[3] - icc;
        Vr[4] = Vin[4] - icc;
        Vr[5] = Vin[5] - icc;
      }
    case 2:
      if (Vin[0] > 0.1 && Vin[1] > 0.1 && Vin[2] > 0.1 && Vin[3] > 0.1 && Vin[4] > 0.1 && Vin[5] > 0.1) {
        Vr[0] = Vin[0] * Vin[0] * 0.02848062071263 + Vin[0] * 1.233808089479950 - 0.285791170374611; // Ajuste do erro consuante calculos do MATLAB
        Vr[1] = Vin[1] * Vin[1] * (- 0.0022891477) + Vin[1] * 1.048112921191865 - 0.050001255229755;
        Vr[2] = Vin[2] * Vin[2] * (- 0.0003769935) + Vin[2] * 1.033537899959138 - 0.037585110412167;
        Vr[3] = Vin[3] * Vin[3] * 0.00099724727495 + Vin[3] * 1.005419419539337 + 0.187821793856340;
        Vr[4] = Vin[4] * Vin[4] * (- 0.0012380283) + Vin[4] * 1.053058138656335 - 0.179696139690356;
        Vr[5] = Vin[5] * Vin[5] * (- 0.0009242895) + Vin[5] * 1.020056451830968 + 0.064401035977903;
      } else {
        Vr[0] = Vin[0] - icc; // Ajuste para tensões negativas e bastante baixas
        Vr[1] = Vin[1] - icc;
        Vr[2] = Vin[2] - icc;
        Vr[3] = Vin[3] - icc;
        Vr[4] = Vin[4] - icc;
        Vr[5] = Vin[5] - icc;
      }
    default:
      Vr[0] = Vin[0];
      Vr[1] = Vin[1];
      Vr[2] = Vin[2];
      Vr[3] = Vin[3];
      Vr[4] = Vin[4];
      Vr[5] = Vin[5];
  }

  // Calculo das tensões individuais de cada andar + 0.15 de folga
  Vfloor[0] = Vr[0] + icc;
  Vfloor[1] = Vr[1] - Vr[0] + icc;
  Vfloor[2] = Vr[2] - Vr[1] + icc;
  Vfloor[3] = Vr[3] - Vr[2] + icc;
  Vfloor[4] = Vr[4] - Vr[3] + icc;
  Vfloor[5] = Vr[5] - Vr[4] + icc;
  Vtotal = Vfloor[0] + Vfloor[1] + Vfloor[2] + Vfloor[3] + Vfloor[4] + Vfloor[5] - icc * 5; // <=> + icc * 1

  // Envio dos dados para o ecrã
  Serial.print("*De baixo para cima*"); // Print de uma string
  Serial.println(); // Dá enter

  Serial.print("Andar 1: ");
  Serial.print(Vfloor[0], 4); // Print de um valor decimal com 4 casas decimais
  if (Vfloor[0] > 3.9) {
    Serial.print(" *AVISO 1 - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[1]) > 0.3 || fabs(Vfloor[0] - Vfloor[2]) > 0.3 || fabs(Vfloor[0] - Vfloor[3]) > 0.3 || fabs(Vfloor[0] - Vfloor[4]) > 0.3 || fabs(Vfloor[0] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 2: ");
  Serial.print(Vfloor[1], 4);
  if (Vfloor[1] > 3.9) {
    Serial.print(" *ATENÇÃO - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[1]) > 0.3 || fabs(Vfloor[1] - Vfloor[2]) > 0.3 || fabs(Vfloor[1] - Vfloor[3]) > 0.3 || fabs(Vfloor[1] - Vfloor[4]) > 0.3 || fabs(Vfloor[1] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 3: ");
  Serial.print(Vfloor[2], 4);
  if (Vfloor[2] > 3.9) {
    Serial.print(" *ATENÇÃO - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[2]) > 0.3 || fabs(Vfloor[1] - Vfloor[2]) > 0.3 || fabs(Vfloor[2] - Vfloor[3]) > 0.3 || fabs(Vfloor[2] - Vfloor[4]) > 0.3 || fabs(Vfloor[2] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 4: ");
  Serial.print(Vfloor[3], 4);
  if (Vfloor[3] > 3.9) {
    Serial.print(" *ATENÇÃO - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[3]) > 0.3 || fabs(Vfloor[1] - Vfloor[3]) > 0.3 || fabs(Vfloor[2] - Vfloor[3]) > 0.3 || fabs(Vfloor[3] - Vfloor[4]) > 0.3 || fabs(Vfloor[3] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 5: ");
  Serial.print(Vfloor[4], 4);
  if (Vfloor[4] > 3.9) {
    Serial.print(" *ATENÇÃO - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[4]) > 0.3 || fabs(Vfloor[1] - Vfloor[4]) > 0.3 || fabs(Vfloor[2] - Vfloor[4]) > 0.3 || fabs(Vfloor[3] - Vfloor[4]) > 0.3 || fabs(Vfloor[4] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 6: ");
  Serial.print(Vfloor[5], 4);
  if (Vfloor[5] > 3.9) {
    Serial.print(" *ATENÇÃO - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[5]) > 0.3 || fabs(Vfloor[1] - Vfloor[5]) > 0.3 || fabs(Vfloor[2] - Vfloor[5]) > 0.3 || fabs(Vfloor[3] - Vfloor[5]) > 0.3 || fabs(Vfloor[4] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Total: ");
  Serial.print(Vtotal, 4);
  Serial.println();

  Serial.println();
  delay(2000); // Tempo em milisegundos (pode ser aumentado ou diminuido)
}
