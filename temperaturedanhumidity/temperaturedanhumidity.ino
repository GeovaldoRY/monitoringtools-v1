#include <DHT.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiUdp.h>
#include <NTPClient.h>               
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>

//Deklarasi Pin untuk LED
int LEDHIJAU = D6;
int LEDKUNING = D8;
int LEDMERAH = D7;

const char* ssid = "MMANew";
const char* password = "+v@=#a6Rjp$99";

#define TOKEN "Z1P641D1muHU" 
char ThingsboardHost[] = "103.160.95.97";

const long utcOffsetInSeconds = 25200;
WiFiUDP ntpUDP;

//Pool untuk ntp client
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);
//Setup format tanggal dan waktu
char Time[ ] = "Time: 00:00:00";
char Date[ ] = "Date: 00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;


#define TOKEN "Z1P641D1muHU" 
char ThingsboardHost[] = "103.160.95.97";

#define DHTPIN D5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;
unsigned long lastSend;

IPAddress IP(10,10,8,153);
IPAddress NETMASK(255,255,255,0);
IPAddress NETWORK(10,10,8,254);
IPAddress DNS(8,8,8,8);

void setup()
{
  pinMode(LEDHIJAU, OUTPUT);
  pinMode(LEDKUNING, OUTPUT);
  pinMode(LEDMERAH, OUTPUT);
  lcd.init();
  lcd.backlight();
  lastSend = 0;
  Serial.begin(115200);
  dht.begin();

  for (int x=1; x<=3; x++)
  {
    digitalWrite(LEDHIJAU, LOW);
    delay(500);                
    digitalWrite(LEDHIJAU, HIGH);
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Created by G.E.O");
  delay(3000);
  lcd.clear();

  

  WiFi.config(IP, NETWORK, NETMASK, DNS);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LEDKUNING, LOW);
    delay(500);                
    digitalWrite(LEDKUNING, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connecting to");
    lcd.setCursor(0,1);
    lcd.print("WiFi...");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to : ");
  Serial.println(ssid);

  client.setServer( ThingsboardHost, 1883 );
  
  

  timeClient.begin();
}

void loop()
{
if ( !client.connected() ) 
{
    reconnect();
}

if ( millis() - lastSend > 5000 ) { // kirim data suhu tiap 1 detik
    getAndSendTemperatureAndHumidityData();
    lastSend = millis();
    waktusekarang();
    showIP();
  }
  
}

void getAndSendTemperatureAndHumidityData()
{
  
  Serial.println("Collecting temperature data...");

  // baca suhu dan kelembaban
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Failed to");
    lcd.setCursor(0,1);
    lcd.print("Read Sensor...");
    while (isnan(h) || isnan(t))
    {
      digitalWrite(LEDHIJAU, LOW);
      delay(500);                
      digitalWrite(LEDHIJAU, HIGH);
      delay(500);
    }
  }

  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Hum : ");
  lcd.print(h);
  lcd.print(" ");
  lcd.print("%");

  delay(5000);
  lcd.clear();
  
  Serial.println("Sending data to ThingsBoard:");
  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"Temperature\":";
  payload += String(t); 
  payload += ",";
  payload += "\"Humidity\":";
  payload += String(h); 
  payload += "}";

  char attributes[1000];
  payload.toCharArray( attributes, 1000 );
  client.publish( "v1/devices/me/telemetry",attributes);
  Serial.println( attributes );
   
}

void waktusekarang() {
  timeClient.update();
  unsigned long unix_epoch = timeClient.getEpochTime();    // Get Unix epoch time from the NTP server

  second_ = second(unix_epoch);
  if (last_second != second_) {
 

    minute_ = minute(unix_epoch);
    hour_   = hour(unix_epoch);
    day_    = day(unix_epoch);
    month_  = month(unix_epoch);
    year_   = year(unix_epoch);

 

    Time[13] = second_ % 10 + 48;
    Time[12] = second_ / 10 + 48;
    Time[10]  = minute_ % 10 + 48;
    Time[9]  = minute_ / 10 + 48;
    Time[7]  = hour_   % 10 + 48;
    Time[6]  = hour_   / 10 + 48;

 

    Date[6]  = day_   / 10 + 48;
    Date[7]  = day_   % 10 + 48;
    Date[9]  = month_  / 10 + 48;
    Date[10]  = month_  % 10 + 48;
    Date[14] = (year_   / 10) % 10 + 48;
    Date[15] = year_   % 10 % 10 + 48;

    Serial.println(Time);
    Serial.println(Date);

    lcd.setCursor(0, 0);
    lcd.print(Time);
    lcd.setCursor(0, 1);
    lcd.print(Date);
    last_second = second_;
   

  }
  delay(25);

  lcd.setCursor(0, 0);
  lcd.print(Time);
  lcd.setCursor(0, 1);
  lcd.print(Date);

  delay(5000);
}

void showIP() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP Address: ");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());

  delay(5000);

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LEDKUNING, LOW);
        delay(500);                
        digitalWrite(LEDKUNING, HIGH);
        delay(500);
        Serial.print(".");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Wifi Disconnect");
        lcd.setCursor(0,1);
        lcd.print("Retrying...");
      }
      Serial.println("Wifi Connected");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Wifi Connected");
      delay(3000);
    }
    Serial.print("Connecting server...");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connecting to");
    lcd.setCursor(0,1);
    lcd.print("Server...");
    for (int x=1; x<=6; x++)
    {
      digitalWrite(LEDMERAH, LOW);
      delay(500);                
      digitalWrite(LEDMERAH, HIGH);
      delay(500);
    }
    // Attempt to connect (clientId, username, password)
    if ( client.connect("Esp8266", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Connected...");
      delay(3000);
      lcd.clear();
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.println( " : retrying in 5 seconds]" );
      digitalWrite(LEDMERAH, LOW);
      delay(500);                
      digitalWrite(LEDMERAH, HIGH);
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Server Error");
      lcd.setCursor(0,1);
      lcd.print("Retrying...");
    }
  }
}