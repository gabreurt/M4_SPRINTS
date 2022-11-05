#define led_vermelho 9
#define led_branco 8
#define led_azul 17
#define led_branco 15
#define botao_salvar 20
#define botao_ler 21
#define ldr 14
#define buzzer 4

int binario[4];
int armazenado[100];
int posicao = 0;

void setup() {

  Serial.begin(115200);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_branco, OUTPUT);
  pinMode(led_azul, OUTPUT);
  pinMode(led_branco, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(botao_salvar, INPUT_PULLUP);
  pinMode(botao_ler, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

}

void led_aceso(){
// nessa funcao, dependendo do numero do binario, determinado led acende ou nao
  if (binario[0] == 0) {
      digitalWrite(led_vermelho, LOW);
    } else {
      digitalWrite(led_vermelho, HIGH);
    }

    if (binario[1] == 0) {
      digitalWrite(led_branco, LOW);
    } else {
      digitalWrite(led_branco, HIGH);
    }

    if (binario[2] == 0) {
      digitalWrite(led_azul, LOW);
    } else {
      digitalWrite(led_azul, HIGH);
    }

    if (binario[3] == 0) {
      digitalWrite(led_branco, LOW);
    } else {
      digitalWrite(led_branco, HIGH);
    }
}

void dec_para_binario(int valor) {

  for (int i = 0; i <= 3; i++) {

    if (valor >= 1) {

      binario[i] = valor % 2;
      valor = valor / 2;

    } else {

      binario[i] = 0;

    }
  }
}

void loop() {

  int valor_LDR = analogRead(ldr);

  int valor_convertido = valor_LDR / 257;

  // 257 é o valor encontrado para leitura do LDR
  // especificamente na placa ESP32 usada nesse simulador

  dec_para_binario(valor_convertido);

  led_aceso();

   if (digitalRead(botao_salvar) == LOW) {

    armazenado[posicao] = valor_convertido;
    tone(buzzer, armazenado[posicao]*100, 350);
    
    posicao += 1;
    delay(50);

    while(digitalRead(botao_salvar)== LOW){}
  }

  if (digitalRead(botao_ler) == LOW) {

    while (posicao >= 0) {
      tone(buzzer, armazenado[posicao]*100, 350);
      dec_para_binario(armazenado[posicao]);
      delay(500);
      led_aceso();

      Serial.println(armazenado[posicao]*100);
      Serial.println(valor_convertido);
    
      posicao = posicao-1;
    }
    while(digitalRead(botao_ler)== LOW){}
  }
 
  
  
  Serial.println(valor_convertido);
  delay(500);
}