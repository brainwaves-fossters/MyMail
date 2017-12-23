#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

struct pass
{
 char user[20],pass[20];
}login;

struct node
{
 struct node *prev;
 char from[20];
 char subject[30];
 char msg[100];
 struct node *next;
};

struct node *getnode()
{
 return (struct node*)malloc(sizeof(struct node));
}

int getCount(char[]);
void mails(char[]);
struct node* reload(struct node*,char[]);
struct node *addFront( struct node * );
int igetcount(char[],struct node*);
struct node *delete(struct node *);

void main()
{
  int ch, flag = 0, n, i;
 FILE *fp1,*fp2;
 char name[20],pword[20],s1[20];
 clrscr();
 while(1)
 {
   clrscr();
   printf("1.Add new user\n2.Login\n3.exit\nEnter your choice: ");
   scanf("%d",&ch);
   fflush(stdin);
   switch(ch)
   {
   case 1 :
	clrscr();
	fp1 = fopen("passwords.dat","a");
	printf("\nEnter username : ");
	gets(login.user);
	printf("Note : The password is invisible\nDo not use backspace while entering password\n\n");
	getch();
	fflush(stdin);
	strcpy(login.pass,getpass("Enter password : "));
	fwrite(&login,sizeof(login),1,fp1);
	fclose(fp1);
	clrscr();
	printf("Your id has been successfully created\nPlease login in order to use it");
	getch();
	break;
      case 2 :
	clrscr();
	fp1 = fopen("passwords.dat","r");
	if(fp1 == NULL)
	{
		printf("Please create 2 id's\n");
		getch();
		break;
	}
	printf("Note : The password is invisible\nDo not use backspace while entering password\nPress any key to continue...");
	getch();
	clrscr();
	gotoxy(30,12);
	printf("Username : ");
	gets(name);
	gotoxy(30,14);
	strcpy(pword,getpass("Password : "));
	strcpy(s1,"passwords.dat");
	n = getCount(s1);
	clrscr();
	for(i=1; i<=n; i++)
	{
	fread(&login , sizeof(login), 1, fp1);
	if((strcmp(login.user,name) == 0) && (strcmp(login.pass,pword) == 0))
	{
		printf("Login succesfull\nPress any key to continue...");
		getch();
		mails(name);
		flag = 1;
		break;
	}
	}
	if(flag != 1)
	{
		printf("OOPS! Username and password does'nt match\nPress any key to continue...");
		getch();
	}
	fclose(fp1);
	break;
       case 3 :
		exit(0);
   }
 }
}

int getCount(char name[])
{
 FILE *fp, *fp3;
 int n;
 fp = fopen(name,"r");
 fseek(fp,0,2);
 n = ftell(fp)/sizeof(login);
 fclose(fp);
 return n;
}

int igetcount(char name[],struct node *T)
{
 FILE *fp;
 int n;
 fp = fopen(name,"r");
 fseek(fp,0,2);
 n = ftell(fp)/sizeof(*T);
 fclose(fp);
 T = T;
 return n;
}

void mails(char name[])
{
  int ch, i, count = 0, choice, del, nul = 0;
  char s1[20], s2[20], s3[20],usr[20], to[20], s4[20];
  struct node *inbox, *outbox, *iref, *oref, *Temp;
  FILE *fpi, *fpo;
  inbox = NULL;
  outbox = NULL;
  oref = NULL;
  strcpy(s1,name);
  strcat(s1,".dat");
  strcpy(s3,name);
  strcpy(usr,"o");
  strcat(usr,s3);
  strcat(usr,".dat");
  inbox = reload(inbox,s1);
  if(inbox != NULL)
  {
	while(inbox->prev != NULL)
		inbox = inbox->prev;
  	iref = inbox;
   }
  else
	nul = 1;
  outbox = reload(outbox,usr);
  if(outbox != NULL)
	oref = outbox;
  while(1)
  {
   clrscr();
   printf("Welcome %s\n\n1.Compose\n2.Inbox\n3.Sent mails\n4.Search\n5.Delete\n6.Log out\nEnter your choice : ",name);
   scanf("%d",&ch);
   fflush(stdin);
   switch(ch)
   {
     case 1 :
		outbox = addFront( outbox );
		strcpy(s2,outbox->from);
		strcpy(to,outbox->from);
		strcat(to,".dat");
		fpi = fopen(to,"a");
		strcpy(outbox->from,name);
		fwrite(outbox, sizeof(*outbox), 1, fpi);
		fclose(fpi);
		strcpy(outbox->from,s2);
		oref = outbox;
		break;

      case 2 :
		count = 0;
		if(inbox == NULL)
		{
			clrscr();
			printf("Inbox is empty\nPress any key to continue...");
			getch();
			break;
		}
		inbox = iref;
		while(inbox->next != NULL)
		{
			count++;
			inbox = inbox->next;
		}
		count++;
		for(i = 0; i < count && i > -1; )
		{
			clrscr();

			printf("From    : %s\nSubject : %s\nMessage : %s\n",inbox->from,inbox->subject,inbox->msg);
			printf("\n\n\n\[P]rev   [N]ext  [Q]uit");
			fflush(stdin);
			ch = getch();
			if( ch == 'p' )
			{
				inbox = inbox->next;
				i--;
			}
			else if( ch == 'n')
			{
				inbox = inbox->prev;
				i++;
			}
			else if( ch == 'q')
				goto ilast;
		}
		ilast :
			inbox = iref;

			break;

     case 3 :
		count = 0;
		if(outbox == NULL)
		{
			clrscr();
			printf("Sent items is empty\nPress any key to continue...");
			getch();
			break;
		}
		outbox = oref;
		while(outbox != NULL)
		{
			count++;
			outbox = outbox->next;
		}
		outbox = oref;
		for(i = 0; i < count && i > -1; )
		{
			clrscr();

			printf("From    : %s\nSubject : %s\nMessage : %s\n",outbox->from,outbox->subject,outbox->msg);
			printf("\n\n\n\[P]rev   [N]ext  [Q]uit");
			fflush(stdin);
			ch = getch();
			if( ch == 'p' )
			{
				outbox = outbox->prev;
				i--;
			}
			else if( ch == 'n')
			{
				outbox = outbox->next;
				i++;
			}
			else if( ch == 'q')
				goto olast;
		}
		olast :
			outbox = oref;

			break;

    case 4 :
		clrscr();
		printf("Enter name of the user : ");
		gets(s4);
		if(inbox == NULL && outbox == NULL)
		{
			clrscr();
			printf("No messages from the given user\n\nPress any key to continue...");
			getch();
			break;
		}
		inbox = iref;
		outbox = oref;
		while(inbox != NULL)
		{
			if(strcmp(inbox->from,s4) == 0)
			{
				clrscr();
				printf("From    : %s\nSubject : %s\nMessage : %s\n\n\nPress any key to continue...",inbox->from,inbox->subject,inbox->msg);
			getch();
			}
			inbox = inbox->next;
		}
		while(outbox != NULL)
		{
			if(strcmp(outbox->from,s4) == 0)
			{
				clrscr();
				printf("From    : %s\nSubject : %s\nMessage : %s\n\n\nPress any key to continue...",outbox->from,outbox->subject,outbox->msg);
			getch();
			}
			outbox = outbox->next;
		}
		inbox = iref;
		outbox = oref;
		break;

     case 5 :
		clrscr();
		printf("1.Delete inbox\n2.Delete sent items\nEnter your choice : ");
		scanf("%d",&choice);
		if(choice == 1)
		{
		if(inbox != NULL)
			inbox = iref;
		if(inbox == NULL)
		{
			clrscr();
			printf("Inbox is empty");
			getch();
			break;
		}
		inbox = delete(inbox);
		iref = inbox;
		}
		else if(choice == 2)
		{
		if(outbox != NULL)
			outbox = oref;
		if(outbox == NULL)
		{
			clrscr();
			printf("Sent items is empty");
			getch();
			break;
		}
		outbox = delete(outbox);
		oref = outbox;
		}
		break;

     case 6 :
		count = 0;
		fpi = fopen(s1,"wb");
		if(nul == 1)
			goto next;
		if(inbox != NULL)
			inbox = iref;
		else
		{
			goto next;
		}
		while(inbox->next != NULL)
		{
			count++;
			inbox = inbox->next;
		}
		count++;
		inbox = iref;
		for(i = 0; i < count; i++)
		{
			fwrite(inbox, sizeof(*inbox), 1, fpi);
			inbox = inbox->next;
		}
		next : 
		fclose(fpi);
		count = 0;
		fpo = fopen(usr,"wb");
		outbox = oref;
		while(outbox != NULL)
		{
			count++;
			outbox = outbox->next;
		}
		outbox = oref;
		for(i = 0; i < count; i++)
		{
			fwrite(outbox, sizeof(*outbox), 1, fpi);
			outbox = outbox->next;
		}
		end :
		fclose(fpo);
		exit(0);
    
    		}
	 }
}

struct node* reload(struct node *H,char s1[])
{
  int count = 0, i, len;
  FILE *fpi;
  struct node *T, *N, *M;
  T = NULL;
  N = NULL;
  M = NULL;
  fpi = fopen(s1,"r");
  count = igetcount(s1,M);
  fseek(fpi,0,0);
	 for(i = 0; i < count; i++)
	{
			N = getnode();
			fread(N , sizeof(*N), 1, fpi);
			N->next = N->prev = NULL;
			len = strlen(N->from);
			N->from[len] = '\0';
			len = strlen(N->subject);
			N->subject[len] = '\0';
			len = strlen(N->msg);
			N->msg[len] = '\0';
			if( H == NULL )
			{
				H = N;
			 }
			else
			 {
				T = H;
				while( T->next != NULL)
				T = T->next;

				T->next = N;
				N->prev = T;
			  }
	   }
	fclose(fpi);
	return H;
   }

  struct node *addFront( struct node *H )
	{
		struct node *N;
		N = getnode( );
		clrscr();
		printf("To      : ");
		gets(N->from);
		printf("Subject : ");
		gets(N->subject);
		printf("Message : ");
		gets(N->msg);
		if(H != NULL)
		{
		N->next = H;
		N->prev = NULL;
		H->prev = N;
		H = N;
		}
		else
		{
			N->next = N->prev = NULL;
			H = N;
		}
		return H;
	  }

struct node *delete(struct node *H)
	{
		int count = 0, i, del, flag = 0;
		struct node *Temp,*ref;
		ref = H;
		while(H != NULL)
		{
			count++;
			H = H->next;
		}
		H = ref;
		clrscr();
		for(i = 1; i <= count; i++)
		{
			printf("\n%d.\nFrom    : %s\nSubject : %s\nMessage : %s\n",i,H->from,H->subject,H->msg);
			getch();
			H = H->next;
		}
		H = ref;
		printf("Enter email number to delete : ");
		scanf("%d",&del);
		if(del > count)
		{
			printf("\nOOPS!!wrong number entered!\nTry again");
			getch();
			goto dlast;
		}
		if(del == 1)
		{
			Temp = ref;
			ref = ref->next;
			if(ref == NULL)
			{
				H = NULL;
				printf("Deleted successfully...");
				getch();
				goto dlast;
			}
			ref->prev = NULL;
			Temp = NULL;
			flag = 1;
		}

		else
		{
			Temp = H;
			for(i = 1; i < del; i++)
			{
				Temp = Temp->next;
			}
			Temp->next->prev = Temp->prev;
			Temp->prev->next = Temp->next;
			free( Temp );
			flag = 1;
		}
		H = ref;


		if(flag == 1)
		{
			printf("\nDeleted succesfully...");
			getch();
		}
		else
		{
			printf("\nOOPS!!wrong number enetered!\nTry again");
			getch();
		}
		dlast:
			return H;
	}


