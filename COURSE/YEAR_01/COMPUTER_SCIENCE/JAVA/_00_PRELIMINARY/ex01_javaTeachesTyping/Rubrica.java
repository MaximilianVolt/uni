package _00_PRELIMINARY.ex01_javaTeachesTyping;



public class Rubrica
{
  private int n_contatti = 0;
  private final Contatto contatti[];
  public final int MAX_CONTATTI = 100;

  public Rubrica()
  {
    contatti = new Contatto[MAX_CONTATTI];
  }

  public void aggiungiContatto(Contatto c)
  {
    if (n_contatti >= MAX_CONTATTI)
      return;

    contatti[n_contatti++] = c;
  }

  @Override
  public String toString()
  {
    StringBuilder sb = new StringBuilder();

    for (int i = 0; i < n_contatti; ++i)
      sb.append(contatti[i]).append("\n");
    
    return sb.toString();
  }
}
