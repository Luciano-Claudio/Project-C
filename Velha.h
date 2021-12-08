#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void criarTab(int jogo[3][3]){
    int l,c;
    for(l=0;l<3;l++){
        for(c = 0; c < 3; c++){
            jogo[l][c]=0;
        }
    }
}

void tela(int jogo[3][3], int x, int y){
    int l,c;
    int i=1;
    printf("\n");
    for(l = 0; l < 3; l++){
        printf("\t\t");
        for(c = 0; c < 3; c++){
            if(l == x && c == y)
                printf("\033[47m");
            if(jogo[l][c] == 0)
                printf("   ");
            else if(jogo[l][c] == 1)
                printf("\033[34m O ");
            else
                printf("\033[31m X ");
                
            printf("\033[0m");
            if(c<2)
                printf("|");
        }

        printf("\t\t %d  %d  %d\n", i,i+1,i+2);
        i+=3;
        if(l<2)
            printf("\t\t--- --- ---");
        printf("\n");
    }
}


int checarVitoria(int jogo[3][3]){
    int l,c,soma;
    //checar se houve vitória por linha
    for(l=0;l<3;l++){
        soma = 0;
        for (c=0;c<3;c++)
            soma += jogo[l][c];
    
        if(soma == 3)
            return 0;
        else if(soma == -3)
            return 1;
    }
    //checar se houve vitória por coluna
    for(c=0 ; c<3 ; c++){
        soma = 0;
        for(l=0 ; l<3 ; l++)
            soma += jogo[l][c];

        if(soma==3)
            return 0;
        else if(soma==-3)
            return 1;
    }
    
    //checar se houve vitória pelas diagonais
    soma = 0;
    for(l=0 ; l<3 ; l++)
        soma += jogo[l][l];
    if(soma==3)
        return 0;
    else if(soma==-3)
        return 1;

    soma = jogo[0][2]+jogo[1][1]+jogo[2][0];
    if(soma==3)
        return 0;
    else if(soma==-3)
        return 1;

    return -1;
}
int casaLivre(int jogo[3][3], int *l, int *c){
    int i,j;
    for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(jogo[i][j] == 0){
                    *l=i;
                    *c=j;
                    return 1;
                }
            }
        }
    return 0;
}

int jogada(int jogo[3][3], int *jogador){
    char ch;
    int l,c;

    casaLivre(jogo, &l,&c);

    while(1){
        system("cls"); // cls windows clear linux
        jogo[l][c]=*jogador;
        tela(jogo,l, c);

        ch = getch();
        if(ch>=49 && 57>=ch){
            ch-=49;
            if(jogo[ch/3][ch%3]==0){
                jogo[l][c] = 0;
                l=ch/3;
                c=ch%3;
            }
        }
        else if(ch == 13)
            break;
            
    }
    *jogador*=-1;
}

int Velha(){

    int l, c, linha, coluna, jogador, ganhou, jogadas, opcao, turno;
    int jogo[3][3];
    criarTab(jogo);

    jogadas = 0;
    jogador = 1;


    do{ // repete até alguém ganhar ou jogadas < 9

        jogada(jogo,&jogador);

        jogadas++;
        ganhou = checarVitoria(jogo);

    }while(ganhou == -1 && jogadas < 9);

    // imprimir jogo
    system("cls"); // cls windows clear linux
    tela(jogo, 4, 4);

    if(ganhou == -1)
        printf("\nDeu VELHA! x_x\n");

    return ganhou;

}
    