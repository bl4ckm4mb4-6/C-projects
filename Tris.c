#include<stdio.h>
#include<stdlib.h>

void griglia(char mat[][3]){
	unsigned i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			mat[i][j]='-';
		}
	}
}
void stampa(char mat[][3]){
	unsigned i,j;
    printf("\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%c\t",mat[i][j]);
		}
		printf("\n");
	}
}
void inserimento(char mat[][3],unsigned *t){
	unsigned i,j;
	if(*t==0){
		do{
			printf("\nScegli riga(da 1 a 3): ");
			scanf("%u",&i);
			printf("Scegli colonna(da 1 a 3): ");
			scanf("%u",&j);
		}while(mat[i-1][j-1]!='-');
		mat[i-1][j-1]='x';
		*t=1-*t;
	}
	else{
		do{
			printf("\nScegli riga(da 1 a 3): ");
			scanf("%u",&i);
			printf("Scegli colonna(da 1 a 3): ");
			scanf("%u",&j);
		}while(mat[i-1][j-1]!='-');
		mat[i-1][j-1]='o';
		*t=0;
	}
}
void verificaRighe(char mat[][3],unsigned *winX,unsigned *winO){
    unsigned i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(mat[i][j]=='x'){
                (*winX)++;
                if(*winX==3){
                    printf("\nX ha vinto!");
                    exit(0);
                }
            }
            else{
                if(mat[i][j]=='o'){
                    (*winO)++;
                    if(*winO==3){
                        printf("\nO ha vinto!");
                        exit(0);
                    }
                }
            }
        }
        *winX=0;
        *winO=0;
    }
    *winX=0;
    *winO=0;
}
void verificaColonne(char mat[][3],unsigned *winX,unsigned *winO){
    unsigned i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(mat[j][i]=='x'){
                (*winX)++;
                if(*winX==3){
                    printf("\nX ha vinto!");
                    exit(0);
                }
            }
            else{
                if(mat[j][i]=='o'){
                    (*winO)++;
                    if(*winO==3){
                        printf("\nO ha vinto!");
                        exit(0);
                    }
                }
            }
        }
        *winX=0;
        *winO=0;
    }
    *winX=0;
    *winO=0;
}
void verificaDiagonali(char mat[][3],unsigned *winX,unsigned *winO){
    unsigned i=0,j;
    for(j=0;j<3;j++){
        if(mat[i][j]=='x'){
            (*winX)++;
            if(*winX==3){
                printf("\nX ha vinto!");
                exit(0);
            }
        }
        else{
            if(mat[i][j]=='o'){
                (*winO)++;
                if(*winO==3){
                    printf("\nO ha vinto!");
                    exit(0);
                }
            }
        }
        i++;
    }
    *winX=0;
    *winO=0;
    if(mat[0][2]=='x' && mat[1][1]=='x' && mat[2][0]=='x'){
        printf("\nX ha vinto!");
        exit(0);
    }
    else{
        if(mat[0][2]=='o' && mat[1][1]=='o' && mat[2][0]=='o'){
            printf("\nO ha vinto!");
            exit(0);
        }
    }
    *winX=0;
    *winO=0;
}
void pareggio(char mat[][3]){
    unsigned i,j,celleOccupate=0;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(mat[i][j]!='-')
                celleOccupate++;
        }
    }
    if(celleOccupate==9){
        printf("\nPareggio!");
        exit(0);
   }
}

int main(){
	char mat[3][3];
	unsigned t=0,winX=0,winO=0;
	printf("Primo giocatore= x");
	printf("\nSecondo giocatore= o\n");
	griglia(mat);
	stampa(mat);
    while(winX!=3 && winO!=3){
        if(t==0)
            printf("\nTurno X\n");
        else
            printf("\nTurno O\n");
        inserimento(mat,&t);
	    stampa(mat);
        verificaRighe(mat,&winX,&winO);
        verificaColonne(mat,&winX,&winO);
        verificaDiagonali(mat,&winX,&winO);
        pareggio(mat);
    }
	return 0;  
}