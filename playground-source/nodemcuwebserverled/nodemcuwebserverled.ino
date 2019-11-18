// https://www.teachmemicro.com/simple-nodemcu-web-server/
// SETUP/INSTALLATION:
// Add boards to IDE: http://arduino.esp8266.com/stable/package_esp8266com_index.json
// Install Boards Manager - ESP8266
// Reference NodeMCU 1.0 ESP-12E

// D1 = GPIO_5;
// D2 = GPIO_4;
// D3 = GPIO_0;
// D4 = GPIO_2;
// D5 = GPIO_14;
// D6 = GPIO_12;
// D7 = GPIO_13;
// D8 = GPIO_15;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Network contants
const char* ssid = "gorideabike";
const char* password = "tomisthebomb";

//instantiate server at port 80 (http port)
ESP8266WebServer server(80);

// ========================================================================================================================
// GLOBAL
// ========================================================================================================================
// Global variables
const String LED_STATE_KEY = "#LED_STATE_KEY#";

int _digitalPin = 0;

int D_0 = 0;
int D_1 = 1;
int D_2 = 2;
int D_3 = 3;
int D_4 = 4;
int D_5 = 5;
int D_6 = 6;
int D_7 = 7;
int D_8 = 8;

int pinMode_1 = 5;
int pinMode_2 = 4;
int pinMode_3 = 0;
int pinMode_4 = 2;
int pinMode_5 = 14;
int pinMode_6 = 12;
int pinMode_7 = 13;
int pinMode_8 = 15;

// ========================================================================================================================
// INITIALIZE HARDWARE
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// INIT : WS2811
// ------------------------------------------------------------------------------------------------------------------------
// Wire configuration
// -[GND] Connects to ground
// -[DI]  (LED PIN) Add a 220 or 470 Ohm resistor between the Arduino digital output pin and the strip data input pin to 
//        reduce noise on that line.
// -[5V]  Connects to a +5V power supply
// ------------------------------------------------------------------------------------------------------------------------

// ========================================================================================================================
// MAIN
// ========================================================================================================================

// ------------------------------------------------------------------------------------------------------------------------
// setup
// ------------------------------------------------------------------------------------------------------------------------
void setup(void){
  // power-up safety delay
  delay(3000);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  pinMode(pinMode_1, OUTPUT);
  pinMode(pinMode_2, OUTPUT);
  pinMode(pinMode_3, OUTPUT);
  pinMode(pinMode_4, OUTPUT);
  
  pinMode(pinMode_5, OUTPUT);
  pinMode(pinMode_6, OUTPUT);
  pinMode(pinMode_7, OUTPUT);
  pinMode(pinMode_8, OUTPUT);
  
  server.on("/", [](){
    GetHtmlPage(0);
  });

  delay(1000);
  
  ConfigureRoutes();
  
  server.begin();
  Serial.println("Web server started!");
}
 
void loop(void){
  server.handleClient();
}

// ========================================================================================================================
// FUNCTIONS
// ========================================================================================================================

void GetHtmlPage(int digitalPin){
  _digitalPin = digitalPin;

  SetDigitalPin(digitalPin);

  ConfigureRoutes();
  
  String d0 = "<p><a href=\"" + String(D_0) + "\"><button class=\"large\">" + String(D_0) + "</button></a></p>";
  
  String d1 = "<p><a href=\"" + String(D_1) + "\"><button class=\"large\">" + String(D_1) + "</button></a></p>";
  String d2 = "<p><a href=\"" + String(D_2) + "\"><button class=\"large\">" + String(D_2) + "</button></a></p>";
  String d3 = "<p><a href=\"" + String(D_3) + "\"><button class=\"large\">" + String(D_3) + "</button></a></p>";
  String d4 = "<p><a href=\"" + String(D_4) + "\"><button class=\"large\">" + String(D_4) + "</button></a></p>";
  
  String d5 = "<p><a href=\"" + String(D_5) + "\"><button class=\"large\">" + String(D_5) + "</button></a></p>";
  String d6 = "<p><a href=\"" + String(D_6) + "\"><button class=\"large\">" + String(D_6) + "</button></a></p>";
  String d7 = "<p><a href=\"" + String(D_7) + "\"><button class=\"large\">" + String(D_7) + "</button></a></p>";
  String d8 = "<p><a href=\"" + String(D_8) + "\"><button class=\"large\">" + String(D_8) + "</button></a></p>";

  String d_1 = d1 + d2 + d3 + d4;
  String d_2 = d5 + d6 + d7 + d8;

  String off = "<a href=\"Off\"><button>OFF</button></a>";
  
  String s = d0 + d_1 + d_2;

  String headerTags = "<header><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/mini.css/3.0.1/mini-default.min.css\"></header>";
  
  String pageTemplate = "<html>" + headerTags + "<body><h1>Tom's Magic Lantern</h1>" + s + "<p>#LED_STATE_KEY#</p></body></html>";

  pageTemplate.replace(LED_STATE_KEY, String(digitalPin));
  String page = pageTemplate;
  
  server.send(200, "text/html", page);
}

void ConfigureRoutes() {
  server.on(("/" + String(D_0)), [](){ GetHtmlPage(D_0); } );
  server.on(("/" + String(D_1)), [](){ GetHtmlPage(D_1); } );
  server.on(("/" + String(D_2)), [](){ GetHtmlPage(D_2); } );
  server.on(("/" + String(D_3)), [](){ GetHtmlPage(D_3); } );
  server.on(("/" + String(D_4)), [](){ GetHtmlPage(D_4); } );
  server.on(("/" + String(D_5)), [](){ GetHtmlPage(D_5); } );
  server.on(("/" + String(D_6)), [](){ GetHtmlPage(D_6); } );  
  server.on(("/" + String(D_7)), [](){ GetHtmlPage(D_7); } );
  server.on(("/" + String(D_8)), [](){ GetHtmlPage(D_8); } );
}

void SetDigitalPin(int digitalPin) {
/* 
  if(digitalPin == D_1) { digitalWrite( 5, HIGH); } else { digitalWrite( 5, LOW); }
  if(digitalPin == D_2) { digitalWrite( 4, HIGH); } else { digitalWrite( 4, LOW); }
  if(digitalPin == D_3) { digitalWrite( 0, HIGH); } else { digitalWrite( 0, LOW); }
  if(digitalPin == D_4) { digitalWrite( 2, HIGH); } else { digitalWrite( 2, LOW); }
  
  if(digitalPin == D_5) { digitalWrite(14, HIGH); } else { digitalWrite(14, HIGH); }
  if(digitalPin == D_6) { digitalWrite(12, HIGH); } else { digitalWrite(12, HIGH); }
  if(digitalPin == D_7) { digitalWrite(13, HIGH); } else { digitalWrite(13, HIGH); }
  if(digitalPin == D_8) { digitalWrite(15, HIGH); } else { digitalWrite(15, HIGH); }
*/

  digitalWrite(pinMode_1, LOW);
  digitalWrite(pinMode_2, LOW);
  digitalWrite(pinMode_3, LOW);
  digitalWrite(pinMode_4, LOW);

  digitalWrite(pinMode_5, LOW);
  digitalWrite(pinMode_6, LOW);
  digitalWrite(pinMode_7, LOW);
  digitalWrite(pinMode_8, LOW);

  if(digitalPin == D_1) { digitalWrite(pinMode_1, HIGH); Serial.println("Digital 1"); }
  if(digitalPin == D_2) { digitalWrite(pinMode_2, HIGH); Serial.println("Digital 2"); }
  if(digitalPin == D_3) { digitalWrite(pinMode_3, HIGH); Serial.println("Digital 3"); }
  if(digitalPin == D_4) { digitalWrite(pinMode_4, HIGH); Serial.println("Digital 4"); }
  
  if(digitalPin == D_5) { digitalWrite(pinMode_5, HIGH); Serial.println("Digital 5"); }
  if(digitalPin == D_6) { digitalWrite(pinMode_6, HIGH); Serial.println("Digital 6"); }
  if(digitalPin == D_7) { digitalWrite(pinMode_7, HIGH); Serial.println("Digital 7"); }
  if(digitalPin == D_8) { digitalWrite(pinMode_8, HIGH); Serial.println("Digital 8"); }
}

//EOL