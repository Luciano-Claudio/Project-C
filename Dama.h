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
    while(getchar() != '\n');
}

int criarMapa(int mapa[10][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            mapa[i][j] = 0;
        }
    }
    mapa[4][5] = 2;
    mapa[3][6] = 1;
    mapa[2][7] = 1;
    mapa[4][5] = 4;
    mapa[6][7] = 1;
    //mapa[3][8] = 1;
    //mapa[1][8] = 1;

    return 0;
    /*
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

void printMapa(int mapa[10][10], Peca * peca_s, int * turno){
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

    // Print Cor da vez
    printf("\t     ");
    *turno%2? printf("\033[34m( AZUIS )"):printf("\033[31m(VERMELHAS)");
    printf("\033[0m\n");
}

int Acoes(int mapa[10][10], Peca * peca){
    int resp = 0;

    for(int dirV = -1; dirV < 2; dirV += 2){
        for(int dirH = -1; dirH < 2; dirH += 2){
            //         (    direcao   ) * (inverte?)
            int dirC = (peca->tipo % 2) *   2 - 1;

            int lin_d = peca->lin+dirV;
            int col_d = peca->col+dirH;

            // Dentro do tabuleiro
            if((-1 < lin_d && lin_d < 10) && (-1 < col_d && col_d < 10)){
                int casaDPS = mapa[lin_d+dirV][col_d+dirH];

                // Pode Mover
                if(mapa[lin_d][col_d] == 0 && 
                  (peca->tipo > 2 || (peca->tipo < 3 && dirV == dirC))){
                        resp = 1;
                }

                // Pode Comer
                //Se Dama
                if(peca->tipo > 2){
                    //DamaMov();

                    while(lin_d > 0 && lin_d < 9 && col_d > 0 && col_d < 9){
                        casaDPS = mapa[lin_d+dirV][col_d+dirH];

                        if(mapa[lin_d][col_d] != 0){
                            if(mapa[lin_d][col_d]%2 == peca->tipo%2){
                                break;
                            }else if(casaDPS == 0){
                                return 2;
                            }
                        }

                        lin_d += dirV;
                        col_d += dirH;
                    }
                }else if(mapa[lin_d][col_d] != 0 && mapa[lin_d][col_d]%2 != peca->tipo%2 && casaDPS == 0){
                    return 2;
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
    system("cls");

    // Dentro do tabuleiro
    if((0 < peca->lin && peca->lin < 11) && (('a'-1) < c && c < 'k')){
        peca->lin -= 1;
        peca->col = c - 97; // 97 = 'a'
        peca->tipo = mapa[peca->lin][peca->col];

        if(peca->tipo == 0){
            printf("Essa casa está vazia!\n");
        }else{
            if(*turno % 2 != peca->tipo % 2){
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
        printf("Posição inválida!\n");
    }

    return 0;
}

int escolherJogada(int mapa[10][10], Peca * peca, Peca * nPos, Peca * pC){
    char c;

    printf("Escolha destino da jogada: exemp.: (4 c)\n");
    scanf(" %d", &nPos->lin);
    scanfC(&c);

    // Limpa terminal    
    system("cls");

    // Dentro do tabuleiro
    if((0 < nPos->lin && nPos->lin < 11) && (('a'-1) < c && c < 'k')){
        nPos->lin -= 1;
        nPos->col = c - 97; // 97 = 'a'
        nPos->tipo = mapa[nPos->lin][nPos->col];

        if(nPos->tipo == 0){
            //       Casa Ocupavel
            if(nPos->lin%2 != nPos->col%2){ 
                int dirV = nPos->lin - peca->lin;
                int dist_l = abs(dirV);
                dirV /= dist_l;
                
                // Tirar dirH?
                int dirH = nPos->col - peca->col;
                int dist_c = abs(dirH);
                dirH /= dist_c;

                int dist = (dist_l+dist_c)/2;

                // Casa nas 2 diagonais  
                if(dist_l == dist_c){
                    if(peca->tipo < 3){
                        if(dist < 3){
                            int dir_certa = ((peca->tipo % 2)*2 - 1);

                            if(dist == 1){
                                if(dirV == dir_certa){
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
                        // Dama jogadas
                        // Se da peca selecionada ate a pos destino tiver apenas uma peca e ela for enimiga
                        int lin_a = peca->lin+dirV;
                        int col_a = peca->col+dirH;
                        int casaDPS, peca_cam = 0;
    
                        while((lin_a != nPos->lin+dirV) || (peca_cam > 1)){
                            casaDPS = mapa[lin_a+dirV][col_a+dirH];

                            if(mapa[lin_a][col_a] != 0){
                                if(mapa[lin_a][col_a]%2 == peca->tipo%2){
                                    peca_cam = 2;
                                    break;
                                }else if(casaDPS == 0){
                                    peca_cam++;
                                    pC->lin = lin_a;
                                    pC->col = col_a;
                                }
                            }

                            lin_a += dirV;
                            col_a += dirH;
                        }

                        if(peca_cam < 2){ 
                            return peca_cam+1;
                        }
                    }
                }
            }else{
                printf("\nLocal inválido!\n");
                return 0;
            }
        }else{
            printf("\nCasa está ocupada!\n");
            return 0;
        }
    }else{
        printf("\nPosição inválida!\n");
        return 0;
    }

    printf("\nJogada inválida!\n");
    return 0;
}

bool varrerMapa(int mapa[10][10], int * turno){
    Peca peca;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            peca.lin = i;
            peca.col = j;
            peca.tipo = mapa[i][j];
            
            if(peca.tipo != 0 && peca.tipo%2 != *turno%2){
                if(Acoes(mapa, &peca) == 2){
                    return true;
                }
            }
        }
    }

    return false;
}

int Dama() {  
    Peca peca, nPos, pC;
    int mapa[10][10], turno, pecas[2], actions;
    char resp = 's';
    bool partida, comeu, entrar;

    //Criar mapa
    criarMapa(mapa);
    pecas[0] = pecas[1] = 20;
    partida = turno = 1;
    pecas[0] = 1;
    pecas[1] = 1;

    // Partida
    while(partida){
        entrar = true;
        actions;

        // Deve capturar
        bool dvCap = varrerMapa(mapa, &turno);
        
        // Escolher peça
        while(entrar){
            peca.lin = 0;
            peca.col = 0;

            // Print mapa
            printMapa(mapa, &peca, &turno);

            entrar = !escolherPeca(mapa, &peca, &turno); 
            actions = Acoes(mapa, &peca);

            if(dvCap && actions != 2){
                printf("Você deve capturar uma peça!\n");
                entrar = true;
            }        
        }

        entrar = true;
        comeu = 0;

        // Jogada        
        while(entrar){
            // Escolher jogada
            while(entrar){
                printMapa(mapa, &peca, &turno);

                resp = escolherJogada(mapa, &peca , &nPos, &pC);
                
                entrar = resp == 0;
                comeu = resp == 2;

                if((comeu || actions == 2) && resp == 1){
                    entrar = true;
                    printf("Você deve capturar uma peca!\n");
                }
            }

            // Realizar Jogada

            mapa[peca.lin][peca.col] = 0;

            peca.lin = nPos.lin;
            peca.col = nPos.col;

            // Fazer Dama 
            if(peca.lin%9==0 && peca.tipo < 3 && peca.tipo%2 == peca.lin/9){
                peca.tipo = (peca.tipo+2); 
            }
            
            mapa[peca.lin][peca.col] = peca.tipo;

            if(comeu){
                mapa[pC.lin][pC.col] = 0;
                pecas[!(turno%2)]--;
                entrar = Acoes(mapa, &peca) == 2;                   
            }
        }

        //Prox turno
        turno++;

        // PECA travada tbm ........... 
        // Win check
        partida = pecas[0] > 0 && pecas[1] > 0;
    }

    printf("\n\n\t\tAs peças ");
    turno%2? printf("\033[31mVERMELHAS\033[0m"):
                printf("\033[34mAZUIS\033[0m");
    printf(" venceram!\n");

    /*
    printf("As peças ");

    if(turno%2){ // mudar se tiver peca travada
        printf("vermelhas");
    }else{
        printf("azuis");
    }

    printf(" venceram!\n");
    */

    return turno%2;
}