DROP DATABASE ProlocoGaicheFontana;

CREATE DATABASE ProlocoGaicheFontana;

USE ProlocoGaicheFontana;

CREATE TABLE UnitaProdotto (
  id INT(2) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  descrittore VARCHAR(16) NOT NULL
);

CREATE TABLE CategoriaProdotto (
  id INT(2) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  descrittore VARCHAR(32) NOT NULL
);

CREATE TABLE CategoriaEvento (
  id INT(2) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  descrittore VARCHAR(80) NOT NULL
);

CREATE TABLE Fornitore (
  id INT(2) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  descrittore VARCHAR(80) NOT NULL
);

CREATE TABLE IVA (
  id INT(2) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  iva_percentuale INT(2) UNSIGNED NOT NULL UNIQUE
);

CREATE TABLE Allergene (
  id INT(2) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  descrittore VARCHAR(80) NOT NULL
);

CREATE TABLE Menu (
  id INT(6) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  nome VARCHAR(80) NOT NULL,
  note VARCHAR(512)
);

CREATE TABLE Evento (
  id INT(6) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  id_menu INT(6) UNSIGNED NOT NULL,
  id_categoria INT(2) UNSIGNED NOT NULL,
  ha_spettacolo BOOLEAN,
  inizio DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
  fine DATETIME,
  note VARCHAR(256),

  FOREIGN KEY (id_categoria) REFERENCES CategoriaEvento(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_menu) REFERENCES Menu(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  CHECK (fine IS NULL OR inizio < fine)
);

-- ID here should NOT have AUTO_INCREMENT, this allows to have customizable ID's for eg menu printing
CREATE TABLE Prodotto (
  id INT(4) UNSIGNED PRIMARY KEY,
  id_categoria INT(2) UNSIGNED NOT NULL,
  descrittore VARCHAR(80) NOT NULL,

  FOREIGN KEY (id_categoria) REFERENCES CategoriaProdotto(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT
);

CREATE TABLE Prezzo (
  id INT(8) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  id_prodotto INT(4) UNSIGNED NOT NULL,
  valore DECIMAL(7, 2) NOT NULL,
  data_inserzione DATETIME DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (id_prodotto) REFERENCES Prodotto(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  UNIQUE KEY (id_prodotto, data_inserzione),

  CHECK (valore >= 0)
);

CREATE TABLE AllergeneProdotto (
  id_prodotto INT(4) UNSIGNED,
  id_allergene INT(2) UNSIGNED,

  FOREIGN KEY (id_prodotto) REFERENCES Prodotto(id)
    ON UPDATE CASCADE
    ON DELETE CASCADE,

  FOREIGN KEY (id_allergene) REFERENCES Allergene(id)
    ON UPDATE CASCADE
    ON DELETE CASCADE,

  PRIMARY KEY (id_prodotto, id_allergene)
);

CREATE TABLE Fornitura (
  id INT(6) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  id_fornitore INT(2) UNSIGNED NOT NULL,
  data_ordine DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,

  FOREIGN KEY (id_fornitore) REFERENCES Fornitore(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT
);

CREATE TABLE FornituraProdotto (
  id INT(8) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  id_fornitura INT(6) UNSIGNED NOT NULL,
  id_prodotto INT(4) UNSIGNED NOT NULL,
  id_prezzo INT(8) UNSIGNED NOT NULL,
  id_unita INT(2) UNSIGNED NOT NULL,
  id_iva INT(2) UNSIGNED NOT NULL,
  sconto_percentuale INT(2) UNSIGNED NOT NULL DEFAULT 0,
  qta DECIMAL(7, 2) NOT NULL DEFAULT 1,

  FOREIGN KEY (id_fornitura) REFERENCES Fornitura(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_prodotto) REFERENCES Prodotto(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_prezzo) REFERENCES Prezzo(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_unita) REFERENCES UnitaProdotto(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_iva) REFERENCES IVA(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  CHECK (
    qta > 0
    AND sconto_percentuale <= 100
  )
);

CREATE TABLE MenuProdotto (
  id_menu INT(6) UNSIGNED,
  id_prodotto INT(4) UNSIGNED,
  id_prezzo INT(8) UNSIGNED NOT NULL,

  FOREIGN KEY (id_menu) REFERENCES Menu(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_prodotto) REFERENCES Prodotto(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_prezzo) REFERENCES Prezzo(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  PRIMARY KEY (id_menu, id_prodotto)
);

CREATE TABLE Ordine (
  id INT(8) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  id_evento INT(6) UNSIGNED NOT NULL,
  numero_coperti INT(3) UNSIGNED NOT NULL DEFAULT 1,
  tracui_bambini INT(3) UNSIGNED DEFAULT 0,
  tracui_anziani INT(3) UNSIGNED DEFAULT 0,

  FOREIGN KEY (id_evento) REFERENCES Evento(id)
    ON UPDATE CASCADE
    ON DELETE CASCADE,

  CHECK (
    numero_coperti > 0
    AND tracui_bambini + tracui_anziani <= numero_coperti
  )
);

CREATE TABLE OrdineProdotto (
  id INT(10) UNSIGNED PRIMARY KEY AUTO_INCREMENT,
  id_ordine INT(8) UNSIGNED NOT NULL,
  id_prodotto INT(4) UNSIGNED NOT NULL,
  id_prezzo INT(8) UNSIGNED NOT NULL,
  qta INT(4) UNSIGNED NOT NULL DEFAULT 1,
  note VARCHAR(256),

  FOREIGN KEY (id_ordine) REFERENCES Ordine(id)
    ON UPDATE CASCADE
    ON DELETE CASCADE,

  FOREIGN KEY (id_prodotto) REFERENCES Prodotto(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  FOREIGN KEY (id_prezzo) REFERENCES Prezzo(id)
    ON UPDATE CASCADE
    ON DELETE RESTRICT,

  CHECK (qta > 0)
);



-- Data insertion
INSERT INTO IVA (iva_percentuale)
VALUES (4), (10), (22);

INSERT INTO `Allergene` (descrittore)
VALUES ("Cereali e derivati"), ("Crostacei"), ("Uova"), ("Pesce"),
  ("Arachidi"), ("Soia"), ("Latte"), ("Frutta a guscio"),
  ("Sedano"), ("Senape"), ("Sesamo"), ("Anidride solforosa e solfiti"),
  ("Lupini"), ("Molluschi")
;

INSERT INTO `CategoriaEvento` (descrittore)
VALUES ("Sagra"), ("Pranzo pro-loco"), ("Cena pro-loco"), ("Pranzo pubblico"), ("Cena pubblica"),
  ("Pranzo su prenotazione"), ("Cena su prenotazione"), ("Compleanno"), ("Prenotazione privata")
;

INSERT INTO `Fornitore` (descrittore)
VALUES ("Bussolini"), ("EuroSpIn Tavernelle");

INSERT INTO `UnitaProdotto` (descrittore)
VALUES ("Pz"), ("Kg"), ("L");
