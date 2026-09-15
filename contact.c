#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

/**
 * Function: listContacts
 * Description: Sorts and displays all contacts based on
 *              name, phone number, or email.
 * Input: AddressBook pointer
 * Return: None
 */

void listContacts(AddressBook *addressBook)
{
    int i, j, choice;
    Contact temp;

    // Check whether the address book contains any contacts.
    if (addressBook->contactCount == 0)
    {
        printf("No contacts found.\n");
        return;
    }

    // Display sorting options to the user.
    printf("\n+----------------------------------+\n");
    printf("|         SORT CONTACTS            |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Sort by Name                  |\n");
    printf("| 2. Sort by Phone                 |\n");
    printf("| 3. Sort by Email                 |\n");
    printf("| 4. Exit                          |\n");
    printf("+----------------------------------+\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Exit the function if the user selects Exit.
    if (choice == 4)
    {
        return;
    }
    // Check whether the entered choice is valid.
    if (choice < 1 || choice > 4)
    {
        printf("Invalid choice.\n");
        return;
    }

    // Sort contacts using Bubble Sort based on the selected field.
    for (i = 0; i < addressBook->contactCount - 1; i++)
    {
          
        for (j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            // Compare contacts by name.
            if (choice == 1)
            {
                if (strcmp(addressBook->contacts[j].name,
                           addressBook->contacts[j + 1].name) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
            // Compare contacts by phone number.
            else if (choice == 2)
            {
                if (strcmp(addressBook->contacts[j].phone,
                           addressBook->contacts[j + 1].phone) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
             // Compare contacts by email.
            else if (choice == 3)
            {
                if (strcmp(addressBook->contacts[j].email,
                           addressBook->contacts[j + 1].email) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
    }

    
    // Display the sorted contacts in table format.
    printf("\nContacts:\n");

    printf("\n+------------+------------+--------------------------------+\n");
    printf("| NAME       | PHONE      | EMAIL                          |\n");
    printf("+------------+------------+--------------------------------+\n");

    for (i = 0; i < addressBook->contactCount; i++)
    { // Print each contact from the address book.
    printf("| %-10s | %10s | %-30s |\n",
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
           addressBook->contacts[i].email);
        }
   printf("+------------+------------+--------------------------------+\n");
}

/**
 * Function: initialize
 * Description: Initializes the address book and loads
 *              existing contacts from the file.
 * Input: AddressBook pointer
 * Return: None
 */
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;// Start with an empty address book.
    loadContactsFromFile(addressBook); // Load existing contacts from the file.
}

/**
 * Function: saveAndExit
 * Description: Saves all contacts to the file and exits
 *              the program.
 * Input: AddressBook pointer
 * Return: None
 */
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save all contacts before exiting the program.
    exit(EXIT_SUCCESS);  // Terminate the program successfully.
}

/**
 * Function: validate_name
 * Description: Validates whether the name contains only
 *              alphabets, spaces, and periods.
 * Input: Name string
 * Return: 1 if valid, otherwise 0.
 */
int validate_name(char *str)
{
     int i;

    if(str[0] == '\0')// Check whether the name is empty.
        return 0;

    for(i = 0; str[i] != '\0'; i++) // Check each character of the name.
    { // Allow alphabets, spaces, and periods only.
        if(!((str[i] >= 'A' && str[i] <= 'Z') ||
             (str[i] >= 'a' && str[i] <= 'z') ||
             str[i] == ' ' || str[i] == '.'))
        {
            return 0;
        }
    }

    return 1;   
}
/**
 * Function: validate_phone
 * Description: Validates whether the phone number contains
 *              exactly 10 digits.
 * Input: Phone number string
 * Return: 1 if valid, otherwise 0.
 */
int validate_phone(char *str)
{
    int i;
    for(i = 0; str[i] != '\0'; i++)// Check whether all characters are digits.
    {
        if(!(str[i] >= '0' && str[i] <= '9'))
        {
            return 0;
        }
    }
    if(i != 10)// Check whether the phone number contains exactly 10 digits.
        return 0;

    return 1;  
}
/**
 * Function: is_duplicate_phone
 * Description: Checks whether the given phone number already exists.
 * Input: AddressBook pointer, phone number, and index to ignore.
 * Return: 1 if duplicate exists, otherwise 0.
 */
int is_duplicate_phone(AddressBook *addressBook, char *phone,int index)
{
    int i ;
    // Compare the phone number with all existing contacts.
    for(i=0;i<addressBook->contactCount;i++)
    {   // Ignore the current contact while editing.
        if(i != index && strcmp(addressBook->contacts[i].phone,phone)==0)
        {
            return 1;
        }
    }
    return 0;
}
/**
 * Function: validate_mail
 * Description: Validates the format of an email address.
 * Input: Email string
 * Return: 1 if valid, otherwise 0.
 */
int validate_mail(char *str)
{
    int i;
    int at = 0, dot = 0;
    int at_pos = -1, dot_pos = -1;
    // Check each character of the email.
    for(i = 0; str[i] != '\0'; i++)
    {   // Allow lowercase letters and digits.
        if((str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= '0' && str[i] <= '9'))
        {
            continue;
        }
        // Count the '@' symbol and store its position.
        if(str[i] == '@')
        {
            at++;
            at_pos = i;
        }// Count the dot and store its position.
        else if(str[i] == '.')
        {
            dot++;
            dot_pos = i;
        }
        else
        {
            return 0;// Reject any other character.
        }
    }
    // Check that exactly one '@' and one '.' are present.
    if(at != 1 || dot != 1)
        return 0;
    // Check that '@' appears before the dot.
    if(at_pos > dot_pos)
        return 0;
    // Check that there is text before '@'.
    if(at_pos == 0)
        return 0;
    // Check that there is text between '@' and '.'.
    if(dot_pos == at_pos + 1)
        return 0;
    // Check that there is text after the dot.
    if(str[dot_pos + 1] == '\0')
        return 0;
    return 1;
}
/**
 * Function: is_duplicate_email
 * Description: Checks whether the given email already exists.
 * Input: AddressBook pointer, email, and index to ignore.
 * Return: 1 if duplicate exists, otherwise 0.
 */
int is_duplicate_email(AddressBook *addressBook, char *email, int index)
{
    int i;
    // Compare the email with all existing contacts.
    for(i = 0; i < addressBook->contactCount; i++)
    {   // Ignore the current contact while editing.
        if(i != index && strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 1;
        }
    }

    return 0;
}

/**
 * Function: createContact
 * Description: Creates and adds a new contact to the address book.
 * Input: AddressBook pointer
 * Return: None
 */
void createContact(AddressBook *addressBook)
{    //Check whether the address book has reached its maximum capacity.
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full.\n");
        return;
    }


    char str1[30], str2[20], str3[30];
    int res1,res2,res3;
     // Read and validate the contact name.
    do
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", str1);
        res1 = validate_name(str1);
    if(res1 == 0)
    {
        printf("Invalid name! Name should contain only alphabets, spaces and '.'.\n");
    }
    }while(res1 == 0); // 0 means invalid
    // Read, validate, and check the phone number for duplicates.
    do
    {
        printf("Enter the Phone Number: ");
        scanf("%19s", str2);
        res2 = validate_phone(str2);
        if(res2 == 0)
        {
             printf("Invalid phone number! Phone number should contain exactly 10 digits.\n");
        }
        if(res2 == 1 && is_duplicate_phone(addressBook, str2 ,-1))// Check whether the phone number already exists.
        {
            printf("Phone number already exists\n");
            res2=0;
        }        
    } while (res2==0);
     // Read, validate, and check the email for duplicates.
     do
    {
    printf("Enter mail: ");
    scanf("%29s", str3);

    res3 = validate_mail(str3);
    if(res3 == 0)
    {
        printf("Invalid email! Please enter a valid email format.\n");
    }
    else if(is_duplicate_email(addressBook, str3, -1))
    {
        printf("Email already exists\n");
        res3 = 0;
    }

} while(res3 == 0);
    int ind = addressBook->contactCount;// Get the next available position in the contacts array.
    // Store the new contact details.
    strcpy(addressBook->contacts[ind].name, str1);
    strcpy(addressBook->contacts[ind].phone, str2);
    strcpy(addressBook->contacts[ind].email, str3);
    addressBook->contactCount++; // Increase the contact count after adding the contact.
    printf("Contact added successfully.\n");
}

/**
 * Function: searchContact
 * Description: Searches for a contact using name, phone, or email.
 * Input: AddressBook pointer
 * Return: None
 */
void searchContact(AddressBook *addressBook) 
{
    int choice;
    // Display search options.
    printf("\n+----------------------------------+\n");
    printf("|        SEARCH CONTACT            |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Search by Name                |\n");
    printf("| 2. Search by Phone               |\n");
    printf("| 3. Search by Email               |\n");
    printf("| 4. Exit                          |\n");
    printf("+----------------------------------+\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);  
    // Perform the search based on the selected option.
    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            break;

        case 2:
            search_by_phone(addressBook);
            break;

        case 3:
            search_by_email(addressBook);
            break;

        case 4:
            return;

        default:
            printf("Invalid choice\n");
    }
}

int search_by_name(AddressBook *addressBook)
{
    char name[30];
    char search_name[30];
    int i, j;
    int found = 0;
    int first_index = -1;
    // Read the name to search for.
    printf("Enter the name: ");
    scanf(" %29[^\n]", name);
    /* Convert entered name to lowercase */
    for(i = 0; name[i] != '\0'; i++)
    {
        if(name[i] >= 'A' && name[i] <= 'Z')
            search_name[i] = name[i] + 32;
        else
            search_name[i] = name[i];
    }
    search_name[i] = '\0';
    for(i = 0; i < addressBook->contactCount; i++)
    {
        char temp_name[50];
        /* Convert stored name to lowercase */
        for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++)
        {
            if(addressBook->contacts[i].name[j] >= 'A' &&
               addressBook->contacts[i].name[j] <= 'Z')
            {
                temp_name[j] = addressBook->contacts[i].name[j] + 32;
            }
            else
            {
                temp_name[j] = addressBook->contacts[i].name[j];
            }
        }
        temp_name[j] = '\0';
        /* Partial + case-insensitive match */
        if(strstr(temp_name, search_name) != NULL)
        {
            if(first_index == -1)
            {
                first_index = i;
            }
            found++;
        }
    }
    /* No contact found */
    if(found == 0)
    {
        printf("\nContact not found\n");
        return -1;
    }
    /* Multiple contacts found */
    if(found > 1)
    {
        int serial;
        int count = 0;

        printf("\nMultiple contacts are matching:\n");
        printf("\n+-----+------------+------------+--------------------------------+\n");
        printf("| NO. | NAME       | PHONE      | EMAIL                          |\n");
        printf("+-----+------------+------------+--------------------------------+\n");
        for(i = 0; i < addressBook->contactCount; i++)
        {
            char temp_name[50];

            for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++)
            {
                if(addressBook->contacts[i].name[j] >= 'A' &&
                addressBook->contacts[i].name[j] <= 'Z')
                {
                    temp_name[j] = addressBook->contacts[i].name[j] + 32;
                }
                else
                {
                    temp_name[j] = addressBook->contacts[i].name[j];
                }
            }
            temp_name[j] = '\0';
            if(strstr(temp_name, search_name) != NULL)
            {
                count++;
                printf("| %3d | %-10s | %-10s | %-30s |\n",
                count,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
        }
        printf("+-----+------------+------------+--------------------------------+\n");
        printf("\nEnter the serial number: ");
        scanf("%d", &serial);

        if(serial < 1 || serial > count)
        {
            printf("Invalid serial number.\n");
            return -1;
        }

    /* Find the actual contact corresponding to serial number */

        count = 0;

        for(i = 0; i < addressBook->contactCount; i++)
        {
            char temp_name[50];

            for(j = 0; addressBook->contacts[i].name[j] != '\0'; j++)
            {
                if(addressBook->contacts[i].name[j] >= 'A' &&
                addressBook->contacts[i].name[j] <= 'Z')
                {
                    temp_name[j] = addressBook->contacts[i].name[j] + 32;
                }
                else
                {
                    temp_name[j] = addressBook->contacts[i].name[j];
                }
            }

                temp_name[j] = '\0';

                if(strstr(temp_name, search_name) != NULL)
            {
                count++;

                if(count == serial)
                {
                    printf("\nSelected Contact:\n");
                    printf("Name  : %s\n", addressBook->contacts[i].name);
                    printf("Phone : %s\n", addressBook->contacts[i].phone);
                    printf("Email : %s\n", addressBook->contacts[i].email);

                    return i;
                }
            }
        }
    }   
    /* Exactly one contact found */
    /* Exactly one contact found */
    printf("\nContact found\n");
    printf("Name  : %s\n", addressBook->contacts[first_index].name);
    printf("Phone : %s\n", addressBook->contacts[first_index].phone);
    printf("Email : %s\n", addressBook->contacts[first_index].email);
    return first_index;
}
/**
 * Function: search_by_phone
 * Description: Searches for a contact using a phone number.
 * Input: AddressBook pointer
 * Return: Contact index if found, otherwise -1.
 */
int search_by_phone(AddressBook *addressBook)
{
    char phone[20];
    int i;
    printf("Enter the phone number: ");
    scanf("%19s", phone);// Read the phone number to search for.
    // Compare the entered phone number with all contacts.
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
            printf("\nContact found\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            return i;  // Return the index of the matching contact.
        }
       
    }

    printf("\nContact not found\n");
    return -1;// Return -1 when no matching contact is found.
}
/**
 * Function: search_by_email
 * Description: Searches for a contact using an email address.
 * Input: AddressBook pointer
 * Return: Contact index if found, otherwise -1.
 */
int search_by_email(AddressBook *addressBook)
{
    char email[30];
    int i;
    printf("Enter email: ");
    scanf("%29s", email);// Read the email address to search for.
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email)==0)
        {
            printf("\nContact found\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            return i;   // Return the index of the matching contact.
        }
    }
    printf("\nContact not found\n");
    return -1;// Return -1 when no matching contact is found.
}

/**
 * Function: editContact
 * Description: Modifies the details of an existing contact.
 * Input: AddressBook pointer
 * Return: None
 */
void editContact(AddressBook *addressBook)
{
    int searchChoice;
    int editChoice;
    int ind = -1;

    char str1[30];
    char str2[20];
    char str3[30];

    int res1, res2, res3;

    /* Select the search criterion. */
    printf("\n+----------------------------------+\n");
    printf("|         SEARCH CONTACT           |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Search by Name               |\n");
    printf("| 2. Search by Phone              |\n");
    printf("| 3. Search by Email              |\n");
    printf("| 4. Exit                         |\n");
    printf("+----------------------------------+\n");

    printf("Enter the choice: ");
    scanf("%d", &searchChoice);

    /* Search for the contact. */
    switch(searchChoice)
    {
        case 1:
            ind = search_by_name(addressBook);
            break;

        case 2:
            ind = search_by_phone(addressBook);
            break;

        case 3:
            ind = search_by_email(addressBook);
            break;

        case 4:
            return;

        default:
            printf("Invalid choice!!\n");
            return;
    }

    /* Stop if contact was not found. */
    if(ind == -1)
    {
        return;
    }

    /* Select the field to edit. */
    printf("\n+----------------------------------+\n");
    printf("|       SELECT FIELD TO EDIT       |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Name                          |\n");
    printf("| 2. Phone                         |\n");
    printf("| 3. Email                         |\n");
    printf("| 4. Exit                          |\n");
    printf("+----------------------------------+\n");

    printf("Enter the choice: ");
    scanf("%d", &editChoice);

    /* Edit the selected field. */
    switch(editChoice)
    {
        case 1:

            do
            {
                printf("Enter new name: ");

                /* Read the complete name including spaces. */
                scanf(" %29[^\n]", str1);

                res1 = validate_name(str1);

                if(res1 == 0)
                {
                    printf("Invalid name\n");
                }

            } while(res1 == 0);

            strcpy(addressBook->contacts[ind].name, str1);

            printf("\nName updated successfully!!\n");

            break;


        case 2:

            do
            {
                printf("Enter new phone number: ");

                scanf(" %19s", str2);

                res2 = validate_phone(str2);

                if(res2 == 0)
                {
                    printf("Invalid phone number!!\n");
                }
                else if(is_duplicate_phone(addressBook, str2, ind))
                {
                    printf("Phone number already exists!!\n");

                    res2 = 0;
                }

            } while(res2 == 0);

            strcpy(addressBook->contacts[ind].phone, str2);

            printf("\nPhone number updated successfully!!\n");

            break;


        case 3:

            do
            {
                printf("Enter new email: ");

                scanf(" %29s", str3);

                res3 = validate_mail(str3);

                if(res3 == 0)
                {
                    printf("Invalid email\n");
                }
                else if(is_duplicate_email(addressBook, str3, ind))
                {
                    printf("Email already exists!!\n");

                    res3 = 0;
                }

            } while(res3 == 0);

            strcpy(addressBook->contacts[ind].email, str3);

            printf("\nEmail updated successfully!!\n");

            break;


        case 4:
            return;


        default:
            printf("Invalid choice!!\n");
    }
}

/**
 * Function: deleteContact
 * Description: Deletes an existing contact from the address book.
 * Input: AddressBook pointer
 * Return: None
 */
void deleteContact(AddressBook *addressBook)
{

    int choice;
    int ind = -1;
    int i;
    char confirm;
    // Display options for selecting the contact to delete.
    printf("\nDelete Contact Menu\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");

    printf("Enter the choice: ");
    scanf("%d", &choice);  
    switch(choice)// Search for the contact using the selected field.
    {
        case 1:
            ind = search_by_name(addressBook);
            break;

        case 2:
            ind = search_by_phone(addressBook);
            break;

        case 3:
            ind = search_by_email(addressBook);
            break;

        case 4:
            return;

        default:
            printf("Invalid choice\n");
            return;
    }
    /*Contact not found*/
    if(ind == -1)
    {
        return;// Stop if the contact was not found.
    }
    printf("\nAre you sure you want to delete this contact?(y/n): "); // Ask the user to confirm deletion.
    scanf(" %c",&confirm);
    if(confirm == 'y' || confirm == 'Y')
    {
        // Shift the remaining contacts one position to the left.
        for(i=ind;i<addressBook->contactCount-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        printf("Contact deleted successfully.\n");
        addressBook->contactCount--;// Decrease the contact count after deletion.

    }
    else
    {
        printf("\nContact deletion cancelled.\n");//Inform the user that the deletion was cancelled.

    }
} 