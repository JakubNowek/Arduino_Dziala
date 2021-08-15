#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

 
const char* ssid = "UPC279E7A2";
const char* password =  "6PajheTberkw";
 
const char * headerKeys[] = {"date", "server"} ;
const size_t numberOfHeaders = 2;
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
 
  Serial.println("Connected to WiFi Network");
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED)  {//Check WiFi connection status

 
    HTTPClient http;
    WiFiClient client;
 
    http.begin(client, "https://time.is"/*,"26:C8:E0:00:06:38:43:E4:EE:62:96:A3:45:8A:4F:A1:1E:A8:2F:B5"*/); 
 
    http.collectHeaders(headerKeys, numberOfHeaders);
 
    int httpCode = http.GET();
 
    if (httpCode > 0) {
 
      for(int i = 0; i< http.headers(); i++){
        Serial.println(http.header(i));
      }
 
      String headerDate = http.header("date");
      Serial.println(headerDate);                     
 
      String headerServer = http.header("server");
      Serial.println(headerServer); 
 
      Serial.println("--------------------");
 
    }else{
      Serial.println("An error occurred sending the request");
    }
 
    http.end();
 
  }
 
  delay(2000);
 
}
