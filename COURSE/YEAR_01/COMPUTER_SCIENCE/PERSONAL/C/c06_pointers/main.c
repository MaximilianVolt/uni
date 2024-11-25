#include <stdio.h>
#include <limits.h>

int main()
{
  int a = 1
    , *p = &a
    , **q = &p;

  printf_s("\n<- COMPLETE LIST ->\n\n");
  printf_s("  a: %d\n", a  );
  printf_s(" &a: %p\n", &a );
  printf_s("  p: %p\n", p  );
  printf_s(" *p: %d\n", *p );
  printf_s(" &p: %p\n", &p );
  printf_s("  q: %p\n", q  );
  printf_s(" *q: %p\n", *q );
  printf_s("**q: %d\n", **q);
  printf_s(" &q: %p\n", &q );

  printf_s("\n<- VALUE LIST ->\n\n");
  printf_s("  a: %d\n", a  );
  printf_s(" *p: %d\n", *p );
  printf_s("**q: %d\n", **q);

  printf_s("\n<- ADRRESS LIST ->\n\n");
  printf_s(" &a: %p\n", &a );
  printf_s("  p: %p\n", p  );
  printf_s(" &p: %p\n", &p );
  printf_s("  q: %p\n", q  );
  printf_s(" *q: %p\n", *q );
  printf_s(" &q: %p\n", &q );

  printf_s("\n\n\n\n\n");

  int arr[2] = {1, 0};
  int mat[2][2] = {{3, 2}, {1, 0}}; 

  /**
   * *: arr[i] == i[arr]   <=>   *(arr + i) == *(i + arr)
   * *: -> Vero!
  */

  printf_s("%d\n", *arr);
  printf_s("%d\n", arr[0]);
  printf_s("%d\n", 0[arr]);

  {
    typedef int i32;
    // mat[i][arr[j]]
    // *(mat + i)[arr[j]]
    // *(mat + i)[*(arr + j)]
    // *(*(mat + i) + *(arr + j))
    i32 i = 1, j = 0;
    printf_s("%d\n", *(*(mat + i) + *(arr + j)));
  }
// (M+1)*3+1 =3M+4
  short int b[4] = {1, 3, [3] = 1};

  // for (int i = 0; i < 4; ++i)
  //   printf_s("b[%d] = %d\n", i, b[i]);

  printf_s("\nVal: %d\n", SHRT_MAX * 6 + 7);
}
