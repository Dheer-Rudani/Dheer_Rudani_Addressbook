#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

//Creating a contact structure
typedef struct  
{
    char name[50];
    char phone[11];
    char email[50];
} Contact;

//Creating the array of contacts structure 
typedef struct 
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

//Function prototype for creating the contact
void createContact(AddressBook *addressBook);

//Function prototype for searching the contact
void searchContact(AddressBook *addressBook);

//Function prototype for editing the contact
void editContact(AddressBook *addressBook);

//Function prototype for deleting the contact
void deleteContact(AddressBook *addressBook);

//Function prototype for list all the contact
void listContacts(AddressBook *addressBook);

//Function prototype for initializing the contact to the structure
void initialize(AddressBook *addressBook);

//Function prototype for saving the contacts into the file
void saveContactsToFile(AddressBook *addressBook);

#endif
