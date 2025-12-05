# PROGETTO D'ESAME - VOLTURNO MASSIMILIANO (Mat. 378044)

## ISTRUZIONI

Compilare con i seguenti comandi:

```sh
gcc -c main.c -Wall -std=c11
gcc -c gamelib.c -Wall -std=c11
gcc -c gamemenu.c -Wall -std=c11
gcc -c gamemath.c -Wall -std=c11
gcc -o game gamemath.o gamemenu.o gamelib.o main.o
```

Eseguire con:

```sh
./game
```

## MODIFICHE E AGGIUNTE

Nel programma, alcune impostazioni progettuali sono state cambiate:

- Non è possibile cambiare stanza se questa ha dei nemici al suo interno
- Vincere o perdere un combattimento rimuoverà tutti i nemici dalla stanza permanentemente, eccezion fatta per quella di Jaffar
- Non esistono *funzioni* corrispondenti a `chiudi_mappa()` e `salta_turno()`: il programma gestisce questa funzionalità con **salti incondizionati**

Il funzionamento base del gioco è stato ampliato con le seguenti aggiunte:

- Il terminale mostrerà le varie opzioni con il **testo colorato**, in rosso se non completamente disponibili
- L'**input** da tastiera è stato **sanificato**, evitando crash del programma; verranno invece mostrati messaggi di errore user-friendly
- Il programma è suddiviso in **più moduli**: uno per funzioni di utility matematiche (**NON USA math.h**, bensì **stdarg.h**, siccome funzioni quali `min()` e `max()` accettano un numero variabile di parametri), uno per i menù e per le stringhe (**NON USA string.h**) e l'ultimo per le funzioni di gioco
- È possibile **aggiungere o eliminare qualsiasi stanza** direttamente digitando l'id numerico unico, senza dover eliminarne alcuna.
- La generazione random delle stanze **permette di scegliere** se sovrascrivere la mappa già esistente o aggiungere nuove stanze a partire dall'ultima
- Il gioco utilizza il sistema di mappatura fisica e intelligente **Mappotron3000™** *(non esiste ma sembra qualcosa di importante e umanamente poco comprensibile)*; di conseguenza:
  - Il gioco riconosce le stanze isolate, **che sono utilizzate per generare le stanze segrete fino ad esaurimento**
  - Le funzioni basate sulla unidirezionalità della mappa nel testo d'esame sono state **accorpate, non rimosse**
  - Si può procedere in **tutte le direzioni**: quelle non disponibili possono generare stanze segrete (non valido durante la fuga)
  - La mappa **tiene** inoltre **conto delle stanze visitate** da ogni giocatore durante la partita (segnate con indicatore direzionale grigio)
- Easter egg (premere ripetutamente **[4]** nel menù principale)
- Interfaccia di combattimento:
  - Mostrare i crediti o visualizzare le informazioni di un giocatore o di un nemico farà vedere una foto del personaggio (randomica per i giocatori, specifica per i nemici)
  - L'interfaccia di combattimento ha inoltre anche delle barre salute con colore adattivo in base alla *percentuale* di vita dell'entità
- **IMPOSTAZIONI DI GIOCO**:
  - **Modalità Genio**: Permette a un giocatore di avere una tre chance nell'eventualità in cui i suoi punti vita (HP) dovessero raggiungere 0
  - **Modalità Revengeance**: Nemici più tosti e scontri peggiori, ma forse i super migliori (attivabile via easter-egg menzionato sopra)
  - **Modalità Programmazione Procedurale**: Inserire un nickname speciale (il Suo cognome) cambierà tutti i messaggi delle interazioni di combattimento; non è importante in che posizione (entro i limiti accettati) si trovi o il casing utilizzato: affinché sia scritto in ordine consecutivo il programma è in grado di riconoscerlo

## DETTAGLI DI CODEBASE

Il codice generava un tipo di warning, `-Wunused-function`, soppresso con l'attributo `[[maybe_unused]]` sulle funzioni che, nonostante fossero state definite, non venivano richiamate direttamente. Se il compilatore non dovesse riconoscere questa sintassi, si provi a modificare l'attributo in `__attr_maybe_unused__`. Se anche quello dovesse fallire, rimuoverlo completamente e compilare.

Il file `main.c` genera un warning paradossale (influisce mentalmente sul programmatore con conoscenze logico-filosofiche).

Il codice infligge 1D6 di danni psichici a chiunque ne tenti la comprensione.

Le funzioni dei moduli aggiuntivi **NON** sono state copiate, ad eccezione delle seguenti che sono state riadattate:

- `chance_weighted()` (preso spunto da @DragoniteSpam, fonte [qui](https://youtu.be/gMZFmBJi0DY&t=1043))
- `chance()` (preso spunto da Sara Spalding; @ZackBellGames, fonte [qui](https://youtu.be/2FroAhEsuE8&t=400))

## NOTE FINALI

I personaggi dei giocatori sono di proprietà personale. Nonostante le immagini siano state generate con un convertitore ASCII art, gli artwork originali appartengono ai rispettivi artisti. Le altre immagini (Scheletro, Guardia, Jaffar, e Senator Armstrong) sono state reperite online.
