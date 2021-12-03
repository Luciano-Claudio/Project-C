#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int AppendHighsocre(char name[20], int jogo){

    FILE *pont_arq;
    int game_dama = 0, game_forca = 0;
    char str[50];
    char texto[255];
    strcpy(texto,"");
    
    pont_arq = fopen("arquivo.txt", "r");
    if (pont_arq != NULL){
        char txt[50],linha[50];
        char *pch, *t;
        while(fgets(txt, 50, pont_arq) != NULL){
            //printf("%s", txt);
            strcpy(linha,txt);
            pch = strtok(linha,",");
            int ret = strcmp(pch,name);
            
            if(ret == 0){
                t = strtok (NULL, ",\n");
                game_dama = atoi(t);
                t = strtok (NULL, ",\n");
                game_forca = atoi(t);
            }
            else
                strcat(texto,txt);

        }
        jogo == 1? game_dama++ : game_forca++;

        fclose(pont_arq);
    }
    //printf("%d",strlen(texto));
    char snum[5];
    
    strcpy(str,name);
    strcat(str,",");
    itoa(game_dama, snum, 10);
    strcat(str,snum);
    strcat(str,",");
    itoa(game_forca, snum, 10);
    strcat(str,snum);
    strcat(str,"\n");

    pont_arq = fopen("arquivo.txt", "w");

    if (pont_arq == NULL){
        printf("ERRO! O arquivo nÃ£o foi aberto!\n");
        return 1;
    }
    
    strcat(texto,str);

   // printf("%s", texto);
    fprintf(pont_arq, "%s", texto);
  
    fclose(pont_arq);
    return 0;

}

int Highscore(){

    FILE *pont_arq;
    char text[50];
    pont_arq = fopen("arquivo.txt", "r");
    char *pch;

    if (pont_arq == NULL){
        printf("ERRO! O arquivo nÃ£o foi aberto!\n");
        return 1;
    }
    
    system("cls"); // cls windows clear linux
    printf("\t\tVencedores\t|\tDama\t|  Jogo da Forca\n\n");
    while(fgets(text, 50, pont_arq) != NULL){
        pch = strtok (text,",");

        strlen(pch)<14?printf("\t\t%s ",pch):printf("\t     %s ",pch);

        while ((pch = strtok (NULL, ",\n")) != NULL)
            printf ("\t\t%s ",pch);

        printf("\n");
    }
    printf("\n\n \t Clique qualquer botão para voltar para o menu!\n\n");
    fclose(pont_arq);
    getch();
    return 0;
}
