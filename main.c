#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char name[25] , surname[25] , mail[50] , phone_number[30];

void remove_newline(char *str) 
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') 
	{
        str[len - 1] = '\0';  
    }
}

void person_add()
{
    FILE *file = fopen("directory.txt","a");
    
	if(file == NULL)
	{
        printf("file not opened!");
	}
	
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("person name : ");
    fgets(name,sizeof(name),stdin);
    fprintf(file,"Name: %s",name);

    printf("person surname : ");
    fgets(surname,sizeof(surname),stdin);
    fprintf(file,"Surname: %s",surname);

    printf("person mail : ");
    fgets(mail,sizeof(mail),stdin);
    fprintf(file,"Mail: %s",mail);

    printf("person phone number : ");
    fgets(phone_number,sizeof(phone_number),stdin);
    fprintf(file,"Phone Number: %s",phone_number);

    fprintf(file,"--------------------\n");

    printf("\nperson added.\n");
    fclose(file);
}

void person_delete()
{
	char name[25], surname[25], mail[50], phone_number[30];
	char temp_name[25], temp_surname[25], temp_mail[50], temp_phone[30];
	char line[100];
	
	FILE *file = fopen("directory.txt", "r");
	FILE *temp = fopen("temp.txt", "w");
	
	if (file == NULL || temp == NULL) 
	{
	    printf("File error!\n");
	    return;
	}
	
	int c;
	while ((c = getchar()) != '\n' && c != EOF); 
	
	    
	printf("Enter the name to delete: ");
	fgets(name, sizeof(name), stdin);
	remove_newline(name);
	
	printf("Enter the surname to delete: ");
	fgets(surname, sizeof(surname), stdin);
	remove_newline(surname);
	
	printf("Enter the mail to delete: ");
	fgets(mail, sizeof(mail), stdin);
	remove_newline(mail);
	
	printf("Enter the phone number to delete: ");
	fgets(phone_number, sizeof(phone_number), stdin);
	remove_newline(phone_number);
	
	int found = 0;
	
	while (fgets(line, sizeof(line), file)) 
	{
	    if (strncmp(line, "Name: ", 6) == 0) 
		{
	            
	        sscanf(line, "Name: %24[^\n]", temp_name);
	        fgets(line, sizeof(line), file);
	        sscanf(line, "Surname: %24[^\n]", temp_surname);
	        fgets(line, sizeof(line), file);
	        sscanf(line, "Mail: %49[^\n]", temp_mail);
	        fgets(line, sizeof(line), file);
	        sscanf(line, "Phone Number: %29[^\n]", temp_phone);
	
	            
	        if (strcmp(name, temp_name) == 0 &&
	        strcmp(surname, temp_surname) == 0 &&
	  	    strcmp(mail, temp_mail) == 0 &&
	        strcmp(phone_number, temp_phone) == 0) 
			{
	       	    found = 1;
	       	    fgets(line, sizeof(line), file);
				continue; 
	       	} 
			else 
			{    
	         	fprintf(temp, "Name: %s\n", temp_name);
	            fprintf(temp, "Surname: %s\n", temp_surname);
	            fprintf(temp, "Mail: %s\n", temp_mail);
	          	fprintf(temp, "Phone Number: %s\n", temp_phone);
	        }
	    }
		else 
		{			
			if(!(found && strncmp(line,"--------------------",20) == 0))
			{
	           	fprintf(temp, "%s", line);
	        }
	    }
	}
	fclose(file);
	fclose(temp);
	
	if (found) 
	{
	    remove("directory.txt");
	    rename("temp.txt", "directory.txt");
	    printf("Person deleted successfully!\n");
	} 
	else 
	{
	    printf("Person not found!\n");
	    remove("temp.txt");
	}
}


int person_update() {
    char name[25], temp_name[25], temp_surname[25], temp_mail[50], temp_phone[30];
    char mail[50], phone_number[30], line[100];
    int choice;

	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	    
    printf("Enter the name of the person to update: ");
    fgets(name, sizeof(name),stdin);
	remove_newline(name);

    if (!person_search(name)) 
	{
        return 0;
    }

    FILE *file = fopen("directory.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) 
	{
        printf("File error!\n");
        return 0;
    }

    while (fgets(line, sizeof(line), file)) 
	{
        if (strncmp(line, "Name: ", 6) == 0) 
		{
            sscanf(line, "Name: %24[^\n]", temp_name);
            fgets(line, sizeof(line), file);
            sscanf(line, "Surname: %24[^\n]", temp_surname);
            fgets(line, sizeof(line), file);
            sscanf(line, "Mail: %49[^\n]", temp_mail);
            fgets(line, sizeof(line), file);
            sscanf(line, "Phone Number: %29[^\n]", temp_phone);

            if (strcmp(name, temp_name) == 0) 
			{
                printf("What would you like to update?\n");
                printf("1. Name\n");
                printf("2. Surname\n");
                printf("3. Mail\n");
                printf("4. Phone Number\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                getchar(); 

                switch (choice) {
                    case 1:
                        printf("Enter new name: ");
                        fgets(temp_name, sizeof(temp_name), stdin);
                        remove_newline(temp_name);
                        break;
                    case 2:
                        printf("Enter new surname: ");
                        fgets(temp_surname, sizeof(temp_surname), stdin);
                        remove_newline(temp_surname);
                        break;
                    case 3:
                        printf("Enter new mail: ");
                        fgets(temp_mail, sizeof(temp_mail), stdin);
                        remove_newline(temp_mail);
                        break;
                    case 4:
                        printf("Enter new phone number: ");
                        fgets(temp_phone, sizeof(temp_phone), stdin);
                        remove_newline(temp_phone);
                        break;
                    default:
                        printf("Invalid choice!\n");
                        fclose(file);
                        fclose(temp);
                        return 0;
                }

                
                fprintf(temp, "Name: %s\n", temp_name);
                fprintf(temp, "Surname: %s\n", temp_surname);
                fprintf(temp, "Mail: %s\n", temp_mail);
                fprintf(temp, "Phone Number: %s\n", temp_phone);
            } 
			else 
			{
                
                fprintf(temp, "Name: %s\n", temp_name);
                fprintf(temp, "Surname: %s\n", temp_surname);
                fprintf(temp, "Mail: %s\n", temp_mail);
                fprintf(temp, "Phone Number: %s\n", temp_phone);
            }
        } 
		else 
		{
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    remove("directory.txt");
    rename("temp.txt", "directory.txt");
    printf("Person updated successfully!\n");
    return 1;
}


void person_list()
{
	FILE *file = fopen("directory.txt","r");
	
	if(file == NULL)
	{
        printf("file not opened!");
	}
	
	char temp_name[25], temp_surname[25], temp_mail[50], temp_phone[30];
	char line[100];
	
	while (fgets(line, sizeof(line), file)) 
	{
		if (strncmp(line, "Name: ", 6) == 0) 
		{
            sscanf(line, "Name: %24[^\n]", temp_name);
            fgets(line, sizeof(line), file);
            sscanf(line, "Surname: %24[^\n]", temp_surname);
            fgets(line, sizeof(line), file);
            sscanf(line, "Mail: %49[^\n]", temp_mail);
            fgets(line, sizeof(line), file);
            sscanf(line, "Phone Number: %29[^\n]", temp_phone);
			
			printf("----------\n");
            printf("Name: %s\n", temp_name);
            printf("Surname: %s\n", temp_surname);
            printf("Mail: %s\n", temp_mail);
            printf("Phone Number: %s\n", temp_phone);
            printf("----------\n");
		}
	}
	
	fclose(file);
}

int person_search(char perSearch[]) 
{
    char line[100];  

    FILE *file = fopen("directory.txt", "r");
    if (file == NULL) 
	{
        printf("Error opening file!\n");
        return 0;
    }

    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) 
	{
        if (strncmp(line, "Name: ", 6) == 0) 
		{
            sscanf(line, "Name: %24[^\n]", name);
            fgets(line, sizeof(line), file);
            sscanf(line, "Surname: %24[^\n]", surname);
            fgets(line, sizeof(line), file);
            sscanf(line, "Mail: %49[^\n]", mail);
            fgets(line, sizeof(line), file);
            sscanf(line, "Phone Number: %29[^\n]", phone_number);

            
            if (strcmp(name, perSearch) == 0) 
			{
                printf("Name: %s\n", name);
                printf("Surname: %s\n", surname);
                printf("Mail: %s\n", mail);
                printf("Phone Number: %s\n", phone_number);
                found = 1;
            }
        }

        
        if (strcmp(line, "--------------------\n") == 0) 
		{
            continue;
        }
    }

    fclose(file);

    if (!found) 
	{
        printf("Person not found!\n");
    }

    return found;
}


int main()
{
	int vote;
	char personName[25];
	while(vote != 6)
	{
		printf("-----------------------\n");
		printf("1-add person\n");
		printf("2-delete person\n");
		printf("3-update person\n");
		printf("4-list person\n");
		printf("5-search person\n");
		printf("6-exit\n");
		printf("Select the action you want to perform:\n");
		scanf("%d",&vote);
		printf("-----------------------\n");
		switch(vote)
		{	
			case 1:
				person_add();
				break;
			case 2:
				person_delete();
				break;
			case 3:
				person_update();
				break;
			case 4:
				person_list();
				break;
			case 5:
    			printf("Enter the name of the person you want to search: ");
    			fscanf(stdin, "%s", personName); 
				personName[strcspn(personName, "\n")] = '\0'; 
    			if(person_search(personName) == 1)
    				printf("\nPerson Found!\n");
    			
				break;
			case 6:
				printf("exiting.......");
				break;
			default :
				printf("You made the wrong choice.\n");
		}	
	}
    return 0;
}
