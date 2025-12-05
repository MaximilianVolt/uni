# ESEMPI

```c
Punto* punto_crea(double x, double y)
{
  Punto* p = malloc(sizeof(Punto));

  if (!p)
    return NULL;

  p->x = x;
  p->y = y;
}

Punto* p = punto_crea(3, 4);
p->func(p, /* ... */);
```

```java
public Punto(double x, double y)
{
  this.x = x;
  this.y = y;
}

Punto p = new Punto(3, 4);
p.func(/* ... */);
```

```java
/// Main.java

public class Main
{
  public static void main(String[] args)
  {
    Punto p = new Punto(0, 0);
    Punto q = new Punto(4, 3);
    double dist = p.calcolaDistanza(q);

    System.out.println("Distanza p-q: " + dist);
  }
}
```

```java
public // Visibile da tutto il programma
private // Visibile solo dentro la classe

public class Punto
{
  private int x; // DEVE ESSERE PARI
  private int y; // DEVE ESSERE DISPARI

  public Punto(int x, int y)
  {
    setX(x);
    setY(y);
  }

  public int getX()
  {
    return this.x;
  }

  public int getY()
  {
    return this.y;
  }

  public void setX(int x)
  {
    if (x & 1)
    {
      System.out.println("La x deve essere pari");
      return;
    }

    this.x = x;
  }

  public void setY(int y)
  {
    if (!(y & 1))
    {
      System.out.println("La y deve essere dispari");
      return;
    }

    this.y = y;
  }
}

public void func()
{
  Punto p = new Punto(0, 0);
  p.setX(1);
}
```

```java
public class Main
{
  public static void main(String[] args)
  {
    System.out.println("Ciao!");
  }
}
```

```php
public class Class
{
  public int $x;
  public int $y;

  public function __construct(int $x, int $y)
  {
    $this->x = $x;
    $this->y = $y;
  }
}
```

```c
void combatti()
{
  Nemico* nemico = crea_nemico();

  while (logica)
  {
    // Logica per scappare

    turno_combattimento(&nemico);

    if (nemico->hp == 0)
    {
      printf("Nemico sconfitto");
      break;
    }
  }

  free(nemico);
  nemico = NULL;
}

void turno_combattimento(Nemico* nemico)
{
  // ...
  nemico->hp = 0;
}
```
