#include "ThingsBoard.h"
#include <Arduino.h>
#include <assert.h>
#include <ESP8266WiFi.h>
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>
#include <IRsend.h>
#include <ir_Gree.h>

#define WIFI_AP             "MMANew"   
#define WIFI_PASSWORD       "+v@=#a6Rjp$99" 

#define TOKEN               "Z1P641D1muHURemote02"  
#define THINGSBOARD_SERVER  "103.160.95.97"

//Penentuan BaudTate
const uint32_t kBaudRate = 115200;
//Untuk Memory Buffer
const uint16_t kCaptureBufferSize = 1024;

#if DECODE_AC
const uint8_t kTimeout = 50;
#else   
const uint8_t kTimeout = 15;
#endif  // DECODE_AC

//Sender Part
const uint16_t kIrLed = 4; 
IRGreeAC ac(kIrLed);  
//Sender Part
//Buzzer Part
const int buzzer = D7;
#ifdef ARDUINO_ESP32C3_DEV
const uint16_t kRecvPin = 10;
#else
const uint16_t kRecvPin = 14;
#endif

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;

IPAddress IP(10,10,8,155);
IPAddress NETMASK(255,255,255,0);
IPAddress NETWORK(10,10,8,254);
IPAddress DNS(8,8,8,8);

const uint16_t kMinUnknownSize = 12;


const uint8_t kTolerancePercentage = kTolerance; 

#define LEGACY_TIMING_INFO false

IRrecv irrecv(kRecvPin, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

void printState() {
  // Display the settings.
  Serial.println("GREE A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
  // Display the encoded IR sequence.
  unsigned char* ir_code = ac.getRaw();
  Serial.print("IR Code: 0x");
  for (uint8_t i = 0; i < kGreeStateLength; i++)
    Serial.printf("%02X", ir_code[i]);
  Serial.println();
}



void setup() {
  // initialize serial for debugging
  ac.begin();
  delay(200);
  WiFi.config(IP, NETWORK, NETMASK, DNS);
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  InitWiFi();
  #if defined(ESP8266)
  Serial.begin(kBaudRate, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(kBaudRate, SERIAL_8N1);
#endif  // ESP8266
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  // Perform a low level sanity checks that the compiler performs bit field
  // packing as we expect and Endianness is as we expect.
  assert(irutils::lowLevelSanityCheck() == 0);

  Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", kRecvPin);
#if DECODE_HASH
  // Ignore messages with less than minimum on or off pulses.
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif  // DECODE_HASH
  irrecv.setTolerance(kTolerancePercentage);  // Override the default tolerance.
  
}

bool subscribed = false;

RPC_Response ts1(const RPC_Data &data)
{
  Serial.println("Received the set switch method 4!");
  char params[10];
  serializeJson(data, params);
  //Serial.println(params);
  String _params = params;
  if (_params == "1") {       
      irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(16);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "2")  {
      irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(17);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "3")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(18);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "4")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(19);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "5")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(20);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "6")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(21);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "7")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(22);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "8")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(23);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "9")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(24);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "10")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(25);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "11")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(26);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "12")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(27);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "13")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(28);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "14")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(29);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "15")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.on();
      ac.setFan(3);
      // kGreeAuto, kGreeDry, kGreeCool, kGreeFan, kGreeHeat
      ac.setMode(kGreeCool);
      ac.setTemp(30);  // 16-30C
      ac.setSwingVertical(false, kGreeSwingMiddleDown);
      ac.setXFan(true);
      ac.setLight(true);
      ac.setSleep(false);
      ac.setTurbo(true);
      sendir();
  }
  else  if (_params == "0")  {
          irrecv.enableIRIn();  // Start the receiver
      //Buzzer part
      pinMode(buzzer, OUTPUT);

      // Set up what we want to send. See ir_Gree.cpp for all the options.
      // Most things default to off.
      Serial.println("Default state of the remote.");
      printState();
      Serial.println("Setting desired state for A/C.");
      ac.off();
      sendir();
  }
}


const size_t callbacks_size = 1;
RPC_Callback callbacks[callbacks_size] = {
  { "getValue_1",         ts1 }   // enter the name of your switch variable inside the string

};

void loop() {

  delay(1000);

  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
  }

  if (!tb.connected()) {
    subscribed = false;
    // Connect to the ThingsBoard
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  if (!subscribed) {
    Serial.println("Subscribing for RPC...");

    // Perform a subscription. All consequent data processing will happen in
    // processTemperatureChange() and processSwitchChange() functions,
    // as denoted by callbacks[] array.
    if (!tb.RPC_Subscribe(callbacks, callbacks_size)) {
      Serial.println("Failed to subscribe for RPC");
      return;
    }

    Serial.println("Subscribe done");
    subscribed = true;

    for (int x=1; x<=2; x++)
    {
      tone(buzzer, 1000, 500);
      delay(200);
      tone(buzzer, 500, 500);
      delay(200);
    }

  }


  tb.loop();
}


void sendir() {
  // Now send the IR signal.
      #if SEND_GREE
      Serial.println("Sending IR command to A/C ...");
      for (int x=1; x<=3; x++)
      {
      ac.send();
      
      //Buzzer part
      tone(buzzer, 1000, 500);
      
      #endif  // SEND_GREE
      printState();
      

      // Check if the IR code has been received.
      if (irrecv.decode(&results)) {
        // Display a crude timestamp.
        uint32_t now = millis();
      Serial.printf(D_STR_TIMESTAMP " : %06u.%03u\n", now / 1000, now % 1000);
      // Check if we got an IR message that was to big for our capture buffer.
      if (results.overflow)
        Serial.printf(D_WARN_BUFFERFULL "\n", kCaptureBufferSize);
      // Display the library version the message was captured with.
      Serial.println(D_STR_LIBRARY "   : v" _IRREMOTEESP8266_VERSION_STR "\n");
      // Display the tolerance percentage if it has been change from the default.
      if (kTolerancePercentage != kTolerance)
      Serial.printf(D_STR_TOLERANCE " : %d%%\n", kTolerancePercentage);
      // Display the basic output of what we found.
      Serial.print(resultToHumanReadableBasic(&results));
      // Display any extra A/C info if we have it.
      String description = IRAcUtils::resultAcToString(&results);
      if (description.length()) Serial.println(D_STR_MESGDESC ": " + description);
      yield();  // Feed the WDT as the text output can take a while to print.
      #if LEGACY_TIMING_INFO
      // Output legacy RAW timing info of the result.
      Serial.println(resultToTimingInfo(&results));
      yield();  // Feed the WDT (again)
      #endif  // LEGACY_TIMING_INFO
        // Output the results as source code
        Serial.println(resultToSourceCode(&results));
        Serial.println();    // Blank line between entries
        yield();             // Feed the WDT (again)
      }
      delay(1500);
    }

}


void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
