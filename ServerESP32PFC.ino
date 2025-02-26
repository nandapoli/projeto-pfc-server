// Importação das bibliotecas necessárias
#include <WiFi.h> // Biblioteca para conexão Wi-Fi
#include <WebServer.h> // Biblioteca para criar o servidor HTTP

// Configuração da Rede Wi-Fi (Substitua pelos dados da sua rede)
const char* ssid = "ESP32";     // Nome do Wi-Fi (SSID)
const char* password = "1234567t"; // Senha do Wi-Fi

// Criação do servidor web na porta 80
WebServer server(80);

// Definição dos pinos dos botões correspondentes a cada dedo
const int polegarPin = 4;
const int indicadorPin = 5;
const int medioPin = 18;
const int anelarPin = 19;
const int mindinhoPin = 21;

// Função que retorna o estado dos dedos em formato JSON
String getFingerStates() {
  String json = "{";
  json += "\"Polegar\": " + String(!digitalRead(polegarPin)) + ",";
  json += "\"Indicador\": " + String(!digitalRead(indicadorPin)) + ",";
  json += "\"Médio\": " + String(!digitalRead(medioPin)) + ",";
  json += "\"Anelar\": " + String(!digitalRead(anelarPin)) + ",";
  json += "\"Mindinho\": " + String(!digitalRead(mindinhoPin));
  json += "}";
  return json;
}

// Função chamada quando a URL "/status" for acessada
void handleStatusRequest() {
  String json = getFingerStates(); // Obtém o estado dos dedos
  server.send(200, "application/json", json); // Envia resposta JSON
}

// Configuração inicial do ESP32
void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  WiFi.softAP(ssid, password); // Cria a rede Wi-Fi do ESP32
  Serial.println("Wi-Fi AP iniciado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.softAPIP()); // Exibe o IP do ESP32 na rede

  // Configura os botões como entrada com PULLUP interno
  pinMode(polegarPin, INPUT_PULLUP);
  pinMode(indicadorPin, INPUT_PULLUP);
  pinMode(medioPin, INPUT_PULLUP);
  pinMode(anelarPin, INPUT_PULLUP);
  pinMode(mindinhoPin, INPUT_PULLUP);

  // Configura a rota do servidor
  server.on("/status", handleStatusRequest);

  // Inicia o servidor HTTP
  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

// Loop principal do ESP32
void loop() {
  server.handleClient(); // Mantém o servidor rodando
}




