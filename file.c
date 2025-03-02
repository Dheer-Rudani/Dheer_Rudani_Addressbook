#include <stdio.h>
#include <string.h>
#include "file.h"
//Function definition to save contacts
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp1;
    Contact temp;
    fp1 = fopen("contacts.csv", "w"); //Declaring the file pointer and collecting the address of the file based on the mode.
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
    
    for(int i=0;i<addressBook->contactCount;i++)
    {
        //Printing all the values of the structure into the .csv file 
        fprintf(fp1,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp1);//Closing the file.
    return;
}
//Function definition to load contacts
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv", "r");//Declaring the file pointer and collecting the address of the file based on the mode.
    if (fp == NULL)//Checking whether the file exist or not
    {
        printf("Error opening file for loading contacts.\n");
        return;
    }

    /*We know that scanf returns number of successful matches and in the csv file the data/value is separated by ','.
    Below looping is performed if the number of success is equal to 3 and the count value is incremented*/
    
    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) 
    {
        addressBook->contactCount++;
    }
    fclose(fp);//Closing the file.
    return;
}