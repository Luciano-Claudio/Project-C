// Jogo da Forca.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printGame(int erros){
	char boneco[7] = {'O', '|', '/', '\\', '|', '/', '\\'};
	char print[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

	for(int i = 0; i < erros; i++){
		print[i] = boneco[i];
	}

	printf("\n\t____________");
	printf("\n\t||         |");
	printf("\n\t||         %c", print[0]);
	printf("\n\t||        %c%c%c", print[2], print[1], print[3]);
	printf("\n\t||         %c", print[4]);
	printf("\n\t||        %c %c", print[5], print[6]);
	printf("\n\t||");
	printf("\n\t||");
	printf("\n\t||");
}	

void cleanBuffer(){
    // Limpa Buffer
    while(getchar() != '\n');
}

void Forca(){
	
	int quant_erros = 0, letra_errada = 1, i;
	char palavra_secr[70], espacos[70], letra;
	
	
	printf("\n\n\tInforme a palavra secreta: ");
	scanf("%s", &palavra_secr); // Só capitura palavras sem espaço.
	cleanBuffer();
	printf("\n\tA palavra informada foi %s.\n\n\t", palavra_secr);
	
	/* Agora é necessário fazer a palavra secreta sumir da tela.
	No windows usar system("pause") e system("pause") e no Linux usar getch() e system(clear). Mas considerando também as IDEs web
	para funcionar em todos os casos, pode-se imprimir várias linhas em branco na tela
	até a palavra sair da visualização.*/

	system("cls");

	printf("\n\n\tA palavra informada tem %i letras.", strlen(palavra_secr));
	strcpy(espacos, palavra_secr);

	for(i = 0; i < strlen(espacos); i++){
		espacos[i] = '*';
	}

	while(1){
		system("cls");
		printGame(quant_erros);
		
		printf("\n\n\tA palavra é: %s.", espacos);
		printf("\n\n\tDigite uma letra: ");
		scanf(" %c",&letra);
		cleanBuffer();
		
		letra_errada = 1;

		for(i = 0; i < strlen(espacos); i++){
			if(letra == palavra_secr[i]){
				espacos[i] = letra;
				letra_errada = 0;
			}
		}

		if(letra_errada){
			quant_erros++;
		}

		if(strcmp(espacos, palavra_secr) == 0){
			printf("\n\n\tVocê advinhou! A palavra secreta é...    %s", &espacos);
			printf("\n\n\tVocê ganhou. Uhu!!!!!!!\n\n");
			break;
		}

		if(quant_erros == 7){
			system("cls");
			printGame(quant_erros);
			printf("\n\n\tTcururu... Você não advinhou! A palavra secreta era...    %s\n\n", &palavra_secr);
			break;
		}
	}

	//return 0;
}
