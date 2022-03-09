double icc = 0.15; // icc pode tomar valores entre [0; +inf[, trata-se do índice de coeficiente de cagasso

int Pin[6]; // Valor lido pelo ADC (entre 0 e 1023)
double Vin[6]; // Valores de tensão referentes ao GND
double Vtotal; // Valor total do pack
double Vfloor[6]; // Valores de tensão de cada andar
double Vr[6]; // Valores de tensão retificados
double norm = (5.0 / 1023); // Constante de normalização
double Resis[6] = {9.98, 10.00, 10.00, 9.97, 10.00, 10.04}, Divisor[6] = {0, 9.97, 19.91, 50.9, 50.4, 50.9}; // Resistências lidas com o multímetro

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
  Vin[1] = Pin[1] * norm * (Resis[1] + Divisor[1]) / (Resis[1]); // Calculo do fator multiplicativo através das resistências lidas com multímetro

  // Leitura de andar 3
  Pin[2] = analogRead(A3);
  Vin[2] = Pin[2] * norm * (Resis[2] + Divisor[2]) / (Resis[2]);

  // Leitura de andar 4
  Pin[3] = analogRead(A2);
  Vin[3] = Pin[3] * norm * (Resis[3] + Divisor[3]) / (Resis[3]);

  // Leitura de andar 5
  Pin[4] = analogRead(A1);
  Vin[4] = Pin[4] * norm * (Resis[4] + Divisor[4]) / (Resis[4]);

  // Leitura de andar 6
  Pin[5] = analogRead(A0);
  Vin[5] = Pin[5] * norm * (Resis[5] + Divisor[5]) / (Resis[5]);

  // Tensão retificada (atualmente sem retificação pois será necessária nova calibração)
  Vr[0] = Vin[0];
  Vr[1] = Vin[1];
  Vr[2] = Vin[2];
  Vr[3] = Vin[3];
  Vr[4] = Vin[4];
  Vr[5] = Vin[5];

  // Calculo das tensões individuais de cada andar + 0.15 de folga
  if (Vin[0] > 0.1 && Vin[1] > 0.1 && Vin[2] > 0.1 && Vin[3] > 0.1 && Vin[4] > 0.1 && Vin[5] > 0.1) {
    Vfloor[0] = Vr[0] + icc;
    Vfloor[1] = Vr[1] - Vr[0] + icc;
    Vfloor[2] = Vr[2] - Vr[1] + icc;
    Vfloor[3] = Vr[3] - Vr[2] + icc;
    Vfloor[4] = Vr[4] - Vr[3] + icc;
    Vfloor[5] = Vr[5] - Vr[4] + icc;
    Vtotal = Vfloor[0] + Vfloor[1] + Vfloor[2] + Vfloor[3] + Vfloor[4] + Vfloor[5] - icc * 5; // <=> + icc * 1
  } else {
    Vfloor[0] = Vr[0];
    Vfloor[1] = Vr[1] - Vr[0];
    Vfloor[2] = Vr[2] - Vr[1];
    Vfloor[3] = Vr[3] - Vr[2];
    Vfloor[4] = Vr[4] - Vr[3];
    Vfloor[5] = Vr[5] - Vr[4];
    Vtotal = Vfloor[0] + Vfloor[1] + Vfloor[2] + Vfloor[3] + Vfloor[4] + Vfloor[5]; // <=> + icc * 1
  }

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
    Serial.print(" *AVISO 1 - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[1]) > 0.3 || fabs(Vfloor[1] - Vfloor[2]) > 0.3 || fabs(Vfloor[1] - Vfloor[3]) > 0.3 || fabs(Vfloor[1] - Vfloor[4]) > 0.3 || fabs(Vfloor[1] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 3: ");
  Serial.print(Vfloor[2], 4);
  if (Vfloor[2] > 3.9) {
    Serial.print(" *AVISO 1 - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[2]) > 0.3 || fabs(Vfloor[1] - Vfloor[2]) > 0.3 || fabs(Vfloor[2] - Vfloor[3]) > 0.3 || fabs(Vfloor[2] - Vfloor[4]) > 0.3 || fabs(Vfloor[2] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 4: ");
  Serial.print(Vfloor[3], 4);
  if (Vfloor[3] > 3.9) {
    Serial.print(" *AVISO 1 - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[3]) > 0.3 || fabs(Vfloor[1] - Vfloor[3]) > 0.3 || fabs(Vfloor[2] - Vfloor[3]) > 0.3 || fabs(Vfloor[3] - Vfloor[4]) > 0.3 || fabs(Vfloor[3] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 5: ");
  Serial.print(Vfloor[4], 4);
  if (Vfloor[4] > 3.9) {
    Serial.print(" *AVISO 1 - maior que 3.9 V* "); // Aviso de tensão alta
  }
  if (fabs(Vfloor[0] - Vfloor[4]) > 0.3 || fabs(Vfloor[1] - Vfloor[4]) > 0.3 || fabs(Vfloor[2] - Vfloor[4]) > 0.3 || fabs(Vfloor[3] - Vfloor[4]) > 0.3 || fabs(Vfloor[4] - Vfloor[5]) > 0.3) {
    Serial.print(" *AVISO 2 - difere mais do que 0.3 V* "); // Aviso de diferenças de tensão grandes
  }
  Serial.println();

  Serial.print("Andar 6: ");
  Serial.print(Vfloor[5], 4);
  if (Vfloor[5] > 3.9) {
    Serial.print(" *AVISO 1 - maior que 3.9 V* "); // Aviso de tensão alta
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
