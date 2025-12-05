package tests.t04_binNumberReader;

public class Main
{
  public static void main(String[] args)
  {
    BinNumberReader r = new BinNumberReader("COURSE\\YEAR_01\\COMPUTER_SCIENCE\\PERSONAL\\JAVA\\tests\\t04_binNumberReader\\in.txt");
    System.out.println(r.getNumber(1));
  }
}
