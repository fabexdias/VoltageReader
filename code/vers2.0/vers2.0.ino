int Pin[6]; // Valor lido pelo ADC (entre 0 e 1023)
double Vin[6]; // Valores de tensão referentes ao GND
double Vfloor[6]; // Valores de tensão de cada andar
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
  Vin[0] = Vin[0] * 0.964477710428959 - 0.0144557368418102; // Ajuste do erro consuante calculos do MATLAB (esta linha pode ser comentada)
  Vfloor[0] = Vin[0];

  // Leitura de andar 2
  Pin[1] = analogRead(A4);
  Vin[1] = Pin[1] * norm * 2; // x2 uma vez que se trata de um divisor de tensão com R_1 e R_2 iguais
  Vin[1] = Vin[1] * 0.963640677589433 - 0.0595120150599494; // (esta linha pode ser comentada)
  Vfloor[1] = Vin[1] - Vin[0];

  // Leitura de andar 3
  Pin[2] = analogRead(A3);
  Vin[2] = Pin[2] * norm * 3; // x3 uma vez que se trata de um divisor de tensão com R_1 = 10k e R_2 = 20k
  Vin[2] = Vin[2] * 0.957234306639532 - 0.0130983700455933; // (esta linha pode ser comentada)
  Vfloor[2] = Vin[2] - Vin[1];

  // Leitura de andar 4
  Pin[3] = analogRead(A2);
  Vin[3] = Pin[3] * norm * 6.1; // x6.1 uma vez que se trata de um divisor de tensão com R_1 = 10k e R_2 = 51k
  Vin[3] = Vin[3] * 0.961077787334594 + 0.00285660413008228; // (esta linha pode ser comentada)
  Vfloor[3] = Vin[3] - Vin[2];

  // Leitura de andar 5
  Pin[4] = analogRead(A1);
  Vin[4] = Pin[4] * norm * 6.1;
  Vfloor[4] = Vin[4] - Vin[3];
  // Ainda não foi analizado o erro deste andar com o MATLAB, porém por serem as mesmas resistências
  // usadas no andar 4, presumo que o ajuste seja bastante parecido

  // Leitura de andar 6
  Pin[5] = analogRead(A0);
  Vin[5] = Pin[5] * norm * 6.1;
  Vfloor[5] = Vin[5] - Vin[4];
  // Idem

  Serial.print("*De baixo para cima*"); // Print de uma string
  Serial.println(); // Dá enter

  Serial.print("Andar 1: ");
  Serial.print(Vfloor[0], DEC); // Print de um valor decimal
  Serial.println();

  Serial.print("Andar 2: ");
  Serial.print(Vfloor[1], DEC);
  Serial.println();

  Serial.print("Andar 3: ");
  Serial.print(Vfloor[2], DEC);
  Serial.println();

  Serial.print("Andar 4: ");
  Serial.print(Vfloor[3], DEC);
  Serial.println();

  Serial.print("Andar 5: ");
  Serial.print(Vfloor[4], DEC);
  Serial.println();

  Serial.print("Andar 6: ");
  Serial.print(Vfloor[5], DEC);
  Serial.println();

  Serial.print("Total: ");
  Serial.print(Vin[5], DEC);
  Serial.println();

  Serial.println();
  delay(1000); // Tempo em milisegundos (pode ser aumentado ou diminuido)
}
