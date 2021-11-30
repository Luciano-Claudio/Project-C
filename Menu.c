#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
//#include "Dama.h"

int menu(){
    char m[3][20] = { " Exit", " Highscore", " Novo jogo"};
    char simbol[] = "->";
    int tam = 2;
    int seta = tam;
    char ch = 1;
    int i,j;

    do{
        system("cls"); // cls windows clear linux

        if(ch == 72){
            if(seta<tam)
                seta++;
            else
                seta=0;
            //seta > 0 ? seta-- : seta=tam;
        }
        else if(ch == 80){
            if(seta>0)
                seta--;
            else
                seta=tam;
            //seta < tam ? seta++ : seta=0;
        }
        else if(ch == 13){
            printf("\n\n \t\t\t    Até a próxima!\n\n");
            break;
        }

        printf("\n\n \t\t\t    Menu:\n\n");
        for(i=tam;i>=0;i--){
            seta==i ? printf("\t\t\t%s", simbol):printf("\t\t\t");
            for(j=0;j<strlen(m[i]);j++){
                printf("%c", m[i][j]);
            }
            printf("\n");
        }
        ch = getch();
    }while(1);
    return seta;
}

int main() {  
    int i,j;
    char x;
    setlocale(LC_ALL, "Portuguese"); 
    system("cls"); // cls windows clear linux
    char text[10][255]=    {"\n\n \t\t    Trabalho de LDA e TDA", "\n\n \t\t\t Criado por:", "\n \t\t\t  Ana Luisa", "\n \t\t\t   Kildere", "\n \t\t\t   Luciano", "\n \t\t\t   Magdiel", "\n\n \t Clique qualquer botão para ir para o menu!\n\n",};
    printf("\n\n");
    for(i=0;i<7;i++){
        for(j = 0; j<strlen(text[i]); j++){
            printf("%c",text[i][j]);
            Sleep(30);
        }
    }
    
    getch();
    int command = 1;
    while(command!=0) {
        command = menu();
        switch (command)
        {
            case 0: break;

            case 1: printf("vc escolheu o valor = %d", command); break;

            case 2: printf("vc escolheu o valor = %d", command);  break;

            default: printf("Escolha inválida!"); break;
        }
    }
  return 0;
}