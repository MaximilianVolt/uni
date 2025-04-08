package _01_ASSIGNMENTS.ex05_algorithms;

public class Main
{
  public static void main(String[] args)
  {
    
  }
}

class Vector
{
  int arr[];

  public int binarySearchRecursive(int data)
  {
    return binarySearchRecursive(arr, data, 0, arr.length - 1);
  }

  private static int binarySearchRecursive(int arr[], int data, int start, int end)
  {
    // if (start > end)
    //   return -1;

    // int middle = (start + end) / 2;

    // if (arr[middle] == data)
    //   return middle;

    // return data < arr[middle]
    //   ? binarySearchRecursive(arr, data, start, middle - 1)
    //   : binarySearchRecursive(arr, data, middle + 1, end)
    // ;

    int middle = (start + end) / 2;

    return start > end
      ? -1
      : (arr[middle] == data
        ? middle
        : (data < arr[middle]
          ? binarySearchRecursive(arr, data, start, middle - 1)
          : binarySearchRecursive(arr, data, middle + 1, end)
        )
      )
    ;
  }



  public static int binarySearchIterative(int arr[], int data)
  {
    int start = 0
      , end = arr.length - 1
      , middle = (start + end) / 2
    ;

    for (; start <= end; middle = (start + end) / 2)
    {
      if (arr[middle] == data)
        return middle;
      else if (data < arr[middle])
        end = middle - 1;
      else
        start = middle + 1;
    }

    return -1;
  }
}