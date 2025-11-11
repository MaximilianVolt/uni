namespace Program
{
  class Program
  {
    public static void Main()
    {
      int age;
      Console.Write("Input your age: ");
      age = Convert.ToInt32(Console.ReadLine());
      Console.WriteLine("Your anhaerobic treshold is: {0}", 220 - age);
    }
  }
}
