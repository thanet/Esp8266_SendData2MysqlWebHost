#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your network credentials
const char* ssid = "True Enjoy";
const char* password = "enjoy7777777777";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://netespdatalog00.free.nf/dbwrite.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.setTimeout(15000); // Increase timeout

    // Prepare your HTTP POST request data
    String httpRequestData = "sendval=" + String(10) + "&sendval2=" + String(189);

    // Initial request
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.print("Initial Response payload: ");
      Serial.println(payload);

      // Check if the response contains the expected JavaScript
      if (payload.indexOf("alert(\"Data sent successfully\")") != -1) {
        Serial.println("Data sent successfully.");
      } else {
        Serial.println("Failed to send data.");
      }
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(30000);
}
