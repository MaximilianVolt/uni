/**
 * @desc
 * Write a Java program that prints "Hello, world!".
 */



package _00_PRELIMINARY.ex00_sanityCheck;



import java.util.ArrayList;



public class Main
{
  // private static final transient int property = 1;

  public static void main(String[] args)
  {
    int a = 2;
    int b = switch (a) {
      case 1 -> 4;
      case 2 -> 50;
      default -> throw new IllegalStateException();
    };

    // Stream<String> stream = Stream.of("Test", "A", String.valueOf(b), "C");
    // stream
    //   .filter(item -> item.length() > 1)
    //   .forEach(Main::f);

    // switch (a)
    // {
    //   case 1: break;
    // }

    Benchmark bm = new Benchmark();

    bm.start();
    System.out.println(power(2, 15));
    // System.out.println(power(1.00000000000001, Long.MAX_VALUE / 130l + 86_033_030_894_397l));
    // System.out.println(powerslow(1.00000000000001, 8_000_000_000l));
    System.out.println(bm.elapsed());
    System.out.println(bm.elapsedMillis());
    // System.out.println(sum(1, 100));
    // System.out.println(factorial(5));
  }

  public static byte sign(double x)
  {
    return (byte) ((x > 0 ? 1 : 0) - (x < 0 ? 1 : 0));
  }

  public static double abs(double x)
  {
    return x * sign(x);
  }

  public static synchronized int f(String s)
  {
    System.out.println(s + " - Called by method f");
    int x = 0;

    if (x == 0)
      if (x > 0)
        x = 0;
      else
        x = 1;
    else
      x = 2;

    return 1;
  }

  public static double power(double n, long k)
  {
    if (k == 0 || n == 1)
      return 1;

    if (n == 0)
      return 0;

    if (k < 0)
    {
      n = 1 / n;
      k = -k;
    }

    if (k == 1)
      return n;

    return power(n * n, k >> 1) * (
      (k & 1) == 1
        ? n
        : 1
    );
  }

  public static double powerslow(double n, long k)
  {
    double base = n;

    for (long e = 0; e < k; ++e)
      n *= base;

    return n;
  }

  public static long factorial(long k)
  {
    return k < 2
      ? 1
      : k * factorial(k - 1)
    ;
    //if (k < 2)
     // return 1;

    //return k * factorial(k - 1);
  }

  public static long sum(long a, long b)
  {
    return (b - a + 1) * (a + b) >> 1;
  }
}

class Benchmark
{
  public boolean ongoing = false;
  public long start;
  public long end;

  public Benchmark()
  {}

  public void start()
  {
    ongoing = true;
    start = System.currentTimeMillis();
  }

  public void stop()
  {
    ongoing = false;
    end = System.currentTimeMillis();
  }

  public long elapsedMillis()
  {
    return ongoing
      ? System.currentTimeMillis() - start
      : end - start
    ;
  }

  public String elapsed()
  {
    long ms = elapsedMillis();
    long s = ms / 1000;
    long m = s / 60;
    long h = m / 60;
    long d = h / 24;

    long times[] = { d, h % 24, m % 60, s % 60, ms % 1000 };
    String timeStrings[] = { "d ", "h ", "m ", "s ", "ms" };
    String time = "";
    int start;

    for (start = 0; start < times.length - 1; ++start)
      if (times[start] > 0)
        break;

    for (int i = start; i < times.length; ++i)
      time += times[i] + timeStrings[i];

    return time;
  }

  public static void method()
  {
    ArrayList<Thread> list = new ArrayList<Thread>(10);

    for (int i = list.size() - 1; i >= 0; --i)
      if (list.get(i) == null)
        list.remove(i);
  }
}
