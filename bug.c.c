#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#define max 20
struct tm* local; 
struct bug  
{ 
    int id; 
    char status[20]; 
    char name[20];
    char type[20];
    char priority[20];
    char description[50]; 
    char time[20];
	int emp; 
}logger; 



int Manager_Assign()
{
	
    int id;
    char cho[20]="Assigned";
    FILE *infile,*cha;   
    cha=fopen("change.txt","w"); 
    infile = fopen ("person.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr,"\nNo Bugs \n"); 
        return 0;
    }
    while(fread(&logger, sizeof(struct bug), 1, infile))
    {   
        printf ("id = %d \nstatus = %s \nname=%s \ntype=%s \npriority=%s \ndescription=%s\ntime=%s\n\n",
                      logger.id,logger.status, logger.name,logger.type,logger.priority,logger.description,logger.time);
    }
    printf("\nWhich bug would you like to assign to employee?\nPlease enter bug id\n");
    scanf("%d",&id);
	while(fread(&logger, sizeof(struct bug), 1, infile))
    {   
    	if(logger.id==id)
    	{
	        strcpy(logger.status,cho);
	        fwrite (&logger, sizeof(struct bug), 1, cha);
		}
		else
			fwrite (&logger, sizeof(struct bug), 1, cha);
    }  
    fclose(infile);
    //fclose(cha);
    return 1;
}

int Manager_View()
{
	FILE *infile;
	int choice;
	 char name[10],priority[20],status[20];
	infile = fopen ("person.txt", "r"); 
    if (infile == NULL) 
    { 
        return 0;
    }
    //fseek(infile, 0, SEEK_SET );
    printf("How would you like to list the bugs\n1)Same person\n2)same category\n3)same status\n4)Everything\n");
    scanf("%d",&choice);
    printf("\n");
    switch (choice)
    {
    case 1:
        printf("Enter name\n");
        scanf("%s",name);
        while(fread(&logger, sizeof(struct bug), 1, infile))
            if(strcmp(logger.name, name) == 0)
                 printf ("id = %d \nstatus = %s \nname=%s \ntype=%s \npriority=%s \ndescription=%s\ntime=%s\n\n",
                      logger.id,logger.status, logger.name,logger.type,logger.priority,logger.description,logger.time); 
        break;
    case 2:
        printf("Enter priority- Low,Medium,High\n\n");
        scanf("%s",priority);
        while(fread(&logger, sizeof(struct bug), 1, infile))
            if(strcmp(logger.priority, priority) == 0)
                 printf ("id = %d \nstatus = %s \nname=%s \ntype=%s \npriority=%s \ndescription=%s\ntime=%s\n\n",
                      logger.id,logger.status, logger.name,logger.type,logger.priority,logger.description,logger.time); 
        break;
    case 3:
        printf("Enter status- Not assigned,Being fixed,Fixed,Delivered\n\n");
        scanf("%s",status);
        while(fread(&logger, sizeof(struct bug), 1, infile))
            if(strcmp(logger.status, status) == 0)
                 printf ("id = %d \nstatus = %s \nname=%s \ntype=%s \npriority=%s \ndescription=%s\ntime=%s\n\n",
                      logger.id,logger.status, logger.name,logger.type,logger.priority,logger.description,logger.time); 
    default:
        while(fread(&logger, sizeof(struct bug), 1, infile))
                printf ("id = %d \nstatus = %s \nname=%s \ntype=%s \npriority=%s \ndescription=%s\ntime=%s\n\n",
                      logger.id,logger.status, logger.name,logger.type,logger.priority,logger.description,logger.time); 
        break;
    } 
    fclose (infile);  
    return 1;
}

void write()
{
    FILE *outfile; 
    outfile = fopen ("person.txt", "a"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    }  
    fwrite (&logger, sizeof(struct bug), 1, outfile);
//	fprintf(outfile,"\n");   
    if(fwrite != 0)  
        printf("contents to file written successfully !\n"); 
    else 
        printf("error writing file !\n");  
    fclose (outfile); 
}

void change()
{   
    FILE *infile,*cha;   
    infile = fopen ("person.txt", "r");
    cha=fopen("change.txt","w"); 
    char cho[10];
    int id;
    printf("\nBug Descriptions: \n ");
    while(fread(&logger, sizeof(struct bug), 1, infile))
    {   
        printf ("id = %d \nstatus = %s \nname=%s \ntype=%s \npriority=%s \ndescription=%s\ntime=%s\n\n",
                      logger.id,logger.status, logger.name,logger.type,logger.priority,logger.description,logger.time);
    }
    printf("\nWhich bug's status would you like to change?\nPlease enter bug id\n");
    scanf("%d",&id);
    fseek(infile, 0, SEEK_SET );
    while(fread(&logger, sizeof(struct bug), 1, infile))
    {   
    	if(logger.id==id)
    	{
			printf("How would you like to change the status?\n1)Being fixed\n2)Fixed\n3)Delivered\n");
	    	scanf("%s",cho);
	        strcpy(logger.status,cho);
	        fwrite (&logger, sizeof(struct bug), 1, cha);
		}
		else
			fwrite (&logger, sizeof(struct bug), 1, cha);
    }  
    fclose(infile);
    fclose(cha);
}
void input()
{     
    srand(time(NULL));
    logger.id=rand();
    printf("Please enter the details of the bug\n");
    fgets(logger.description,50,stdin);
    strtok(logger.description, "\n");
    printf("Enter your Name\n");
    fgets(logger.name,max,stdin);
    strtok(logger.name, "\n");
    printf("Enter the type of bug - Major,Minor,Cosmetic\n");
    fgets(logger.type,max,stdin);
    strtok(logger.type, "\n");
    printf("Enter the priority of bug - Low,Medium,High\n");
    fgets(logger.priority,max,stdin);
    strtok(logger.priority, "\n");
    strcpy(logger.status,"Not assigned");
    strcpy(logger.time,asctime(local));
}
void main()
{   
    time_t t = time(NULL);
    local = localtime(&t); 
    char s[10];
    int choice;
    printf("-----------BUG TRACKING SYSTEM-------------\n");
    do{
    printf("Enter your designation in words\n1)Manager\n2)User\n3)Employee\n");
    scanf("%s",s);
    fflush(stdin);
    if (strcmp(s, "Manager") == 0) 
    {
      int test=Manager_Assign();
    	remove("person.txt");  
    	rename("change.txt","person.txt"); 
 		int test1=Manager_View();
    } 
    else if (strcmp(s, "User") == 0)
    {
      input();
      write();
    }    
    else if (strcmp(s, "Employee") == 0)
    {
      change(); 
      remove("person.txt");  
      rename("change.txt","person.txt"); 
    }
    else
    	printf("Invalid designation");
    printf("\nDo you want to continue? \nPress 1 to continue\nPress 0 to exit\n");
    scanf("%d",&choice);
    printf("\n\n");
    }while(choice==1);
}



