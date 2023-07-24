//Code By G.E.O
#include <Arduino.h>
#include "PubSubClient.h"
#include "ESP8266WiFi.h"

//Konek wifi
const char* ssid = "MMANew";
const char* password = "+v@=#a6Rjp$99"; 

#define TOKEN "Z1P641D1muHUAC2" 
char ThingsboardHost[] = "103.160.95.97";


//Modul magnetic
const int reedSwitch = 4;   // Magnet switch
const int led =  14;      // LED pin




const char* h = "Closed";
int state = 0;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;
unsigned long lastSend;

IPAddress IP(10,10,8,158);
IPAddress NETMASK(255,255,255,0);
IPAddress NETWORK(10,10,8,254);
IPAddress DNS(8,8,8,8);

void setup() {
  Serial.begin(115200);
  lastSend = 0;

  WiFi.config(IP, NETWORK, NETMASK, DNS);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to");
  Serial.println(ssid);
  client.setServer( ThingsboardHost, 1883);
  
  pinMode(reedSwitch, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  

}

void loop() {

  if ( !client.connected() ) 
  {
    reconnect();
  }
  getAndSenddoorData();
  //if ( millis() - lastSend > 1000 ) { // kirim data suhu tiap 1 detik
   // getAndSenddoorData();
   // lastSend = millis();
  //}
  
}

void getAndSenddoorData()
{
  
  int bacaSensor = digitalRead(reedSwitch);
  if (bacaSensor == HIGH && state == 0) {
    Serial.println("Open");
    digitalWrite(led, LOW);
    
    state = 1;
    h = "Open";
    // Check if any reads failed and exit early (to try again).
    if (h != "Open") {
      Serial.println("Failed to read from sensor!");
      return;
    }
    Serial.print("Status: ");
    Serial.print(h);
 
    // Prepare a JSON payload string
    String payload = "{";
    payload += "\"Status\":";
    payload += String(h);
    payload += "}";

    char attributes[1000];
    payload.toCharArray( attributes, 1000 );
    client.publish( "v1/devices/me/telemetry",attributes);
    Serial.println( attributes );
  }
  else if (bacaSensor == LOW) {
    state = 0;
    Serial.println("Closed");
    digitalWrite(led, HIGH);
    h = "Closed";

    if (h != "Closed") {
      Serial.println("Failed to read from sensor!");
      return;
    }
    Serial.print("Status: ");
    Serial.print(h);
 
    // Prepare a JSON payload string
    String payload = "{";
    payload += "\"Status\":";
    payload += String(h);
    payload += "}";

    char attributes[1000];
    payload.toCharArray( attributes, 1000 );
    client.publish( "v1/devices/me/telemetry",attributes);
    Serial.println( attributes );
    
  }

  
  delay(1000);

  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(led, LOW);
        delay(500);                
        digitalWrite(led, HIGH);
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to Wifi");
    }
    
    Serial.print("Connecting server...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("Esp8266", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.println( " : retrying in 5 seconds]" );
      digitalWrite(led, LOW);
      delay(500);                
      digitalWrite(led, HIGH);
      delay(500);
    }
  }
}


