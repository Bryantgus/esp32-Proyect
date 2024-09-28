#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Grupo Pimentelense SRL";         // Reemplaza con tu SSID
const char* password = "48575443C4E3B99E"; // Reemplaza con tu contraseña
const char* serverName = "http://10.0.0.1:3000/make"; // Reemplaza con la URL de tu API

void setup() {
    Serial.begin(115200);
    
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
    // Realizar la solicitud POST
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(serverName); // Iniciar la conexión
        http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Establecer el tipo de contenido

        // Crear los datos a enviar
        String postData = "value=123"; // Cambia "123" por el valor que quieras enviar

        // Enviar la solicitud POST
        int httpResponseCode = http.POST(postData);
        
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

    delay(10000); // Esperar 10 segundos antes de repetir
}
