#include <Servo.h>


//////////////
// Petit Bot //
///////////////
// Un programme pedagogique des petits debrouillards ?=+ pour gerer le robot "Petit Bot"
// Voir sur http://wikidebrouillard.org/index.php?title=Petit_Bot_un_robot_controlable_en_Wifi
// Ce programme est inspire de : http://www.esp8266.com/viewtopic.php?f=29&t=6419#sthash.gd1tJhwU.dpuf
// Sous licence CC-By-Sa
// Par des gens bien

#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


const char* version = "V4";
//Bibliotheque Servo
Servo servoG;
Servo servoD;
// Constantes de Broches
int pin_servoG = D1; // pin servo gauche
int pin_servoD = D2; // pin servo droit

String ssid ;
String mdp ;

IPAddress server(192,168,4,15);

WiFiClient client;


void setup() {
    WifiSetup();
}

void WifiSetup()
{
       // IP address of the AP
  ssid = "Manette2";//Manette ou esp
  mdp = "12345678";
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, mdp);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}

void loopManette()
{
  int Etat=0;
  client.connect(server, 80);
  Serial.println("********************************");
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  client.flush();
  client.stop();
  delay(100);
  Etat = answer.toInt();
  Action(Etat);

}

void TournerAGauche()
{
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(0);
  servoD.write(90);
  
}
void TournerADroite()
{
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(90);
  servoD.write(180);
}

void AvancerADroite()
{
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(180);
  servoD.write(70);
 
}

void ReculerADroite()
{
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(70);
  servoD.write(180);
 
}

void AvancerAGauche()
{
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(110);
  servoD.write(0);

}

void ReculerAGauche()
{
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(0);
  servoD.write(110);
 
}

void Avancer()
{
  Serial.println("Avancer");
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(180);
  servoD.write(0);
 
}

void Reculer()
{
  Serial.println("Reculer");
  servoG.attach(pin_servoG);
  servoD.attach(pin_servoD);
  servoG.write(0);
  servoD.write(180);
   
}
void Stop()
{
 servoG.attach(pin_servoG);
 servoD.attach(pin_servoD);
  servoG.write(90);
  servoD.write(90);
   
}

void Action(int c)
{
  Serial.println("Action");
 switch(c){
  
  case 0:
  Serial.println("stop");
  Stop();
  break;
  
  case 1:
  Serial.println("Reculer");
  Reculer();
  break;
  
  case 2:
  Serial.println("Avancer");
  Avancer();
  break;
  
  case 4:
  TournerADroite();
  Serial.println("droite");
  break;

  case 5:
  ReculerADroite();
  //Serial.println("AvancerADroite");
  break;
  
  case 6:
  AvancerADroite();
 // Serial.println("ReculerADroite");
  break;
  
  case 8:
  TournerAGauche();
  break;
  
  case 9:
  ReculerAGauche();
  break;
  
  case 10:
  AvancerAGauche();
  break; 
   
  default:
  Stop();
  break;
  
 }
}

void loop() {
    loopManette();
}
