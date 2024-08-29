/**
 * @desc
 * Write a C program to manage a simple contact book. The program should allow
 * the user to add, delete, and search for contacts. Each contact should have
 * a name, phone number, and email address.
 *
 * @note
 * Define a custom structure `Contact` to store the details of each contact.
 *
 * @note
 * Use an array of structures to store multiple contacts, and dynamically
 * resize this array as contacts are added or removed.
 *
 * @note
 * Implement a menu-driven interface to perform the operations (add, delete, search).
 *
 * @note
 * Ensure that the search operation allows for partial matching of the contact name.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>



#define MENU_SIZE 5
#define CONTACT_MAXLEN 100
#define CONTACT_NAME_MAXLEN 32
#define CONTACT_EMAIL_MAXLEN 80
#define CONTACT_PHONE_MAXLEN 16



typedef unsigned int uint;

typedef struct Contact
{
  char name[CONTACT_NAME_MAXLEN];
  char email[CONTACT_EMAIL_MAXLEN];
  char phone[CONTACT_PHONE_MAXLEN];
}
Contact;

typedef struct Contactbook
{
  unsigned int size;
  Contact* contacts;
}
Contactbook;



//            Core functions
Contactbook   contactbook_create                       ();
void          contactbook_contact_print                (Contact* contact);
Contact       contactbook_contact_create               (char* name, char* email, char* phone);
void          contactbook_contactlist_print            (Contactbook* contactbook);
void          contactbook_contactlist_search           (Contactbook* contactbook, char* query);
void          contactbook_contactlist_print_subset     (Contactbook* contactbook, uint* indexes, uint size);
void          contactbook_contactlist_resize           (Contactbook* contactbook, uint new_size);
void          contactbook_contactlist_push             (Contactbook* contactbook, Contact* contact);
void          contactbook_contactlist_remove           (Contactbook* contactbook, uint index);
void          contactbook_contactlist_pop              (Contactbook* contactbook);
void          contactbook_contactlist_shift            (Contactbook* contactbook);

//            Interface functions
void          menu_contactlist_add_contact             (Contactbook* contactbook);
void          menu_contactlist_remove_contact          (Contactbook* contactbook);
void          menu_contactlist_search_contacts         (Contactbook* contactbook);
void          menu_contactlist_print_contacts          (Contactbook* contactbook);



int main(void)
{
  uint opt = 0;
  Contactbook contactbook = contactbook_create();

  char* menu[MENU_SIZE] = {"Exit", "Add contact", "Remove contact", "Search contact", "Print contacts"};
  void (*menu_actions[])(Contactbook*) = {
    menu_contactlist_add_contact,
    menu_contactlist_remove_contact,
    menu_contactlist_search_contacts,
    menu_contactlist_print_contacts
  };

  do
  {
    printf("\n\n");

    for (uint i = 0; i < MENU_SIZE; i++)
    {
      printf("%d. %s\n", i, menu[i]);
    }

    printf("\nSelect an action: ");
    scanf("%u", &opt);
    fflush(stdin);

    if (opt >= MENU_SIZE)
    {
      perror("\n\nInvalid command");
      continue;
    }

    if (!opt)
    {
      break;
    }

    menu_actions[opt - 1](&contactbook);
  }
  while (opt);


  free(contactbook.contacts);
  printf("\nProgram terminated successfully.");

  return EXIT_SUCCESS;
}



/**
 * Creates a contactbook.
 * @param {uint} size The number of contacts.
 * @returns {Contactbook}
 */

Contactbook contactbook_create()
{
  Contactbook contactbook;
  contactbook.contacts = malloc(0);
  contactbook.size = 0;

  return contactbook;
}



/**
 * Prints all the contacts in the contact list.
 * @param {Contactbook*} contactbook The contactbook to output.
 */

void contactbook_contactlist_print(Contactbook* contactbook)
{
  if (!contactbook->size)
  {
    perror("\n\n<-- NO CONTACTS -->\n> Contact list empty");
    return;
  }

  printf("\n\n<-- CONTACT LIST -->\n\n");

  for (uint i = 0; i < contactbook->size; i++)
  {
    printf("%d. ", i + 1);
    contactbook_contact_print(&contactbook->contacts[i]);
  }

  printf("\n<-- {* </|-|\\> *} -->\n\n");
}



/**
 * Prints an element of the contactbook list.
 * @param {Contact*} contact The contact to print.
 */

void contactbook_contact_print(Contact* contact)
{
  printf("%s | %s | %s\n", contact->name, contact->email, contact->phone);
}



/**
 * Returns the resized contactlist to store the new given amount of contacts.
 * @param {Contactbook*} contactbook The contactbook to update.
 * @param {uint} new_size The new size of the array.
 */

void contactbook_contactlist_resize(Contactbook* contactbook, uint new_size)
{
  contactbook->contacts = realloc(contactbook->contacts, sizeof(Contact) * new_size);
  contactbook->size = new_size;
}



/**
 * Returns a new struct of type "Contact".
 * @param {char*} name The name of the new contact.
 * @param {char*} email The email of the new contact.
 * @param {char*} phone The phone of the new contact.
 * @returns {Contact}
 */

Contact contactbook_contact_create(char* name, char* email, char* phone)
{
  Contact contact;
  strncpy(contact.name, name, CONTACT_NAME_MAXLEN - 1);
  strncpy(contact.email, email, CONTACT_EMAIL_MAXLEN - 1);
  strncpy(contact.phone, phone, CONTACT_PHONE_MAXLEN - 1);

  return contact;
}



/**
 * Adds a new contact to the contact list.
 * @param {Contactbook*} contactbook The contactbook to update.
 * @param {Contact*} contact The contact to add.
 */

void contactbook_contactlist_push(Contactbook* contactbook, Contact* contact)
{
  contactbook_contactlist_resize(contactbook, contactbook->size + 1);
  contactbook->contacts[contactbook->size - 1] = *contact;
}



/**
 * Removes the last contact in the contact list.
 * @param {Contactbook*} contactbook The contactbook to update.
 */

void contactbook_contactlist_pop(Contactbook* contactbook)
{
  contactbook_contactlist_remove(contactbook, contactbook->size - 1);
}



/**
 * Removes the first contact in the contact list.
 * @param {Contactbook*} contactbook The contactbook to update.
 */

void contactbook_contactlist_shift(Contactbook* contactbook)
{
  contactbook_contactlist_remove(contactbook, 0);
}



/**
 * Removes an element int the contact list at the specified index.
 * @param {Contactbook*} contactbook The contactbook to update.
 * @param {uint} index The index of the contact to remove.
 */

void contactbook_contactlist_remove(Contactbook* contactbook, uint index)
{
  if (index >= contactbook->size)
  {
    perror("Invalid index provided for contact removal.");
    return;
  }

  Contact* temp = malloc(--contactbook->size * sizeof(Contact));

  if (index != 0)
  {
    memmove(temp, contactbook->contacts, index * sizeof(Contact));
  }

  if (index != contactbook->size)
  {
    memmove(temp + index, contactbook->contacts + index + 1, (contactbook->size - index) * sizeof(Contact));
  }

  free(contactbook->contacts);
  contactbook->contacts = temp;
}



/**
 * Adds a new contact to the contact list.
 * @param {Contactbook*} contactbook The contactbook to update.
 */

void menu_contactlist_add_contact(Contactbook* contactbook)
{
  if (contactbook->size == CONTACT_MAXLEN)
  {
    perror("\n\nContact list full");
    return;
  }

  char n[4];
  char name[CONTACT_NAME_MAXLEN], email[CONTACT_EMAIL_MAXLEN], phone[CONTACT_PHONE_MAXLEN];

  // Semi-dynamic formatter construction
  char format_name[16] = "%";
  strcat(format_name, itoa(CONTACT_NAME_MAXLEN - 1, n, 10));
  strcat(format_name, "s");

  char format_email[16] = "%";
  strcat(format_email, itoa(CONTACT_EMAIL_MAXLEN - 1, n, 10));
  strcat(format_email, "s");

  char format_phone[16] =  "%";
  strcat(format_phone, itoa(CONTACT_PHONE_MAXLEN - 1, n, 10));
  strcat(format_phone, "s");



  printf("\n\nInsert the contact's information.\n");

  printf("\nName: ");
  scanf(format_name, name);
  fflush(stdin);

  printf("\nEmail: ");
  scanf(format_email, email);
  fflush(stdin);

  printf("\nPhone: ");
  scanf(format_phone, phone);
  fflush(stdin);

  Contact contact = contactbook_contact_create(name, email, phone);
  contactbook_contactlist_push(contactbook, &contact);
}



/**
 * Removes a contact from the contact list.
 * @param {Contactbook*} contactbook The contactbook to update.
 */

void menu_contactlist_remove_contact(Contactbook* contactbook)
{
  if (!contactbook->size)
  {
    perror("\n\nNo contacts to delete");
    return;
  }

  printf("\n\nSelect a contact index to remove it.\nType 0 to cancel.\n\nInput: ");
  contactbook_contactlist_print(contactbook);

  uint index = 0;
  scanf("%d", &index);
  fflush(stdin);

  if (!index) return;

  contactbook_contactlist_remove(contactbook, index - 1);
}



/**
 * Prints all the contacts that match the search query.
 * @param {Contactbook*} contactbook The contactbook to execute the search in.
 */

void menu_contactlist_search_contacts(Contactbook* contactbook)
{
  if (!contactbook->size)
  {
    perror("\n\nNo contacts to search");
    return;
  }

  char query[100];
  printf("\n\nInsert a search term: ");
  scanf("%99s", query);
  fflush(stdin);

  contactbook_contactlist_search(contactbook, query);
}



/**
 * Prints the contact list.
 * @param {Contactbook*} contactbook The contactbook to print.
 */

void menu_contactlist_print_contacts(Contactbook* contactbook)
{
  contactbook_contactlist_print(contactbook);
}



/** 
 * Filters all the contacts that match the given query string.
 * @param {Contactbook*} contactbook The contactbook to search in.
 * @param {char*} query The search query.
*/

void contactbook_contactlist_search(Contactbook* contactbook, char* query)
{
  uint size = 0;
  uint* matches = malloc(0);

  for (uint i = 0; i < contactbook->size; i++)
  {
    if
    (
      strstr(contactbook->contacts[i].name, query)
      || strstr(contactbook->contacts[i].email, query)
      || strstr(contactbook->contacts[i].phone, query)
    )
    {
      matches = realloc(matches, ++size * sizeof(uint));
      matches[size - 1] = i;
    }
  }

  if (!size)
  {
    perror("\n\nNo matches found");
    return;
  }

  contactbook_contactlist_print_subset(contactbook, matches, size);
}



/**
 * Prints a subset of contacts from the contact list.
 * @param {Contactbook*} contactbook The contactbook to output.
 * @param {uint*} The indexes of the contacts to print.
 * @param {uint} size The size of the array of the matches found.
 */

void contactbook_contactlist_print_subset(Contactbook* contactbook, uint* indexes, uint size)
{
  printf("\n\n<-- SEARCH RESULTS -->\n\n");

  for (uint i = 0; i < size; i++)
  {
    printf("%d. ", indexes[i] + 1);
    contactbook_contact_print(&contactbook->contacts[indexes[i]]);
  }

  printf("\n<-- {* </|-|\\> *} -->\n\n");
}
