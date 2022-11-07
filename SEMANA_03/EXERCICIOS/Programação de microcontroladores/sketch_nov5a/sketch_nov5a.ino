// Professor, fiz o exercício com a ajuda do meu colega de quarto e turma Antonio Ribeiro.
// Além disso, gostaria de dizer que, meu código que funcionou no WOKWI não performou da mesma forma na IDE, por isso tive que fazer algumas mudanças.

#define led_vermelho 9
#define led_branco 8
#define led_azul 17
#define led_amarelo 15
#define botao_salvar 20
#define botao_ler 21
#define ldr 38
#define buzzer 4

int binario[4];
int frequencias[100];
int posicao = 0;

void setup() {

  // Serial.begin(115200);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_azul, OUTPUT);
  pinMode(led_branco, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(botao_salvar, INPUT_PULLUP);
  pinMode(botao_ler, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

}

void led_aceso(){
// Nesta função, dependendo do numero do binario, determinado led acende ou não.
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
      digitalWrite(led_amarelo, LOW);
    } else {
      digitalWrite(led_amarelo, HIGH);
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
// int freq_buzzer;

void loop() {
  // Estes códigos comentados são testes que eu fiz para verificar se todos os meus itens estavam funcionando.

  /* Serial.println(analogRead(ldr));
  // if (digitalRead(botao_salvar) == LOW){
  //   digitalWrite(led_azul, !digitalRead(led_azul));
  //   freq_buzzer = analogRead(ldr);
  //   tone(buzzer, freq_buzzer, 100);
  //   delay(100); // debounce (impede que o botão )
  //   while(digitalRead(botao_salvar) == LOW){}
  // }

  // if (digitalRead(botao_salvar == LOW)){
  //   digitalWrite(led_azul, LOW);
  //   digitalWrite(led_vermelho, LOW);
  //   digitalWrite(led_branco, LOW);
  //   digitalWrite(led_amarelo, LOW);
  //   delay(500);
  // }  
  //   if (digitalRead(botao_salvar == HIGH)){
  //   digitalWrite(led_azul, LOW);
  //   digitalWrite(led_vermelho, LOW);
  //   digitalWrite(led_branco, LOW);
  //   digitalWrite(led_amarelo, LOW);
  //   delay(500);
  */   

  // aqui, coloco o valor do ldr numa var
  int num_do_ldr = analogRead(ldr);
// divido por 257, que é o valor para leitura do LDR da placa
  int num_do_ldr_padronizado = num_do_ldr / 257;
  // transformo o decimal em binario
  dec_para_binario(num_do_ldr_padronizado);

// aqui coloco para quando o botao de gravar a nota for apertado tocar a nota, e quando o botao de tocar a musica for clicado, ele tocar todas as frequencias/notas.
  led_aceso();

   if (digitalRead(botao_salvar) == LOW) {

    frequencias[posicao] = num_do_ldr_padronizado;
    tone(buzzer, frequencias[posicao]*100, 350); 
    posicao += 1;
    delay(50);
    while(digitalRead(botao_salvar)== LOW){}
  }

  if (digitalRead(botao_ler) == LOW) {

    while (posicao >= 0) {
      tone(buzzer, frequencias[posicao]*100, 350);
      dec_para_binario(frequencias[posicao]);
      delay(500);
      led_aceso();

      Serial.println(frequencias[posicao]*100);
      Serial.println(num_do_ldr_padronizado);
    
      posicao = posicao-1;
    }
    while(digitalRead(botao_ler)== LOW){}
  }
  delay(50);
}