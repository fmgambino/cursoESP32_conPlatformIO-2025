#include <Arduino.h>
#include <WiFiManager.h> // Libreria para la Gestión de Redes WiFi
#include <WiFi.h>      // Libreria del Framework Arduino para ESP32

// ====== DESCOMENTA SOLO PARA FORZAR RESETEO DEL PORTAL/AP (UNA VEZ) ======
//#define FORCE_WIFI_RESET
// ========================================================================

//Construye "ESP32-XXXXXX" donde "XXXXX" son los últimos 6 dígitos de la MAC
String buildDeviceIdFromMac() {
  String mac = WiFi.macAddress(); //Identifico la MAC: "AA:BB:CC:DD:EE:FF"
  mac.replace(":", "");
  String last6 = mac.substring(mac.length() - 6);
  last6.toUpperCase();
  return "ESP32-" + last6; // p.ej. "ESP32-DDEEFF"
}

void setup() {
  Serial.begin(115200);
  delay(300);

  //Modo STA (Station)
  WiFi.mode(WIFI_STA);

  //Crear ID  y fijartlo como hotname antes de conectar a la red
  String deviceId = buildDeviceIdFromMac();
  WiFi.setHostname(deviceId.c_str());

  // Iniciar WiFiManager
  WiFiManager wm;

#ifdef FORCE_WIFI_RESET
  // Forzar reseteo de credenciales WiFi (solo una vez)
  Serial.println("FORZANDO RESETEO DE CREDENCIALES WiFi...");
  wm.resetSettings(); //Borra las credenciales guardadas
  delay(2000);
  // (Opcional) también limpiar credenciales del SDK:
  // WiFi.disconnect(true, true);
  Serial.println("Credenciales borradas. Se abrirá un portal de configuración limpio.");
#endif

  // Nombre del portal de configuración (AP temporal)
  String apName = "Configura_" + deviceId; // p.ej. "Configura_ESP32-DDEEFF"

  Serial.println();
  Serial.println("=== Portal WiFiManager ===");
  Serial.print("Abriendo AP: "); Serial.println(apName);
  Serial.println("Conéctate a ese AP y elige tu WiFi...");

  // autoConnect: si hay credenciales guardadas intenta usarlas; sino abre portal
  bool ok = wm.autoConnect(apName.c_str()); // sin contraseña para el portal

  if (!ok) {
    Serial.println("No se pudo conectar. Reiniciando en 5 s...");
    delay(5000);
    ESP.restart(); // Reiniciar el Dispositivo ESP32
  } else {
    // Conectado correctamente
    Serial.println("\n¡Conectado correctamente a WiFi!");
    Serial.print("SSID: ");         Serial.println(WiFi.SSID());
    Serial.print("MAC: ");          Serial.println(WiFi.macAddress());
    Serial.print("ID del dispositivo: "); Serial.println(deviceId);
    Serial.print("IP asignada: ");  Serial.println(WiFi.localIP());
  }
} //Cerramos la funcion Setup o de Inicialización

void loop() {
  // Aquí iría el código principal del programa
  // Por ejemplo, leer sensores, controlar actuadores, etc.
}