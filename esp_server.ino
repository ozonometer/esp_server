/*********
 * Control pins by webserver
*********/
/*
WL_CONNECTED = 3
WL_NO_SHIELD = 255
WL_IDLE_STATUS = 0
WL_NO_SSID_AVAIL = 1
WL_SCAN_COMPLETED = 2
WL_CONNECT_FAILED = 4
WL_CONNECTION_LOST = 5
WL_DISCONNECTED = 6

 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "MMG2";
const char* password = "PracticalElectronicsForInventors";

ESP8266WebServer server(80);
String webPage = "";
//int sensorPin = 12;
int led0 = 2;
//int led1 = 4;
//int led2 = 5;
//int ledSensor = 16;

  
void setup(void){
  
  webPage +="<meta http-equiv='refresh' content='3'><title>ESP8266 Demo</title>\n";
  webPage += "<style>body{ background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>\n";
  webPage +="<button onclick='myFunction()'>RELOAD</button>";
  webPage +="<script>function myFunction() {location.reload();}</script>";
  webPage +="<h1>ESP8266 Remote control</h1><p>LED #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>\n";
  webPage += "<p>LED #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>\n";
  
  // preparing GPIOs
  pinMode(led0, OUTPUT);
  digitalWrite(led0, LOW);
  /*
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(sensorPin, INPUT);
  pinMode(ledSensor, OUTPUT);
  */
  
  Serial.begin(9600);
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
    Serial.println(WiFi.status());
  }
  digitalWrite(led0, HIGH);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
 if (mdns.begin("esp8266", WiFi.localIP())) {
   Serial.println("MDNS responder started");
  }
    server.on("/", [](){
    server.send(200, "text/html", webPage);
    });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led0, HIGH);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led0, LOW);
  });
  /*
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led2, HIGH); 
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(led2, LOW);
  });
  */
    
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
  //String sentences ="<p>Flame is detected!!!</p>";
  if(WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led0, LOW);
    Serial.println("");
    Serial.print("Wifi is disconnected!");
    Serial.println("");
    Serial.print("Reconnecting");
    Serial.println("");
    //WiFi.begin(ssid,password);
    
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    digitalWrite(led0,HIGH);
  }
 /*
  if(digitalRead(sensorPin) ==LOW) 
  {
   Serial.print("Flame is detected");
   Serial.println("");
   webPage+=sentences;
   digitalWrite(ledSensor,HIGH);
   delay(300);
   
  }
  else                            //if no detect
  {
   digitalWrite(ledSensor,LOW);
  }
  */

} 
