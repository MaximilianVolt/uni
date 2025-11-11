# APPUNTI PROGRAMMAZIONE ORIENTATA AGLI OGGETTI

## 24/02/25 - INTRODUZIONE

Java favorisce la portabilità rispetto alle prestazioni.
Un esempio di programma scrivibile in Java:

```java
public class Ciao
{
  public static void main(String args[])
  {
    System.out.println("Ciao!");
  }
}
```

Il nome del file deve essere uguale al nome della classe principale che contiene.
Nell'esempio sopra, il file si chiamerà `Ciao.java`. Se ci sono più classi in un file, il nome sarà quello dell'**unica** classe pubblica al suo interno.

Comando di compilazione:

```sh
# Genera un file File.class (javac, Java Compiler)
javac File.java
```

Comando di interpretazione (esecuzione):

```sh
# Omettere l'estensione *.class
java File
```

## 25/02/25

Quando viene dichiarata (non definita) una variabile, la sua dimensione è di 4 byte, a meno che non venga specificato al compilatore di utilizzare un indirizzamento a 64 bit. Il riferimento a qualsiasi oggetto si trova nello stack, mentre i dati dell'oggetto istanziato si trovano nell'heap.

## 28/02/25

### TIPI DI DATI

I tipi indicano il dominio dei valori con cui si intende operare.

In Java tipi di dati semplici in Java possono essere:

- Primitivi: valori semplici numerici o di verità
- Composti (o per riferimento): collezioni di dati o strutture composte

I tipi di dati primitivi si dividono a loro volta in base alla rappresentazione necessaria per adoperare con un determinato dato. Si hanno tipi interi, decimali, caratteri e booleani.

I tipi interi sono:

| Tipo    | Dimensione | Range dei valori  |
|---------|------------|-------------------|
| `byte`  | 8 bit      | [-2^7, 2^7 - 1]   |
| `short` | 16 bit     | [-2^15, 2^15 - 1] |
| `int`   | 32 bit     | [-2^31, 2^31 - 1] |
| `long`  | 64 bit     | [-2^63, 2^63 - 1] |

> ⚠️ I tipi interi usano la rappresentazione in complemento a 2.

I tipi per la rappresentazione numerica decimale sono:

| Tipo     | Dimensione | Precisione |
|----------|------------|------------|
| `float`  | 32 bit     | 6 cifre    |
| `double` | 64 bit     | 15 cifre   |

Per la rappresentazione dei caratteri si usa:

- `char` (16 bit, standard Unicode)

Infine, per i valori di verità, si ha:

- `boolean` (8 bit) { `false`, `true` }

### COSTANTI LETTERALI

I suffissi e le lettere per la rappresentaione delle costanti letterali sono case-insensitive.

```java
// Decimale
4                 // int
4l                // long



// Binario
0b100             // int
0b100l            // long



// Ottale
04                // int
04l               // long



// Esadecimale
0x4               // int
0x4l              // long



// Virgola mobile
1.  1.0           // double
1.f 1.0f          // float

10e10             // Notazione scientifica
.1e-3             // Notazione scientifica

0x1.p-1  0x1.p+1  // Notazione esponenziale esadecimale (double)
0x1.p-1f 0x1.p+1f // Notazione esponenziale esadecimale (float)



// Caratteri
'a'



// Sequenze di escape
'\''     // Apostrofo
'\"'     // Virgolette
'\n'     // Newline
'\t'     // Tab
'\b'     // Backspace
'\\'     // Backslash
'\ddd'   // Codifica carattere in ottale (d indica una cifra ottale)
'\udddd' // Codifica carattere in esadecimale (d indica una cifra esadecimale)



// Assegnazioni di carattere possibili
char x = 'b';
char x = 98;  // 98 == 'b'
```

### L-VALUE E R-VALUE

Con R-Value si intendono valori risultanti da un'espressione, e possono comparire solo alla destra di un assegnamento.
Con L-Value si intendono locazioni di memoria, che in un'espressione possono comparire sia a sinistra che a destra.
Se gli L-Value sono posizionati a sinistra di un uguale (=), si intende sovrascrivere il loro valore, altrimenti viene recuperato il loro valore.

### OPERATORI

```java
// Operatori logici/booleani
!a      // Not
a && b  // And
a || b  // Or

// AND e OR cortocircuitano, se un operando è già sufficiente per determinare il risultato dell'espressione, gli altri operandi NON vengono valutati

// Es:
true || f(1)  // f(1) NON viene eseguita
false && g(2) // g(2) NON viene eseguita
f(1) || g(2)  // g(2) viene valutata SOLO SE f(1) è FALSA
f(1) && g(2)  // g(2) viene valutata SOLO SE f(1) è VERA



// Operatori artimetici
+a    // Prefisso unario
a + b // Somma
-a    // Negazione aritmetica
a - b // Sottrazione
a * b // Moltiplicazione
a / b // Divisione
a % b // Modulo (resto della divisione)

5 / 2   // 2
5 % 2   // 1
5.0 / 2 // 2.5

// Casting
(double) 5 / 2   // 2.5 (valutato come ((double) 5) / 2)
(double) (5 / 2) // 2.0



// Operatori relazionali
a == b   // Comparativo di uguaglianza
a != b   // Compatativo di disuguaglianza
a > b    // Maggiore stretto
a < b    // Minore stretto
a >= b   // Maggiore o uguale
a <= b   // Minore o uguale



// Operatori bitwise (lavorano sugli interi)
~a       // Negazione bitwise
a & b    // And bitwise
a | b    // Or bitwise
a ^ b    // Xor bitwise
a << b   // Shift a sinistra
a >> b   // Shift a destra
a >>> b  // Shift a destra senza segno



// Operatori con effetti collaterali
++a   // Incremento (di 1), ESSENDO PREFISSO, prima modifica il valore, poi lo resituisce
a++   // Incremento (di 1), ESSENDO POSTFISSO, prima restituisce il valore, poi lo modifica
--a   // Decremento (di 1), ESSENDO PREFISSO, prima modifica il valore, poi lo resituisce
a--   // Decremento (di 1), ESSENDO POSTFISSO, prima restituisce il valore, poi lo modifica



// Concatenazione di stringhe o numeri, un operando DEVE essere una stringa
a + b



// Operatori di assegnamento
a = b    // Assegnazione del valore di b ad a, restituisce il valore assegnato

// Possono essere composti con operatori BINARI aritmetici e bitwise
a op= b  // a = a op b
```

### PRECEDENZA DEGLI OPERATORI

Se in un'espressione compaiono degli operatori con la stessa precedenza, si controlla la loro associatività.

| Precedenza | Operatori                                                                   | Descrizione                   | Associatività verso |
|------------|-----------------------------------------------------------------------------|-------------------------------|---------------------|
| 1          | `()`                                                                        | Raggruppamento                | N/A                 |
| 2          | `()`, `[]`, `.`, `::`                                                       | Risoluzione                   | dx                  |
| 3          | `new`                                                                       | Instaziazione                 | sx                  |
| 4          | `++`, `--`                                                                  | Unari postfissi               | dx                  |
| 5          | `++`, `--`, `+`, `-`, `~`, `!`, `(type)`                                    | Unari prefissi, casting       | sx                  |
| 6          | `*`, `/`, `%`                                                               | Moltiplicativi                | dx                  |
| 7          | `+`, `-`                                                                    | Additivi                      | dx                  |
| 8          | `<<`, `>>`, `>>>`                                                           | Bit shift                     | dx                  |
| 9          | `<`, `<=`, `>`, `>=`, `instanceof`                                          | Comparativi                   | dx                  |
| 10         | `==`, `!=`                                                                  | Comparativi di uguaglianza    | dx                  |
| 11         | `&`                                                                         | AND Bitwise                   | dx                  |
| 12         | `^`                                                                         | XOR Bitwise                   | dx                  |
| 13         | `\|`                                                                        | OR Bitwise                    | dx                  |
| 14         | `&&`                                                                        | AND Logico                    | dx                  |
| 15         | `\|\|`                                                                      | OR Logico                     | dx                  |
| 16         | `? :`                                                                       | Ternario                      | sx                  |
| 17         | `=`, `+=`, `-=`, `*=`, `/=`, `%=` , `&=`, `\|=`, `^=`, `<<=`, `>>=`, `>>>=` | Assegnamento                  | sx                  |
| 18         | `->`                                                                        | Espressione switch, predicato | N/A                 |

### ESPRESSIONI

Un'espressione è una scrittura che combina quindi L-Value, R-Value e operatori, e ha SEMPRE un valore di ritorno.

```java
int m = 3, n = 5;
int result = (m += n -= m *= 2);



int num = 15;
int res = num > 10 ? (num % 2 == 0 ? 20 : 25) : 30;



int a = 6, b = 2, c = 4;
int result = ++a * b-- + (c %= 3) - b;



String nome = "Giocatore" + (int) (Math.random() * 5 + 1);
```

## 03/03/25

### ARRAY

Gli array sono aggregazioni di dati dello stesso tipo. In Java, anche gli Array sono oggetti. Vi sono due modi per istanziarli:

```java
<tipo> <identificatore>[]; // int array[];
<tipo>[] <identificatore>; // int[] array;
```

Per la definizione, si procede con:

```java
<identificatore> = new <tipo>[<dimensione>];
```

La definizione è compattabile anche in una sola istruzione:

```java
// Equivalente con <tipo>[] <identificatore>
<tipo> <identificatore>[] = new <tipo>[<dimensione>];
```

Gli array contengono la proprietà `length`, che indica il numero di elementi che essi contengono. L'indicizzazione degli array parte da `0` a `length - 1`; per accedere a una posizione di un array si usano le parentesi quadre `[]`:

```java
array[posizione] // Espressione che ottiene l'elemento posizione-esimo della variabile array
```

Gli array possono essere multidimensionali. Per dichiarare una matrice (array bidimensionale), si può procedere nella maniera seguente:

```java
<tipo> <identificatore>[][] = new <tipo>[<dimensione_1>][<dimensione_2>];
```

Per accedervi, si usano più coppie di parentesi:

```java
matrice[posizione_1][posizione_2] // Espressione che ottiene l'elemento della riga posizione_1 e colonna posizione_2
```

Quando sono creati, gli array sono automaticamente inizializzati con tutti i valori a `0` se sono di numeri, a `false` se sono booleani e a `null` se sono di oggetti.

### ISTRUZIONI

#### ISTRUZIONI SEMPLICI

Le istruzioni semplici possono essere composte da assegnamenti, chiamate di funzione, oppure comandi speciali di salto incondizionato, e sono sempre delimitate da `;`. Le istruzioni composte invece hanno delle parole chiave che identificano il comportamento del programma, e hanno sintassi variabili.

#### ISTRUZIONI COMPOSTE

L'istruzione composta più elementare è il **blocco istruzioni**, che racchiude una sequenza di istruzioni (semplici o composte anch'esse). Il blocco istruzione ha la seguente sintassi:

```java
{
  // Metasintassi
  [<istruzione>]
  [<...>]
}

{
  int a = 1;
  a += 2;

  oggetto.metodo(3);

  {
    int b = 4;

    // ...
  }

  // ...
}
```

Dentro un blocco di istruzioni, non è possibile ridefinire variabili dichiarate in precedenza. Ogni variabile dichiarata all'interno del blocco è visibile solo al suo interno dopo che è stata dichiarata.

#### ISTRUZIONI CONDIZIONALI

In un programma è inevitabile che sia richiesto eseguire azioni *solo se* certe condizioni sono verificate. In Java, il lessema "se" si traduce con:

```java
if (<condizione>) <istruzione>
```

Le istruzioni condizionali accettano **una sola** istruzione sottoposta a esse. Se si vogliono compiere più operazioni al verificarsi di una condizione, l'istruzione sottoposta deve naturalmente essere un blocco di istruzioni. Un esempio:

```java
if (x % 2 == 0)
  System.out.println("Pari");



if (x % 2 == 0)
{
  System.out.println("Trovato numero pari");
  contatorePari++;
}
```

Se si vogliono aggiungere delle istruzioni di "fallback", nel caso esclusivo in cui una condizione *non è* verificata, si può utilizzare:

```java
if (<condizione>) <istruzione>
else <istruzione>
```

Un esempio:

```java
if (x % 2 == 0)
  System.out.println("Pari");
else
  System.out.println("Dispari");



if (x % 2 == 0)
{
  System.out.println("Trovato numero pari");
  contatorePari++;
}
else
{
  System.out.println("Trovato numero dispari");
  contatoreDispari++;
}
```

`if` e `else` possono essere concatenati:

```java
if (x > 0)
{
  System.out.println("Numero positivo");
}
else
{
  if (x == 0)
  {
    System.out.println("Numero nullo");
  }
  else
  {
    // if (x < 0) // logicamente ridondante
    // {
    System.out.println("Numero negativo");
    // }
  }
}
```

Si può riscrivere il seguente programma con una sintassi più compatta:

```java
if (x > 0)
  System.out.println("Numero positivo");
else if (x == 0)
  System.out.println("Numero nullo");
else // if (x < 0) // logicamente ridondante
  System.out.println("Numero negativo");
```

Si presti attenzione al fatto che la clausola `else` si aggancia all prima clausola `if` più vicina ad essa.

```java
if (utente.registrato())
  if (utente.loginEffettuato())
    System.out.println("Utente autenticato con successo.");
else
  System.out.println("Registrazione necessaria.");
```

In questo caso, se l'utente è registrato ma il login fallisce, all'utente verrà detto di eseguire la registrazione. Se invece l'utente non è registrato, il codice continua oltre tutte le clausole, causando potenziali errori e comportamenti dannosi da parte dell'ultimo.
Si tratta di un errore erroneamente logico dovuto alla sintassi. Il compilatore non guarda le tabulazioni per capire la nidificazione della logica, bensì le parentesi e i blocchi di codice. Per ottenere il risulato desiderato, bisogna esplicitare dove mettere le parentesi:

```java
if (utente.registrato())
{
  if (utente.loginEffettuato())
    System.out.println("Utente autenticato con successo.");
}
else
  System.out.println("Registrazione necessaria.");

```

Se si tratta di controllare l'uguaglianza di un valore tra una serie di altri, ora scriveremmo:

```java
if (x == 0) <...>
else if (x == 1) <...>
else if (<...>) <...>
```

Tuttavia, se si volesse fare uno stesso set di operazioni se due valori sono uguali o magari avere comportamenti diversi in casi particolari scriveremmo:

```java
if (x == 0 || x == 1)
{
  System.out.println("x = 0 oppure x = 1");
}
else if (x == 2)
  System.out.println("x = 2");
else if (x == 3)
  System.out.println("x = 3");
else
  System.out.println("x non appartiene a [0, 3]");
```

Ma, come si può notare, il codice diventa abbastanza verboso per fare delle comparazioni di uguaglianza. Esiste quindi un'altra istruzione per abbreviare la scrittura precedente:

```java
switch (<espressione_costante>)
{
  case <COSTANTE_1>:
    <istruzione>
  case <COSTANTE_2>:
    <istruzione>
  <...>
}
```

L'istruzione switch compara il valore dell'espressione costante con tutte le costanti nell'ordine specificato. Una volta trovato il caso (appunto, `case`) corrispettivo, l'esecuzione dello `switch` **prosegue fino alla fine del blocco**, o a un'istruzione di salto incondizionato. Nell'esempio sopra, se l'espressione costante equivale a `COSTANTE_1`, l'istruzione eseguirebbe tutte quelle degli altri casi, quindi anche il codice posto dentro il caso di `COSTANTE_2` e qualsiasi altro caso sottostante che non abbia interruzioni. Come specificare di interropere il codice in ogni caso? Si possono usare solo i lessemi `break` e `return` (approfonditi più avanti). `break` interrompe l'istruzione, mentre `return` interrompe anche l'esecuzione della funzione attuale in cui è stato eseguito. Quindi, se si intende eseguire **solo** il codice di un case, in queso caso potremmo scrivere:

```java
switch (<espressione_costante>)
{
  case <COSTANTE_1>:
    <istruzione>
  break; // Interrompe solo l'istruzione

  case <COSTANTE_2>:
    <istruzione>
  return; // Interrompe l'istruzione E il metodo in esecuzione

  <...>
}
```

Se l'espressione costante passata all'istruzione non dovesse essere contenuta nell'elenco di costanti provvisto, il codice non farà nulla. Si può specificare in generale una clausola di default in questa maniera:

```java
switch (<espressione_costante>)
{
  case <COSTANTE_1>:
    <istruzione>
  break;

  default:
    <istruzione>
  break;

  <...>
}
```

Se si vogliono dichiarare variabili dentro ogni caso dell'istruzione switch, sono richieste le parentesi graffe.

```java
switch (<espressione_costante>)
{
  case <COSTANTE_1>:
  {
    int a = 1;
    System.out.println("Dichiarata \"a\" che vale " + a);
  }
  break;

  <...>
}
```

L'esempio di prima, quindi, si può riscrivere in questo modo:

```java
switch (x)
{
  case 0:
  case 1:
    System.out.println("x = 0 oppure x = 1");
  break;

  case 2:
    System.out.println("x = 2");
  break;

  case 3:
    System.out.println("x = 3");
  break;

  default:
    System.out.println("x non appartiente a [0, 3]");
  // break; // facoltativo, il blocco finisce comunque qui
}
```

#### ISTRUZIONI D'ITERAZIONE

L'ultimo costrutto algoritmico è l'iterazione, ovvero la ripetizione di un'istruzione (o blocco). Si prenda per esempio il seguente programma.

```java
int x = 0;

System.out.println("x vale " + x);
x += 1;
System.out.println("x vale " + x);
x += 1;
System.out.println("x vale " + x);
x += 1;
System.out.println("x vale " + x);
```

Il programma stampa il valore di una variabile x sullo schermo, incrementandola di 1 ogni volta. L'output del codice, infatti, è:

```md
x vale 0
x vale 1
x vale 2
x vale 3
```

Si può comunque intuire che il design dell'applicazione non è ideale, specialmente se si vuole iterare più volte. Se molte istruzioni sono ripetute in sequenza, si può usare quindi un'iterazione. Java offre 4 tipi di iterazione: `while`, `do... while` e `for` (che ha due sintassi). Il ciclo `while` è il più semplice da scrivere sintatticamente, e si costruisce nella seguente maniera:

```java
while (<condizione>) <istruzione>
```

Quando si parla di cicli, di solito vengono dichiarate variabili aventi uno dei due scopi: **accumulatore** o **contatore**. Con accumulatore si intende quel tipo di variabile che varia in maniera imprevedibile o non determinabile, mentre con contatore si intende un'accumulazione a intervalli sempre prevedibili. Per iterare un certo numero di volte, sarà quindi necessario introdurre nel codice una variabile contatore che tenga traccia di quante volte si ha iterato. In questo esempio, già x è un contatore. Riscrivendo l'esempio, si ha:

```java
// Istruzione di inizializzazione (I)
int x = 0;

// Condizione di iterazione (C)
while (x < 3)
{
  System.out.println("x vale " + x);

  // Istruzione di aggiornamento (A)
  ++x;
}
```

Come si può notare dai commenti, i cicli while con conteggi richiedono due istruzioni "extra" per inizializzare e aggiornare il contatore. Java offre anche il costrutto `for` che compatta sintatticamente la stessa logica.

```java
for ([<I>]; [<C>]; [<A>]) <istruzione>
```

L'ordine di esecuzione, considerando il caso in cui il loop non ha interruzioni all'interno del suo corpo, è il seguente:

1. Viene eseguita `<I>`, che serve a inizializzare tutte le variabili per lavorare con l'iterazione
2. Viene valutata `<C>`: se l'espressione è `true`, allora il ciclo viene eseguito, altrimenti salta al passo `6`.
3. Si esegue poi l'istruzione interna al blocco `for`.
4. Si esegue `<A>`.
5. Viene valutata nuovamente `<C>`: se l'espressione è `true`, allora si ripete dal passo `3`, altrimenti continua al passo `6`.
6. L'esecuzione del codice continua dalla prima istruzione direttamente successiva al ciclo `for`.

Si può quindi riscrivere l'esempio precendente in questa maniera:

```java
//        <I>    <C>   <A>
for (int x = 0; x < 3; ++x)
  System.out.println("x vale " + x);
```

Le istruzioni/espressioni del ciclo `for` possono essere omesse; la mancanza di queste semplicemente eviterà che venga inizializzato un contatore dentro il loop oppure che venga aggiornato il contatore. I separatori (`;`) vanno comunque inseriti. Se viene omessa la condizione di iterazione, questa varrà automaticamente `true`. Le seguenti espressioni sono quindi valide:

```java
int i = 0;

for (; i < 5; ++i)
  // Inizializzatore dichiarato fuori



for (int j = 0; j < 5;)
  // Aggiornamento interno al loop
  ++j;



for (;;)
  // Loop infinito
```

Nel caso in cui si desidera iterare completamente per un array di oggetti, si potrebbe scrivere:

```java
for (int i = 0; i < array.length; ++i)
  <istruzione>
```

Ma Java offre una versione più compatta del `for`, in altri linguaggi conosciuto come "`foreach`", che, diversamente dagli altri costrutti, ci permette di dichiarare una variabile che ad ogni iterazione prenderebbe l'elemento `i`-esimo dell'array:

```java
for (Oggetto i : listaIterabile)
  <istruzione>
```

Ad esempio, se si volesse stampare a schermo i dati delle istanze di tipo `Oggetto` contenute all'interno dell'array `arrayOggetti`, si potrebbe procedere in due modi:

```java
// Si legga come: "per i da 0 a <lunghezza>, si stampi l'elemento i-esimo di arrayOggetti"
for (int i = 0; i < arrayOggetti.length; ++i)
  System.out.println(arrayOggetti[i]);



// Si legga come: "per ogni Oggetto o in arrayOggetti, si stampi o"
for (Oggetto o : arrayOggetti)
  System.out.println(o);
```

Con le iterazioni non è sempre possibile conoscere una condizione prima di eseguire le istruzioni al suo interno. Si consideri ad esempio l'input dell'utente: non è possibile sapere se questo è valido o no finché non è stato captato. Per questo motivo, esiste il tipo di iterazione post-condizionale che, a differenza di tutte le altre, garantisce sempre almeno un'esecuzione del suo corpo di istruzioni. Si tratta del costrutto iterativo `do... while`, che segue la sintassi:

```java
do <istruzione> while (<condizione>);
```

Applicandolo all'esempio dell'input utente dove si vuole chiedere all'utente un valore positivo, si avrebbe ad esempio:

```java
int x;
Scanner tastiera = new Scanner(System.in);

do
{
  x = tastiera.nextInt();
}
while (x < 0);
```

Si noti che per usare la variabile nella condizione finale, questa deve essere dichiarata al di fuori del blocco `do... while`. Inoltre, il `;` è obbligatorio dopo la condizione.

#### ISTRUZIONI DI SALTO INCONDIZIONATO

Tutti i controlli, iterazioni, etc. possono essere scritte senza istruzioni di salto incondizionato concatenando istruzioni condizionali (tranne i metodi che restituiscono un valore, quelli necessitano dell'istruzione di `return`). Tuttavia, effettuare tutti i controlli possibili per garantire la corretta esecuzione del programma può generare codice molto verboso, anche se magari si tratta solo di saltare o interrompere un ciclo o una sequenza di istruzioni. Per questo vi sono anche delle istruzioni di salto incondizionato che permettono di spostare il flusso dell'esecuzione dove più sensato, risparmiando molteplici controlli e nidificazioni della logica.
Le istruzioni di salto incondizionato sono:

- `break`: esce da uno `switch` o da un **ciclo** in cui è posizionato. Ammette un label come parametro; se nessun label è specificato, esce SOLO dal **ciclo** più nidificato in cui si trova
- `continue`: prosegue alla prossima iterazione di un ciclo in cui è posizionato. Ammette un label come parametro; se nessun label è specificato, prosegue SOLO il **ciclo** più nidificato in cui si trova
- `return`: esce **immediatamente** dalla funzione/metodo in cui è stato eseguito. Può ammettere un'esepressione come parametro, il cui valore viene restituito alla funzione chiamante
- `goto` (**non usato in Java**), salta in un'altra parte di codice all'interno di un metodo

Sintassi di `break`:

```java
break [<label>];
```

Esempi di `break`:

```java
// Uso del lessema "break" dentro il comando switch

switch (x)
{
  case 1:
    System.out.println("x = 1");

  // Esce direttamente dallo switch dopo aver eseguito il caso in cui x sia 1
  break;

  case 2:
  case 3:
    System.out.println("x = 2 \\/ x = 3");

  // Esce dallo switch dopo aver stampato che x vale 2 o 3
  break;

  default:
    System.out.println("Valore inaspettato.");

  // Opzionale, non ci sono altre istruzioni successive a questo comando
  break;
}



// Uso del lessema "break" dentro un iterazione

for (int i = 0; i < array.length; ++i)
{
  if (array[i] == valoreSentinella)
  {
    System.out.println("Valore sentinella (" + valoreSentinella + ") trovato in posizione [" + i + "].");
    break;
  }

  ++contatoreValoriNonSentinella;
}
```

Sintassi di `continue`:

```java
continue [<label>];
```

Esempi di `continue`:

```java
// Codice con lo stesso comportamento di quello sopra.

for (int i = 0; i < array.length; ++i)
{
  if (array[i] != valoreSentinella)
  {
    ++contatoreValoriNonSentinella;
    continue;
  }

  System.out.println("Valore sentinella (" + valoreSentinella + ") trovato in posizione [" + i + "].");
  break;
}



// Esempio di continue per gestire menù

Scanner tastiera = new Scanner(System.in);
boolean invalido = true;
int opz = 0;

// Entra nell'iterazione siccome "invalido" vale true
for (int numeroInterazioni = 0; opz != 0 || invalido; ++numeroInterazioni)
{
  opz = tastiera.nextInt();

  if (invalido = opz < 0 || opz > 2)
    // Salta i controlli successivi e ricomincia il corpo dell'iterazione
    continue;

  if (opz == 0)
    break;

  switch (opz)
  { 
    case 1:
      f();
    break;

    case 2:
      g();
    break;

    default:
      System.out.println("Input invalido");
  }
}
```

Sintassi di `return`:

```java
return [<espressione>];
```

Esempi di `return`:

```java
public void stampaRettangolo(int b, int h)
{
  if (b < 1 || h < 1)
  {
    System.out.println("Dimensioni rettangolo invalide");
    return;
  }

  for (int i = 0; i < b; ++i)
  {
    for (int j = 0; j < h; ++j)
      // Il metodo print() (non println()) non manda a capo
      System.out.print("*");

    System.out.println();
  }
}



public static short sign(double x)
{
  return (short) ((x > 0 ? 1 : 0) - (x < 0 ? 1 : 0));
}



public static double abs(double x)
{
  return x * sign(x);
}
```

Java permette di definire identificatori per le istruzioni; la sintassi per definire questi label è la seguente:

```java
<label>: <istruzione>
```

I label sono riconosciuti dalle istruzioni di `break`/`continue`, e possono essere usati per interrompere/avanzare dentro un qualsiasi ciclo in cui si trova questo tipo di istruzione.

```java
// Anche le istruzioni hanno un indirizzo in memoria
loopEsterno:
for (int i = 0; i < array.length; ++i)
{
  for (int j = 0; j < array.length; ++j)
  {
    if (i + j == 25)
      break loopEsterno;
    
    if (i * j > 100)
      continue loopEsterno;
  }
}
```

#### PATTERN DESIGN

Ecco alcuni esempi di come poter migliorare il design del codice semplificando la logica e sfruttando le proprietà delle istruzioni.

Semplificare i controlli `bool == true` e `bool == false` rispettivamente in `bool` e `!bool`.

```java
if (b1 == true)
  <istruzione>
else if (b2 == false)
  <istruzione>



if (b1)
  <istruzione>
else if (!b2)
  <istruzione>
```

Due `if` in cascata immediatamente nidificati possono essere raggruppati in un solo controllo che effettua il prodotto logico delle loro condizioni.

```java
if (condizione_1)
{
  if (condizione_2)
  {
    <istruzione>
  }
}



if (condizione_1 && condizione_2)
{
  <istruzione>
}
```

Due `if` consecutivi che compiono la stessa istruzione possono essere raggruppati in un solo controllo che effettua la somma logica delle loro condizioni.

```java
if (condizione_1)
{
  <istruzione>
}

if (condizione_2)
{
  <istruzione>
}



if (condizione_1 || condizione_2)
{
  <istruzione>
}
```

Se nei metodi serve effettuare più validazioni di un dato e adoperare solo nel caso positivo, di solito si userebbe un pattern di `if` e `else` nidificati e in cascata. Questo però rende gestire la logica e spostarsi in varie parti del codice più difficile. Se si sfrutta l'istruzione di `return`, si può ottenere invece un approccio più lineare:

```java
public void method()
{
  if (condizione_1)
  {
    if (condizione_2)
    {
      // Dato valido
    }
    else
    {
      // Gestione errore / caso particolare di condizione_2
    }
  }
  else
  {
    // Gestione errore / caso particolare di condizione_1
  }
}



public void method()
{
  // Clausola di guardia: nega la condizione per verificare subito gli errori; esce dalla funzione appena possibile
  if (!condizione_1)
  {
    // Gestione errore / caso particolare di condizione_1
    return;
  }

  if (!condizione_2)
  {
    // Gestione errore / caso particolare di condizione_2
    return;
  }

  // Dato valido (scope semplificati)
}
```

#### ESERCIZI

1. Si realizzi un programma che, dati `n` e `k`, generi un array di `n` `int` scelti randomicamente tra `0` e `15` e che restituisca la posizione del primo elemento che abbia un valore `k`.

2. Si realizzi un programma che implementi le funzioni `average()` e `sum()`, che prendono come input un array di `double` e che restituiscano rispettivamente la media e la somma dei SOLI valori strettamente positivi in questo contenuti. I metodi dovrebbero far uso dell'istruzione `continue`.

3. Realizzare un programma in Java che controlli se una cifra di testo corrisponde a una codifica esadecimale valida, e in caso stampi in ordine il valore di ogni cifra. Il programma deve implementare due metodi: `isValidHexString()` che prende in input una sequenza di caratteri e restituisce `true` se la stringa è una codifica valida o `false` altrimenti, e `printDecValues()` che, data una cifra esadecimale, restituisca il suo valore come intero, senza fare distinzione tra caratteri maiuscoli o minuscoli.

4. Realizzare un programma che popoli un array di oggetti con 5 elementi usando un menù. Si istanzi un oggetto della classe `Scanner` e si usi il metodo `nextInt()` per leggere un numero intero da tastiera. Se l'input è `0`, si interrompa l'esecuzione del programma. Se l'input è `1`, si aggiunga un oggetto (se possibile) nella prima posizione disponibile dell'array. Se l'utente inserisce `2`, si aggiunga un oggetto nell'array in una posizione da questo specificato (con una seconda richiesta di input) e analogamente si proceda con l'implementazione di un metodo per la rimozione di un elemento da una qualsiasi posizione specificata dall'utente in caso questa selezioni `3` dal menù. Infine, se l'utente preme `4`, deve poter visualizzare il numero di elementi non nulli (`!= null`) nell'array. Il programma deve usare `break`, `continue` e `return`.

## 06/05/25

### FLUSSI DI I/O

Il package in cui sono contenute le classi per la gestione di flussi è `java.io`.

Le gerarchie di classi che lavorano con i dati in input sono:

- `InputStream`: flusso di *byte*
- `Reader`: flusso di caratteri

I nomi delle classi sono mantenuti come postfissi anche nelle classi figlie (ad es, `FileReader`).

Queste classi offrono metodi base per la lettura, mentre le classi figlie implementano metodi per *l'interpretazione* dei dati.

### FLUSSI COLLEGATI A FILE

- `FileReader` (per file di caratteri)
- `FileInputStream` (per file binari)
- `ByteArrayInputStream`
- `CharArrayReader`
- `StringBufferInputStream`
- `StringReader`

### WRAPPER DI FLUSSI DI INPUT

- `InputStreamReader`: incapsula ogni InputStream trasformandolo in un flusso di caratteri

```sh
java program > outputfile # Redirect dell'output del programma
java program < inputfile # Redirect dell'input del programma
```

### CLASSI ASTRATTE DI FILTRI

Discendono da `FilterInputStream` e `FilterReader`:

- `BufferedInputStream`
- `BufferedReader`

L'idea per ottimizzare la velocità di esecuzione è quella di separare l'applicazione dalla sorgente fisica di dati introducento uno stato intermedio.

Se l'applicazione acedesse direttamente ai dati su disco, questa sarebbe più lenta di un normale accesso in memoria RAM.

Per questo si usano dei buffer, aree di memoria in RAM che sfruttano i tempi morti del programma per caricare i dati da disco all'interno del buffer.

# RIPASSO JAVA

## FILE

Lettura:

```java
/// Caratteri
BufferedReader in = new BufferedReader(new FileReader("file.ext"));
  .readLine()

Scanner in = new Scanner(new FileInputStreaam("file.ext"));
  .hasNextLine()
  .nextLine()
  .nextInt() /* ... */
  .hasNext() /* ... */

/// Binario
DataInputStream in = new DataInputStream(new FileInputStream("file.ext"));
  .readUTF()
  .readInt() /* ... */
```

Scrittura:

```java
/// Caratteri
BufferedWriter out = new BufferedWriter(new FileWriter("file.ext"));
  .write()
  .newLine()
  .flush()

PrintWriter out = new PrintWriter((OutputStream) o, /* autoflush: */ true);
PrintWriter out = new PrintWriter("file.ext");
  .println()
  .printf()
  .print()
  .flush()

/// Binario
DataOutputStream out = new DataOutputSream(new FileOutputStream("file.ext"));
  .writeUTF()
  .writeInt() /* ... */
  .flush()
```

## MULTITHREADING

```java
// Usa l'istanza chiamante come monitor
synchronized /* ... */ metodo()

// Usa objRef come monitor
synchronized (objRef) { /* ... */ }

// Usa la classe di ClassRef come monitor (es. per modificare campi statici)
synchronized (ClassRef.class) { /* ... */ }

// Usata all'interno di eredi della superclasse Thread o contraenti di Runnable
// Evita il caching del dato; si usa se sufficiente effettuare operazioni esclusivamente atomiche
volatile nomeCampo
```

Per lettura/scrittura concorrente:

```java
/// Caratteri
PipedWriter out = new PipedWriter();
  .write()
  .flush()

PipedReader in = new PipedReader(out);
  .read()

/// Binario (si usano wrapper)
PipedOutputStream out = new PipedOutputStream();
  .write()
  .flush()

PipedInputStream in = new PipedInputStream(out);
  .read()
```

## SOCKET

Server: crea un `ServerSocket`, si occupa di accettare i `Socket` dei client e avviare i propri `Thread`
Client: crea un `Socket` per connettersi al `ServerSocket` ed esegue le operazioni necessarie
Thread: "partizione" della CPU del server, esegue le operazioni necessarie. Sovrascrive il metodo `run`
