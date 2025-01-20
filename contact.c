#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"

void initialize(AddressBook *addressBook) {
	addressBook->contactCount = 0;
	populateAddressBook(addressBook);
	// Load contacts from file during initialization (After files)
    //loadContact(addressBook);
}
void listContacts(AddressBook *addressBook) //int sortCriteria
{
	printf("----------------------------------ADDRESS BOOK------------------------------------\n");
	printf("%15s | %20s | %15s | %20s\n","Serial_No","Name","phone","email");
	printf("----------------------------------------------------------------------------------\n");
	for(int i=0; i<addressBook->contactCount; i++)  //Display all contacts
	{
		printf("%15d | %20s | %15s | %20s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	printf("----------------------------------------------------------------------------------\n");
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
	char name[20];
	char phone[20];
	char email[20];
	int flag=1;     // Flag to validate phone number
	int Atsymbol=0,hasDot=0;   // Flag to validate email format
	printf("Enter the name:");
	scanf(" %[^\n]",name);
	strcpy(addressBook->contacts[addressBook->contactCount].name,name);    //store name in the contact
mobile:
	printf("Enter Mobile number:");
	scanf(" %s",phone);
	flag=1;
	if(strlen(phone)!=10)   // Check if phone length is exactly 10
	{
		flag=0;
	}
	for(int i=0;i<strlen(phone);i++)
	{
		if((phone[i]<'0')||(phone[i]>'9'))   // Check if all characters are digits
		{
			flag=0;
		}
	}
	for(int j=0; j<addressBook->contactCount; j++)
	{
		if(strcmp(addressBook->contacts[j].phone,phone)==0)  // Check for duplicate phone number
		{
			flag=0;
		}
	}
	if(!flag)    //if phone number validation fails
	{
		int ch;     // Choice for re-entering or exiting
		printf("1.Re-Enter the number\n");
		printf("2.Exit\n");
		printf("Enter choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				goto mobile;
				break;
			case 2:
				return ;
				break;
		}
	}
	strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);  // Store validated phone number

email:
	printf("Enter Email id:");
	scanf("%s",email);
	Atsymbol = 0;
	hasDot = 0;
	for(int j=0;j<strlen(email);j++)
	{
		if(email[j]=='@')
		{
			Atsymbol=1;    // Mark presence of '@'
		}
		else if(Atsymbol && email[j]=='.')
		{
			hasDot=1;     // Mark presence of '.' after '@'
			strcpy(addressBook->contacts[addressBook->contactCount].email,email);   // Store validated email
			addressBook->contactCount++;  // Increment contact count
		}
	}
	if(!(Atsymbol && hasDot))   // If email validation fails
	{
		int choice;     // Choice for re-entering or exiting
		printf("1.Re-Enter the mail\n");
		printf("2.Exit\n");
		printf("Enter choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				goto email;
				break;
			case 2:

				return ;
				break;
		}
	}
}
void searchContact(AddressBook *addressBook) 
{
	/* Define the logic for search */
	char input[10];
	char name[20];
	char phone[20];
	char email[20];
	int option;  // Variable to store the user's choice
	int flag = 0;  // Flag to indicate if a contact is found
	printf("1.Search by Name:\n ");
	printf("2.Search by Phone:\n");
	printf("3.Search by Email:\n");
	printf("Enter the option: ");
	scanf(" %[^\n]",input);
	if(sscanf(input, "%d",&option) != 1)
	{
		printf("Invalid input. Please enter a number.\n");
		return;
	}
	switch(option)
	{
		case 1 :
			printf("Enter the Name: ");
			scanf(" %[^\n]",name);
			printf("---------------------------ADDRESS BOOK-------------------------------\n");
			printf("%20s | %15s | %20s\n","Name","phone","email");
			printf("----------------------------------------------------------------------\n");

			for(int i=0;i<addressBook->contactCount;i++)      
			{
				if(strstr(addressBook->contacts[i].name,name)!=0)      // Check if the entered name matches a contact
				{
					flag = 1;   // Contact found
					printf("%20s |",addressBook->contacts[i].name);
					printf("%15s |",addressBook->contacts[i].phone);
					printf("%20s\n",addressBook->contacts[i].email); 
				}
			}
			printf("----------------------------------------------------------------------\n");
			break;

		case 2 :

			printf("Enter the mobile number: ");
			scanf(" %[^\n]",phone);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(strstr(addressBook->contacts[i].phone,phone)!=0)     // Check if the entered phone number matches a contact
				{
					flag = 1 ;  // Contact found
					printf("%s ",addressBook->contacts[i].name);
					printf("%s ",addressBook->contacts[i].phone);
					printf("%s\n",addressBook->contacts[i].email);
				}
			}
			break;

		case 3 :

			printf("Enter the email: ");
			scanf(" %[^\n]",email);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(strstr(addressBook->contacts[i].email,email)!=0)    // Check if the entered email matches a contact
				{
					flag = 1 ;   //contact found
					printf("%s ",addressBook->contacts[i].name);
					printf("%s ",addressBook->contacts[i].phone);
					printf("%s\n",addressBook->contacts[i].email);
				}
			}
			break;
	}
	if(flag==0)
	{
		printf("Contact not found\n");   //no contact was found
	}
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int option;
	char input[10];
	printf("Delete by:\n");
	printf("1. Name\n");
	printf("2. Phone number\n");
	printf("3. Email\n");
	printf("Enter your choice:");
	scanf(" %[^\n]",input);
	if(sscanf(input, "%d",&option) != 1)
	{
		printf("Invalid input. Please enter a number.\n");
		return;
	}
	char Deleteterm[30];
	int found = 0;
	switch(option)
	{
		case 1:
			//delete contact by name
			printf("Enter the name to delete: ");
			scanf(" %[^\n]", Deleteterm);
			found = 0;
			for (int i = 0; i < addressBook->contactCount; i++) // Display all contacts with the matching name
			{
				if (strstr(addressBook->contacts[i].name, Deleteterm) != NULL)    // Match found
				{
					printf("Found contact %d:\n", i + 1);
					printf(" %s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					found = 1;
				}
			}
			if (!found)
			{
				printf("No contact found with that name.\n");
			}
			else
			{
				// Ask the user to specify the contact to delete
				int delchoice;  // Variable to store the contact number to delete
				printf("Enter the serial number of the contact to delete: ");
				if (scanf("%d", &delchoice) != 1 || delchoice <= 0 || delchoice > addressBook->contactCount)
				{
					printf("Invalid choice. No contact deleted.\n");
				}
				else
				{
					delchoice--; // Convert to zero-based index

					// Delete the selected contact
					char confirm;
					printf("Are you sure you want to delete the contact (y/n) : ");
					scanf(" %c",&confirm);
					if(confirm == 'y' || confirm == 'Y')
					{
						for (int j = delchoice; j < addressBook->contactCount - 1; j++) 
						{
							addressBook->contacts[j] = addressBook->contacts[j + 1];
						}
						addressBook->contactCount--; // Decrease the count
						printf("Contact deleted successfully.\n");
					}
				}
			}
			break;

		case 2:
			// delete using phone number
			printf("Enter the phone number: ");
			scanf("%29s", Deleteterm);
			found = 0;
			for (int i = 0; i < addressBook->contactCount; i++)
			{
				if (strstr(addressBook->contacts[i].phone, Deleteterm) != NULL)    //match phone number
				{
					printf("Found contact %d: %s %s %s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
					found = 1;
				}
			}
			if (!found)
			{
					printf("No contact found with that phone number.\n");
			}
			else
			{
					// Ask the user to specify the contact to delete
					int delchoice;
					printf("Enter the serial number of the contact to delete: ");
					if (scanf("%d", &delchoice) != 1 || delchoice <= 0 || delchoice > addressBook->contactCount)
					{
							printf("Invalid choice. No contact deleted.\n");
					}
					else
					{
							delchoice--; // Convert to zero-based index
							// Delete the selected contact
							char confirm;
							printf("Are you sure you want to delete the contact (y/n) : ");
							scanf(" %c",&confirm);
							if(confirm == 'y' || confirm == 'Y')
							{
								for (int j = delchoice; j < addressBook->contactCount - 1; j++)
								{
									addressBook->contacts[j] = addressBook->contacts[j + 1];
								}
								addressBook->contactCount--; // Decrease the count
								printf("Contact deleted successfully.\n");
							}
					}
			}
			break;
					
		case 3:
			  // delete using mail ID
			printf("Enter the email: ");
			scanf(" %[^\n]", Deleteterm);
			found = 0;
			for (int i = 0; i < addressBook->contactCount; i++)
			{
					if (strstr(addressBook->contacts[i].email,Deleteterm)!=NULL)
					{
							printf("Found contact: %d   %s   %s   %s\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
							found = 1;
					}
			}
			if (!found)
			{
				printf("No contact found.\n");
			}
			else
			{
					int delchoice; //ask the user to specify the contact to delete
					printf("Enter the serial number of the contact to delete: ");
					if (scanf("%d", &delchoice) != 1 || delchoice <= 0 || delchoice > addressBook->contactCount) {
							printf("Invalid choice. No contact deleted.\n");
					}
					else
					{
							delchoice--;
							// Delete the selected contact
							char confirm;
							printf("Are you sure you want to delete the contact (y/n) : ");
							scanf(" %c",&confirm);
							if(confirm == 'y' || confirm == 'Y')
							{
								for (int j = delchoice; j < addressBook->contactCount - 1; j++) 
								{
									addressBook->contacts[j] = addressBook->contacts[j + 1];
								}
								addressBook->contactCount--; // Decrease the count
								printf("Contact deleted successfully.\n");
							}
					}
			}
			break;
		default:
                printf("Invalid choice.\n");
                break;
	}
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int option;
	char input[10];
	// Display editing menu
	printf("1. Name\n2. Phone\n3. Email\n");
	printf("Enter the option you want to edit: ");
	scanf(" %[^\n]",input);
	if(sscanf(input, "%d",&option) != 1)
	{
		printf("Invalid input. Please enter a number.\n");
		return;
	}
	switch (option) // Switch case based on the selected option
	{
		case 1: // Edit Name
			{
				char name[100];
				printf("Enter the name to search: ");
				scanf(" %[^\n]",name); // Read the name

				int matches = 0, indices[100];  // To store indices of matching contacts
				for (int i = 0; i < addressBook->contactCount; i++)
				{
					if (strstr(addressBook->contacts[i].name,name) != 0)  // Check if the name matches any contact
					{
						indices[matches++] = i;  // Store the index of the matching contact
					}
				}

				if (matches == 0)
				{
					printf("No matching contacts found. Try again.\n");    // No matches found
				}
				else if (matches == 1)
				{
					// One match found, proceed to edit
					char newName[100];
					printf("Enter the new name: ");
					scanf(" %[^\n]", newName);    // Read the new name
					strcpy(addressBook->contacts[indices[0]].name, newName);  // Update the name
					printf("Name edited successfully.\n");
				}
				else
				{
					printf("Multiple contacts found:\n");   // Multiple matches found, display options
					for (int i = 0; i < matches; i++)
                    {
						// Display each matching contact
						printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1,addressBook->contacts[indices[i]].name,addressBook->contacts[indices[i]].phone,addressBook->contacts[indices[i]].email);
					}
					int choice;
					printf("Enter the serial number you want to edit: ");
					scanf("%d", &choice);
					if (choice > 0 && choice <= matches)
					{
						char newName[100];
						printf("Enter the new name: ");
						scanf(" %[^\n]", newName);  // Read the new name
						strcpy(addressBook->contacts[indices[choice - 1]].name, newName);
						printf("Name edited successfully.\n");
					}
					else
					{
						printf("Invalid choice. Try again.\n");
					}
				}
				break;
			}
		case 2: // Edit Phone Number
			{

				char oldPhone[20];
				printf("Enter the old phone number: ");
				scanf(" %[^\n]", oldPhone);  // Read the old phone number

				int indices[100];
				int matches=0;       
				for (int i = 0; i < addressBook->contactCount; i++)
				{
					if (strstr(addressBook->contacts[i].phone,oldPhone) != NULL)  // Check if the phone number matches any contact
					{
						indices[matches++] = i;   // Store the index of the matching contact
					}
				}

				if (matches==0)
				{
					printf("No matching contacts found");
				}
				else
				{
					printf("Contact found\n");
					for (int i = 0; i < matches; i++)
					{
						printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1,             // Display each matching contact
								addressBook->contacts[indices[i]].name,
								addressBook->contacts[indices[i]].phone,
								addressBook->contacts[indices[i]].email);
					}
				}
				int choice;
				printf("Enter the serial number you want to edit: ");
				scanf("%d", &choice);
				if (choice > 0 && choice <= matches)
				{
					char newPhone[20];
					printf("Enter the new phone number: ");
					scanf(" %[^\n]", newPhone);

					int isValid = 1, isUnique = 1;
					if (strlen(newPhone) != 10)    
					{
						isValid = 0;                // Check if the phone number length is valid
					}
					else
					{
						for (int i = 0; i < 10; i++)
						{
							if (newPhone[i] < '0' || newPhone[i] > '9')    // Check if all characters are digits
							{
								isValid = 0;
								break;
							}
						}
					}

					for (int i = 0; i < addressBook->contactCount; i++)
					{
						if (strcmp(newPhone, addressBook->contacts[i].phone) == 0)   // Check if the phone number is unique
						{
							isUnique = 0;
							break;
						}
					}

					if (isValid && isUnique)
					{
						strcpy(addressBook->contacts[indices[choice-1]].phone, newPhone); //Valid and unique phone number, update it
						printf("Phone number edited successfully.\n");
						break;
					}
					else
					{
						printf("Invalid or duplicate phone number.\n");
						printf("1. Re-enter phone number\n2. Exit\n");
						int choice;
						scanf("%d", &choice);
						if (choice != 1)
						{
							break;
						}
					}
				}
				else
				{
					printf("No matching contact found. Try again.\n");
				}
				break;
			}

		case 3: // Edit Email
			{
				char oldEmail[100];
				printf("Enter the old email: ");
				scanf(" %[^\n]", oldEmail);

				int indices[100];
				int matches=0;
				for (int i = 0; i < addressBook->contactCount; i++)
				{
					if (strstr(addressBook->contacts[i].email,oldEmail) != NULL)
					{
						indices[matches++] = i;
					}
				}
				if (matches==0)
				{
					printf("No matching contacts found");
				}
				else
				{
					printf("Contact found\n");
					for (int i = 0; i < matches; i++)
					{
						printf("%d. Name: %s, Phone: %s, Email: %s\n", i + 1,
								addressBook->contacts[indices[i]].name,
								addressBook->contacts[indices[i]].phone,
								addressBook->contacts[indices[i]].email);
					}
				}
				int choice;
				printf("Enter the serial number you want to edit: ");
				scanf("%d", &choice);
				if (choice > 0 && choice <= matches)
				{
					char newEmail[50];
					printf("Enter the new email: ");
					scanf(" %[^\n]", newEmail);
					if (strstr(newEmail, "@") != 0 && strstr(newEmail, ".com") != NULL)   // Validate email format (basic validation)
					{
						strcpy(addressBook->contacts[indices[choice-1]].email, newEmail);
						printf("Email edited successfully.\n");
						break;
					}
					else
					{
						printf("Invalid or duplicate email.\n");
						printf("1. Re-enter email\n2. Exit\n");
						int choice;
						scanf("%d", &choice);
						if (choice != 1)
						{
							break;
						}
					}
				}
				else
				{
					printf("No matching contact found. Try again.\n");

 				}
				break;
			}
		default:
			printf("Invalid input. Try again.\n");
	}
}
void saveContact(AddressBook *addressBook)
{
        FILE *fptr=fopen("contacts.csv","w");    // Open the file "contacts.csv" in write mode ("w")
        fprintf(fptr,"#%d\n",addressBook->contactCount);
        for(int i=0;i<addressBook->contactCount;i++)  // Loop through each contact in the address book and save the details
        {
            fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
	    printf("contact saved successfully");
        fclose(fptr);
}
void loadContact(AddressBook *addressBook)
{
        // Open the file "contacts.csv" in read mode ("r")
        FILE *fptr=fopen("contacts.csv","r");
        fscanf(fptr,"#%d",&addressBook->contactCount);  // Read the total number of contacts from the file
        for(int i=0;i<addressBook->contactCount;i++)  // Loop through the file to read each contact's details
        {
                // Read each contact's name, phone, and email (comma-separated) and store them in the address book
                fscanf(fptr,"\n%[^,],%[^,],%[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        fclose(fptr);  // Close the file after reading is complete
}
