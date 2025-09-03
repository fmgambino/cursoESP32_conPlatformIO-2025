#include <WiFi.h>

// Credenciales de tu red WiFi
const char* WIFI_SSID = "JUAREZ";
const char* WIFI_PASS = "CAROLINA342";

void setup() {
  Serial.begin(115200);
  delay(200);

  // Configurar ESP32 en modo estación
  WiFi.mode(WIFI_STA);

  // Iniciar conexión
  Serial.printf("Conectando a %s ...\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Esperar hasta conectarse
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Mostrar información
  Serial.println("\n¡Conectado Exitosamente a la Red WiFi:");
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("IP: ");   Serial.println(WiFi.localIP());
}

void loop() {
  // Aquí tu lógica de programa
}
