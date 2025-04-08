package _01_ASSIGNMENTS.ex03_lists;



public class Main
{
  public static void main(String[] args)
  {
    Vector v = new Vector();
    System.out.println(v);
  }
}



class List
{
  Element head;

  public List(long count)
  {
    Element temp = head;

    while (count-- > 0)
    {
      String data = "";

      for (byte i = (byte) (Math.random() * 10 + 1); i >= 0; --i)
        data += "ciao";

      temp = new Element(data);
      temp = temp.next;
    }
  }

  public int lengthSum(int n)
  {
    int sum = 0;

    for (Element e = head; e != null; e = e.next)
    {
      int len = e.data.length();

      if (len > n)
        sum += len;
    }

    return sum;
  }



  public double averageEvenLength()
  {
    double sum = 0;
    int count = 0;

    for (Element e = head; e != null; e = e.next)
    {
      int len = e.data.length();

      // Controllo su bit di parita'
      if ((len & 0b1) == 0)
      {
        sum += len;
        ++count;
      }
    }

    return count > 0
      ? sum / count
      : 0
    ;
  }



  public boolean contains(String s)
  {
    for (Element e = head; e != null; e = e.next)
      if (e.data.equals(s))
        return true;

    return false;
  }



  public int sameLengthCount(String s)
  {
    int count = 0, len = s.length();

    for (Element e = head; e != null; e = e.next)
      count += e.data.length() == len ? 1 : 0;
    
    return count;
  }



  public int sameLengthCountWhile(String s)
  {
    Element e = head;
    int count = 0, len = s.length();

    while (e != null)
    {
      count += e.data.length() == len ? 1 : 0;
      e = e.next;
    }
    
    return count;
  }



  public int sameLengthCountRecursive(String s)
  {
    if (head == null)
      return 0;

    return sameLengthCountRecursive(s.length(), head);
  }



  private int sameLengthCountRecursive(int l, Element e)
  {
    if (e == null)
      return 0;

    return sameLengthCountRecursive(l, e.next) + (
      l == e.data.length() ? 1 : 0
    );
  }



  public int sameLengthCountRecursiveTail(String s)
  {
    if (head == null)
      return 0;

    return sameLengthCountRecursiveTail(s.length(), head, 0);
  }



  private int sameLengthCountRecursiveTail(int l, Element e, int sum)
  {
    if (e == null)
      return sum;

    return sameLengthCountRecursiveTail(l, e.next, sum + (
      l == e.data.length() ? 1 : 0
    ));
  }



  public int maxLength()
  {
    int max = 0;

    for (Element e = head; e != null; e = e.next)
    {
      int len = e.data.length();

      if (len > max)
        max = len;
    }

    return max;
  }



public int maxLengthWhile()
{
  int max = 0;
  Element e = head;

  while (e != null)
  {
    int len = e.data.length();

    if (len > max)
      max = len;
    
    e = e.next;
  }

  return max;
}



  public int maxLengthBelow(int m)
  {
    int max = 0;

    for (Element e = head; e != null; e = e.next)
    {
      int len = e.data.length();

      if (len > max && len < m)
        max = len;
    }

    return max;
  }




  public int maxLengthBelowRecursiveTail(int m)
  {
    return maxLengthBelowRecursiveTail(0, head, m);
  }



  private int maxLengthBelowRecursiveTail(int max, Element e, int m)
  {
    if (e == null)
      return max;

    int len = e.data.length();

    return maxLengthBelowRecursiveTail(
      (len > max && len < m) ? len : max,
      e.next,
      m
    );
  }



  public int maxLengthBelowRecursive(int m)
  {
    return maxLengthBelowRecursive(head, m);
  }



  private int maxLengthBelowRecursive(Element e, int m)
  {
    if (e == null)
      return 0;

    int len = e.data.length()
      , max = maxLengthBelowRecursive(e.next, m)
    ;

    return (len > max && len < m) 
      ? len
      : max
    ;
  }
}



class Element
{
  String data;
  Element next;

  public Element(String data)
  {
    this.data = data;
    next = null;
  }
}


class Vector
{

}