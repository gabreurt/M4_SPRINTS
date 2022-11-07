// // Professor, fiz o exercício com a ajuda do meu colega de quarto e turma Antonio Ribeiro.
#define led_verde 25
#define led_vermelho 12
#define led_amarelo 26
#define led_roxo 27
#define botao_gravar 32
#define botao_musica 33
#define ldr 14
#define buzzer 5

int binario[4];
int frequencias[100];
int x = 0;

void setup() {

  Serial.begin(115200);
  pinMode(led_verde, OUTPUT);
  pinMode(led_roxo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(botao_gravar, INPUT_PULLUP);
  pinMode(botao_musica, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

}

void led_aceso(){
// Nesta função, dependendo do numero do binario, determinado led acende ou não.
  if (binario[0] == 0) {
      digitalWrite(led_amarelo, LOW);
    } else {
      digitalWrite(led_amarelo, HIGH);
    }

    if (binario[1] == 0) {
      digitalWrite(led_vermelho, LOW);
    } else {
      digitalWrite(led_vermelho, HIGH);
    }

    if (binario[2] == 0) {
      digitalWrite(led_roxo, LOW);
    } else {
      digitalWrite(led_roxo, HIGH);
    }

    if (binario[3] == 0) {
      digitalWrite(led_verde, LOW);
    } else {
      digitalWrite(led_verde, HIGH);
    }
}

void dec_para_binario(int valor) {
 // transformo decimais para binário usando a estratégia de dividir por 2 e pegar o resto
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
// aqui, coloco o valor do ldr numa var
  int num_do_ldr = analogRead(ldr);
// divido por 257, que é o valor para leitura do LDR da placa
  int num_do_ldr_padronizado = num_do_ldr / 257;
  // transformo o decimal em binario
  dec_para_binario(num_do_ldr_padronizado);

// aqui coloco para quando o botao de gravar a nota for apertado tocar a nota, e quando o botao de tocar a musica for clicado, ele tocar todas as frequencias/notas.
  led_aceso();

  if (digitalRead(botao_gravar) == LOW) {

    frequencias[x] = num_do_ldr_padronizado;
    tone(buzzer, frequencias[x]*100, 350);
    Serial.println(frequencias[x]);
    x += 1;
    delay(50);
  }

  if (digitalRead(botao_musica) == LOW) {

    while (x >= 0) {
      tone(buzzer, frequencias[x]*100, 350);
      dec_para_binario(frequencias[x]);
      delay(500);
      led_aceso();

      Serial.println(frequencias[x]*100);

      x = x-1;
    }
  }
  delay(50);
}