package _01_ASSIGNMENTS.ex01_instructions;



import java.util.Scanner;



/**
 * @version Java v23.0.2
 */

public class Main
{
  public static Scanner kb = new Scanner(System.in);

  public static void main(String[] args)
  {
    // Ex. 4
    System.out.println("Positive number input");
    System.out.println("Enter x");
    long x = ExerciseSet.ex04readPositive();
    System.out.println("Enter y");
    long y = ExerciseSet.ex04readPositive();

    // Ex. 1
    System.out.println("\nOdd/Even - if statement");
    System.out.println(ExerciseSet.ex01isEven(x));

    System.out.println("\nOdd/Even - ternary operator");
    System.out.println(ExerciseSet.ex01bisIsEven(x));

    System.out.println("\nOdd/Even - bitwise");
    System.out.println(ExerciseSet.ex01extraIsEven(x));

    // Ex. 2
    System.out.println("\nHexStr to val - switch statement");
    System.out.println(ExerciseSet.ex02char2Hex('a'));

    System.out.println("\nHexStr to val - switch expression");
    System.out.println(ExerciseSet.ex02extraChar2Hex('d'));

    System.out.println("\nHexStr to val - Byte.parseByte()");
    System.out.println(ExerciseSet.ex02extra2Char2Hex('3'));

    // Ex. 3
    System.out.println("\nGCD");
    System.out.println(ExerciseSet.ex03gcd(x, y));

    // Ex. 5
    System.out.println("\nFactorial");
    System.out.println(ExerciseSet.ex05factorial(x));

    kb.close();
  }
}



class ExerciseSet
{
  public static boolean ex01isEven(long x)
  {
    if ((x & 1) == 0)
      return true;

    return false;
  }

  public static boolean ex01bisIsEven(long x)
  {
    return (x & 1) == 0
      ? true
      : false
    ;
  }

  public static boolean ex01extraIsEven(long x)
  {
    return (x & 1) == 0;
  }



  public static byte ex02char2Hex(char c)
  {
    switch (c)
    {
      case '0': return 0;
      case '1': return 1;
      case '2': return 2;
      case '3': return 3;
      case '4': return 4;
      case '5': return 5;
      case '6': return 6;
      case '7': return 7;
      case '8': return 8;
      case '9': return 9;

      case 'A':
      case 'a':
        return 10;

      case 'B':
      case 'b':
        return 11;

      case 'C':
      case 'c':
        return 12;

      case 'D':
      case 'd':
        return 13;

      case 'E':
      case 'e':
        return 14;

      case 'F':
      case 'f':
        return 15;

      default:
        return -1;
    }
  }

  public static byte ex02extraChar2Hex(char c)
  {
    return switch (c)
    {
      case '0' -> 0;
      case '1' -> 1;
      case '2' -> 2;
      case '3' -> 3;
      case '4' -> 4;
      case '5' -> 5;
      case '6' -> 6;
      case '7' -> 7;
      case '8' -> 8;
      case '9' -> 9;
      case 'A' -> 10;
      case 'a' -> 10;
      case 'B' -> 11;
      case 'b' -> 11;
      case 'C' -> 12;
      case 'c' -> 12;
      case 'D' -> 13;
      case 'd' -> 13;
      case 'E' -> 14;
      case 'e' -> 14;
      case 'F' -> 15;
      case 'f' -> 15;
      default -> -1;
    };
  }

  public static byte ex02extra2Char2Hex(char c)
  {
    return Byte.parseByte(String.valueOf(c), 16);
  }



  public static long ex03gcd(long a, long b)
  {
    long r = 0;

    while (b != 0)
    {
      r = a % b;
      a = b;
      b = r;
    }

    return Math.abs(a);
  }



  public static long ex04readPositive()
  {
    long x;

    do
    {
      System.out.print("Enter a positive number: ");
      x = Main.kb.nextInt();
    }
    while (x <= 0);

    System.out.println("Read: " + x);

    return x;
  }



  public static long ex05factorial(long x)
  {
    long f = x > 0 ? x : 1;

    while (x > 1)
      f *= --x;

    return f;
  }
}
