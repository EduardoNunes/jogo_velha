#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define texto "Jogo da velha contra IA by Lakke:"

void tabuleiro();
void tabujog();
void armazenar();
void vd();
void empate();
void armazenarvitder();
void randomico();
void digito();

char var[9], tatimemo1[7], qualimemo1[4], humano[5], simbolo[2] = {'x' ,'o'};
int tatimemocon1, qualimemocon1, humanoconv, tatimemocon2, qualimemocon2, humanoconv2;
FILE *memoria;
int escolha, random = 10, escolhaquali = 0, escolhamemo = 0, qualidade = 0, somajog = 0, somabot = 0, multjog = 0;
int simbol, jogadas = 0, jogador[20], vitoria = 0, zero = 0;
int taticajog[5], taticaia[4], z = 0, todas[9];
int humanvet[5], botvet[4];

int main(void){
	setlocale(LC_ALL, "Portuguese");
	
	printf("%s\n\n", texto);	

	int x, y[5], s;	
	
			
	for (x=0; x<10; x++){
		var[x] = ' ';
		todas[x] = 99;
		taticaia[x] = 0;
	}
	x = 0;
	
/*	printf("Olá, eu sou Bug, uma IA que joga Jogo da velha:");
	getchar();
	printf("Cada partida que você jogar comigo eu irei aprender um pouco:");
	getchar();
	printf("Vou me esforçar para vencê-lo:\n");
	getchar();	
	printf("Me diga seu nome:\n");
	gets(jogador);
	fflush(stdin);
		
	printf("Certo, %s, vamos jogar.\n\n", jogador);
	getchar();
	system("cls");
	
	tabuleiro();
	
	printf("Este é o tabuleiro, cada número representa uma casa, \npara escolhar a casa que você quer jogar basta digitar \no número referente à essa casa.\n\n");
*/
while (jogadas<9){
	
	
	printf("Escolha uma casa:\n");//humano joga
	scanf("%d", &escolha);
	fflush(stdin);
		
	todas[x] = escolha;
	taticajog[z] = escolha;
	
	simbol = 0; //atribuindo 'x' para o jogador humano
	y[jogadas] = escolha - 1; // aloca a casa escolhida pelo humano em um vetor 
	var[y[jogadas]] = simbolo[simbol];//coloca 'x' na casa q o humano escolheu
	y[jogadas]++;//aqui é somado 1 pq o banco de dados n reconhece 0 à esquerda, então para evidar bugs não trabalharemos com zeros no momento da leitura das memórias da IA					

	tabuleiro();//chama o tabuleiro ensinando e o de baixo o tabuleiro com as posições q os jogadores escolheram
	tabujog();

	vd(); //chamando declaração de vitória ou derrota
				
	multjog = y[jogadas] + (somajog*10);
	somajog = multjog;
		
	if (vitoria == 1){//finalizar o jogo em caso da vitória do humano
		armazenarvitder();
		goto fim;
	}
	if (jogadas >= 4 && vitoria == 0){//finalizar o jogo em caso de terminar as jogadas sem vitória
		armazenarvitder();
		empate();
	goto fim;
	}		
		
		memoria = fopen ("memoriajv1", "r");		
		
			while (!feof(memoria)){				
				
				fgets(humano, 7, memoria);
				fgets(tatimemo1, 7, memoria);
				fgets(qualimemo1, 4, memoria);
				
				humanoconv = atoi (humano);
				tatimemocon1 = atoi (tatimemo1);
				qualimemocon1 = atoi (qualimemo1);
				
				digito();
				
				if (humanvet[jogadas] == todas[0] || tatimemocon1 == todas[1] || tatimemocon1 == todas[2] || tatimemocon1 == todas[3] || tatimemocon1 == todas[4] || tatimemocon1 == todas[5] || tatimemocon1 == todas[6] || tatimemocon1 == todas[7] || tatimemocon1 == todas[8]){
					continue;
				}
				
				if(qualimemocon1 >= 10){//Testando se a jogada do humano está salvo no banco de dados com alguma jogada para IA usar
					if (tatimemocon1 == todas[0] || tatimemocon1 == todas[1] || tatimemocon1 == todas[2] || tatimemocon1 == todas[3] || tatimemocon1 == todas[4] || tatimemocon1 == todas[5] || tatimemocon1 == todas[6] || tatimemocon1 == todas[7] || tatimemocon1 == todas[8]){
						continue;
					}else{
						escolhamemo = tatimemocon1;
						break;
					}
				}
				else if(qualimemocon1==0){
					continue;
				}
			}		
			
			fclose(memoria);
			
			simbol = 1;//troca de símbolo do 'x' para 'o'
			
			if (escolhamemo == 0){
				
				randomico();//escolhe uma jogada randomica para o BOT
							
				var[random] = simbolo[simbol];//atribuindo o símbolo 'o' para a escolha do bot
				escolhamemo = random + 1;			
			}			
	
			else {
				var[escolhamemo-1] = simbolo[simbol];
			}
			
			x++;
			todas[x] = escolhamemo;			
			taticaia[z] = escolhamemo;
			x++;
			
			tabuleiro();//chama o tabuleiro ensinando e o de baixo o tabuleiro com as posições q os jogadores escolheram
			tabujog();	
					
			vd();
			if (vitoria == 1){//finalizar o jogo em caso de vitória do bot	
				armazenarvitder();
				goto fim;
			}
			if (jogadas >= 4 && vitoria == 0){//finalizar o jogo em caso de terminar as jogadas sem vitória
				armazenarvitder();
				empate();
			goto fim;
			}
			
			somabot = (somabot * 10) + escolhamemo;
			escolhamemo = 0;
			z++;			
			jogadas++;//contagem de rodadas para finalização do jogo por contagens de jogadas
	}		
	
	fim:
	
	system("pause");
	
//	armazenar();
}

//Chamando a função tabuleiro de orientação
void tabuleiro(){
	printf("     |     |     \n");
	printf("  7  |  8  |  9  \n");
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  4  |  5  |  6  \n");
	printf("_____|_____|_____\n");
	printf("     |     |     \n");
	printf("  1  |  2  |  3  \n");
	printf("     |     |     \n\n\n");
}

void tabujog(){	//chamando a função tabuleiro com as jogadas
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

/*void armazenar(){//salvar as jogadas na memória permanente do bot	
	int a = 0;

	memoria = fopen ("memoriajv1", "a");
	
	for (a=0; a<z; a++){
		
		if (taticajog[a] != 0){
			fprintf(memoria, "%d", taticajog[a]);	
		}
		if (taticaia[a] != 0){
			fprintf(memoria, "%d", taticaia[a]);			
		}
	}
			fprintf(memoria, "%d\n", zero);
	
		fclose(memoria);
}*/

void armazenarvitder(){//salvar as jogadas na memória permanente do bot
	int a = 0;

	memoria = fopen ("memoriajv1", "a");
	
	if(simbol == 0){//se perder armazena as jogadas com a crítica 0 q quer dizer para n usar mais essa combinação
		for (a=0; a<z+1; a++){
			
			if (taticajog[a] != 0){
				fprintf(memoria, "%d", taticajog[a]);	
			}
		}
				fprintf(memoria, "\n", NULL);
				
		for (a=0; a<z+1; a++){
			if (taticaia[a] != 0){
				fprintf(memoria, "%d", taticaia[a]);
			}
		}
			fprintf(memoria, "\n%d\n", 0);
	}else{
		for (a=0; a<z+1; a++){
			
			if (taticajog[a] != 0){
				fprintf(memoria, "%d", taticajog[a]);	
			}
		}
				fprintf(memoria, "\n", NULL);
				
		for (a=0; a<z+1; a++){
			if (taticaia[a] != 0){
				fprintf(memoria, "%d", taticaia[a]);
			}
		}	
			fprintf(memoria, "\n%d\n", 10);
	}			
		fclose(memoria);
}

void vd(){
		//Crítica de vitória caso algum jogador vença a partida				
	if((var[0] == simbolo[simbol]) && (var[1] == simbolo[simbol]) && (var[2] == simbolo[simbol])||(var[3] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[5] == simbolo[simbol])||(var[6] == simbolo[simbol]) && (var[7] == simbolo[simbol]) && (var[8] == simbolo[simbol])||(var[0] == simbolo[simbol]) && (var[3] == simbolo[simbol]) && (var[6] == simbolo[simbol])||(var[1] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[7] == simbolo[simbol])||(var[2] == simbolo[simbol]) && (var[5] == simbolo[simbol]) && (var[8] == simbolo[simbol])||(var[0] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[8] == simbolo[simbol])||(var[2] == simbolo[simbol]) && (var[4] == simbolo[simbol]) && (var[6] == simbolo[simbol])){ 
		jogadas+=10;
		vitoria++;							
	
		switch(simbol){
			case 0:
				printf("\n%s VENCEU O JOGO!\n\n", jogador);		
				break;
			case 1:
				printf("\nVOCÊ PERDEU O JOGO hahahaha!\n\n");				
				break;
				
			default:
				break;
		}
	}
}

void empate(){
		printf("\nEMPATAMOS FINALMENTE ALGUÉM PÁREO PARA MIM!\n\n");
		
//		armazenar();
		
		jogadas+=10;
}

void randomico(){
	do{				
	srand(time(NULL));
					
	random = (rand()%9);//escolha aleatória de jogada dos bots
					
}while (random == todas[0] || random == todas[1] || random == todas[2] || random == todas[3] || random == todas[4] || random == todas[5] || random == todas[6] || random == todas[7] || random == todas[8]);
	escolhamemo = random;
}

void digito(){
	int a = 0, dighuman, digmemo;
	
	if(humanoconv >= 10000){
		dighuman = 5;
	}else if(humanoconv < 10000 && humanoconv >= 1000){
		dighuman = 4;
	}else if(humanoconv < 1000 && humanoconv >= 100){
		dighuman = 3;
	}else if(humanoconv < 100 && humanoconv >= 10){
		dighuman = 2;
	}else if(humanoconv < 10 && humanoconv >= 0){
		dighuman = 1;
	}
	
	if(tatimemocon1 >= 10000){
		digmemo = 5;
	}else if(tatimemocon1 < 10000 && tatimemocon1 >= 1000){
		digmemo = 4;
	}else if(tatimemocon1 < 1000 && tatimemocon1 >= 100){
		digmemo = 3;
	}else if(tatimemocon1 < 100 && tatimemocon1 >= 10){
		digmemo = 2;
	}else if(tatimemocon1 < 10 && tatimemocon1 >= 0){
		digmemo = 1;
	}
	
	for(a=0; a < dighuman; a++){
		humanvet[a] = humanoconv % 10;
		humanoconv = humanoconv/10;
	}
	for(a=0; a < digmemo; a++){
		botvet[a] = tatimemocon1 % 10;
		tatimemocon1 = tatimemocon1 / 10;
	}
	
		
}

