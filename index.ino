#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "{wifi-ssid}";
const char* password = "{wifi-password}";

const char* cloudUrl = "{cloud-url}";
int segundos = 0;

const size_t CAPACITY = JSON_OBJECT_SIZE(5);
String payload;

int tensao = 220;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while ((WiFi.status() != WL_CONNECTED)) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("Conectado ao WiFi!");
  pinMode(2, OUTPUT);
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    if (segundos == 8) {
      digitalWrite(2, HIGH);

      HTTPClient http;

      http.begin(cloudUrl);
      http.addHeader("Content-Type", "application/json");

      StaticJsonDocument<CAPACITY> jsonDoc;
      JsonObject jsonPayload = jsonDoc.to<JsonObject>();

      int corrente = 1;

      jsonPayload["data"] = "2019-06-18T01:24:38.287Z";
      jsonPayload["corrente"] = corrente;
      jsonPayload["tensao"] = tensao;
      jsonPayload["potencia"] = corrente * tensao;
      jsonPayload["tempoArcoAberto"] = segundos;

      serializeJson(jsonDoc, payload);

      int responseStatusCode = http.POST(payload);

      Serial.println(responseStatusCode);
      http.end();
      payload = "";

      Serial.println("Fim da requisição ao servidor.");
      digitalWrite(2, LOW);
      segundos = 0;
    }

    segundos++;
    delay(1000);
  }
}
