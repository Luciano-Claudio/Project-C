#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int lin;
    int col;
    int tipo;
    int movimento[1][1];
}Peca;

void scanfC(char * carac){
    scanf(" %c", carac);

    // Limpa Buffer
    fflush(stdin); // no Windows 
    //__fpurge(stdin); // no Linux
}

int criarMapa(int mapa[10][10]){
    /*
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            mapa[i][j] = 0;
        }
    }

    mapa[3][6] = 1;
    mapa[1][8] = 1;
    mapa[3][8] = 1;
    mapa[4][5] = 2;

    return 0;
    */

    for(int l = 0; l < 10; l++){
        for(int c = 0; c < 10; c++){
            // Se casa n ocupavel
            if(l%2 == c%2){
                mapa[l][c] = 0;
            }else{
                // Pecas da:
                if(l < 4){ // Parte de cima
                    mapa[l][c] = 1;
                }else if(l > 5){ // Parte de baixo
                    mapa[l][c] = 2;
                }else{ // Parte do meio
                    mapa[l][c] = 0;
                }
            }
        }
    }
}

void printMapa(int mapa[10][10], Peca * peca_s){
    printf("__________________________________\n");
    printf("|                                |\n");
    for(int l = 0; l < 10; l++){
      printf("|");
      printf("    %2d ", l+1); // Nums da esquerda

      for(int c = 0; c < 10; c++){
          printf("|");
          int peca = mapa[l][c];

          if(peca == 0){
              printf("_");
          }else{
              // Se peca selecionada
              if(l == (*peca_s).lin && c == (*peca_s).col){
                  printf("\033[47m");
              }

              // Se cor vermelha/preta
              if(peca%2 == 1){
                  printf("\033[31m");
              }else{
                  printf("\033[34m");
              }
              if(peca < 3){
                  printf("P");
              }else{
                  printf("D");
              }
              
              printf("\033[0m");
          }
        }
        printf("|    |\n");
    }
    printf("|        a b c d e f g h i j     |\n");
    printf("|________________________________|\n\n");
}

int Acoes(int mapa[10][10], Peca * peca){
    int resp = 0;

    for(int i = 0; i < 1+(peca->tipo>2)*2; i+=2){
        for(int j = -1; j < 2; j += 2){
            //        (      direcao    ) * (inverte?)
            int dir = ((peca->tipo % 2)*2 - 1) * (1-i);

            int lin_d = peca->lin+dir;
            int col_d = peca->col+j;

            // Dentro do tabuleiro
            if((-1 < lin_d && lin_d < 10) && (-1 < col_d && col_d < 10)){
                int casaDPS = mapa[lin_d+dir][col_d+(j*2)];

                // Pode Comer
                printf("D: %d, PS: %d, CDPS: %d\n", mapa[lin_d][col_d]%2, peca->tipo%2, casaDPS);
                if(mapa[lin_d][col_d]%2 != peca->tipo%2 && casaDPS == 0){
                    return 2;
                }

                // Pode Mover
                if(mapa[lin_d][col_d] == 0){
                    resp = 1;
                }

            }
        }
    }

    // Sem Acoes
    return resp;
}

int escolherPeca(int mapa[10][10], Peca * peca, int * turno){
    char c;

    printf("Escolha a peca: exemp.: (7 d)\n");
    scanf(" %d", &peca->lin);
    scanfC(&c);

    // Limpa terminal
    // (linux  || windowns)
    system("clear || cls");

    printf("\n");

    // Dentro do tabuleiro
    if((0 < peca->lin && peca->lin < 11) && (('a'-1) < c && c < 'k')){
        peca->lin -= 1;
        peca->col = c - 97; // 97 = 'a'
        peca->tipo = mapa[peca->lin][peca->col];

        if(peca->tipo == 0){
            printf("Essa casa está vazia!\n");
        }else{
            // turno azul => impar | peca azul => par
            //turno verm. => par | peca verm. => impar
            if(*turno % 2 != peca->tipo % 2){ // se turno da peca
                if(Acoes(mapa, peca) == 0){
                    printf("Esta peca não pode ser movida!\n");
                }else{
                  return 1;
                }
            }else{
                printf("Não é o turno desta cor!\n");
            }
        }
    }else{
        printf("Posição invalida!\n");
    }

    return 0;
}

int escolherJogada(int mapa[10][10], Peca * peca, Peca * nPos, Peca * pC){
    char c;

    printf("Escolha destino da jogada: exemp.: (4 c)\n");
    scanf(" %d", &nPos->lin);
    scanfC(&c);

    // Limpa terminal
    // (linux  || windowns)
    system("clear || cls");
    printf("\n");
    // Dentro do tabuleiro
    if((0 < nPos->lin && nPos->lin < 11) && (('a'-1) < c && c < 'k')){
        nPos->lin -= 1;
        nPos->col = c - 97; // 97 = 'a'
        nPos->tipo = mapa[nPos->lin][nPos->col];

        if(nPos->tipo == 0){
            //       Casa Ocupável
            if(nPos->lin%2 != nPos->col%2){ 
                int dir = nPos->lin - peca->lin;
                int dist_l = abs(dir);
                dir /= dist_l;
                int dist_c = abs(peca->col - nPos->col);
                int dist = (dist_l+dist_c)/2;

                // Casa nas 2 diagonais  
                if(dist_l == dist_c){
                    if(peca->tipo < 3){
                        if(dist < 3){
                            int dir_certa = ((peca->tipo % 2)*2 - 1);

                            if(dist == 1){
                                if(dir == dir_certa){
                                    return 1;
                                }
                            }else{
                                pC->lin = (peca->lin + nPos->lin) / 2;
                                pC->col = (peca->col + nPos->col) / 2;
                                pC->tipo = mapa[pC->lin][pC->col];

                                if(pC->tipo != 0 && peca->tipo%2 != pC->tipo%2){
                                    return 2;
                                }
                            }
                        }
                    }else{
                        //Dama jogadas
                    }
                }
            }else{
                printf("Local inválido!\n");
                return 0;
            }
        }else{
            printf("Casa já ocupada!\n");
            return 0;
        }
    }else{
        printf("Posição invalida!\n");
        return 0;
    }

    printf("Jogada inválida!\n");
    return 0;
}

void Dama(){
    int mapa[10][10];
    Peca peca;
    Peca nPos;
    Peca pC;
    int turno = 1;
    char resp = 's';
    bool partida;
    bool comeu;
    int entrar;
    //turno%2 == 0 -> azul | turno%2 == 1 -> vermelha

    // JOGO
    while(resp == 's'){
        partida = 1;

        // Partida
        while(partida){
            //Criar mapa
            criarMapa(mapa);
            entrar = 1;
            
            //Escolher peça
            while(entrar == 1){
                peca.lin = 0;
                peca.col = 0;

                //Print mapa
                printMapa(mapa, &peca);

                entrar = !escolherPeca(mapa, &peca, &turno);        
            }

            entrar = 1;

            // Jogada        
            while(entrar){
                comeu = 0;

                // Escolher jogada
                while(entrar){
                    printMapa(mapa, &peca);

                    resp = escolherJogada(mapa, &peca , &nPos, &pC);
                    comeu = resp == 2;
                    entrar = resp == 0;
                }

                // Realizar Jogada

                mapa[peca.lin][peca.col] = 0;
                mapa[nPos.lin][nPos.col] = peca.tipo;
                peca = nPos;
                peca.tipo = mapa[peca.lin][peca.col];

                if(comeu){
                    mapa[pC.lin][pC.col] = 0;

                    if(Acoes(mapa, &nPos) == 2){
                        printMapa(mapa, &peca);
                        printf("\nRealizar nova captura? (s/n) ");
                        scanfC(&resp);
                        
                        if(resp == 's'){
                            entrar = 1;
                            //prox jogada tem que ser captura... fun()
                        }

                        // Limpa terminal
                        // (linux  || windowns)
                        system("clear || cls");                    
                    }
                }
            }

            //  Ver se tem mais...... mais oq?

            //Troca turno
            turno++;

            //Win check
            //  Varrer mapa
            //  ou
            //  Usar contador
        }

        printf("Jogar Novamente? (s/n) ");
        scanfC(&resp);
    }
}

int main() {  
    setlocale(LC_ALL, "Portuguese"); 
    char command = '1';
    while(command!='0') {
        printf("Menu:\n");
        printf("1. Novo jogo\n");
        printf("2. Highscore\n");
        
    }
    
    

  return 0;
}