#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "WiFiEsp.h"
#include <WiFiEspClient.h>
#include <ThingsBoard.h>
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3);
#endif
#include "EmonLib.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
EnergyMonitor emon1, emon2, emon3;




char ssid[] = "MMANew";
char pass[] = "+v@=#a6Rjp$99";

#define TOKEN "PowerMeter0821"
char thingsboardServer[] = "103.160.95.97";

WiFiEspClient espClient;
ThingsBoard tb(espClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  lastSend = 0;
  lcd.init();
  lcd.backlight();
  emon1.current(0, 35);
  emon2.current(1, 85);
  emon3.current(2, 85);
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Created by Geo");
  lcd.setCursor(0, 1);
  lcd.print("Connecting to Wifi..");

  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to WPA SSID: "));
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }

  Serial.println(F("You're connected to the network"));
  Serial.println();
  lcd.clear();
}

void loop()
{
  if ( !tb.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 1000 ) {
    getAndSendCurrentData();
    lastSend = millis();
  }

  tb.loop();

}

void getAndSendCurrentData()
{
  lcd.setCursor(0, 0);
  lcd.print("IP: ");
  lcd.setCursor(3, 0);
  lcd.print(WiFi.localIP());

  


  double Irmsr = emon1.calcIrms(1480);
  double Irmss = emon2.calcIrms(1480);
  double Irmst = emon3.calcIrms(1480);
  
  double v= 236;
  double ar= Irmsr*v;
  double as= Irmss*v;
  double at= Irmst*v;
  
  Serial.print(F("R: "));
  Serial.println(Irmsr,4);
  Serial.print(F("S: "));
  Serial.println(Irmss,4);
  Serial.print(F("T: "));
  Serial.println(Irmst,4);

  lcd.setCursor(0, 1);
  lcd.print("R :");
  lcd.setCursor(3, 1);
  lcd.print(Irmsr,2);
  lcd.setCursor(7, 1);
  lcd.print("A");

  /*lcd.setCursor(9, 1);
  lcd.print("236");
  lcd.setCursor(12, 1);
  lcd.print("V");
  lcd.setCursor(14, 1);
  lcd.print(ar,2);
  lcd.setCursor(19, 1);
  lcd.print("W");*/

  lcd.setCursor(0, 2);
  lcd.print("S :");
  lcd.setCursor(3, 2);
  lcd.print(Irmss,2);
  lcd.setCursor(7, 2);
  lcd.print("A");
  /*lcd.setCursor(9, 2);
  lcd.print("236");
  lcd.setCursor(12, 2);
  lcd.print("V");
  lcd.setCursor(14, 2);
  lcd.print(as,2);
  lcd.setCursor(19, 2);
  lcd.print("W");*/

  lcd.setCursor(0, 3);
  lcd.print("T :");
  lcd.setCursor(3, 3);
  lcd.print(Irmst,2);
  lcd.setCursor(7, 3);
  lcd.print("A");
  /*lcd.setCursor(9, 3);
  lcd.print("236");
  lcd.setCursor(12, 3);
  lcd.print("V");
  lcd.setCursor(14, 3);
  lcd.print(at,2);
  lcd.setCursor(19, 3);
  lcd.print("W");*/

  tb.sendTelemetryFloat("R", Irmsr);
  tb.sendTelemetryFloat("S", Irmss);
  tb.sendTelemetryFloat("T", Irmst);
}

void reconnect() {
  while (!tb.connected()) {
    Serial.print(F("Connecting to ThingsBoard node ..."));
    if ( tb.connect(thingsboardServer, TOKEN) ) {
      Serial.println(F("[DONE]"));
      lcd.clear();
    } else {
      Serial.print(F("[FAILED]"));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Failed to Connect");
      lcd.setCursor(0, 1);
      lcd.print("Server...");
      delay(2000);
    }
  }
}
