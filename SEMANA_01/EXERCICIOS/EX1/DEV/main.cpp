// Ei prof, passando para avisar que fiz este exercicio em conjunto com meus amigos Gustavo Ferreira (Turma 1), Lyorrei Quintão (Turma 1), Henrique Lemos (Turma 1) e Lívia Bonotto (Turma 5). Nos ajudamos durante todo o processo, porém fizemos separados!
#include <iostream>
#include <string>

using namespace std;

/*
1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente entre dois valores mínimo e máximo e retorna esse valor
*/


int converteSensor(int medida, int min, int max){
  // aqui, quero pegar o valor medida e ver qual é o percentual dele entre o valor maximo e minimo
    medida = (medida - min) * 100;
    int delta = max - min; 
    int resultado = (medida / delta);
  return resultado;
}


// 2 - Faça uma função que simule a leitura de um sensor lendo o valor do teclado ao final a função retorna este valor

// na função leComando, peço para o usuário um valor atraves do cin e guardo na var resposta através do cout
int leComando(){
  int resposta;  
  cout << "Digite um valor:";
  cin >> resposta;
  return resposta;
}

// ----------------------------------------------------------

/*
3 - Faça uma função que armazena uma medida inteira qualquer em um vetor fornecido. Note que como C não possui vetores nativos da linguagem, lembre-se que você precisa passar o valor máximo do vetor assim como a última posição preenchida.
Evite também que, por acidente, um valor seja escrito em uma área de memória fora do vetor
// */

int insereVetor(int elemento, int valorMax, int lastPos, int* Vetor){
    // aqui, crio uma outra variavel chamada indice que nada mais é do que o próprio lastPos, apenas para uso livre
    int indice = lastPos;
   // verifico se o indice é menor que o valor maximo do vetor
    if (indice < valorMax) { 
      // coloco o elemento no indice indicado
		  Vetor[indice] = elemento;
	}
  indice = lastPos + 1;
  return indice;
}
// ----------------------------------------------------------

/*
4 - Faça duas funções que recebem um vetor com 4 posições que contém o valor da distância de um pequeno robô até cada um dos seus 4 lados.
A primeira função deve retornar a direção de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a segunda função deve retornar esta maior distância.
*/


char* dirMaiorDist(int *Vetor){
  // preciso declarar algum numero inicial para ser minha maior distancia, a fins de comparação durante o for
  int maiordist = Vetor[0];
  // depois, crio um vetor com os nomes de cada direção e a var "indiceDasDirecoes" que usarei como indice deste vetor no futuro.
  char *direcoes[4] = {(char *)"Direita", (char *)"Esquerda", (char *)"Frente",    (char *)"Tras"}; 
  int indiceDasDirecoes = 0;
  // fiz um for para comparar dentre todos os numeros do vetor qual é o maior e, colocar na variavel "maiordist". Além disso, coloco a var "indiceDasDirecoes" para receber o i, para eu saber exatamente qual o índice que foi o de maior distancia.
  for (int i = 0; i < 4; i++){
    if(Vetor[i] > maiordist){
      maiordist = Vetor[i];
      indiceDasDirecoes = i;
    } 
  }
  // assim, para retornar o nome da direcao de maior distancia, uso o indice encontrado no for
  return direcoes[indiceDasDirecoes];
}

// quase a mesma coisa que fiz acima
int maiorDist(int *Vetor){
  int maiordist = Vetor[0];
    for (int i = 0; i < 4; i++){
      if(Vetor[i] > maiordist){
      maiordist = Vetor[i];
    } 
  }
return maiordist;
}
// ----------------------------------------------------------

// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o mapeamento e retorna verdadeiro ou falso


int continuar(){
  // basicamente gurado a variavel de resposta do usuario na var "numero" e verifico se ele deseja parar ou não
  int numero;
  cout << "Digite 1 para parar o mapeamento!";
  cin >> numero;
  if (numero != 1){
    cout << "O mapeamento continua!";
    return 1;
  }
  else{
    cout << "Obrigado por mapear!";
    return 0;
  }
}


/* 6 - Escreva uma função que vai "dirigindo" virtualmente um robô e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda", "Frente", "Tras"). 
A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno para uma movimentação futura. 
Ele vai armazenando estas distancias em um vetor fornecido como parâmetro e retorna a ultima posicao preenchida do vetor.
Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado.
Para simular os sensores e os comandos de pare, use as funções já construídas nos ítens anteriores e em um looping contínuo até que um pedido de parada seja enviado pelo usuário.
A função final deve utilizar as funções declaradas acima para ler os sensores e o movimento do robô e no final percorrer o vetor e mostrar o movimento a cada direção na maior distância a cada movimento.
*/

// Defina as funções aqui

int dirige(int *v,int maxv){
  // declaro as variaveis dadas pelos parametros
	int maxVetor = maxv;
	int *vetorMov = v;
  // e as variaveis para a propria funcao dirige, a posAtualVetor que é como a lastPos e o dirigindo.  
	int posAtualVetor = 0;
	int dirigindo = 1;		
	while(dirigindo){		
    // aqui, faço um for para ele fazer com cada direção as seguintes funcoes: ler, converter em % e inserir o vetor
    for (int i = 0; i < 4; i++){
      int medida = leComando();
      medida = converteSensor(medida, 0, 830);
		  posAtualVetor = insereVetor(medida, maxVetor, posAtualVetor, vetorMov);
    }		
    // pergunto se o usuario deseja continuar
		dirigindo = continuar();		
	}
	return posAtualVetor;
}


// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado 
// na maior distância a cada movimento
void percorre(int *v,int tamPercorrido){		
	int *vetorMov = v;
	int maiorDir = 0;
	
	for(int i = 0; i< tamPercorrido; i+=4){
    // fala a direcao e o numero dela
		char *direcao = dirMaiorDist(&(vetorMov[i]));
    int maiordir = maiorDist(&(vetorMov[i]));
		printf("Movimentando para %s distancia = %i% \n",direcao,maiordir);
	}
}

int main(int argc, char** argv) {
	int maxVetor = 100;
	int vetorMov[maxVetor*4];
	int posAtualVet = 0;
	
	posAtualVet = dirige(vetorMov,maxVetor);
	percorre(vetorMov,posAtualVet);
	
	return 0;
}


