//>>>>>>>>>>>>>>>>>>>Definieren für Blynk und Pins<<<<<<<<<<<<<<<<<<<<<<<
#define BLYNK_TEMPLATE_ID "TMPLILL0zvGV"
#define BLYNK_DEVICE_NAME "Süßigkeitenbox"
#define BLYNK_AUTH_TOKEN "lSmmQXi7QHBQdrdSSsgNGdX-pX5YLpHe"
#define BLYNK_PRINT Serial
#define servoPin D4 
#define pushButtonPin D3

//>>>>>>>>>>>>>>>>>>>>Einbinden nötiger Bibiotheken<<<<<<<<<<<<<<<<<<<<<<<

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include <TimeLib.h>
#include <Time.h>
Servo myservo;                            // Erstellen eines Servoobjekts

//>>>>>>>>>>>>>>>>>>>>>>>>>>>Variablen<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
char auth[] = BLYNK_AUTH_TOKEN;           // Eingabe der Blynk und WIFI Daten 
char ssid[] = "Fischer";                  // SSID des Routers eingeben
char pass[] = "77759504838540776417";     // Passwort des Routers eingeben

int angle =90;                            // Uhrspungs Startgrad des Servos (zwischen 1 und 179)
int angleStep =10;                        // in 10er Schritten
int buttonPushed =0;                      // Variable des Zustandes vom Button


const int minAngle = 0;                   // Konstante nicht änderbare int Werte zur Bestimmung Maximale Schwenkung
const int maxAngle = 180;
const int type =2;                        // Typ 2 start von 180 bis 0 und Typ 1 umgekehrt

//>>>>>>>>>>>>>>>>>>>>Blynk Konfiguration WIFI <<<<<<<<<<<<<<<<<<<<<<<<<<<
BlynkTimer timer;

BLYNK_WRITE(V0){
  int value = param.asInt();              // Umwandeln des Virtuellen Pins in ein Integer
  Blynk.virtualWrite(V1, value);
}

void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}
//>>>>>>>>>>>>>>>>>>>>>Setup für Blink und Servo<<<<<<<<<<<<<<<<<<<<<<<<<<<
void setup()
{
  Serial.begin(115200);                  // Konsolenausgabe per Serial Monitor
  Blynk.begin(auth, ssid, pass);         // Verbindung zum Internet aufgaben
  timer.setInterval(1000L, myTimerEvent);
  
  myservo.attach(servoPin);              // Servo wird dem PIN zugeteilt
  pinMode(pushButtonPin,INPUT_PULLUP);
  myservo.write(angle);
}
  
//>>>>>>>>>>>>>>>>>>>>Servo Bedienung per phyischen Knopfdruck<<<<<<<<<<<<<<<<<<<<<<
double COUNT = 0;                           // Counter um Ausgabe zu begrenzen

void loop(){
  Blynk.run();
  timer.run();
    if (year() != 1970 && hour() == 0 && minute() == 0 && second() == 0){
    COUNT = 0;
  }

  if(digitalRead(pushButtonPin) == LOW){  
    buttonPushed = 1;
    COUNT++;
    Serial.print("Anzahl Knopdrücke: ");
    Serial.println(COUNT);
    Blynk.virtualWrite(V5, COUNT);
    Blynk.syncVirtual(V5);
  }
   if( buttonPushed ){
 
   if (COUNT <= 5)                       
  angle = angle + angleStep;

    // Umkeheren der Rotation
    if (angle >= maxAngle) {
      angleStep = -angleStep;
        if(type ==1)
        {
            buttonPushed =0;
        }
    }

    if (angle <= minAngle) {
      angleStep = -angleStep;
       if(type ==2)
        {
            buttonPushed =0;
        }
    }

  myservo.write(angle);               //Rükehr zur Ursprungsgrad
  delay(100);                         //Wartezeit bis Servo ankommt
   }

}

//>>>>>>>>>>>>>>>>>>>>Methode zur Servodrehung<<<<<<<<<<<<<<<<<<<<<<
void sweep(){
  int pos;
  for (pos = 0; pos <= 40; pos += 1) { // Geht von 0 zu 180 Grad
    
    myservo.write(pos);                // Servo soll zur position "pos" gehen
    delay(0); 
  }
  for (pos = 180; pos >= 0; pos -= 1) { // geht von 180 zu 0 Grad
    myservo.write(pos);                 
    delay(0);                          // Keine Verzögerung, jedoch einstellbar
  }
}

//>>>>>>>>>>>>>>>>>>>>Servobedienung per Blynk App<<<<<<<<<<<<<<<<<<<<<<
BLYNK_WRITE(V4) 
{
  int pinValue = param.asInt();
  if (pinValue == 1) {                  // Wenn Button 1 sendet
    sweep();                            // Startet die sweep Methode
    Blynk.run();                        // Wird ausgeführt bis die loop verlassen/widerholt wird
    int pinValue = 0;                   // Setze V0 auf 0 um aus der loop zu gehen
    Blynk.syncVirtual(V4);              // Status der Blynk_Write funktion testet ob widerholt oder verlassen wird
  }
}
  
