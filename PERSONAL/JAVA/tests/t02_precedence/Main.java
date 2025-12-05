package tests.t02_precedence;

public class Main
{
  public static void main(String[] args) {
    // 1
    System.out.println(new String("ciao").toUpperCase());

    // 2
    String[] arr = new String[5];
    System.out.println(arr.length);

    // 3
    // System.out.println("Risultato: " + new Integer(5) + 1);

    // 4
    // System.out.println((new Integer(5)) + 1);

    // 5
    System.out.println((new int[3])[1]);

    // 6
    String str = new String("test" + "ing");
    System.out.println(str);

    // 7
    Object o = new Object();
    System.out.println(o == new Object());

    // 8
    System.out.println(new int[]{1,2,3}[0] + new int[]{4,5}[1]);

    // 2 - new usato due volte in una singola espressione
    System.out.println(new String("A") + new String("B"));

    // 3 - new con accesso a metodo
    System.out.println(new String("ciao").substring(1));

    // 4 - new con array + accesso a elemento
    System.out.println(new int[]{10, 20, 30}[1]);

    // 5 - Due livelli di new
    class Wrapper {
        String s;
        Wrapper(String s) { this.s = s; }
    }
    System.out.println((new Wrapper(new String("ok"))).s);

    // 6 - new con ternario (ambiguità evitata con parentesi)
    // System.out.println(true ? new String("yes") : new String("no"));

    // 7 - new con assegnamento multiplo (attenzione alla lettura a destra o sinistra)
    String x, y;
    x = y = new String("cat");
    System.out.println(x + y);

    // 8 - new con chiamata metodo e operazione
    int len = new String("hello").concat("!").length();
    System.out.println(len);
  }
}