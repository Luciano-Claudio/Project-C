#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "Dama.h"

int main() {  
    int i,j;
    setlocale(LC_ALL, "Portuguese"); 
    system("clear || cls");
    char text[10][255]=    {"\n\n \t\t\t    Dama", "\n\n \t\t\t Criado por:", "\n \t\t\t  Ana Luisa", "\n \t\t\t   Kildere", "\n \t\t\t   Luciano", "\n \t\t\t   Magdiel", "\n\n \t Clique qualquer botão para ir para o menu!\n\n",};
    printf("\n\n");
    for(i=0;i<7;i++){
        for(j = 0; j<strlen(text[i]); j++){
            printf("%c",text[i][j]);
            Sleep(100);
        }
    }
    
    _getch();
    system("clear || cls");
    char command = '1';
    while(command!='0') {
        printf("\n\n \t\t\t    Menu:\n\n");
        printf("\t\t\t1. Novo jogo\n");
        printf("\t\t\t2. Highscore\n");
        printf("\t\t\t0. Exit\n");
        printf("\n\n \t\t\tEscolha: 0,1,2? ");
        command= getchar();
        while(getchar() != '\n');

        switch (command)
        {
        case '0': break;

        case '1': /*chamar a função do jogo*/ break;

        case '2': /*chamar função de arquivo*/  break;

        default: printf("Escolha inválida!"); break;
        }
        
    }
    
    

  return 0;
}