# ESERCIZIO 24/11/26

## EX. 6

Cerchiare le affermazioni vere dato:

```c
int a[6] = {
  25,
  [2] = 131074,
  [4] = 131070,
  255
};

char* p = (char*) a;
short* q = (short*) a;
```

Sapendo che i tre tipi occupano 4, 1 e 2 byte, e 131072 = 2^17 (valori rappresentati in little endian). Autovalutare il risultato programmando l'esempio direttamente.

Little endian, CA2:

a[0] = 10011000 00000000 00000000 00000000 (25)
a[1] = 00000000 00000000 00000000 00000000 (0)
a[2] = 01000000 00000000 01000000 00000000 (131074)
a[3] = 00000000 00000000 00000000 00000000 (0)
a[4] = 01111111 11111111 10000000 00000000 (131070)
a[5] = 11111111 00000000 00000000 00000000 (255)

```c
/** 1) */ *(p + 8) + q[0] > 24

  *(p + 8) == 0b00000010         // (i8) 2
      q[0] == 0b0000000000011001 // (i16) 25

  2 + 25 > 24
  27 > 24
  1



/** 2) */ p[8] - p[10] > 0

  p[8]  == 0b00000010 // (i8) 2
  p[10] == 0b00000010 // (i8) 2

  2 - 2 > 0
  0 > 0
  0



/** 3) */ ((int) (q + 6) - (int) (&a[1]) - *(q + 9)) % 2 == 1

  // Si suppone che l'indirizzo in memoria di a[0] sia 0x1000
  (int) (q + 6) == 0x100c // (i32) 4108
  (int) (&a[1]) == 0x1004 // (i32) 4100
       *(q + 9) == 0b0000000000000001 // (i16) 1
  
  (0x100c - 0x1004 - 1) % 2 == 1
  (0x0008 - 1) % 2 == 1
  (7) % 2 == 1
  1 == 1
  1




/** 4) */ &a[5] - (a + 1) + *(p + 18) <= 5

  // Si suppone che l'indirizzo in memoria di a[0] sia 0x1000
      &a[5] == 0x1014 // (i32*) 4116
      a + 1 == 0x1004 // (i32*) 4100
  *(p + 18) == 0b00000001 // 1

  // Gli indirizzi NON sono convertiti a int, quindi (4116 - 4100) / sizeof(i32) == 4
  4 + 1 <= 5
  5 <= 5
  1



/** 5) */ *(p + 20) - *(p + 17) < 0

  *(p + 20) == 0b11111111 // (i8) -1
  *(p + 17) == 0b11111111 // (i8) -1

  -1 - -1 < 0
  0 < 0
  0



/** 6) */ *(p + 17) >= 0

  *(p + 17) == 0b11111111 // (i8) -1

  -1 >= 0
  0

```
