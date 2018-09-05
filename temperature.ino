
// Mesure de la température
// @DemangeJeremy

// Include
#include <LiquidCrystal.h>

const int CAPTEUR = 0;
const int SON = 3;
const int rs = 6, en = 7, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int valeur = 0;
float temp = 0;
float voltage = 0;

float memoireTemp[20];
int increment = 0;
float moyenneTemp = 0;

bool premiereTemp = true;

void setup() {
  Serial.begin(9600);
  pinMode(CAPTEUR, OUTPUT);

  lcd.begin(16, 2);
}

void loop() {  
  // Valeur capteur
  valeur = analogRead(A0);

  // Info
  lcd.setCursor(0,0);
  if (premiereTemp == true) {
  lcd.print("Mesure en cours...");
  }

  // Voltage 
  voltage = (valeur/1024.0) * 5;

  // Temmpérature en degrès
  temp = (voltage - 0.5) * 100;
  memoireTemp[increment] = temp;
  increment++;

  // Affichage de la tempèrature en degrès
  if (increment == 20) {
  premiereTemp = false;
  moyenneTemp = 0;
  for (int i = 0; i < 20; i++) {
    moyenneTemp += memoireTemp[i];
  }
  moyenneTemp = moyenneTemp / 20;
  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(moyenneTemp);
  lcd.print(" C");
  Serial.print("Température : ");
  Serial.print(moyenneTemp);
  Serial.print("\n");
  increment = 0;
  }
  
  delay(500);
}
