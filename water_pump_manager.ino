#include <Wire.h>

/*
Gestion pompe à eau
Améliorer par Bruno Enée 
brunoenee@gmail.com
*/

// DECLARATION DES VARIABLES
// -------------------------
int waterPression = A2;         // Pin lecture pression de l'eau du surpresseur
int delais = 1000;              // Variable pour la fonction delay en milliseconde
int pValue;
float pVout;

const int waterPumpRelay = 13;   // Relay activation pompe à eau
bool statusMoteur;
// -------------------------

// DECLARATION DES FONCTIONS
// -------------------------
void LirePressionEau();
void ActiverPump();
void DesactiverPump();
// -------------------------

void setup(){
   pinMode(waterPression, INPUT);
   pinMode(waterPumpRelay, OUTPUT);

   digitalWrite(waterPumpRelay, HIGH);

   Serial.begin(9600);
   delay(5000);
}

void ActiverPump(){
    //Serial.println("Activation pompe");
    digitalWrite(waterPumpRelay, LOW);
}

void DesactiverPump(){
    //Serial.println("Desactivation pompe");
    digitalWrite(waterPumpRelay, HIGH);
}

void LirePressionEau(){

  pValue = analogRead(waterPression);       // Lire la valeur du pin waterPression
  pVout = (pValue * 5.0) / 1024.0;          // Convertir signal signal analogique 0-5v en signal 0-1024 (echantillonnage) 

  float pressionPascal =  (3.0 * ((float)pVout - 0.47 )) *  1000000.0;  // Convertir signal en pression pascal
  float pressionBar = pressionPascal / 10e5; // Convertir pression pascal en bar

  //Serial.print("\nPression bars  = ");
  //Serial.println(pressionBar, 2);
  statusMoteur = digitalRead(waterPumpRelay);
  //Serial.print("Status relais: ");
  //Serial.print(statusMoteur);
  if (statusMoteur == LOW and pressionBar >= 2 ){
      DesactiverPump();
  }
  else if (statusMoteur == HIGH and pressionBar <= 0.8 ){
      ActiverPump();
  }
}

void loop(){
   LirePressionEau();
   delay(delais);
}
