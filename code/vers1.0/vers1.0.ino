int Pin[6];
double Vin[6], Vfloor[6];
double norm = (5.0 / 1023);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Pin[0] = analogRead(A5);
  Vin[0] = Pin[0] * norm;
  Vfloor[0] = Vin[0];

  Pin[1] = analogRead(A4);
  Vin[1] = Pin[1] * norm * 2;
  Vfloor[1] = Vin[1] - Vin[0];

  Pin[2] = analogRead(A3);
  Vin[2] = Pin[2] * norm * 3;
  Vfloor[2] = Vin[2] - Vin[1];

  Pin[3] = analogRead(A2);
  Vin[3] = Pin[3] * norm * 6.1;
  Vfloor[3] = Vin[3] - Vin[2];

  Pin[4] = analogRead(A1);
  Vin[4] = Pin[4] * norm * 6.1;
  Vfloor[4] = Vin[4] - Vin[3];

  Pin[5] = analogRead(A0);
  Vin[5] = Pin[5] * norm * 6.1;
  Vfloor[5] = Vin[5] - Vin[4];

  Serial.print("*De baixo para cima*");
  Serial.println();
  
  Serial.print("Andar 1: ");
  Serial.print(Vfloor[0], DEC);
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
  delay(1500);
}
