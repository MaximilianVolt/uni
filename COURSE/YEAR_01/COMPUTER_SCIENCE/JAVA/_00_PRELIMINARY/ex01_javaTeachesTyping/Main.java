package _00_PRELIMINARY.ex01_javaTeachesTyping;



public class Main
{
  public static void main(String[] args)
  {
    Rubrica r = new Rubrica();
    Contatto c = new Contatto("Piero", "Angela");

    r.aggiungiContatto(c);

    System.out.println(r);
  }
}
