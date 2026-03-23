#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void inserimento(char parola_segreta[],unsigned *tent,unsigned *win,unsigned dim,char word[]){
	char sc,lettera,parola[20];
	unsigned i,flag=0;
	printf("\n------------------------------------\n");
	printf("Tentativi: %u\n",*tent);
	do{
		printf("Vuoi inserire una lettera(l) o una parola(p)? ");
		scanf(" %c",&sc);
	}while(sc!='l' && sc!='p');
	if(sc=='l'){
		printf("\nInserisci una lettera: ");
		scanf(" %c",&lettera);
		for(i=0;i<dim;i++){
			if(parola_segreta[i]==lettera){
				word[i]=lettera;
				flag=1;
			}
		}
		if(strcmp(parola_segreta,word)==0){
			printf("\nComplimenti hai vinto. La parola segreta era: %s",parola_segreta);
			*win=1;
		}
		else{
			for(i=0;i<dim;i++){
				printf(" %c  ",word[i]);
			}
		}
		if(flag==0){
			*tent-=1;
		}
		if(*tent==0){
			printf("\nHai perso. La parola segreta era: %s",parola_segreta);
		}
	}
	else{
		printf("\nInserisci la parola: ");
		scanf("%s",parola);
		if(strcmp(parola_segreta,parola)==0){
			printf("\nComplimenti hai vinto. La parola segreta era: %s",parola_segreta);
			*win=1;
		}
		else{
			if(*tent>0){
				for(i=0;i<dim;i++){
					printf(" %c  ",word[i]);
				}
				printf("\nHai sbagliato. Riprova");
				*tent-=1;
			}
			else{
				printf("\nHai perso. La parola segreta era: %s",parola_segreta);
			}
		}
	}
}
int main(){
	char parola_segreta[20];
	unsigned tent=8,win=0,dim,i;
	printf("Inserisci parola segreta: ");
	scanf("%s",parola_segreta);
    system("cls");
	dim=strlen(parola_segreta);
	char word[dim];
	for(i=0;i<dim;i++){
		word[i]='_';
	}
	while(tent>0 && win==0){
		inserimento(parola_segreta,&tent,&win,dim,word);
	}
	return 0;
}