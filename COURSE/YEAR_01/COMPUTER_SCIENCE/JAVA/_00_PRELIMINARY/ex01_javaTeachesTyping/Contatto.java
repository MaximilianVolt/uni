package _00_PRELIMINARY.ex01_javaTeachesTyping;



public class Contatto extends Object
{
  private final String nome;
  private final String cognome;

  public Contatto(String nome, String cognome)
  {
    this.nome = nome;
    this.cognome = cognome;
  }

  @Override
  public String toString()
  {
    return new StringBuilder()
      .append("<| Nome: ")
      .append(this.nome)
      .append(" | Cognome: ")
      .append(this.cognome)
      .append(" |>")
    .toString();
  }
}
