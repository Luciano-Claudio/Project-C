#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "Dama.h"
#include "Velha.h"
#include "Forca.h"
#include "Highscore.h"


int menu(int x){
    char m[3][20] = { " Exit", " Highscore", " Novo jogo"};
    char n[4][20] = { " Voltar", " Jogo da Forca", " Jogo da Velha", " Dama"};
    char simbol[] = "->";
    int tam = x+2;
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
        }
        else if(ch == 80){
            if(seta>0)
                seta--;
            else
                seta=tam;
        }
        else if(ch == 13)
            break;
            
        if (x == 0){
            printf("\n\n \t\t\t    Menu:\n\n");
            for(i=tam;i>=0;i--){
                seta==i ? printf("\t\t\t%s", simbol):printf("\t\t\t");
                for(j=0;j<strlen(m[i]);j++){
                    printf("%c", m[i][j]);
                }
                printf("\n");
            }
        }
        else{
            printf("\n\n \t\t\t    Novo Jogo:\n\n");
            for(i=tam;i>=0;i--){
                seta==i ? printf("\t\t\t%s", simbol):printf("\t\t\t");
                for(j=0;j<strlen(n[i]);j++){
                    printf("%c", n[i][j]);
                }
                printf("\n");
            }
        }
        ch = getch();
    }while(1);
    return seta;
}

void Iniciar(int c){
    char player[2][20];
    int a;
    if(c == 1)
        Forca();
    else{
        system("cls"); // cls windows clear linux
        printf("\n\t\tDigite o Nome do Player um: ");
        scanf("%[ -Ý]", player[0]);
        while(getchar() != '\n');
        printf("\n\t\tDigite o Nome do Player dois: ");
        scanf("%[ -Ý]", player[1]);
        while(getchar() != '\n');

        system("cls"); // cls windows clear linux
        if(c == 2)
            a = Velha();
        else if(c == 3)
            a = Dama();
        if(a >= 0){
            printf("Parabéns %s",player[a]);
            AppendHighsocre(player[a],c);
        }
    }
    printf("\n\n \t Clique qualquer botão para voltar para o menu!\n\n");
    getch();
}


int main() {  
    int i,j;
    char x;
    setlocale(LC_ALL, "Portuguese"); 
    system("cls"); // cls windows clear linux
    char text[10][255] = {"\n\n \t\t    Trabalho de LDA e TDA", "\n\n \t\t\t Criado por:", "\n \t\t\t  Ana Luisa", "\n \t\t\t   Kildere", "\n \t\t\t   Luciano", "\n \t\t\t   Magdiel", "\n\n \t Clique qualquer botão para ir para o menu!\n\n",};
    printf("\n\n");
    for(i=0;i<7;i++){
        for(j = 0; j<strlen(text[i]); j++){
            printf("%c",text[i][j]);
            Sleep(30);
        }
    }
    
    getch();
    int command;
    do{
        command = menu(0);

        if(command == 1)
            Highscore();

        else if(command == 2){
            // novo jogo
            int c = menu(1);
            if(c!=0)
                Iniciar(c);
        }
        else 
            printf("\n\n \t\t\t    Até a próxima!\n\n");

    } while(command!=0);
  return 0;
}