// Port scanning. Tool name: pscan
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#include<ws2tcpip.h>

#define SUCCESS 0
#define ERR 1
#define HELP 2

int main(int argc, char *argv[]){
	// Comando help
	if(strcmp(argv[1],"?") == 0 || strcmp(argv[1],"h") == 0 || strcmp(argv[1],"help") == 0 ||
		strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"/?") == 0){
		
		printf("\nQuesto tool e' un port scanning semplice scritto in C. ");
		printf("Per eseguire un port scanning correttamente, la struttura del comando e' la seguente:\n\n");
		printf("\t\tpscan <IP> <Porta_inizio> <Porta_fine>\n");
		return HELP;
	}
	// Comando errato
	if(argc < 4){
		printf("\nIl comando deve seguire questa struttura: pscan <IP> <Porta_inizio> <Porta_fine>\n");
		return ERR;
	}
	
	WSADATA wsa;  // Struttura che contiene i dati tecnici sulla versione di Windows Socket caricata
    SOCKET sock;  // Identificativo del canale di comunicazione
    struct sockaddr_in target_addr;  // Struttura dati per indirizzo socket di un target
    char *target_ip = argv[1];  // Target IP. Macchina a cui connettersi
    int start_port = atoi(argv[2]);  // Porta da cui iniziare lo scanning. atoi = ASCII to Integer
    int end_port = atoi(argv[3]);  // Porta in cui finire lo scanning
    
    // Controllo sul range delle porte
    if(start_port > end_port){
		printf("\nLa porta di inizio deve essere minore della porta finale! Digita pscan ? per maggiori informazioni\n");
		return ERR;
	}
    
    // Inizializzazione Winsock
    int winsoc = WSAStartup(MAKEWORD(2,2), &wsa);
    if (winsoc != 0) {
        printf("\nErrore di inizializzazione dei componenti socket di Windows [Winsock]: %d\n", winsoc);
        return ERR;
    }
    
    printf("\nInizio scansione di %s dalla porta %d alla porta %d...\n", target_ip, start_port, end_port);
	int open_port_count = 0;
	
	for(int port=start_port;port<=end_port;port++){
		// Creazione socket
		sock = socket(AF_INET , SOCK_STREAM , 0 );
	    if(sock == INVALID_SOCKET) {
	        printf("\nErrore nella creazione del socket: %d\n" , WSAGetLastError());
	        return ERR;
	    }
	    
	    // Configurazione struttura dati sockaddr_in
	    target_addr.sin_addr.s_addr = inet_addr(target_ip);  // IP target convertito in long a 32 bit
	    target_addr.sin_family = AF_INET;  // Protocollo utilizzato: IPv4
	    target_addr.sin_port = htons(port);  /*Imposta la porta. htons inverte l'ordine dei byte.
											I processori scrivono le porte al contrario rispetto alla rete Internet*/
		
		// Connessione
		if(connect(sock,(struct sockaddr *) &target_addr,sizeof(target_addr)) == 0){
			printf("\nPorta %d: OPEN", port);
			open_port_count++;
		}
		
		// Chiusura socket
		closesocket(sock);
	}
	
	if(open_port_count == 0)
		printf("\nLe porte analizzate sono chiuse o filtrate\n");
	
    printf("\n");
    // Libera risorse di rete allocate dalla libreria winsock
    WSACleanup();
    return 0;
}