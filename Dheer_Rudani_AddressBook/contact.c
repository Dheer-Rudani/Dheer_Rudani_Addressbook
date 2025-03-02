#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

//Function definition to initilize the saved contacts
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

//Function definition to validate name
int validate_name(char *name)
{
    //STEP1: Traverse througn the name until null and check whether the name consists of alphabets and space or not
    int i = 0;
    while(name[i] != '\0')
    {
        if((!(isalpha(name[i]))) && name[i] != ' ')
        {
            return 1;
        }
        i++;
    }
    return 0;                                   
}

//Function definition to validate mobile number
int validate_phone(AddressBook *addressBook,char *phone)
{
    // check for length of number = 10 or not
    int i = 0;
    if(strlen(phone) != 10)
    {
        printf("Please enter a valid mobile number.");
        return 1;
    }
    while(phone[i] != '\0')//Traverse througn the mobile number until null and check for digits
    {
        if((!(isdigit(phone[i]))))
        {
            printf("INFO: Mobile number validation not done, Please enter valid number...\n");
            return 1;
        }
        i++;
    }
    for(i = 0; i < addressBook->contactCount; i++)//check whether the number is already present or not
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printf("Mobile number already exists.\n");
            return 1;
        }
    }
    return 0;
}

//Function definition to validate Email_ID
int validate_email(AddressBook *addressBook,char *email)
{
    //Traverse througn the email until null and check for presence of @ and .com
    int i = 0;
    while(email[i] != '\0')
    {
        if((!strstr(email,"@")) || (!strstr(email,".com")))
        {
            printf("INFO: Email_ID validation not done, Please enter valid email...\n");
            return 1;
        }
        i++;
    }
    for(i = 0; i < addressBook->contactCount; i++)// Check whether the email is already present or not.
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printf("Email_ID already exists.\n");
            return 1;
        }
    }
    return 0;
}

//Function definition to create a new contact
void createContact(AddressBook *addressBook)
{
    char name[20], phone[11], email[20];
    //STEP1: Read the name from the user
    printf("Enter the name: ");
     __fpurge(stdin);
    scanf("%[^\n]", name);
    //STEP2: Validate the name -> Alphabets
    while(validate_name(name) == 1)
    {
        printf("INFO: Name validation not done, Please enter valid name...\n");
        printf("Enter the name: ");
        __fpurge(stdin);
        scanf("%[^\n]", name);
    }

    //STEP3: Read the phone number from the user
    printf("Enter the mobile number: ");
     __fpurge(stdin);
    scanf("%[^\n]", phone);
    //STEP4: Validate the mobile number -> Digits & unique
    while( validate_phone(addressBook, phone) == 1)
    {
        printf("Enter the mobile number: ");
        __fpurge(stdin);
        scanf("%[^\n]", phone);
    }

    //STEP5: Read the email ID from the user
    printf("Enter the Email_ID: ");
     __fpurge(stdin);
    scanf("%[^\n]", email);
    //STEP6: Validate the Email_ID -> @ & .com & unique
    while(validate_email(addressBook,email) == 1)
    {
        printf("Enter the Email_ID: ");
        __fpurge(stdin);
        scanf("%[^\n]", email);
    }

    //STEP7: Save the above details into the structure
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount++;

    printf("\nContact created successfully.\n");
}

//Function definition to search the name
int search_name(AddressBook *addressBook)
{
    char name[20];
    int i;
    //STEP1: Read the name from the user
    printf("\nEnter the name: ");
     __fpurge(stdin);
    scanf("%[^\n]", name);
    //STEP2: Validate the name -> Alphabets
    while(validate_name(name) == 1)
    {
        printf("INFO: Name validation not done, Please enter valid name...\n");
        printf("Enter the name: ");
        __fpurge(stdin);
        scanf("%[^\n]", name);
    }

    for(i = 0;i < addressBook->contactCount; i++)//Print the details if present.
    {
        if(strcasecmp(name, addressBook->contacts[i].name) == 0)
        {
            printf("\nDetails found\n");
            printf("Name: %s\n",addressBook->contacts[i].name);
            printf("Mobile: %s\n",addressBook->contacts[i].phone);
            printf("Email: %s\n",addressBook->contacts[i].email);
            return i;
        }
    }

    //To list the matching names if a partial name is entered
    int flag=1,flg=1;
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcasestr(addressBook->contacts[i].name,name) != NULL)
        {
            if(flg==1)//Condition to print the below string for only once during the loop
            {
                printf("\nThe following names are found\n");
                flg=0;
            }
            printf("%s\n",addressBook->contacts[i].name);
            flag=0;
        }
    }
    if(flag==0)//Perform the operation if the names are found.
    {
        printf("\nPlease type the full name from the above to get its details\n");
        printf("Enter the name: ");
        __fpurge(stdin);
        scanf("%[^\n]", name);
        for(i = 0;i < addressBook->contactCount; i++)//Print the details if full name is entered.
        {
            if(strcasecmp(name, addressBook->contacts[i].name) == 0)
            {   
                printf("\nDetails found\n");
                printf("Name: %s\n",addressBook->contacts[i].name);
                printf("Mobile: %s\n",addressBook->contacts[i].phone);
                printf("Email: %s\n",addressBook->contacts[i].email);
                return i;
            }
        }
    }
    printf("Entered name not found.\n"); 
    return -1; 
}

//Function definition to search the mobile number
int search_mobile(AddressBook *addressBook)
{
    char phone[11];
    int i,flag;
    //STEP1: Read the phone number from the user
    do
    {   
        printf("\nEnter the mobile number: ");
        __fpurge(stdin);
        scanf("%[^\n]", phone);
        //STEP2: Validate the mobile number -> Digits & unique
        i = 0;
        while(phone[i] != '\0')
        {
            if(strlen(phone) != 10)
            {
                printf("Invalid number. Enter a valid number.\n");
                flag = 1;
                break;
            }
            if((!(isdigit(phone[i]))))
            {
                printf("INFO: Mobile number validation not done, Please enter valid number...\n");
                flag = 1;
                break;
            }
            flag = 0;
            i++;
        }
    }while(flag != 0);

    for(i = 0; i < addressBook->contactCount; i++)//Print the details if present
    {
        if(strcmp(phone,addressBook->contacts[i].phone)==0)
        {
            printf("\nDetails found\n");
            printf("Name: %s\n",addressBook->contacts[i].name);
            printf("Mobile: %s\n",addressBook->contacts[i].phone);
            printf("Email: %s\n",addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Entered number not found.\n");
    return -1;
} 

//Function definition to search the Email_ID
int search_email(AddressBook *addressBook)
{
    char email[50];
    int i,flag;
    //STEP1: Read the email ID from the user
    do
    {
        printf("\nEnter the Email_ID: ");
        __fpurge(stdin);
        scanf("%[^\n]", email);
        //STEP2: Validate the Email_ID -> @ & .com
        if (strstr(email, "@") && strstr(email, ".com"))
        {
            flag = 0; // Valid email
        } 
        else 
        {
            printf("INFO: Email_ID validation not done, Please enter valid email...\n");
            flag = 1; // Invalid email
        }
    }while(flag!=0);

    for(i=0; i < addressBook->contactCount; i++)//Print the details if present
    {
        if(strcmp(email,addressBook->contacts[i].email) == 0)
        {
            printf("\nDetails found\n");
            printf("Name: %s\n",addressBook->contacts[i].name);
            printf("Mobile: %s\n",addressBook->contacts[i].phone);
            printf("Email: %s\n",addressBook->contacts[i].email);
            return i;
        }
    }
    printf("Entered email not found.\n");
    return -1;
}

//Function definition to search contact
void searchContact(AddressBook *addressBook) 
{
    int choice;
    //STEP1: Print the menu based on what you want to search
    printf("\nChoose what you want to search:\n");
    printf("1.Name\n");
    printf("2.Mobile number\n");
    printf("3.Email_ID\n");

    //STEP2:Choose what you want to search
    printf("Enter your choice: ");
    scanf("%d", &choice);
    //Based on the choice call respective function
    switch(choice)
    {
        case 1:
            search_name(addressBook);
            break;
        case 2:
            search_mobile(addressBook);
            break;
        case 3:
            search_email(addressBook);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    return;
}

//Function definition to edit the name
void editname(AddressBook *addressBook,int i)
{
    char name[20];
    //Read the name
    printf("\nEnter the new name: ");
     __fpurge(stdin);
    scanf("%[^\n]", name);
    //Validate the name
    while(validate_name(name) == 1)
    {
        printf("INFO: Name validation not done, Please enter valid name...\n");
        printf("Enter the name: ");
        __fpurge(stdin);
        scanf("%[^\n]", name);
    }
    //Change the name
    strcpy(addressBook->contacts[i].name,name);
    printf("The name has been updated.\n");
    return;
}

//Function definition to edit the mobile number
void editnumber(AddressBook *addressBook,int i)
{
    char phone[11];
    int j,flag;
    //STEP1: Read the new phone number from the user
    do
    {   
        printf("\nEnter the new mobile number: ");
        __fpurge(stdin);
        scanf("%[^\n]", phone);
        //STEP2: Validate the mobile number -> Digits & unique
        j = 0;
        while(phone[j] != '\0')
        {
            if(strlen(phone) != 10)
            {
                printf("Invalid number. Enter a valid number.\n");
                flag = 1;
                break;
            }
            if((!(isdigit(phone[j]))))
            {
                printf("INFO: Mobile number validation not done, Please enter valid number...\n");
                flag = 1;
                break;
            }
            flag = 0;
            j++;
        }
    }while(flag != 0);

    //Change the number
    strcpy(addressBook->contacts[i].phone,phone);
    printf("The mobile number has been updated.\n");
    return;
}

//Function definition to edit the Email_ID
void editemail(AddressBook *addressBook,int i)
{
    char email[50];
    int flag;
    //STEP1: Read the email ID from the user
    do
    {
        printf("\nEnter the new Email_ID: ");
        __fpurge(stdin);
        scanf("%[^\n]", email);
        //STEP2: Validate the Email_ID -> @ & .com & unique
        if (strstr(email, "@") && strstr(email, ".com"))
        {
            flag = 0; // Valid email
        } 
        else 
        {
            printf("INFO: Email_ID validation not done, Please enter valid email...\n");
            flag = 1; // Invalid email
        }
    }while(flag != 0);

    //Change the email
    strcpy(addressBook->contacts[i].email,email);
    printf("The Email_ID has been updated.\n");
    return;
}

//Function definition to edit the contact
void editContact(AddressBook *addressBook)
{
    //Print the menu based on what you want to search
    int choice,i;
    printf("\nChoose what you want to search:\n");
    printf("1.Name\n");
    printf("2.Mobile number\n");
    printf("3.Email_ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);//Read the choice
    //Based on the choice call the respective function
    switch(choice)
    {
        case 1:
            i = search_name(addressBook);
            break;
        case 2:
            i = search_mobile(addressBook);
            break;
        case 3:
            i = search_email(addressBook);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    
    if(i < 0)
    {
        return;
    }

	//Print the menu based on what you want to edit
    int choice1;
    printf("\nChoose what you want to edit\n");
    printf("1.Name\n");
    printf("2.Mobile number\n");
    printf("3.Email\n");
    printf("Enter your choice: ");
    scanf("%d",&choice1);//Read the choice
    //Based on the choice call the respective function
    switch (choice1)
    {
        case 1:
            editname(addressBook,i);
            break;
        case 2:
            editnumber(addressBook,i);
            break;
        case 3:
            editemail(addressBook,i);
            break;
        default:
            printf("Invalid Choice\n");
            return;
    }
    return;  
}

//Function to delete the contact
void deleteContact(AddressBook *addressBook)
{
	//Perform search operation
    int choice,i;
    printf("\nChoose what you want to search:\n");
    printf("1.Name\n");
    printf("2.Mobile number\n");
    printf("3.Email_ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    //Based on the choice call the respective function
    switch(choice)
    {
        case 1:
            i = search_name(addressBook);
            break;
        case 2:
            i = search_mobile(addressBook);
            break;
        case 3:
            i = search_email(addressBook);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    if(i < 0)
    {
        return;
    }

	//Print the menu based on whether you want to delete or not
    int choice1,j;
    printf("\nDo you want to delete the contact.\n");
    printf("1.Yes\n");
    printf("2.No\n");
    printf("Enter your choice: ");
    scanf("%d",&choice1);//Read the choice
    //Based on the choice perform the operation
    switch (choice1)
    {
        case 1:
            for(j = i; j < addressBook->contactCount; j++)//Condition to perform delete
            {
                addressBook->contacts[j] = addressBook->contacts[j+1];
            }
            addressBook->contactCount--;
            printf("The contact has been deleted\n");
            break;
        case 2:
            return;
        default:
            printf("Invalid Choice\n");
    }
    return;  
}

//Function call to list all the contacts
void listContacts(AddressBook *addressBook) 
{
    Contact temp;
    //Sort the data in the database
    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0)
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
    
    //Print all the data int the database
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nUser %d:\n",i+1);
        printf("Name: %s\n",addressBook->contacts[i].name);
        printf("Mobile: %s\n",addressBook->contacts[i].phone);
        printf("Email: %s\n",addressBook->contacts[i].email);
    }
}