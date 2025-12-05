package _01_ASSIGNMENTS.ex05_algorithms;

import java.util.Random;

public class Main
{
  public static void main(String[] args)
  {
    int[] v = new int[]{ 0, 9, 1, 17, 165, 22, 44, 75, 91, 86, 74 };

    Vector.mergeSort(v);

    printArr(v);
  }

  public static void printArr(int[] arr) {
    for (int i : arr) {
      System.out.println(i);
    }
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

    for (; start <= end; middle = (start + end) >> 1)
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



  public static void mergeSort(int[] arr) {
    int len = arr.length;

    if (len < 2)
      return;

    int half = len >> 1;

    int[] h1 = new int[half],
      h2 = new int[len - half]
    ;

    for (int i = 0; i < half; ++i)
      h1[i] = arr[i];

    for (int i = half; i < len; ++i)
      h2[i - half] = arr[i];

    mergeSort(h1);
    mergeSort(h2);
    merge(arr, h1, h2);
  }

  private static void merge(int[] arr, int[] h1, int[] h2) {
    int l1 = h1.length
      , l2 = h2.length
    ;

    int i = 0, i1 = 0, i2 = 0;

    while (i1 < l1 && i2 < l2) {
      arr[i++] = h1[i1] < h2[i2]
        ? h1[i1++]
        : h2[i2++]
      ;
      // if (h1[i1] < h2[i2])
      //   arr[i] = h1[i1++];
      // else 
      //   arr[i] = h2[i2++];
      
      // ++i;
    }

    while (i1 < l1) {
      arr[i++] = h1[i1++];
    }

    while (i2 < l2) {
      arr[i++] = h2[i2++];
    }
  }



  public static void quickSort(int arr[]) {
    quickSort(arr, 0, arr.length - 1);
  }

  private static void quickSort(int arr[], int lo, int hi) {
    // Se l'indice inferiore e superore sono incrociati
    if (lo >= hi) {
      return;
    }

    // Ottiene il limite inferiore ed effettua la ricorsione
    int l = partition(arr, lo, hi);
    quickSort(arr, lo + 1, hi);
    quickSort(arr, lo, l - 1);
  }

  private static int partition(int[] arr, int l, int h) {
    // Sceglie un pivot dato un indice randomico tra l e h
    // (migliore nel caso medio)
    int pivotIdx = new Random().nextInt(h - l) + l
      , pivot = arr[pivotIdx]
      // Indice per ciclare da destra senza perdere
      // il riferimento all'ultimo elemento dell'array
      , r = h
    ;

    // Sposta l'elemento scelto alla fine dell'array
    swap(arr, pivotIdx, h);

    // Mentre gli indici non si incrociano, trova il primo elemento da scambiare
    while (l < r) {
      while (arr[l] <= pivot && l < r) {
        ++l;
      }

      while (arr[r] >= pivot && r > l) {
        --r;
      }

      swap(arr, l, r);
    }

    // Sposta l'ultimo elemento scelto da sinistra in fondo all'array
    swap(arr, l, h);

    // Ritorna il limite inferiore
    return l;
  }

  private static void swap(int[] arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

/*
  7   5

  12  5   // a += b
  12  7   // b = a - b
  5   7   // a -= b
*/