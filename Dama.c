#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum cor{
  Branco,
  Preto
}cor;

typedef struct pos{
  int x;
  int y;
}pos;

struct jogador{
  enum cor Color;
};

void Iniciar(unsigned short int tab[10][10]){
  int i,j;
  for(i=0;i<10;i++){
       for(j=0;j<10;j++){
         if(j%2!=i%2 && i != 4 && i != 5){
           if(i<4){
             tab[i][j] = 1;
           }
           else if(i>5){
             tab[i][j] = 3;
           }
         }
         else{
           tab[i][j]=0;
         }
        }
      }
}

void Checar(unsigned short int tab[10][10], pos origem, int turno,   bool *is_Peca, char escolha[50]){
  char naoPeca[50] = "Não há peça nessa casa!\nEscolha novamente: ";
  char corErrada[50] = "Não é o turno dessa cor\nEscolha novamente: ";
  if(tab[origem.x][origem.y] != 0){
    if(turno%2 != 0 && tab[origem.x][origem.y] != 3 && tab[origem.x][origem.y] != 4){
      //Brancas (azul)
      strcpy(escolha,corErrada);
      *is_Peca = false;
    }
    else if(turno%2 == 0 && tab[origem.x][origem.y] != 1 && tab[origem.x][origem.y] != 2){
      //Pretas (vermelhas)
      strcpy(escolha,corErrada);
      *is_Peca = false;
    }
    else{
      *is_Peca = true;
    }
  }
  else{
    strcpy(escolha,naoPeca);
    *is_Peca = false;
  }
}

void Tela(unsigned short int tab[10][10], pos posicao, int turno){
    int i,j;
    char letra;
    printf("______________________________\n");
    printf("|                            |\n");
    for(i=0;i<10;i++){
      i == 9 ? printf("| %d ",i+1):printf("|  %d ",i+1);
      for(j=0;j<10;j++){
          printf("|");
          if(tab[i][j] == 1 || tab[i][j] == 3){
            letra = 'P';
          }
          else{
            letra = 'D';
          }
          if(posicao.x == i && posicao.y == j){
            printf("\033[47m");
          }
          if(tab[i][j] == 0){
              printf("_");
          }
          else if(tab[i][j] == 1 || tab[i][j] == 2){
            printf("\033[31m%c",letra); //pretas
          }
          else if(tab[i][j] == 3 || tab[i][j] == 4){
            printf("\033[34m%c", letra);//brancas
          }
            printf("\033[0m");
      }
      printf("|   |");
      printf("\n");
    }
    printf("|     1 2 3 4 5 6 7 8 9 10   |\n");
    printf("|____________________________|\n");
    if(turno%2!=0){
      printf("\nTurno das Brancas!");
    }else{
      printf("\nTurno das Pretas!");
    }
}




int main() {
  
    setlocale(LC_ALL, "Portuguese");
    pos origem, destino;
    origem.x = -1;
    char escolha[50] = "Escolha a peca: ";

    struct jogador player1, player2;
    player1.Color = Branco;
    player2.Color = Preto;

    unsigned short int tab[10][10];
    int turno = 1, pos1, pos2;
    bool partida = true, is_Peca = false;

     Iniciar(tab);

   // while(partida){

      Tela(tab,origem,turno);

      while(is_Peca == false){
        printf("\n%s",escolha);
        scanf(" %d %d", &origem.x,&origem.y);
        origem.x--;origem.y--;
        Checar(tab, origem, turno, &is_Peca, escolha);
      }
      //voltar atras na escolha
      system("clear");
      Tela(tab,origem,turno);
      printf("\nEscolha o destino: ");
      scanf(" %d %d", &destino.x,&destino.y);
      origem.x = -1;
      //turno++;
      //system("clear");
    //}
  return 0;
}
