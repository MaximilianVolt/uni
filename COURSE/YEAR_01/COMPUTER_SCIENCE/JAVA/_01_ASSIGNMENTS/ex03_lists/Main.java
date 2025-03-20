package _01_ASSIGNMENTS.ex03_lists;



public class Main
{
  public static void main(String[] args)
  {
    Vector v = new Vector();
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



  public int sameLengthCount(int n)
  {
    int count = 0;

    for (Element e = head; e != null; e = e.next)
      count += e.data.length() == n ? 1 : 0;
    
    return count;
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