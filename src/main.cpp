/*************************************************************************************************
 *  Created By: Tauseef Ahmad
 *  Created On: 3 April, 2023
 *  
 *  YouTube Video: https://youtu.be/VEN5kgjEuh8
 *  My Channel: https://www.youtube.com/channel/UCOXYfOHgu-C-UfGyDcu5sYw/
 *  
 *********************************************************************************************
 *  Preferences--> Aditional boards Manager URLs : 
 *  For ESP8266:
 *  http://arduino.esp8266.com/stable/package_esp8266com_index.json
 ***********************************************************************************************/

#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
WiFiClient client;
HTTPClient http;


String URL = "http://192.168.1.57/esp8266/test.php";

const char* ssid = "True Enjoy"; 
const char* password = "enjoy7777777777"; 

int temperature = 29; 
int humidity = 99;

void connectWiFi();

void setup() {
  Serial.begin(115200); 
  connectWiFi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) { 
    connectWiFi();
  }

  String postData = "temperature=" + String(temperature) + "&humidity=" + String(humidity); 

  HTTPClient http; 
  http.begin(client, URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
  
  int httpCode = http.POST(postData); 
  String payload = ""; // Initialize payload to an empty string
  
  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();  // Close connection
  
  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData); 
  Serial.print("httpCode: "); Serial.println(httpCode); 
  Serial.print("payload : "); Serial.println(payload); 
  Serial.println("--------------------------------------------------");
  
  delay(10000); // Wait for 10 seconds before sending the next data
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}
