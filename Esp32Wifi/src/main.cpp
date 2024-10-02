#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Grupo Pimentelense SRL";         // Reemplaza con tu SSID
const char* password = "48575443C4E3B99E";        // Reemplaza con tu contraseña
const char* serverName = "https://siembraintegrator-dev.azurewebsites.net/api/example/post"; // Reemplaza con la URL de tu API

const int buttonPin = 0; // GPIO0 está conectado al botón BOOT

void setup() {
    Serial.begin(115200);
    
    // Configurar el pin del botón como entrada
    pinMode(buttonPin, INPUT_PULLUP);

    // Conectar a WiFi
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
    }
    
    Serial.println("Conectado a WiFi");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP()); // Mostrar la dirección IP
}

void loop() {
    // Verificar si el botón BOOT ha sido presionado
    if (digitalRead(buttonPin) == LOW) {
        // Realizar la solicitud POST
        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;

            // Crear los parámetros de consulta
            String value = "12"; // Cambia "100" por el valor que quieras enviar
            String fullURL = String(serverName) + "?value=" + value; // Construir la URL completa con parámetros

            http.begin(fullURL); // Iniciar la conexión
            Serial.println(fullURL);
            
            // Enviar la solicitud POST (con cadena vacía ya que usamos query params)
            int httpResponseCode = http.POST(""); 

            // Comprobar la respuesta
            if (httpResponseCode > 0) {
                String response = http.getString(); // Obtener la respuesta
                Serial.println(httpResponseCode); // Mostrar el código de respuesta
                Serial.println(response); // Mostrar la respuesta
            } else {
                Serial.print("Error en la solicitud POST: ");
                Serial.println(httpResponseCode); // Mostrar el error
            }
            http.end(); // Finalizar la conexión
        } else {
            Serial.println("Error en la conexión WiFi");
        }
        
        // Añadir un pequeño retraso para evitar múltiples registros de un solo toque
        delay(500);
    }

    delay(100); // Pequeño retraso para no saturar el ciclo loop
}
