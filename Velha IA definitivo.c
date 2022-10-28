#include <stdio.h>
#include <locale.h>
#include <stdio.h>

void apresentacao();
void tabuleiro();
void escolha_jogador();
void tabujog();
void jogada_bot_random();
void vitoria_derrota();

char nomejog[20], var[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',}, simbolo[2] = {'x', 'o'};
int todas[9], simbol = 0;
int jogada_hum, jogada_bot, random;
int a = 0, rodadas = 1, vitoria=0;//contadores

main(){
	setlocale(LC_ALL,"Portuguese");
	
	apresentacao();
	
	system("cls");	
	
	tabuleiro();
	
	do{

		escolha_jogador();
		
		var[jogada_hum - 1] = simbolo[simbol];
		todas[a] = jogada_hum;
		a++;//Contador para alocação de todas as jogadas feitas tanto humanas quanto do bot, o armazenamento vai para variável "todas"


		system("cls");
		
		tabuleiro();		
		tabujog();
		
		vitoria_derrota();
		
		simbol = 1;
		
		if(vitoria==1){
			rodadas++;
			break;
		}
		
		jogada_bot_random();
		
		var[random-1] = simbolo[simbol];
		todas[a] = jogada_bot;
		a++;//Contador para alocação de todas as jogadas feitas tanto humanas quanto do bot, o armazenamento vai para variável "todas"
		
		if(vitoria==1){
			break;
		}
				
		system("cls");
		
		tabuleiro();
		tabujog();

		vitoria_derrota();
		
		simbol = 0;
		
		rodadas++;		
		
	}while(rodadas<10);
	
	system("pause");
}

void apresentacao(){
	printf("Digite seu nome:\n");
	scanf("%s", &nomejog);
	
	printf("\n%s, você é o player 1, seu símbolo é o 'x'\n\n", nomejog);
	system("pause");
	printf("\nCada casa do tabuleiro é representada por um número, para jogar basta digitar o número referente à casa que você escolher.\n\n");
	system("pause");
}

void tabuleiro(){//função do tabuleiro de orientação para o jogador
	printf("     |     |     \n");
	printf("  7  |  8  |  9  \n");
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  4  |  5  |  6  \n");
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  1  |  2  |  3  \n");
	printf("     |     |     \n\n");
}

void escolha_jogador(){//Função da escolha do jogador humano

	do{	
		printf("%s, digite o número da casa que deseja jogar.\n", nomejog);
		scanf("%d", &jogada_hum);
		
		if(jogada_hum < 1 || jogada_hum > 9){
			
			printf("\nJogada inválida, escolha um número válido.\n");
			
		}else if(jogada_hum == todas[0] || jogada_hum == todas[1] || jogada_hum == todas[2] || jogada_hum == todas[3] || jogada_hum == todas[4] || jogada_hum == todas[5] || jogada_hum == todas[6] || jogada_hum == todas[7] || jogada_hum == todas[8]){
			printf("\nEssa casa já foi escolhida, selecione outra.\n");
		}
		
	}while(jogada_hum < 1 || jogada_hum > 9 || jogada_hum == todas[0] || jogada_hum == todas[1] || jogada_hum == todas[2] || jogada_hum == todas[3] || jogada_hum == todas[4] || jogada_hum == todas[5] || jogada_hum == todas[6] || jogada_hum == todas[7] || jogada_hum == todas[8]);
	
}

void tabujog(){	//Função tabuleiro com as jogadas dos jogadores
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", var[6], var[7], var[8]);
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", var[3], var[4], var[5]);
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", var[0], var[1], var[2]);
	printf("     |     |     \n\n");
}

void jogada_bot_random(){//Jogada aleatória do bot pra caso n haja uma jogada na memória
	do{				
	srand(time(NULL));
					
	random = (rand()%9);//escolha aleatória de jogada do bot
					
}while (random == todas[0] || random == todas[1] || random == todas[2] || random == todas[3] || random == todas[4] || random == todas[5] || random == todas[6] || random == todas[7] || random == todas[8]);
	jogada_bot = random;
}

void vitoria_derrota(){//Crítica de vitória caso algum jogador vença a partida				

	if((var[0] == simbolo[simbol]) && (var[1] == simbolo[simbol]) && (var[2] == simbolo[simbol])||(var[3] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[5] == simbolo[simbol])||(var[6] == simbolo[simbol]) && (var[7] == simbolo[simbol]) && (var[8] == simbolo[simbol])||(var[0] == simbolo[simbol]) && (var[3] == simbolo[simbol]) && (var[6] == simbolo[simbol])||(var[1] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[7] == simbolo[simbol])||(var[2] == simbolo[simbol]) && (var[5] == simbolo[simbol]) && (var[8] == simbolo[simbol])||(var[0] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[8] == simbolo[simbol])||(var[2] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[6] == simbolo[simbol])){							
	
		switch(simbol){
			case 0:
				printf("\n%s VENCEU O JOGO!\n\n", nomejog);
				break;
			case 1:
				printf("\nVOCÊ PERDEU O JOGO hahahaha!\n\n");				
				break;
				
			default:
				break;
		}
		vitoria++;
	}
}
