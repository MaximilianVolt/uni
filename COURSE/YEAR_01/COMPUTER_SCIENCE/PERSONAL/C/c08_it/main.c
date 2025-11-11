#include "lib.h"


/**********************************************************
 * COSTRUTTI ALGORITMICI
 *
 * se           // Esegue un blocco di codice se una condizione è vera
 * altrimenti   // Esegue un blocco alternativo se la condizione è falsa
 * compara      // Confronta un'espressione con più valori chiamati casi
 * caso         // Seleziona un blocco di codice in base a un valore (blocco di comparazione)
 * mentre       // Ripete un blocco finché la condizione è vera
 * fai          // Esegue il blocco almeno una volta, poi verifica la condizione
 * per          // Ripete il blocco per un numero specifico di volte
 * ritorna      // Uscita da una funzione, eventualmente con un valore
 * interrompi   // Esce immediatamente da un ciclo o da un blocco di comparazione
 * continua     // Salta alla prossima iterazione del ciclo
 **********************************************************/

/**********************************************************
 * INPUT/OUTPUT
 *
 * stampa       // Scrive un valore o un messaggio a schermo
 * digita       // Specifica il tipo di un dato (numero, decimale, carattere, ecc.)
 **********************************************************/

/**********************************************************
 * DEFINIZIONE DI DATI E STRUTTURE
 *
 * costante     // Definisce un valore fisso che non può essere modificato
 * struttura    // Raggruppa più variabili in un unico blocco (struct)
 * unione       // Condivide lo stesso spazio di memoria tra più variabili
 * enumeratore  // Definisce una lista di costanti numeriche con nomi simbolici
 **********************************************************/

/**********************************************************
 * MODIFICATORI DI MEMORIZZAZIONE
 *
 * statico      // Mantiene il valore tra chiamate o limita la visibilità a un file
 * esterno      // Dichiara una variabile definita altrove (in un altro file)
 **********************************************************/

/**********************************************************
 * PUNTATORI E GESTIONE DELLA MEMORIA
 *
 * dereferenzia // Accede al valore puntato da un puntatore (*)
 * indirizza    // Ottiene l’indirizzo di memoria di una variabile (&)
 * puntatore    // Variabile che contiene l’indirizzo di un’altra variabile
 * nullo        // Valore speciale che indica "nessun indirizzo valido"
 **********************************************************/



programma()
{
  // 1. Cosa stampa?
  // NOTA: '\n' è il carattere che manda a capo.
  stampa("\nCiao, come stai?\nTutto bene?\n");



  // 2. Lavorare con i numeri
  // Dichiara una variabile di tipo 'numero' e
  // di nome 'n', assegnandole il valore 12.
  // Stampa il suo valore.
  //
  // NOTA: usa '__FMT_NUMERO__' per posizionare
  // * il numero dentro la stringa
  // NOTA: usa l'operatore di assegnazione ('=')
  numero n = 12;
  stampa("\nn = " __FMT_NUMERO__ "\n", n);



  // 3. Ripetizioni
  ripeti (10)
  {
    stampa("\n" __FMT_NUMERO__ ". Ciao!", contatore);
  }



  interruttore i prende acceso;

  mentre (i vale acceso)
  {
    stampa("Acceso!\n");
    i prende spento;
  }

  while (i == 1)
  {
    printf("Acceso!\n");
    i = 0;
  }
}