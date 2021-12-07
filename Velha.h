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
        for(c = 0; c < 3; c++){
            if(l == x && c == y)
                printf("\033[47m");
            if(jogo[l][c] == 0)
                printf(" %d ",i);
            else if(jogo[l][c] == 1)
                printf("\033[34m O ");
            else
                printf("\033[31m X ");
                
            printf("\033[0m");
            if(c<2)
                printf("|");
            i++;
        }
        printf("   \n");
        if(l<2)
            printf("___ ___ ___\n");
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
        if(soma == -3)
            return 1;
    }
    //checar se houve vitória por coluna
    for(c=0 ; c<3 ; c++){
        soma = 0;
        for(l=0 ; l<3 ; l++)
            soma += jogo[l][c];

        if(soma==3)
            return 0;
        if(soma==-3)
            return 1;
    }
    
    //checar se houve vitória pelas diagonais
    soma = 0;
    for(l=0 ; l<3 ; l++)
        soma += jogo[l][l];
    if(soma==3)
        return 0;
    if(soma==-3)
        return 1;

    soma = jogo[0][2]+jogo[1][1]+jogo[2][0];
    if(soma==3)
        return 0;
    if(soma==-3)
        return 1;

    return -1;
}
int casaLivre(int jogo[3][3], int vet[2]){
    int l,c;
    for(l=0;l<3;l++){
            for(c=0;c<3;c++){
                if(jogo[l][c] == 0){
                    vet[0] = l;
                    vet[1] = c;
                    return 1;
                }
            }
        }
    return 0;
}

int jogada(int jogo[3][3], int *jogador){
    char ch;
    int vet[2];
    int l,c;

    casaLivre(jogo, vet);
    l = vet[0], c = vet[1];

    while(1){
        system("cls"); // cls windows clear linux
        jogo[l][c]=*jogador;
        tela(jogo,l, c);

        ch = getch();
        
        if(ch == 49 && jogo[0][0] == 0){// tecla 1
            jogo[l][c]=0;
            l=0;c=0;
        }  
            
        else if(ch == 50 && jogo[0][1] == 0){// tecla 2
            jogo[l][c]=0;
            l=0;c=1;
        }  
            
        else if(ch == 51 && jogo[0][2] == 0){// tecla 3
            jogo[l][c]=0;
            l=0;c=2;
        }  
            
        else if(ch == 52 && jogo[1][0] == 0){// tecla 4
            jogo[l][c]=0;
            l=1;c=0;
        }  
            
        else if(ch == 53 && jogo[1][1] == 0){// tecla 5
            jogo[l][c]=0;
            l=1;c=1;
        }  
            
        else if(ch == 54 && jogo[1][2] == 0){// tecla 6
            jogo[l][c]=0;
            l=1;c=2;
        }  
            
        else if(ch == 55 && jogo[2][0] == 0){ // tecla 7
            jogo[l][c]=0;
            l=2;c=0;
        } 
            
        else if(ch == 56 && jogo[2][1] == 0){// tecla 8
            jogo[l][c]=0;
            l=2;c=1;
        }  
            
        else if(ch == 57 && jogo[2][2] == 0){// tecla 
            jogo[l][c]=0;
            l=2;c=2;
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
    // imprime tabuleiro do jogo
    tela(jogo, 4, 4);

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
    