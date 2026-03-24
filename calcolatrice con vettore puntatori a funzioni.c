// Calcolatrice con vettore di puntatori a funzioni
#include<stdio.h>
#include<stdlib.h>  // Libreria per funzioni: system("cls") e system("pause")
#include<unistd.h>  // Libreria per la funzione sleep(unsigned int seconds)
#include<float.h>  // Libreria per il valore minimo dei float per gestire divisione per zero
#include<math.h>

int menu(void);
void inserisci(float *, float *, char *);
// Siccome sono funzioni dove si calcola un nuovo valore, meglio assicurarci che i numeri inseriti non vengano modificati
float somma(const float, const float);
float differenza(const float, const float);
float prodotto(const float, const float);
float divisione(const float, const float);
float potenza(const float, const float);

int main(){
    // array di puntatori a funzioni
    float (*operazione[5])(const float, const float) = {somma,differenza,prodotto,divisione,potenza};
    int op;
    float num1, num2;
    // array di puntatori a char
    char *messaggi[5];
    messaggi[0] = (char *) "Inserisci addendi: ";
    messaggi[1] = (char *) "Inserisci sottraendo e minuendo: ";
    messaggi[2] = (char *) "Inserisci fattori: ";
    messaggi[3] = (char *) "Inserisci dividendo e divisore: ";
    messaggi[4] = (char *) "Inserisci base e esponente: ";
    // gestione del flusso e del menu
    do{
        op = menu();
        switch(op){
            // somma
            case 1:
                inserisci(&num1,&num2,messaggi[op-1]);
                float somma = (*operazione[op-1])(num1,num2);
                printf("\n%.2f + %.2f = %.2f\n", num1,num2,somma);
                break;
            // differenza
            case 2:
                inserisci(&num1,&num2,messaggi[op-1]);
                float differenza = (*operazione[op-1])(num1,num2);
                printf("\n%.2f - %.2f = %.2f\n", num1,num2,differenza);
                break;
            // prodotto
            case 3:
                inserisci(&num1,&num2,messaggi[op-1]);
                float prodotto = (*operazione[op-1])(num1,num2);
                printf("\n%.2f * %.2f = %.2f\n", num1,num2,prodotto);
                break;
            // divisione
            case 4:
                inserisci(&num1,&num2,messaggi[op-1]);
                float divisione = (*operazione[op-1])(num1,num2);
                if(divisione != FLT_MIN)
                    printf("\n%.2f / %.2f = %.2f\n", num1,num2,divisione);
                else
                    printf("\nErrore! Divisione per zero\n");
                break;
            // potenza
            case 5:
                inserisci(&num1,&num2,messaggi[op-1]);
                float potenza = (*operazione[op-1])(num1,num2);
                printf("\n%.2f ^ %.2f = %.2f\n", num1,num2,potenza);
                break;
            // uscita dal programma
            case 6:
                printf("\nUscita dal programma...");
                sleep(1);
                exit(0);
                break;
        }
        system("pause");
    }while(op!=6);
}

int menu(){
    int op;
    do{
        system("cls");
        printf("----CALCOLATRICE----\n");
        printf("1) Somma\n2) Differenza\n3) Prodotto\n4) Divisione\n5) Potenza\n6) Exit\n");
        printf("Inserisci operazione desiderata: ");
        scanf("%d", &op);
        if(op<1 || op>6){
            printf("Valore non consentito. Reinserisci\n");
            system("pause");
        }
    }while(op<1 || op>6);
    return op;
}

void inserisci(float *a, float *b, char *messaggio){
    printf("%s", messaggio);
    // Sono puntatori quindi contengono gia' l'indirizzo di memoria su cui scrivere
    scanf("%f %f", a, b);
}

float somma(const float a, const float b){
    return a+b;
}

float differenza(const float a, const float b){
    return a-b;
}

float prodotto(const float a, const float b){
    return a*b;
}

float divisione(const float a, const float b){
    // Gestione errore della divisione per zero
    if(b!=0)
        return a/b;
    else
        return FLT_MIN;
}

float potenza(const float a, const float b){
    return pow(a,b);
}