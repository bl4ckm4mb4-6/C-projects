#include "persona.h"
#include<stdio.h>

int main ()
{
    Persona* utente = persona_crea ("Mario Rossi", 30);
    
    //printf("%d", utente->eta); //Errore di compilazione
    
    printf("Eta: %d\n", persona_get_eta(utente));
    
    persona_get_nome(utente);
    persona_distruggi(utente);
    return 0;
}