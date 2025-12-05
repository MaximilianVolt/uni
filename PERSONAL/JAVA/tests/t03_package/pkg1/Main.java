package tests.t03_package.pkg1;

import tests.t03_package.pkg2.*;

public class Main
{
  public static void main(String[] args)
  {
    Test[] tests = new Test[] { new TestChild1(), new TestChild2() };

    for (Test instp1 : tests)
      instp1.method();
  }
}
