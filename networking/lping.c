// Diagnostica di rete ping. Tool name: lping
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<limits.h>
#include<winsock2.h>  /*htons (host to network short) converte un numero a 16 bit da ordine host a quello di rete,
						mentre ntohs (network to host short) fa l'opposto*/

#define ERR 1
#define HELP 2

// Struttura pacchetto ICMP
typedef struct {
    unsigned char  type;     // 8 = ICMP_ECHO_REQUEST , 0 = ICMP_ECHO_REPLY
    unsigned char  code;     // 0
    unsigned short checksum; // Da calcolare
    unsigned short id;       // Identificativo
    unsigned short seq;      // Numero sequenza
} Header_ICMP;

unsigned short checksum(unsigned short *, int );
unsigned long media(DWORD [], int );

int main(int argc, char *argv[]){
	// Comando help
	if(strcmp(argv[1],"?") == 0 || strcmp(argv[1],"h") == 0 || strcmp(argv[1],"help") == 0 ||
		strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"/?") == 0){
		
		printf("\nQuesto tool e' un utilita' di diagnostica di rete scritto in C che sfrutta il protocollo ICMP, chiamato lping, simile al comando ping di Windows.\n");
		printf("Per eseguire il ping correttamente, la struttura del comando e' la seguente:\n\n");
		printf("\t\tlping <IP>\n");
		return HELP;
	}
	// Comando errato
	if(argc < 2 || argc > 2){
		printf("\nIl comando deve seguire la seguente struttura: lping <IP>\n");
		return ERR;
	}
	
	WSADATA wsa;  // Struttura che contiene i dati tecnici sulla versione di Windows Socket caricata
    SOCKET sock;  // Identificativo del canale di comunicazione
    struct sockaddr_in dest;  // Struttura dati per indirizzo socket di un target
    char *target_ip = argv[1];  // Target IP. Macchina a cui inviare pacchetto ICMP
    
    // Inizializzazione Winsock
    int winsoc = WSAStartup(MAKEWORD(2,2), &wsa);
    if (winsoc != 0) {
        printf("\nErrore di inizializzazione dei componenti socket di Windows [Winsock]: %d\n", winsoc);
        return ERR;
    }
    
    printf("\nEsecuzione di LPing %s con 32 byte di dati:", target_ip);
    
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if(sock == INVALID_SOCKET){
    	printf("\nErrore nella creazione del socket: %d\n" , WSAGetLastError());
	    return ERR;
	}
	
	// Configurazione struttura dati sockaddr_in
	dest.sin_addr.s_addr = inet_addr(target_ip);  // IP target convertito in long a 32 bit
	dest.sin_family = AF_INET;  // Protocollo utilizzato: IPv4
	
	// Timeout per rendere il socket non bloccante
	DWORD timeout = 1000;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*) &timeout, sizeof(timeout));	
	
	// Costruzione pacchetto
	Header_ICMP icmp;
	icmp.type = 8;
	icmp.code = 0;
	icmp.id = htons((unsigned short) GetCurrentProcessId());
	
	int send_pkt = 0;
	int recv_pkt = 0;
	DWORD min_ms = UINT_MAX;
	DWORD max_ms = 0;
	DWORD media_ms[4] = {0};
	int count_response = 0;
	
	for(int i=0;i<4;i++){
		char buffer[40];
		memset(buffer, 0, sizeof(buffer));  // Pulisce il buffer
		icmp.seq = htons((unsigned short) i);  // Ordina i byte cosi' come se li aspetta la rete
		icmp.checksum = 0;
		
		memcpy(buffer, &icmp, sizeof(Header_ICMP));  // Copia l'header ICMP nel buffer
		memset(buffer + sizeof(Header_ICMP), 'E', 32);  // Payload di 32 byte
		
		unsigned short chksum = checksum((unsigned short *) buffer, 40);
		((Header_ICMP *) buffer)->checksum = chksum;
		
		// Invio pacchetto e calcolo RTT
		DWORD start_time = GetTickCount();
		int status = sendto(sock, buffer, 40, 0, (struct sockaddr *) &dest, sizeof(dest));
		if(status == SOCKET_ERROR)
			printf("\nInvio fallito: %d", WSAGetLastError());
		else
			send_pkt++;
		
		// Ricezione pacchetto
		char recv_buffer[1024];
		struct sockaddr_in target;
		int targetlen = sizeof(target);
		
		int bytes = recvfrom(sock, recv_buffer, sizeof(recv_buffer), 0, (struct sockaddr *) &target, &targetlen);
		DWORD end_time = GetTickCount();
		
		if(bytes == SOCKET_ERROR){
			if(WSAGetLastError() == WSAETIMEDOUT)
				printf("\nRichiesta scaduta");
			else
				printf("\nErrore in ricezione: %d", WSAGetLastError());
		}
		else{
			Header_ICMP *reply = (Header_ICMP *) (recv_buffer + 20);  // L'Header IP occupa i primi 20 byte

			if(reply->type == 0){  // Verifica che sia una echo reply
				if(ntohs(reply->id) == (unsigned short) GetCurrentProcessId()){  // Verifica che l'id sia lo stesso che ho inviato in precedenza  e riordina i byte per farli comprendere al processore
					printf("\nRisposta da %s: byte=%d seq=%d durata=%lums", target_ip, bytes - 20 - 8, ntohs(reply->seq), end_time - start_time);  // Stampa il payload senza header IP e ICMP
				}
			}
			else{
				printf("\nRicevuto pacchetto ICMP di tipo diverso: %d", reply->type);
			}
			
			// Calcolo massima, minima e media durata in millisecondi
			DWORD aux = end_time - start_time;
			if(aux < min_ms)
				min_ms = aux;
			
			if(aux > max_ms)
				max_ms = aux;
			
			media_ms[i] = aux;

			recv_pkt++;
			count_response++;
		}
		
		sleep(1);
	}
	
	// Chiusura socket
	closesocket(sock);
	// Libera risorse di rete allocate dalla libreria winsock
    WSACleanup();
    
    if(count_response == 0)
    	min_ms = 0;
    
    printf("\n\nStatistiche LPing per %s:\n", target_ip);
	printf("\tPacchetti: Trasmessi = %d, Ricevuti = %d,\n", send_pkt, recv_pkt);
	printf("\tPersi = %d (%.0f%% persi),\n", send_pkt - recv_pkt, (100.0 - ((float) recv_pkt/send_pkt)*100));
	printf("Tempo approssimativo percorsi andata/ritorno in millisecondi:\n");
	printf("\tMinimo = %lums, Massimo =  %lums, Medio =  %lums", min_ms, max_ms, media(media_ms, recv_pkt));
    return 0;	
}

unsigned short checksum(unsigned short *addr, int len) {
    unsigned long sum = 0;
    while(len > 1) {
        sum += *addr++;
        len -= 2;
    }
    if(len == 1) {
        sum += *(unsigned char *)addr;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

unsigned long media(DWORD media_ms[], int recv_pkt){
	if(recv_pkt == 0)
		return 0;

	unsigned long media = 0;
	for(int i=0;i<4;i++){
		media += media_ms[i];
	}
	return media/4;
}
