package _01_ASSIGNMENTS.ex02_arrays;



import java.util.Scanner;



public class Main
{
  public static Scanner kb = new Scanner(System.in);

  public static void main(String[] args)
  {
    // Ex. 1
    long x;
    Vector v = ExerciseSet.ex01create(4, 3);

    // Ex. 2
    System.out.println("Vector creation");
    System.out.println(ExerciseSet.ex02toString(v));

    do
    {
      System.out.print("\nEnter a positive value: ");
      x = kb.nextInt();
    }
    while (x < 0);

    // Ex. 4
    System.out.print("\nCount of " + x + ": ");
    System.out.println(ExerciseSet.ex04count(v, x));

    // Ex. 5
    System.out.print("\nAverage of numbers above " + x + ": ");
    System.out.println(ExerciseSet.ex05avrgAbove(v, x));

    // Ex. 6
    System.out.print("\nIndex search of " + x + ": ");
    System.out.println(ExerciseSet.ex06search(v, x));

    // Ex. 7
    System.out.print("\nMax below " + x + ": ");
    System.out.println(ExerciseSet.ex07maxBelow(v, x));

    v.invert();
    System.out.println(v);
  }
}



class ExerciseSet
{
  public static Vector ex01create(int n, long limit)
  {
    return new Vector(n, limit);
  }



  public static String ex02toString(Vector v)
  {
    return v.toString();
  }



  public static int ex04count(Vector v, long n)
  {
    int count = 0;

    for (long x : v.values)
      count += x == n ? 1 : 0;

    return count;
  }



  public static double ex05avrgAbove(Vector v, long n)
  {
    int count = 0;
    double avrg = 0;

    for (long x : v.values)
    {
      if (x <= n)
        continue;

      avrg += x;
      ++count;
    }

    return (count > 0)
      ? avrg / count
      : 0
    ;
  }


  



  public static int ex06search(Vector v, long n)
  {
    for (int i = 0; i < v.values.length; ++i)
      if (v.values[i] == n)
        return i;

    return -1;
  }

  public static long ex07maxBelow(Vector v, long n)
  {
    long max = Integer.MIN_VALUE;

    for (long x : v.values)
      if (x > max && x < n)
        max = x;

    return max;
  }



  


}



class Vector
{
  public long values[];

  public Vector(int n, long limit)
  {
    if (n < 1)
      return;

    values = new long[n];

    while (n-- > 0)
      values[n] = (long) (Math.random() * limit);
  }

  // Ex. 3
  public String toString()
  {
    return "[" + valuesToString() + "]";
  }

  public String valuesToString()
  {
    String s = "";
    int size = values.length - 1;

    for (int i = 0; i < size; ++i)
      s += values[i] + ", ";

    s += values[size];

    return s;
  }

  public void invert()
  {
    long tmp; int j = values.length - 1;

    for (int i = (j >> 1) + 1; i <= j; ++i)
    {
      tmp = values[i];
      values[i] = values[j - i];
      values[j - i] = tmp;
    }
  }
}
