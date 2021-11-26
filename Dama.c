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
             tab[i][j] = 2;
           }
           else if(i>5){
             tab[i][j] = 1;
           }
         }
         else{
           tab[i][j]=0;
         }
        }
      }
}

bool Checar(unsigned short int tab[10][10], pos origem, int turno, char escolha[50]){

  if(origem.x < 10 && origem.x >=0 && origem.y < 10 && origem.y >= 0){
    int peca = tab[origem.x][origem.y];
    if(peca != 0){
      if(turno%2 != 0 && peca%2 == 0){
        //Brancas (azul) peças brancas são impares e o turno também é impar
        strcpy(escolha,"Não é o turno dessa cor\nEscolha novamente: ");
      }
      else if(turno%2 == 0 && peca%2 != 0){
        //Pretas (vermelhas) peças brancas são pares e o turno também é par
        strcpy(escolha,"Não é o turno dessa cor\nEscolha novamente: ");
      }
      else{
        if(peca == 1){
          //peao branco
          if(tab[origem.x-1][origem.y-1] == 0 || tab[origem.x-1][origem.y+1] == 0 ){
            return true;
          }
          else if((tab[origem.x-1][origem.y-1] == 2 || tab[origem.x-1][origem.y+1] == 2 || tab[origem.x+1][origem.y-1] == 2 || tab[origem.x+1][origem.y+1] == 2) || (tab[origem.x-1][origem.y-1] == 4 || tab[origem.x-1][origem.y+1] == 4 || tab[origem.x+1][origem.y-1] == 4 || tab[origem.x+1][origem.y+1] == 4)){        
            return true;
          }
          else{
            strcpy(escolha,"Não há movimentos para essa peça\nEscolha novamente: ");
          }
        }
        else if(peca == 2){
          //peao preto
          if(tab[origem.x+1][origem.y-1] == 0 || tab[origem.x+1][origem.y+1] == 0){
            return true;
          }
          else if((tab[origem.x-1][origem.y-1] == 1 || tab[origem.x-1][origem.y+1] == 1 || tab[origem.x+1][origem.y-1] == 1 || tab[origem.x+1][origem.y+1] == 1) || (tab[origem.x-1][origem.y-1] == 2 || tab[origem.x-1][origem.y+1] == 2 || tab[origem.x+1][origem.y-1] == 2 || tab[origem.x+1][origem.y+1] == 2)){        
            return true;
          }
          else{
            strcpy(escolha,"Não há movimentos para essa peça\nEscolha novamente: ");
          }
        }
        // falta as damas
        else{
        }
      }
    }
    else{
      strcpy(escolha,"Não há peça nessa casa!\nEscolha novamente: ");
    }
  }
  else{
    strcpy(escolha,"Não há casa nessa posição\nEscolha novamente: ");
  }
  return false;
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
          if(tab[i][j] == 1 || tab[i][j] == 2){
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
          else if(tab[i][j] == 2 || tab[i][j] == 4){
            printf("\033[31m%c",letra); //pretas
          }
          else if(tab[i][j] == 1 || tab[i][j] == 3){
            printf("\033[34m%c", letra);//brancas
          }
            printf("\033[0m");
      }
      printf("|   |");
      printf("\n");
    }
    printf("|     a b c d e f g h i j    |\n");
    printf("|____________________________|\n");
    if(turno%2!=0){
      printf("\nTurno das Brancas!");
    }else{
      printf("\nTurno das Pretas!");
    }
}

//colocar no .h
void limparBuffer(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

int main() {
  
    setlocale(LC_ALL, "Portuguese");
    pos origem, destino;
    origem.x = -1;
    char letraTab;
    char escolha[50] = "Escolha a peca: ";

    struct jogador player1, player2;
    player1.Color = Branco;
    player2.Color = Preto;

    unsigned short int tab[10][10];
    int turno = 1, pos1, pos2;
    bool partida = true, podeMover = false;

     Iniciar(tab);

   // while(partida){

      Tela(tab,origem,turno);

      while(podeMover == false){
        printf("\n%s",escolha);
        scanf(" %d %c", &origem.x,&letraTab);
        origem.y = (int)letraTab;
        origem.x--;origem.y-=97;
        podeMover = Checar(tab, origem, turno, escolha);
        
        limparBuffer();
      }
      //voltar atras na escolha
      // colocar esses 2 numa função
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
