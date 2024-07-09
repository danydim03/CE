#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct prenotazione
{
    int id;
    char *nomecliente;
    int posti;
    char *codiceSpettacolo;
}Prenotazione;

typedef struct Catena
{
    char *nomeCatena;
    struct prenotazione **elencoPrenotazione;
    int num_prenotazioni;
    
}Catena;

Prenotazione *crea_prenotazione(int id, char *nomecliente, int posti, char *codiceSpettacolo)
{
    Prenotazione *new_prenotazione= (Prenotazione *)malloc(sizeof(Prenotazione));
    if (!new_prenotazione)
    {
        perror("errore di allocazione di memoria");
        exit(EXIT_FAILURE);
    }
    
    new_prenotazione->id = id;
    new_prenotazione->nomecliente = strdup (nomecliente);
    if(!new_prenotazione->nomecliente)
    {
        perror("errore di allocazione di memoria");
        exit(EXIT_FAILURE);
    }
    new_prenotazione->posti= posti;
    new_prenotazione->codiceSpettacolo = strdup (codiceSpettacolo);
    if(!new_prenotazione->codiceSpettacolo)
    {
        perror("errore di allocazione di memoria");
        exit(EXIT_FAILURE);
    }
    
    return new_prenotazione;
}


void aggiungi_prenotazioni(struct Catena *catena, char * nomecatena, int id, char *nomecliente, int posti, char *codiceSpettacolo)
{
    Prenotazione * new_prenotazione=crea_prenotazione(id,nomecliente, posti, codiceSpettacolo);
    if(!new_prenotazione)
    {
        perror("non è stato possibile allocare memoria per una nuova prenotazione");
        exit(EXIT_FAILURE);
        
    }
    
    catena->elencoPrenotazione = realloc(catena->elencoPrenotazione, (catena->num_prenotazioni +1 )* sizeof(Prenotazione));
    if (!catena)
    {
        perror("non è stato possibile allocare memoria per una nuova prenotazione");
        exit(EXIT_FAILURE);
        
    }
    catena->elencoPrenotazione[catena->num_prenotazioni]= new_prenotazione;
    catena->num_prenotazioni++;
    
}


static Prenotazione *cerca_prenotazione( Catena * Cinema, char *nome)
{
    for (int i= 0; i< Cinema->num_prenotazioni; i++)
    {
        if(strcmp(Cinema->elencoPrenotazione[i]->nomecliente,nome)== 0 )
        {
            return Cinema->elencoPrenotazione[i];
        }
  
    }
    return NULL;
    
}


char *leggi_stringa(void)
{

    char * buffer= (char *)malloc(BUFSIZ * sizeof(char));
    if(buffer == NULL )
    {
        perror("non è stato possibile allocare memoria per una nuova prenotazione");
        exit(EXIT_FAILURE);
        
    }
    if(!fgets(buffer,BUFSIZ, stdin))
    {
        perror("non è stato possibile prendere l'input");
        exit(EXIT_FAILURE);
    }
    int i=0;
    size_t len = strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    
    return buffer;
}

long leggi_numero(void)
{
    char *buffer;
    buffer= (char *)malloc(BUFSIZ * sizeof(char));
    if(buffer == NULL)
    {
        perror("non è stato possibile allocare memoria");
        exit(EXIT_FAILURE);
    }
    if(!fgets(buffer, BUFSIZ, stdin))
    {
        perror("non è stato possibile prendere l'input");
        exit(EXIT_FAILURE);
    }
    char * endptr;
    errno=0;
    long x = strtol(buffer,&endptr,10);
    if(errno != 0 || endptr == buffer || *endptr != '\n')
    {
        perror("errore nella conversione dell'input");
        free(buffer);
        exit(EXIT_FAILURE);
    }
    free(buffer);
    return x;
}




int main(int argc, char *argv[])
{
    long x = leggi_numero();
    printf("il numero inserito è: %ld ",x);
    long y= 66;
    printf("la somma tra x e y è: %ld ",(x+y));
    int id= 346327;
    char *nomecliente;
    int posti=66;
    char *codiceSpettacolo;
    Catena *Romanina =(Catena *)malloc(sizeof(Catena));
    if (Romanina == NULL)
    {
        perror("non è stato possibile allocare memoria");
        exit(EXIT_FAILURE);
        
    }
    printf("inserisci il nome della catena");
    char * nomecatena=leggi_stringa();
    
    printf("------inserimento dati prenotazione------ \n");
    printf("inserisci nome cliente \n");
    nomecliente= leggi_stringa();
    printf("inserisci nome codice spettacolo \n");
    codiceSpettacolo=leggi_stringa();
    
    
    aggiungi_prenotazioni(Romanina,nomecatena, id,nomecliente, posti,codiceSpettacolo);
    printf("visualizza prenotazione \n");
    
    printf("nome catena:  %s \n", Romanina->nomeCatena);
    printf("id prenotazione:  %d \n", Romanina->elencoPrenotazione[0]->id);

    
    
}
