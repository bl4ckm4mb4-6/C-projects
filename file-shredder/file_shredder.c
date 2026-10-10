// File shredder
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

void shredder(char *, const long , const int );
long dimensione_file(FILE *);
char *path_cleaner(char *);  // Rimozione delle virgolette dal path

int main(){
	srand(time(NULL));
	char file_path[1024];
	
	// Inserimento path del file
	printf("Inserisci path del file da eliminare: ");
	fgets(file_path, sizeof(file_path), stdin);
	file_path[strcspn(file_path, "\n")] = '\0';  // sostituisce \n che inserisce fgets con \0
	char *new_file_path = path_cleaner(file_path);

	// Apertura file
	FILE *fp;
	fp = fopen(new_file_path, "rb+");
	if(fp == NULL){
		printf("Il file non esiste");
		return 1;
	}
	
	// Calcola la dimensione del file
    long dim = dimensione_file(fp);
    
    // Allocazione memoria del buffer di lettura
    char *buffer = malloc(dim);
    if(buffer == NULL){
    	printf("\nErrore nell'allocazione della memoria del buffer!");
    	fclose(fp);
    	return 1;
	}
	
    // Sovrascrittura utilizzando DoD 5220.22-M
    fread(buffer, sizeof(char), dim, fp);
    for(int i=0;i<3;i++){
    	fseek(fp, 0, SEEK_SET);
    	shredder(buffer, dim, i);
    	fwrite(buffer, sizeof(char), dim, fp);
    	fflush(fp);
	}
	
	printf("Shredding del file effettuato");
    fclose(fp);
    free(buffer);
    
    // Rimozione file
    printf("\nRimozione file in corso...");
    sleep(1);
    if(remove(new_file_path) == 0)
    	printf("\nFile eliminato!");
    else
    	printf("\nErrore durante l'eliminazione del file");
    
	return 0;
}

void shredder(char *buffer, const long dim, const int scelta){
	switch(scelta){
		case 0:
			memset(buffer, 0, dim);
			break;
		case 1:
			for(int j=0;j<dim;j++)
				buffer[j] = 0xFF;
			break;
		case 2:
			for(int j=0;j<dim;j++)
				buffer[j] = rand();
			break;
	}
}

long dimensione_file(FILE *file){
	fseek(file, 0, SEEK_END);
    long dim = ftell(file);
    fseek(file, 0, SEEK_SET);
    return dim;
}

char *path_cleaner(char *stringa){
	int j = 0;
	for(int i=0;stringa[i]!='\0';i++){
		if(stringa[i] != '\"')
			stringa[j++] = stringa[i];
	}
	stringa[j] = '\0';
	return stringa;
}