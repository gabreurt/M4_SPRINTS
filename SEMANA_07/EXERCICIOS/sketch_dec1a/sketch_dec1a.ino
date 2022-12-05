// defino os leds
int led_azul = 4;
int led_vermelho = 5;
int led_amarelo = 6;
// bibliotecas de wifi
#include <WiFi.h>
#include <WebServer.h>

// SSID e senha
const char* ssid = "Redmi 9A";
const char* password = "gabrielgato";
// usando o server 80 porque é o padrão
WebServer server(80);

void O_WINNER(){ // função para acender o led vermelho quando o O ganhar 
  digitalWrite(led_vermelho, HIGH);
  server.send(200); 
  delay(1000);
  digitalWrite(led_vermelho, LOW);
}


void X_WINNER(){ // função para acender o led do azul quando o X ganhar 
  digitalWrite(led_azul, HIGH);
  server.send(200); 
  delay(1000);
  digitalWrite(led_azul, LOW);
}

void TIE(){ // função para O led amarelo acender quando empatar 
  digitalWrite(led_amarelo, HIGH);
  server.send(200); 
  delay(1000);
  digitalWrite(led_amarelo, LOW);
}

void setup() { 
  // declarando as saídas 
  Serial.begin(115200);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_vermelho, OUTPUT);

  // usando o esquema de wifi ensinado nas aulas anteriores
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
 // aqui irei descobrir através do Serial Monitor qual que é o IP Adress para colocar no script.js
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// crio as rotas
  server.on("/x_vencedor", X_WINNER);
  server.on("/o_vencedor", O_WINNER);
  server.on("/empate", TIE);
  server.begin(); 
}


void loop() {
  // a execução fica no loop
  server.handleClient();
}