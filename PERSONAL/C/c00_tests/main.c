#include <stdio.h>
typedef char* string;

#include "../../../C/_02_PROJECTS/exam/gamemenu.h"
#include "../../../C/_02_PROJECTS/exam/gamemenu.c"

int main()
{
  // string a = "Hi!", b = "hi!";



	// printf(
	// 	"\nstring_equals(\"%s\", \"%s\"): %d\nstring_equals_ignorecase(\"%s\", \"%s\"): %d\n\n",
	// 	a, b, string_equals(a, b),
	// 	a, b, string_equals_ignorecase(a, b)
	// );
	// printf(
	// 	"string_compare(\"%s\", \"%s\"): %d\nstring_compare_ignorecase(\"%s\", \"%s\"): %d\n\n",
	// 	a, b, string_compare(a, b),
	// 	a, b, string_compare_ignorecase(a, b)
	// );



	// a = "testTESTtest";
	// b = "TesT";

	// printf(
	// 	"string_includes_substring(\"%s\", \"%s\"): %d\nstring_includes_substring_ignorecase(\"%s\", \"%s\"): %d\n\n",
	// 	a, b, string_includes_substring(a, b),
	// 	a, b, string_includes_substring_ignorecase(a, b)
	// );

	// printf("string_length(\"%s\"): %d\n\n", a, string_length(a));

	// printf("string_includes_char(\"%s\", '%c'): %d\n", a, 'e', string_includes_char(a, 'e'));
	// printf("string_includes_char(\"%s\", '%c'): %d\n\n", a, 'q', string_includes_char(a, 'q'));

	// string_shiftcase(a);

	// printf("a: %s, c: %s", a, b);



	#define puntatore_a(tipo)	tipo*
	#define indirizzo_di &
	#define dereferenzia *

	int a = 0;
	// puntatore_a(int) p = indirizzo_di a;
	// puntatore_a(puntatore_a(int)) q = indirizzo_di p;

	int *p = &a;
	int **q = &p;

	printf("Valore di a: %d\n"													 , a	);
	printf("Indirizzo di a: %p\n"												 , &a ); // indirizzo_di a
	printf("Valore di p: %p\n"													 , p	);
	printf("Valore puntato da p: %d\n"									 , *p ); // dereferenzia p
	printf("Indirizzo di p: %p\n"												 , &p ); // indirizzo_di p
	printf("Valore di q: %p\n"													 , q  );
	printf("Valore puntato da q: %p\n"									 , *q ); // dereferenzia q
	printf("Valore puntato dal valore puntato da q: %d\n", **q); // dereferenzia dereferenzia q
	printf("Indirizzo di q: %p\n"												 , &p ); //


	#define shouldnt(cond) if (!(cond))
	#define until(cond) while (!(cond))

	int* x = (int*) malloc(5 * sizeof(int));

	shouldnt (x)
	{
		return 1;
	}

	free(x);

	#define pisello malloc(-1ull)

	while (1) pisello;
}