int main()
{
  // Crea stanza (assegna solo i valori)
  Stanza* stanza = crea_stanza();

  // Collega la stanza alla lista
  ultima_stanza->stanza_successiva = stanza;

  // Collega la stanza nella mappa
  stanza_collega(ultima_stanza, stanza, direzione);
}