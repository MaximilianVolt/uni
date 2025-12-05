package _01_ASSIGNMENTS.ex08_files;

import java.io.*;
import java.util.Scanner;

public class Main
{
  public static final String folder = "COURSE\\YEAR_01\\COMPUTER_SCIENCE\\JAVA\\_01_ASSIGNMENTS\\ex08_files\\";
  public static void main(String args[]) throws IOException
  {
    String filename = "file.txt";
    printOnFile(filename);
    // System.out.printf("Average for file %s is %.2f", filename, avrg(filename));
  }
    


  /**
   * 
   * @param filename
   * @return
   */

  public static double avrg(String filename)
  {
    int count = 0;
    double sum = 0;

    try (
      BufferedReader br = new BufferedReader(new FileReader(Main.folder + filename))
    ) {
      String line;

      while ((line = br.readLine()) != null)
      {
        try {
          sum += Double.parseDouble(line);
          ++count;
        }
        catch (NumberFormatException ex) {
          System.err.println("Unexpected non-number string received");
        }
      }
    }
    catch (IOException ex) {
      System.err.println(ex.getMessage());
    }

    if (count == 0)
      System.out.println("File had no numeric values");

    return count > 0
      ? sum / count
      : 0
    ;
  }



  public static void printOnFile(String filename)
  {
    try (
      PrintWriter out = new PrintWriter(Main.folder + filename);
      Scanner sc = new Scanner(System.in)
    ) {
      String text = "";

      while (!(text = sc.nextLine()).isEmpty()) {
        out.write(text);
      }
    }
    catch (FileNotFoundException e) {
      System.err.println("File not found.");
    }
  }
}
