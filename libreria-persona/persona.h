#ifndef PERSONA_H
#define PERSONA_H

//Dichiarazione "forward" della struct opaca
typedef struct Persona Persona;
//Funzioni "pubbliche" per interagire con l'oggetto
Persona* persona_crea (const char* nome, int eta);
void persona_distruggi(Persona* p);
void persona_stampa (const Persona* p);
int persona_get_eta(const Persona* p);
void persona_get_nome(const Persona* p);

#endif