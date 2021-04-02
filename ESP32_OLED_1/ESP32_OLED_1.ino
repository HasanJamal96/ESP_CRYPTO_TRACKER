#include "WiFi.h"
#include "index.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <Adafruit_SSD1327.h>

#define LED 5
#define OLED_RESET -1
Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);

int httpcode = 0;
String value = "";
double price = 0;
double usd = 0;


String C1 = "";
String C2 = "";
String C3 = "";
String C4 = "";
String C5 = "";

double V1 = 0;
double V2 = 0;
double V3 = 0;
double V4 = 0;
double V5 = 0;

String SI = "";
String PA = "";
String currencies = "";
String vals = "";
int count = 0;

String html = MAIN_page;
bool start = false;
bool one = true;
String postBody = "";
String baseurl = "https://api1.binance.com/api/v3/ticker/price?symbol=";
                  
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

WebServer server(80);

DynamicJsonDocument doc(1024);


void access_point(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.setCursor(0,0);
  display.println("Setting ESP as AP");
  Serial.print("Setting soft access point mode");
  display.display();
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  display.setCursor(0,10);
  display.print("AP IP address: ");
  delay(10000);
  display.println(IP);
  Serial.println(IP);
  display.display();
}

void setup(){
  Serial.begin(115200);
  if ( ! display.begin(0x3D) ) {
     Serial.println("Unable to initialize OLED");
     while (1) yield();
  }
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  access_point();
  server.on("/",HTTP_GET, handle_OnConnect);
  server.on("/update",HTTP_POST, handle_OnUpdate);
  server.begin();
}


void ConnectToWiFi(char sid[], char pass[]){
  unsigned long start_time = millis()/1000;
  unsigned long current_time = millis()/1000;
  WiFi.mode(WIFI_STA);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1327_WHITE);
  display.setCursor(0,0);
  display.println("Connecting to WIFI");
  display.display();
  Serial.println("Connecting to WIFI");
  WiFi.begin(sid, pass);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    current_time = millis()/1000;
    delay(500);
    if ((++i % 16) == 0){
      display.setCursor(0,10);
      display.println("Still trying to Connect");
      display.display();
      Serial.println(F("Still Trying to Connect"));
    }
    if(current_time - start_time>10){
      display.setCursor(0,20);
      display.println("Unable to Connect");
      display.display();
      delay(2000);
      Serial.println("Unable to Connect");
      access_point();
      start = false;
      break;
    }
    if(WiFi.status() == WL_CONNECTED){
      display.setCursor(0,20);
      display.println("Connected to WIFI");
      display.display();
      delay(2000);
      Serial.print(F("Connected to WIFI"));
      start = true;
      one = true;
    }
  }
}

void handle_OnConnect() {
  server.send(200, "text/html", MAIN_page); 
}

void handle_OnUpdate() {
  postBody = server.arg("plain");
  deserializeJson(doc, postBody);
  JsonObject obj = doc.as<JsonObject>();

  SI = obj[String("ssid")].as<String>();
  PA = obj[String("pass")].as<String>();
  currencies = obj[String("currencies")].as<String>();
  vals = obj[String("vals")].as<String>();
  count = (obj[String("len")].as<String>()).toInt();
  char SS[SI.length()+1];
  char PAS[PA.length()+1];
  SI.toCharArray(SS, SI.length()+1);
  PA.toCharArray(PAS, PA.length()+1);
  ConnectToWiFi(SS,PAS);
  server.send(200);
}
void loop(){
  server.handleClient();
  if(start){
    if(one){
      String sap = "";
      if(SI != "null"){    
        int i=0;
        int k=0;
        for(int y=0; y<currencies.length(); y++){
          if(currencies[y] == ';'){
            switch(i){
              case 0:
                C1 = sap;
                break;
              case 1:
                C2 = sap;
                break;
              case 2:
                C3 = sap;
                break;
              case 3:
                C4 = sap;
                break;
              case 4:
                C5 = sap;
                break;
            }
            sap = "";
            i++;
          }
          else{
            sap = sap + currencies[y];
          }
        }
        for(int y=0; y<vals.length()+1; y++){
          
          if(vals[y] == ';'){
            switch(k){
              case 0:
                V1 = sap.toDouble();
                break;
              case 1:
                V2 = sap.toDouble();
                break;
              case 2:
                V3 = sap.toDouble();
                break;
              case 3:
                V4 = sap.toDouble();
                break;
              case 4:
                V5 = sap.toDouble();
                break;
            }
            sap = "";
            k++;
          }
          else{
            sap = sap + vals[y];
          }
        } 
      }
      one = false;
    }
    while(1){
      HTTPClient http;
      http.begin("https://blockchain.info/tobtc?currency=USD&value=1");
      httpcode = http.GET();
      if(httpcode == 200){
        value = http.getString();
        usd = 1/value.toDouble();
        if(C1 != ""){
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(SSD1327_WHITE);
          display.setCursor(0,0);
          display.println("Current Currency");
          display.setCursor(0,10);
          display.println(C1);
          Serial.print("Current Currency: ");
          Serial.println(String(C1));
          if(C1 != "BTC"){
            HTTPClient hC1;
            hC1.begin((baseurl+C1+"BTC"));
            httpcode = hC1.GET();
            if(httpcode == 200){
              value = hC1.getString();
              deserializeJson(doc, value);
              JsonObject obj = doc.as<JsonObject>();
              value = (obj["price"].as<String>());
              price = (value.toDouble())*usd;
            }
          }
          else
            price = usd;
          display.setCursor(0,20);
          display.println("Current Price");
          display.setCursor(0,30);
          display.println(String(price,8));
          display.setCursor(0,40);
          display.println("Set Price");
          display.setCursor(0,50);
          display.println(String(V1,8));
          display.display();
          
          Serial.print("Current Price: ");
          Serial.println(String(price,8));
          Serial.print("Set Price: ");
          Serial.println(String(V1,8));
          if(price>V1)
            digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);
          delay(2000); 
          }
          
          if(C2 != ""){
            HTTPClient hC2;
            hC2.begin((baseurl+C2+"BTC"));
            httpcode = hC2.GET();
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1327_WHITE);
            display.setCursor(0,0);
            display.println("Current Currency");
            display.setCursor(0,10);
            display.println(C2);
            Serial.print("Current Currency: ");
            Serial.println(String(C2));
            if(C2 != "BTC"){
              if(httpcode == 200){
                value = hC2.getString();
                deserializeJson(doc, value);
                JsonObject obj = doc.as<JsonObject>();
                value = (obj["price"].as<String>());
                price = (value.toDouble())*usd;
                }
            }
            else
              price = usd;
  
            display.setCursor(0,20);
            display.println("Current Price");
            display.setCursor(0,30);
            display.println(String(price,8));
            display.setCursor(0,40);
            display.println("Set Price");
            display.setCursor(0,50);
            Serial.println(String(V1,8));
            display.display();
          
            Serial.print("Current Price: ");
            Serial.println(String(price,8));
            Serial.print("Set Price: ");
            Serial.println(String(V2,8));
            if(price>V2)
              digitalWrite(LED, HIGH);
            else
              digitalWrite(LED, LOW);
            delay(2000);
          }
          
          if(C3 != ""){
            HTTPClient hC3;
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1327_WHITE);
            display.setCursor(0,0);
            display.println("Current Currency");
            display.setCursor(0,10);
            display.println(C3);
            Serial.print("Current Currency: ");
            Serial.println(String(C3));
            if(C4 != "BTC"){
              hC3.begin((baseurl+C3+"BTC"));
              httpcode = hC3.GET();
              if(httpcode == 200){
                value = hC3.getString();
                deserializeJson(doc, value);
                JsonObject obj = doc.as<JsonObject>();
                value = (obj["price"].as<String>());
                price = (value.toDouble())*usd;
              }
            }
            else
              price = usd;

            display.setCursor(0,20);
            display.println("Current Price");
            display.setCursor(0,30);
            display.println(String(price,8));
            display.setCursor(0,40);
            display.println("Set Price");
            display.setCursor(0,50);
            display.println(String(V3,8));
            display.display();
            
            Serial.print("Current Price: ");
            Serial.println(String(price,8));
            Serial.print("Set Price: ");
            Serial.println(String(V3,8));
            if(price>V3)
              digitalWrite(LED, HIGH);
            else
              digitalWrite(LED, LOW);
            delay(2000);
          }
  
          if(C4 != ""){
            HTTPClient hC4;
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1327_WHITE);
            display.setCursor(0,0);
            display.println("Current Currency");
            display.setCursor(0,10);
            display.println(C4);
            Serial.print("Current Currency: ");
            Serial.println(String(C4));
            if(C4 != "BTC"){
              hC4.begin((baseurl+C4+"BTC"));
              httpcode = hC4.GET();
              if(httpcode == 200){
                value = hC4.getString();
                deserializeJson(doc, value);
                JsonObject obj = doc.as<JsonObject>();
                value = (obj["price"].as<String>());
                price = (value.toDouble())*usd;
              }
            }
            else
              price = usd;
            display.setCursor(0,20);
            display.println("Current Price");
            display.setCursor(0,30);
            display.println(String(price,8));
            display.setCursor(0,40);
            display.println("Set Price");
            display.setCursor(0,50);
            display.println(String(V4,8));
            display.display();
              
            Serial.print("Current Price: ");
            Serial.println(String(price,8));
            Serial.print("Set Price: ");
            Serial.println(String(V4,8));
            if(price>V4)
              digitalWrite(LED, HIGH);
            else
              digitalWrite(LED, LOW);
            delay(2000);
          }
  
          if(C5 != ""){
            HTTPClient hC5;
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1327_WHITE);
            display.setCursor(0,0);
            display.println("Current Currency");
            display.setCursor(0,10);
            display.println(C4);
            Serial.print("Current Currency: ");
            Serial.println(String(C5));
            if(C5 != "BTC"){
              hC5.begin((baseurl+C5+"BTC"));
              httpcode = hC5.GET();
              if(httpcode == 200){
                value = hC5.getString();
                deserializeJson(doc, value);
                JsonObject obj = doc.as<JsonObject>();
                value = (obj["price"].as<String>());
                price = (value.toDouble())*usd;
              }
            }
            else
              price = usd;
            display.setCursor(0,20);
            display.println("Current Price");
            display.setCursor(0,30);
            display.println(String(price,8));
            display.setCursor(0,40);
            display.println("Set Price");
            display.setCursor(0,50);
            display.println(String(V5,8));
            display.display();
              
            Serial.print("Current Price: ");
            Serial.println(String(price,8));
            Serial.print("Set Price: ");
            Serial.println(String(V5,8));
            if(price>V5)
              digitalWrite(LED, HIGH);
            else
              digitalWrite(LED, LOW);
            delay(2000);
          }
        }
        delay(2000);
      }
    }
  }
