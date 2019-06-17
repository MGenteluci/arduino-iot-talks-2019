#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MG";
const char* password = "Genteluci2!";

const char* cloudUrl = "http://ec2-35-172-193-18.compute-1.amazonaws.com/events";

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
    digitalWrite(2, HIGH);

    HTTPClient http;

    http.begin(cloudUrl);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"data\":\"2019-06-17T01:24:38.287Z\",\"corrente\":8,\"tensao\":110,\"potencia\":880,\"tempoArcoAberto\":15}";
    int responseStatusCode = http.POST(payload);

    http.end();

    Serial.println("Fim da requisição ao servidor.");
    digitalWrite(2, LOW);
    delay(15000);
  }
}
