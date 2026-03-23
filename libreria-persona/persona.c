#include "persona.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Persona{
    char nome [50];
    int eta;
};
//Funzione per inserire la persona
Persona* persona_crea(const char * nome, int eta){
    //con malloc la memoria rimane riservata
    Persona* p = (Persona*) malloc(sizeof(Persona));
    if (p!=NULL){
        strncpy(p->nome, nome, 49);
        p->eta = eta;
    }
    return p;
}
//Funzione per deallocare la memoria
void persona_distruggi(Persona* p){
    free(p);
}
//Funzione per accedere al membro età di Persona
int persona_get_eta (const Persona* p){
    return p->eta;  //Accesso ai campi consentito solo qui
}
//Funzione per accedere al membro nome di Persona
void persona_get_nome(const Persona* p){
    printf("%s", p->nome);  //Accesso ai campi consentito solo qui
}

void persona_stampa(const Persona* p){
    
}