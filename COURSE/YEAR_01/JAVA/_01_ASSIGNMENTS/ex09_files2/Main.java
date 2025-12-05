package _01_ASSIGNMENTS.ex09_files2;

import java.io.*;

public class Main {
  public static final String PATH = "COURSE\\YEAR_01\\COMPUTER_SCIENCE\\JAVA\\_01_ASSIGNMENTS\\ex09_files2\\";

  public static void main(String[] args) {
    String filename = "file.txt";
    String filename2 = "numbers.txt";
    int mark = 18;
    int n = 14;

    // Ex. 1
    try {
      System.out.printf(
        "The number of students with a mark greater than %d is: %d",
        mark,
        studentsWithGradeOrMore(filename, mark)
      );
    }
    catch (IOException e) {
      System.out.println("Something went wrong");
    }

    // Ex. 2
    System.out.printf(
      "\n\nFile %s contains (?) a number divisible by %d: %b\n\n",
      filename,
      n,
      containsNumberDivisibleBy(filename, n)
    );

    // Ex. 3
    try {
      System.out.printf("\n\nFile contains only numbers: %b\n\n", hasOnlyIntType(filename2));
    }
    catch (IOException e) { }

    // Ex. 4
    // !: May not work, because it *needs* a binary file
    try {
      System.out.printf(
        "File contains (?) lines of length %d or more: %b",
        n,
        hasStringOfLengthOrGreater(filename, n)
      );
    }
    catch (IOException e) { }
  }



  public static int studentsWithGradeOrMore(String filename, int filterGrade) throws IOException
  {
    int counter = 0;

    try (
      BufferedReader reader = new BufferedReader(new FileReader(Main.PATH + filename))
    ) {
      String line;
      int lineIndex = 0;

      while ((line = reader.readLine()) != null) {
        // If mark line
        if (
          lineIndex++ % 2 != 0
          && Integer.parseInt(line) >= filterGrade
        ) {
          ++counter;
        }
      }
    }
    catch (NumberFormatException e) {
      System.err.println("Error in format conversion");
      throw e;
    }
    catch (FileNotFoundException e) {
      System.err.printf("File %s not found\n", filename);
      throw e;
    }
    catch (IOException e) {
      System.err.println("Something went wrong");
      throw e;
    }

    return counter;
  }



  public static boolean containsNumberDivisibleBy(String filename, int n) {
    try (
      BufferedReader reader = new BufferedReader(new FileReader(Main.PATH + filename))
    ) {
      String line;

      while ((line = reader.readLine()) != null) {
        try {
          if (Integer.parseInt(line) % n == 0) {
            return true;
          }
        }
        catch (NumberFormatException e) { }
      }
    }
    catch (FileNotFoundException e) {
      System.err.printf("File %s not found\n", filename);
    }
    catch (IOException e) {
      System.err.println("Something went wrong");
    }

    return false;
  }



  public static boolean hasOnlyIntType(String filename) throws IOException {
    try (
      BufferedReader reader = new BufferedReader(new FileReader(Main.PATH + filename))
    ) {
      String line;

      while ((line = reader.readLine()) != null)
        Integer.parseInt(line);

      return true;
    }
    catch (NumberFormatException e) {
      return false;
    }
    catch (FileNotFoundException e) {
      System.err.printf("File %s not found\n", filename);
      throw e;
    }
    catch (IOException e) {
      System.err.println("Something went wrong");
      throw e;
    }
  }



  public static boolean hasStringOfLengthOrGreater(String filename, int n) throws IOException {
    try (
      DataInputStream reader = new DataInputStream(new FileInputStream(Main.PATH +  filename))
    ) {
      String line;

      while ((line = reader.readUTF()) != null) {
        if (line.length() >= n) {
          return true;
        }
      }

      return false;
    }
    catch (EOFException e) {
      return false;
    }
    catch (FileNotFoundException e) {
      System.err.printf("File %s not found", filename);
      throw e;
    }
    catch (IOException e) {
      System.err.println("Something went wrong");
      throw e;
    }
  }
}
