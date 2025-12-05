# RIPASSO

## TEORIA

### 1. Variabili aleatorie (unidimensionali)

- Qualitative
  - Sconnesse (colore occhi)
  - Ordinali
    - Lineari (valutazione a stelle)
    - Cicliche (mesi)
- Quantitative
  - Discrete
  - Continue

Modalità (sono i singoli valori delle V.A.)

### 2. Distribuzioni

- Distribuzione unitaria
  - Sintesi con distribuzione di frequenze assolute (ripetizioni delle modalità delle V.A., perdita di associazione 1-1)
  - Sintesi con distribuzione di frequenze relative $ \dfrac{m_{i}}{n} $ (perdita di misurazioni effettive)
    - Percentuali ottenute con $ f_{i} * 100 $
  - Frequenze cumulate (vanno da 0 a 1 e sono la somma delle freq. rel.) $ \displaystyle\sum_{i=0}^{k} f_{i} $
- Ditribuzione in classi (intervalli, solo su **V.A. quantitative o qualitative ordinali**)
  - (Stesse sintesi della distr. unitaria)
  - Densità = $ \dfrac{f_{i}}{(c_{i} - c_{i - 1})} $

Funzione di ripartizione empirica:

- Distribuzione di frequenza:
  - Vale $ 0 $ da $ x \lt m_{1} $ e $ 1 $ da $ x \geq m_{k + 1} $
  - Vale $ F_{i} $ per $ m_{i} \leq x \lt m_{i+1},\ i = 1...k $
- Distribuzione in classi:
  - Vale $ 0 $ da $ x \leq c_{0} $
  - Vale $ 1 $ da $ x \geq c_{k} $
  - Vale $ h_{i} * (x - c_{i-1}) - F_{i-1} $

### 3. Indici di sintesi

- Valori medi:
  - **Moda** (maggiore numero di ripetizioni):
    - Dist. freq: $ f_{j} : f_{j} \geq f_{r},\ j,r = 1...k$
    - Dist. classi: $ c_{j} : h_{j} \geq h_{r},\ j,r = 1...k$
  - **Mediana** (valore che divide in parti uguali la distribuzione):
    - Dist. unit.:
      - n pari: $ \dfrac{x_{(\frac{n}{2})} + x_{(\frac{n}{2}+1)}}{2} $
      - n dispari: $ x_{(\frac{n+1}{2})} $
    - Dist. freq.:
      - $ m_{j} : f_{j-1} \lt \dfrac{1}{2} \lt f_{j} $
      - $ \dfrac{m_{j} + m_{j+1}}{2}: f_{j} = \dfrac{1}{2} $
    - Dist. classi:
      1. Trovare la classe mediana $ c_{j} : F_{j-1} \lt \dfrac{1}{2} \leq F_{j} $
      2. Trovare il valore mediano con $ \dfrac{(\frac{1}{2} - F_{j-1})}{h_{j}} + c_{j-1} $
  - **Media** ($ \overline{x} $):
    - Aritmetica (quando tutti i valori hanno lo stesso "peso"):
      - Dist. unitaria: $ \dfrac{\displaystyle\sum_{i=0}^{n} x_{i}}{n} $
      - Dist. freq: $ \displaystyle\sum_{i=0}^{n} f_{i} * m_{i} $
      - Dist. classi: $ \displaystyle\sum_{i=0}^{n} f_{i} * \overline{x}_{i} $
    - Geometrica (grandezze che crescono come i tassi di crescita, il loro prodotto rimane inalterato): $ (\displaystyle\prod_{i=1}^{n} x_{i})^{\frac{1}{n}} $
    - Armonica (grandezze del tipo $ \dfrac{x}{y} $): $ \dfrac{n}{\displaystyle\sum_{i=1}^{n}\dfrac{1}{x_{i}}} $
    - Quadratica (quando interessa l'intensità e non il segno): $ \sqrt{\dfrac{\displaystyle\sum_{i=1}^{n} x_{i}^2}{n}} $

### 4. Proprietà dei valori medi

1. **Consistenza**: se il campione è costante $ x_{i} = a,\ i=1...n \Rightarrow \text{M}(X) = a $
2. **Internalità**: $ x_{(1)} \leq \text{M}(X) \leq x_{(n)} $
3. **Monotonia**:
   - Debole: $ A \prec_{1} B \iff \text{M}(A) \leq \text{M}(B) $
   - Forte: $ A \prec_{1} B \iff \text{M}(A) \lt \text{M}(B) $
4. **Associatività**: siano $ A = (a_{i}),\ B = (b_{j}),\ i = 1...n,\ j = 1...m $ e $ A \cup B = (a_{1...n}, b_{1...m}) $, allora $ \text{M}(A \cup B) = \text{M}(\underbrace{\text{M}(A),\ ...}_{\text{n volte}},\ \underbrace{\text{M}(B),\ ...}_{\text{m volte}}) $

L'associatività della media aritmetica è data dalla seguente caratterizzazione: un valore medio $ \text{M}(...) $ consistente e monotono forte è anche associativo $ \iff \exists \text{U}:\R \rightarrow \R $ invertibile $ :\ \text{M}(x_{1...n}) = \text{U}^{-1}\Bigg(\dfrac{\displaystyle\sum_{i=1}^{n}\text{U}(x_{i})}{n} \Bigg)  $

> ⚠️ Solo la moda NON è monotona, solo le medie sono associative (quindi non moda e mediana)

### 5. Dominanza stocastica

Si tratta di un ordinamento parziale dei campioni:

- Se $ n = m $: $ A \prec_{1} B \iff a_{(i)} \leq b_{(i)}\ \land\ \exists j : a_{(j)} \lt b_{(j)} $
- Se $ n \neq m $: $ A \prec_{1} B \iff F_{n}^{A}(x) \geq F_{m}^{B}(x)\ \land\ \exists \tilde{x} : F_{n}^{A}(\tilde{x}) \gt F_{m}^{B}(\tilde{x}),\ \forall x \in \R $

### 6. Indici di posizione

- **Quartili**: $ \text{Q1} $ ($ \dfrac{1}{4} $ dei valori a sinistra), $ \text{Q2} $ (mediana), $ \text{Q3} $ ($ \dfrac{1}{4} $ dei valori a destra)
- **Quantili**: generalizzano la mediana, di livello $ p \in [0,\ 1] $ sono quei valori $ x_{p} : F_{n}(x_{p}) = p $

### 7. Indici di variabilità

- **Range**: $ x_{(n)} - x_{(1)} $
- **Intervallo interquartile**: $ \text{Q3} - \text{Q1} $
- **Varianza campionaria**:
  - Corretta:
    - Dist. unit.: $ \dfrac{\displaystyle\sum_{i=1}^{n}(x_{i} - \overline{x})^{2}}{n-1} $
    - Dist. freq.: $ \dfrac{\displaystyle\sum_{i=1}^{k}(m_{i} - \overline{x})^{2}n_{i}}{n-1} $
    - Dist. classi: $ \dfrac{\displaystyle\sum_{i=1}^{k}(\overline{x}_{i} - \overline{x})^{2}n_{i}}{n-1} $
  - Distorta (di popolazione): $ \sigma^{2} = \dfrac{(n - 1)s}{n}$
- **Deviazione standard** (scarto quadratico medio):
  - Corretta: $ s = \sqrt{s^2}$
  - Distorta: $ \sigma = \sqrt{\sigma^2}$

### 8. Indice di connessione o dipendenza

Si usa per coppie di V.A. con dati unitari. Si indica con $ n_{ij} $ la frequenza assoluta congiunta della coppia $ (m_{i}^{X}, m_{j}^{Y}) $.

- L'ampiezza campionaria $ n = \displaystyle\sum_{i=1}^{h}\displaystyle\sum_{j=1}^{k}n_{ij} $ (somma delle ripetizioni di tutte le modalità)
- Le **frequenze marginali** ($ h $ righe, $ k $ colonne):
  - Per la X: $ n_{i \cdot} = \displaystyle\sum_{j=1}^{k} n_{ij} $
  - Per la Y: $ n_{\cdot j} = \displaystyle\sum_{i=1}^{h} n_{ij} $
- Le frequenze relative:
  - **Congiunte**: $ f_{ij} = \dfrac{n_{ij}}{n} $
  - Per la X: $ f_{i \cdot} = \dfrac{n_{i \cdot}}{n} $
  - Per la Y: $ f_{\cdot j} = \dfrac{n_{\cdot j}}{n} $
  - **Condizionate** di $ X $ a $ Y = m_{j}^{Y} $: $ f_{i|Y=m_{j}^{Y}},\ i = 1...h $
  - **Condizionate** di $ Y $ a $ X = m_{i}^{X} $: $ f_{j|X=m_{i}^{X}},\ j = 1...k $

Considerando $ n_{ij}^{*} = \dfrac{n_{i \cdot} \cdot n_{\cdot j}}{n} $, in caso di perfetta indipendenza dovremmo osservare:

- $ f_{i \cdot} = f_{i|Y=m_{j}^{Y}}^{*} = \dfrac{n_{ij}^{*}}{n_{\cdot j}} $
- $ f_{\cdot j} = f_{j|X=m_{i}^{X}}^{*} = \dfrac{n_{ij}^{*}}{n_{i \cdot}} $

Si può definire quindi un indice che **"misuri la distanza" tra le coppie della situazione effettiva e quella ipotetica di perfetta indipendenza**:

- $ \chi^{2} = \dfrac{\displaystyle\sum_{i=1}^{h}\displaystyle\sum_{j=1}^{k}(n_{ij} - n_{ij}^{*})^{2}}{n_{ij}^{*}} = n \Bigg(\dfrac{\displaystyle\sum_{i=1}^{h}\displaystyle\sum_{j=1}^{k}n_{ij}^{2}}{n_{i \cdot} \cdot n_{\cdot j}} - 1 \Bigg) $

Si osservi che $ 0 \leq \chi^{2} \leq \chi_{\text{max}}^{2} $, dove $ \chi_{\text{max}}^{2} $ si ottiene nel caso di perfetta dipendenza, ovvero nel caso in cui si abbia una sottomatrice quadrata di dimensioni $ w \times w,\ w = \min(h, k) : \exists ! j_{i} : n_{ij_{i}} \neq 0 \ \land \ n_{ij_{i}} = n_{i \cdot} = n_{\cdot j_{i}} $

- $ \chi_{\text{max}}^{2} = n(w - 1) $
- $ \tilde{\chi}^{2} = \dfrac{\chi^{2}}{\chi_{\text{max}}^{2}} $

Se $ \tilde{\chi}^{2} $ è "vicino" a 0 si ha un caso di indipendenza, altrimenti se è vicino a 1 si ha un caso di dipendenza stocastica. Se si trova nel mezzo, non è possibile trarne una conclusione.

### 9. Covarianza campionaria

Serve a calcolare la varianza su due V.A., ovvero la **prevalenza di coppie con scarti dalle medie di segno concorde**:

- $ \sigma_{xy} = \dfrac{\displaystyle\sum_{i=1}^{n}(x_{i}-\overline{x})(y_{i}-\overline{y})}{n} = \dfrac{\displaystyle\sum_{i=1}^{n}x_{i} \cdot y_{i}}{n} - \overline{x} \cdot \overline{y}$

### 10. Nuvola campionaria

- $ \sigma_{xy} \gt 0 $: **Trend positivo** (coppie prev. nel I° e III° quadrante)
- $ \sigma_{xy} \lt 0 $: **Trend negativo** (coppie prev. nel II° e IV° quadrante)
- $ \sigma_{xy} = 0 $: **Nessun trend** (equipresenti nei quadranti, dati incorrelati)

Proposizione:

$ -\sigma_{x}\sigma_{y} \leq \sigma_{xy} \leq \sigma_{x}\sigma_{y} $

Dove, appunto:

- $ \sigma_{x} = \sqrt{\sigma_{x}^{2}} = \sqrt{\dfrac{\displaystyle\sum_{i=1}^{n}(x_{i}-\overline{x})^{2}}{n}} $ (deviazione standard per X)
- $ \sigma_{y} = \sqrt{\sigma_{y}^{2}} = \sqrt{\dfrac{\displaystyle\sum_{i=1}^{n}(y_{i}-\overline{y})^{2}}{n}} $ (deviazione standard per Y)

Si definisce l'indice di correlazione $ \rho_{xy} = \dfrac{\sigma_{xy}}{\sigma_{x}\cdot\sigma_{y}},\ \rho_{xy} \in [-1,\ 1] $

Proposizione:

- $ \rho_{xy} = 1 \iff \exists a \gt 0,b : Y = aX + b $ e si dice che i dati sono perfettamente allineati con la retta positiva
- $ \rho_{xy} = -1 \iff \exists a \lt 0,b : Y = aX + b $ e si dice che i dati sono perfettamente allineati con la retta negativa
- $ \rho_{xy} = 0 \iff \sigma_{xy} = 0 $, e non c'è trend

### 11. Regressione lineare

Indica la dipendenza tra due V.A. quantitative del tipo $ Y = aX + b + Z $, con:

- $ Y $: variabile dipendente
- $ X $: variabile indipendente
- $ Z $: variabile inosservabile di rumore

Proposizione: si cerca di stimare i coefficienti $ \hat{a},\ \hat{b} $ tale che la retta $ y = \hat{a}x + \hat{b} $ sia il più possibile vicino alle coppie del campione (usando la minima distanza tra punti e "retta dei minimi quadrati"), che risultano essere $ \hat{a} = \dfrac{\sigma_{xy}}{\sigma_{x}^{2}},\ \hat{b} = \overline{y} - \hat{a}\overline{x} $

### 12. Retta di regressione

Si definisce la retta di regressione la retta:

- $ Y^{*} = \hat{a}X + \hat{b} $, con $ \hat{a} = \dfrac{\sigma_{xy}}{\sigma_{x}^{2}},\ \hat{b} = \overline{y} - \hat{a}\overline{x} $

Osservazioni:

  1. $ \hat{a}\overline{x} + \hat{b} = \overline{y} $ (la retta passa per il baricentro della nuv. camp.)
  2. La media $ \dfrac{\displaystyle\sum_{i=1}^{n}y_{i}^{*}}{n} = \overline{y} $, cioè $ y_{i}^{*} $ e $ y_{i} $ hanno la stessa media

### 13. Indice di bontà del modello lineare

Si definisce $ R^{2} = \rho_{xy}^{2},\ R^{2} \in [0,\ 1] $.

Più è alto $ R^{2} $ più i dati originali sono vicini all'essere allineati, indicando quindi un'alta "affidabilità" del modello lineare. In alcuni casi è possibile modificare il modello per ottenere un $ R^{2} $ più elevato tramite un cambiamento di scala.

### 14. Cambiamenti di scala su modelli lineari

In generale, se si vuole ottenre un modello non lineare del tipo: $ Y^{*} = g(aX + b) $, con $ g $ invertibile:

1. Si applica $ g^{-1} $: $ g^{-1}(Y^{*}) = aX + b $
2. Con le coppie $ (x_{i},\ g^{-1}(y_{i})) $ si stimano $ \hat{a},\ \hat{b} $ con il metodo dei minimi quadrati
3. Si ottengono i valori teorici $ y_{i}^{*} = g(\hat{a}x_{i} + \hat{b}) $

I modelli di regressione, lineari e non, si usano per fare delle previsioni, cioè il calcolo del modello in corrisponenza a particolari valori $ \tilde{x} $ della V.A. indipendente $ X $

Si suddividono in:

- Modello **lineare semplice**: Previsione $ E(Y|X=\tilde{x}) = \hat{a}\tilde{x} + \hat{b} $
- Modello **con cambiamento di scala**: Previsione $ E(Y|X=\tilde{x}) = g(\hat{a}\tilde{x} + \hat{b}) $

La previsione è attendibile solo se $ x_{(1)} \leq \tilde{x} \leq x_{(n)} $.

&nbsp;

## PRATICA

### BASI ELABORAZIONE

1. Lettura dati:

   ```r
   DATI = read.table("PERCORSO_FILE", header = T)
   ```

2. Suddivisione dei dati in classi:

   ```r
   # Vettore con gli estremi
   classi = cut(DATI, breaks = c(...))

   # Include l'estremo più a sinistra
   classi = cut(DATI, breaks = c(...), include.lowest = T)
   ```

3. Campioni:

   ```r
   # Al più 100 elementi di DATI
   campione = sample(DATI, 100, replace = F)

   # Al più 100 elementi t.c. FN(x) == TRUE
   campione = sample(which( FN(DATI) ), 100, replace = F)
   ```

4. Tabella frequenze assolute, relative e cumulate:

   ```r
   frequenze.abs = table(DATI_UNITARI_O_CLASSI)
   frequenze.rel = frequenze.abs / length(DATI_UNITARI_O_CLASSI)
   frequenze.cum = cumsum(frequenze.rel)
   ```

5. Tabella frequenze congiunte e condizionate:

   ```r
   frequenze.abs = table(X, Y)
   frequenze.cong = prop.table(frequenze.abs)
   frequenze.cond = prop.table(frequenze.abs, INDICE_Y) # In questo caso vale 2

   frequenze = ...

   # Per filtrare in base a modalità specifiche:
   frequenze[MOD_RIGA, ]
   frequenze[, MOD_COLONNA]
   ```

6. Intervalli:

   ```r
   # Tutti i valori interi tra A e B
   intervallo = A:B

   # Vettore di tutti gli STEP da A a B 
   intervallo = seq(from = A, to = B, by = STEP)
   ```

7. Dati qualitativi:

   ```r
   # Ottiene i livelli
   livelli = levels(DATI)

   # Imposta i livelli
   DATI = ordered(DATI, levels = c("LIVELLO 1", "LIVELLO 2", "LIVELLO 3"))
   ```

### STATISTICHE DESCRITTIVE

1. Quantili:

   ```r
   # p in [0, 1]
   q = quantile(DATI, p)

   # Calcola i quantili di tutti i livelli specificati
   estremi = quantile(DATI, c(...))

   # Versione generica (incluso indice = 1)
   quantile_classe = function(Fn, Fi, h) {
     i = min(which(Fi >= Fn))
     gt1 = i > 1
     (Fn - Fi[i - gt1] * gt1) / h$density[i] + h$breaks[i]
   }

   quantile_classe(LVL_QUANT, FREQ_CUM, ISTOGRAMMA)
   ```

2. Moda, media, mediana:

   ```r
   moda = function(x) {
     names(which.max(table(x)))
   }

   moda_classi = function(x, h) {
     names(table(cut(x, breaks = h$breaks, include.lowest = ...)))[which.max(h$density)]
   }

   media = mean(DATI)
   media_classe = sum(ISTOGRAMMA$mids * ISTOGRAMMA$counts) / sum(ISTOGRAMMA$counts) 
   
   # Dati numerici
   mediana = median(DATI)
   mediana_classe = ... # Quantile di livello .5

   # Dati qualitativi
   indice_mediana = meadian(as.numeric(DATI_ORDINATI))
   mediana = levels(DATI_ORDINATI)[indice_mediana]
   ```

3. Indice di dipendenza $ \chi^{2} $:

   ```r
   tabella = table(X, Y)
   sommario = summary(tabella)
   chi2.abs = sommario$statistic

   # Frequenze assolute
   dimensione = sommario$n.cases

   # Frequenze condizionate
   dimensione = length(X)

   chi2.max = dimensione * (min(dim(tabella)) - 1)
   chi2.rel = chi2.abs / chi2.max
   ```

4. Varianza $ s^{2} $:

   ```r
   varianza = var(DATI_UNITARI)

   varianza_classe = sum((ISTOGRAMMA$mids - MEDIA_CLASSE) ^ 2) * ISTOGRAMMA$counts / (sum(ISTOGRAMMA$counts) - 1)
   ```

5. Deviazione standard $ s $:

   ```r
   devstd = sqrt(varianza)
   ```

6. Indice $ R^{2} $:

   ```r
   cor(x, FN_INV(y)) ^ 2
   ```

7. Previsioni $ E(Y|X=\tilde{x}) $:

   ```r
   modello = lm(FN_INV(y) ~ x)
   sommario = summary(modello)
   x_previsioni = ... # Vettori con le ascisse dove effettuare le previsioni
   previsioni = FN(predict(modello, data.frame(x = x_previsioni)))
   ```

### GRAFICI

1. Funzione di ripartizione empirica:

   ```r
   func = ecdf(DATI)
   plot(func)
   ```

2. Istogramma:

   ```r
   h = hist(DATI, breaks = ..., include.lowest = ...)
   ```

3. Boxplot:

   ```r
   boxplot(X)
   ```

4. Boxplot multipli:

   ```r
   boxplot(Y ~ X, varwidth = T)
   ```

5. Frequenze cumulate:

   ```r
   plot(ESTREMI, c(0, FREQ_CUM_1), type = "l", col = "#F88")
   points(ESTREMI, c(0, FREQ_CUM_2), type = "l", col = "#88F")
   ```

6. Linea di regressione:

   ```r
   model = lm(y ~ x)
   plot(x, y)
   abline(model, col = "#88F")
   ```
