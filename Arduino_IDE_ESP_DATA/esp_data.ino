#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Sup";
const char* password = "12345678";
const char* serverUrl = "https://ecstacy.pythonanywhere.com/api/update-dht-data"; // Update with your local server URL

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  sendDhtDataToServer();
  delay(500); // Wait for 1 second before sending the next data
}

void sendDhtDataToServer() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    float temperature = random(30, 90); // Generate random temperature
  

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["temperature"] = temperature;
    

    String requestBody;
    serializeJson(jsonDoc, requestBody);

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode == 200) {
      Serial.println(temperature);
      Serial.println("Data sent successfully to the server.");
    } else {
      Serial.print("Failed to send data to the server. Status code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}