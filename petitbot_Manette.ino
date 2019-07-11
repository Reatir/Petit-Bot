#include <ESP8266WiFi.h>

WiFiServer server(90);
IPAddress IP(192,168,5,15); //changer l'ip pour chaque nouveau robot 192,168,xxx,xxx
IPAddress mask = (255, 255, 255, 0);

const int buttonPinHaut = D2;     // the number of the pushbutton pin
const int buttonPinBas = D1;
const int buttonPinDroite = D5;     // the number of the pushbutton pin
const int buttonPinGauche = D6;

// variables will change:
int buttonStateHaut = 0;         // variable for reading the pushbutton status
int buttonStateBas = 0;
int buttonStateDroite = 0;         // variable for reading the pushbutton status
int buttonStateGauche = 0;  

String Etat;

const char* ssid = "Manette"; // a changer
const char* password = "12345678";  // a changer
void setup() {
  pinMode(buttonPinHaut, INPUT_PULLUP); // boutton à relier en entree et gnd
  pinMode(buttonPinBas, INPUT_PULLUP);
  pinMode(buttonPinDroite, INPUT_PULLUP);
  pinMode(buttonPinGauche, INPUT_PULLUP);
  Serial.begin(9600); 
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  Serial.println();
  Serial.println("Server started.");
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());
  Serial.print("MAC: "); Serial.println(WiFi.softAPmacAddress());
}

String BoutonAppuye()
{
  int i=0;
  char nombre[5];
  i=buttonStateHaut;
  i+=buttonStateBas*2;
  i+=buttonStateDroite*4;
  i+= buttonStateGauche*8;
  itoa(i,nombre,10);
  Serial.println(nombre);
  return nombre;
  }
  
 void loop() {
 WiFiClient client = server.available();
 if (!client) {return;}
 buttonStateHaut = !digitalRead(buttonPinHaut);
 buttonStateBas = !digitalRead(buttonPinBas);
 buttonStateDroite = !digitalRead(buttonPinDroite);
 buttonStateGauche = !digitalRead(buttonPinGauche);
 Etat = BoutonAppuye();
 Serial.println("********************************");
 Serial.print("Byte sent to the station: ");
 Serial.println(client.println(Etat + "\r"));
}
