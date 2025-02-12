#include <WiFi.h> // Biblioteca para uso do Wi-Fi
#include <WebServer.h> // Biblioteca para criar servidor web

// Configuração do WiFi
const char* ssid = "SSID"; // SSID do Wi-Fi local
const char* password = "Senha"; // Senha do Wi-Fi

// Definição dos pinos dos botões
const int botao1 = 4;
const int botao2 = 5;
const int botao3 = 18;
const int botao4 = 19;
const int botao5 = 21;

// Criando o servidor web na porta 80
WebServer server(80);

// Função para ler os contatos e enviar resposta em JSON
void handleDataRequest() {
    int estado1 = digitalRead(botao1);
    int estado2 = digitalRead(botao2);
    int estado3 = digitalRead(botao3);
    int estado4 = digitalRead(botao4);
    int estado5 = digitalRead(botao5);

    String jsonData = "{";
    jsonData += "\"botao1\": " + String(estado1) + ",";
    jsonData += "\"botao2\": " + String(estado2) + ",";
    jsonData += "\"botao3\": " + String(estado3) + ",";
    jsonData += "\"botao4\": " + String(estado4) + ",";
    jsonData += "\"botao5\": " + String(estado5);
    jsonData += "}";

    server.send(200, "application/json", jsonData);
}

void setup() {
    Serial.begin(115200); // Inicia a serial
    WiFi.begin(ssid, password); // Conecta ao Wi-Fi

    Serial.print("Conectando ao WiFi...");
    while (WiFi.status() != WL_CONNECTED) { // Aguarda conexão
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi conectado!");
    Serial.print("Endereço IP: "); // Informa o IP do ESP32
    Serial.println(WiFi.localIP());

    // Configurar pinos como entrada com pull-up
    pinMode(botao1, INPUT_PULLUP);
    pinMode(botao2, INPUT_PULLUP);
    pinMode(botao3, INPUT_PULLUP);
    pinMode(botao4, INPUT_PULLUP);
    pinMode(botao5, INPUT_PULLUP);

    // Definir a rota para obter os dados dos contatos
    server.on("/dados", handleDataRequest);

    // Iniciar o servidor
    server.begin();
}

void loop() {
    server.handleClient();
}


