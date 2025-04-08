# APPUNTI ARCHITETTURA DEGLI ELABORATORI

## 25/02/25 - INTRODUZIONE

Un calcolatore è una macchina/dispositivo in grado di eseguire calcoli in modo automatico.
Prende in ingresso informazioni, elabora queste ultime seguendo le regole stabilite da una lista di istruzioni macchina e manda in uscita i risultati dell'elaborazione.

La lista di istruzioni macchina definisce il programma che risiede in memoria.

## 26/02/25 - BASI, CODIFICHE E CONVERSIONI

### NOTAZIONE POSIZIONALE

Notazione adatta alla rappresentazione dei numeri.
Si ha:

- una base di riferimento **B**
- un insieme di **B** caratteri per la rappresentazione dei numeri (cifre)
- che il valore attribuito a ogni cifra dipende dalla sua posizione

Esempi:

- ***1023** (10)*
- ***10100***

Un numero A di n cifre in base **B** si scrive come
a[n - 1] a[n - 2] ... a[1] a[0] (**B**)

## 25/03/25

### Livello RTL (Register Transfer Language) *(livello funzionale)*

Base: registri, memoria, bus, ALU

Micro-operazione: l'insieme di azioni stabilite durante l'esecuzione di un'istruzione che si esaurisce durante un tick di clock.

Esempio: trasferimento del contenuto tra due registri

Registro A: [...]
Registro B: [...]

Logica di controllo: quando un predicato **P** è vero, si procede con l'istruzione

**P**: A <- B

| SIMBOLO | DESCRIZIONE | ESEMPIO |
| --------------------- | - | - |
| {\<maiusc> \| \<numero>} | Contenuno di un registro | `A`, `B`, `M3` |
| \<pedice> | Bit specifico | `A2` ("2" pedice), `Bi` |
| `<-` | Trasferimento | `A <- B` |
| `:` | Terminazione di una funzione di controllo | `P:` |
| `,` | Separatore tra due micro-operazioni eseguite in parallelo nello stesso ciclo di clock | `A <- B, C <- D` |

`P: A <- B`

```js
A: [ | | | ] <- P
    ^ ^ ^ ^
B: [ | | | ]
```
