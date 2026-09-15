
#include <stdio.h>

#include "file.h"

/**
 * Function: saveContactsToFile
 * Description: Saves all contacts from the address book to a CSV file.
 * Input: AddressBook pointer
 * Return: None
 */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    int i;

    /* Open the contacts file in write mode. */
    fp = fopen("contacts.csv", "w");

    /* Check whether the file was opened successfully. */
    if(fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    /* Write the total number of contacts to the file. */
    fprintf(fp, "#%d\n", addressBook->contactCount);

    /* Write each contact in CSV format. */
    for(i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    /* Close the file after saving all contacts. */
    fclose(fp);

    printf("Contacts saved successfully.\n");
}

/**
 * Function: loadContactsFromFile
 * Description: Loads contacts from the CSV file into the address book.
 * Input: AddressBook pointer
 * Return: None
 */
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;
    int count;
    int i;

    /* Open the contacts file in read mode. */
    fp = fopen("contacts.csv", "r");

    /* Check whether the contacts file exists. */
    if(fp == NULL)
    {
        printf("No existing contact file found.\n");
        return;
    }

    /* Read the total number of contacts from the file. */
    if(fscanf(fp, "#%d\n", &count) != 1)
    {
        printf("Invalid contact file.\n");
        fclose(fp);
        return;
    }

    /* Reset the contact count before loading contacts. */
    addressBook->contactCount = 0;

    /* Read each contact from the file. */
    for(i = 0; i < count && i < MAX_CONTACTS; i++)
    {
        if(fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) == 3)
        {
            /* Increase the contact count after loading a contact successfully. */
            addressBook->contactCount++;
        }
        else
        {
            /* Stop loading if contact data cannot be read correctly. */
            break;
        }
    }

    /* Close the file after loading all contacts. */
    fclose(fp);
}
