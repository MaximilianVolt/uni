package tests.t01_comparator;

import java.util.Comparator;

public class Main
{
  public static void main(String[] args)
  {
    Test a = new Test(10), b = new Test(15);
    System.out.println(new TestComparator().compare(b, a));
  }
}



class Test
{
  int c;

  public Test(int c)
  {
    this.c = c;
  }
}

class TestComparator implements Comparator<Test>
{
  public int compare(Test a, Test b)
  {
    return b.c - a.c;
  }
}