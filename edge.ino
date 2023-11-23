#define TRIGGER_PIN 21 // Pino de trigger do sensor ultrassônico
#define ECHO_PIN 22    // Pino de echo do sensor ultrassônico
#define TAMANHO_MEDICAMENTO 0.5 // Tamanho de cada unidade de medicamento em centímetros
#define DISTANCIA_CHEIO 40 // Distância que consideramos o estoque cheio (em centímetros)
#define DISTANCIA_VAZIO 20 // Distância que consideramos o estoque vazio (em centímetros)
#include "ArduinoJson.h"
#include "EspMQTTClient.h"


EspMQTTClient client{
  "Wokwi-GUEST", //SSID do WiFi
  "",     // Senha do wifi
  "mqtt.tago.io",  // Endereço do servidor
  "Default",       // Usuario
  "4cead135-205d-474d-a6ad-11850b5c5bb3",         // Token do device
  "Global solution",           // Nome do device
  1883             // Porta de comunicação
};

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Conectando WiFi");
  while (!client.isWifiConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
  }
  Serial.println("WiFi Conectado");
  Serial.println("Conectando com Servidor MQTT");
  while (!client.isMqttConnected()) {
    Serial.print('.'); client.loop(); delay(1000);
  }
  Serial.println("MQTT Conectado");
}
void onConnectionEstablished() {}

char bufferJson[100];
int medicamentos = 0;

void loop() {
  long duration, distance;

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0343) / 2; // Converte o tempo para distância em centímetros

  int quantidadeMedicamentos = distance / TAMANHO_MEDICAMENTO; // Calcula a quantidade de medicamentos

  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.print(" cm | Quantidade de medicamentos: ");
  Serial.println(quantidadeMedicamentos);

  if (distance > DISTANCIA_CHEIO) {
    Serial.println("Estoque cheio");
  } else if (distance > DISTANCIA_VAZIO) {
    Serial.println("Estoque intermediário");
  } else {
    Serial.println("Estoque vazio");
  }

  delay(1000); // Aguarda 1 segundo antes de realizar a próxima leitura
 
  StaticJsonDocument<300> documentoJson;
  documentoJson["variable"] = "medicamentos";
  documentoJson["value"] = quantidadeMedicamentos;
  serializeJson(documentoJson, bufferJson);
  Serial.println(bufferJson);
  client.publish("topico", bufferJson);
  delay(5000);
  client.loop();
}
