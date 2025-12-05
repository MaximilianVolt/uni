package tests.t03_package.pkg2;

import tests.t03_package.pkg1.*;

public class Main
{
  public static void main(String[] args)
  {
    Test[] tests = new Test[] { new TestChild1(), new TestChild2() };

    for (Test instp2 : tests)
      instp2.method();
  }
}
