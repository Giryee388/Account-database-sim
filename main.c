#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>

typedef struct
{
    char username[30];
    char email[40];
    char password[40];
    int birthYear;
} account;

void systemClear();
void whenLoggedIn(FILE *fp, char datName[], int accNo);
void deleteAccount(FILE *fp, char datName[], int accNo);
int stringCompare(char string1[], char string2[], int to);
void newFile(FILE *fp, char ime_dat[]);
void newAccount(FILE *fp, char datName[]);
void fileOutput(FILE *fp, char datName[]);
void usernameSearch(FILE *fp, char datName[]);
void newAccountHidden(FILE *fp, char datName[]);
void login(FILE *fp, char datName[]);
void editUsername(FILE *fp, char datName[], int accNo);
void editEmail(FILE *fp, char datName[], int accNo);
void editPassword(FILE *fp, char datName[], int accNo, account accLoggedIn);
account enterNewPassword(FILE *fp, char datName[], int accNo);
void editBirthYear(FILE *fp, char datName[], int accNo);

int main(int argc, char *argv[])
{
    FILE *fp;
    int n;
    printf("Welcome to account database simulator, press any key to start");
    getch();
    system("cls");
    while(1){
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%cChoose an action:%c\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c 1 Create/delete file\n%c 2 Create a new account\n%c 3 Create a new account (password hidden)\n%c 4 View all accounts\n%c 5 Find a user by username\n%c 6 Login\n%c 0 End program\n",213,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,184,179,179,212,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,190,201,204,204,204,204,204,200);
        scanf("%d", &n);
        switch(n){
            case 1:
                newFile(fp, argv[1]);
                break;
            case 2:
                newAccount(fp,argv[1]);
                break;
            case 3:
                newAccountHidden(fp,argv[1]);
                break;
            case 4:
                fileOutput(fp,argv[1]);
                break;
            case 5:
                usernameSearch(fp,argv[1]);
                break;
            case 6:
                login(fp,argv[1]);
                break;
            case 0:
                return 0;
                break;
            default:
                printf("Input doesn't match any action. Try again");
                systemClear();
                break;
        }
    }
    return 0;
}

void systemClear()
{
    printf ("Press any key to continue . . .\n");
    getch();
    system("cls");
    return;
}

void whenLoggedIn(FILE *fp, char datName[], int accNo)
{
    account acc;
    int n=0;
    fp=fopen(datName, "r");
    for(int i=0; i<accNo; i++)
    {
        fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
    }
    fclose(fp);
    while(1)
    {
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%cChoose an action:%c\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c 1 Edit Username\n%c 2 Edit Email\n%c 3 Edit Password\n%c 4 Edit Birth year \n%c 5 Delete account\n%c 0 Logout\n",213,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,184,179,179,212,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,190,201,204,204,204,204,200);
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            editUsername(fp, datName, accNo);
            printf("Username successfully changed \n");
            systemClear();
            break;
        case 2:
            editEmail(fp, datName, accNo);
            printf("Email successfully changed \n");
            systemClear();
            break;
        case 3:
            editPassword(fp, datName, accNo, acc);
            printf("Password successfully changed \n");
            systemClear();
            break;
        case 4:
            editBirthYear(fp, datName, accNo);
            systemClear();
            break;
        case 5:
            fclose(fp);
            deleteAccount(fp, datName, accNo);
            printf("Account successfully deleted \n");
            systemClear();
            return;
            break;
        case 0:
            systemClear();
            fclose(fp);
            return;
        default:
            break;
        }
    }
}

void deleteAccount(FILE *fp, char datName[], int accNo)
{
    int ctr = 0;
    FILE *fptr1, *fptr2;
    char str[256], temp[] = "temp.txt";
    fptr1 = fopen(datName, "r");

    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("ERROR");
        fclose(fptr1);
        return;
    }
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, 256, fptr1);
        if (!feof(fptr1))
        {
            ctr++;
        }
        if (ctr != accNo)
        {
            fprintf(fptr2, "%s", str);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(datName);
    rename(temp, datName);
}

int stringCompare(char string1[], char string2[], int to)
{
    for(int i=0; i<to; i++)
    {
        //printf("%d\n",i);
        if(string1[i]!=string2[i])
        {
            return 1;
        }
    }
    return 0;
}

void newFile(FILE *fp, char ime_dat[])
{
    fp=fopen(ime_dat, "w");
    if(fp==NULL)
    {
        fprintf(stderr, "Error with creating a file");
        exit(EXIT_FAILURE);
    }
    printf("file successfully created! \n");
    fclose(fp);
    systemClear();
}

void newAccount(FILE *fp, char datName[])
{
    account acc, allOther;
    fp=fopen(datName, "r");

    fflush(stdin);
    printf("Enter username: ");
    scanf("%[^\n]s", acc.username);
    fflush(stdin);
    while(1)
    {
        fscanf(fp,"%s %s %s %d", allOther.username, allOther.email, allOther.password, &allOther.birthYear);
        if(feof(fp))
        {
            break;
        }
        if(strcmp(acc.username, allOther.username)==0)
        {
            printf("That username is already in use, try another one\n");
            newAccount(fp, datName);
            return;
        }
    }
    email:
    rewind(fp);
    printf("Enter email: ");
    scanf("%s", acc.email);
    fflush(stdin);
    while(1)
    {
        fscanf(fp,"%s %s %s %d", allOther.username, allOther.email, allOther.password, &allOther.birthYear);
        if(feof(fp))
        {
            break;
        }
        if(strcmp(acc.email, allOther.email)==0)
        {
            printf("An account with this email already exists\nRepeat input\n");
            goto email;
        }
    }
    fclose(fp);

    printf("Enter password: ");
    scanf("%s", acc.password);
    fflush(stdin);

    printf("Enter birth year: ");
    scanf("%d", &acc.birthYear);
    fflush(stdin);

    for(int i=0; i<30; i++)
    {
        if(acc.username[i] == ' ')
        {
            acc.username[i] = '$';
        }
    }
    fp=fopen(datName, "a");
    fprintf(fp, "%s %s %s %d", acc.username, acc.email, acc.password, acc.birthYear);
    fprintf(fp,"\n");
    fclose(fp);
    systemClear();
}

void fileOutput(FILE *fp, char datName[])
{
    account acc;
    fp=fopen(datName,"r");
    if(fp==NULL)
    {
        fprintf(stderr,"Error with outputing the file");
        exit(EXIT_FAILURE);
    }
    printf("\nUsername                       Email                                    Password                                 Birth year\n");
    while(1)
    {
        fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        for(int i=0; i<30; i++)
        {
            if(acc.username[i] == '$')
            {
                acc.username[i] = ' ';
            }
        }
        if(feof(fp))
        {
            break;
        }
        printf("%-30s %-40s %-40s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
    }
    fclose(fp);
    systemClear();
}

void usernameSearch(FILE *fp, char datName[])
{
    account acc;
    fp=fopen(datName,"r");
    if(fp==NULL)
    {
        fprintf(stderr,"Error with opening the file");
        exit(EXIT_FAILURE);
    }
    printf("Enter the first character of the username: \n");
    fflush(stdin);
    char c;
    scanf("%c",&c);

    printf("\nUsername                       Email                                    Password                                     Birth year\n");
    while(1)
    {

        fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(acc.username[0]==c || acc.username[0]==toupper(c))
        {
            for(int i=0; i<30; i++)
            {
                if(acc.username[i] == '$')
                {
                    acc.username[i] = ' ';
                }
            }
            if(feof(fp))
            {
                break;
            }
            printf("%-30s %-40s %-40s %8d\n",acc.username, acc.email, acc.password, acc.birthYear);
        }
        if(feof(fp))
        {
            break;
        }
    }
    systemClear();
}

void newAccountHidden(FILE *fp, char datName[])
{
    int c;
    char temp;
    account acc, allOther;
    fp=fopen(datName, "r");

    fflush(stdin);
    printf("Enter username: ");
    scanf("%[^\n]s", acc.username);
    fflush(stdin);
    while(1)
    {
        fscanf(fp,"%s %s %s %d", allOther.username, allOther.email, allOther.password, &allOther.birthYear);
        if(feof(fp))
        {
            break;
        }
        if(strcmp(acc.username, allOther.username)==0)
        {
            printf("That username is already in use, try another one\n");
            newAccount(fp, datName);
            return;
        }
    }
    email:
    rewind(fp);
    printf("Enter email: ");
    scanf("%s", acc.email);
    fflush(stdin);
    while(1)
    {
        fscanf(fp,"%s %s %s %d", allOther.username, allOther.email, allOther.password, &allOther.birthYear);
        if(feof(fp))
        {
            break;
        }
        if(strcmp(acc.email, allOther.email)==0)
        {
            printf("An account with this email already exists\nRepeat input\n");
            goto email;
        }
    }
    fclose(fp);

    c=0;
    printf("Enter password: ");
    fflush(stdin);
    while((temp=getch())!='\r')
    {
        acc.password[c]=temp;
        printf("*");
        c++;
        fflush(stdin);
    }
    printf("\n");
    fflush(stdin);

    printf("Enter birth year: ");
    scanf("%d", &acc.birthYear);
    fflush(stdin);

    for(int i=0; i<30; i++)
    {
        if(acc.username[i] == ' ')
        {
            acc.username[i] = '$';
        }
    }
    fp=fopen(datName, "a");
    fprintf(fp, "%s %s ", acc.username, acc.email);
    for(int i=0; i<c; i++)
    {
        fprintf(fp, "%c", acc.password[i]);
    }
    fprintf(fp, " ");
    fprintf(fp, "%d ",acc.birthYear);
    fclose(fp);
    systemClear();
}

void login(FILE *fp, char datName[])
{
    account acc, login;
    char temp;
    int passModeChoose, izlaz, accNo=0, passLenght=0;
    enterEmail:
    fp=fopen(datName, "r");

    printf("Enter email: ");
    scanf("%s", login.email);
    fflush(stdin);
    while(1)
    {
        fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(feof(fp))
        {
            break;
        }
        accNo++;
        if(strcmpi(login.email, acc.email)==0)
        {
            enterPass:
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%cChoose a password input mode:%c\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c 1 Hide password\n%c 2 Show password\n",213,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,184,179,179,212,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,190,201,200);
            invalidPassMode:
            scanf("%d", &passModeChoose);
            switch(passModeChoose)
            {
            case 1:
                printf("Enter password: ");
                fflush(stdin);
                while((temp=getch())!='\r')
                {
                    login.password[passLenght]=temp;
                    printf("*");
                    passLenght++;
                    fflush(stdin);
                }
                printf("\n");
                fflush(stdin);
                rewind(fp);
                for(int i=0; i<accNo; i++)
                {
                    fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
                }
                //printf("%s %s %d\n", login.password, acc.password, strlen(acc.password));
                if(stringCompare(login.password, acc.password, strlen(acc.password))==0)
                {
                    printf("Successfully logged in\n");
                    systemClear();
                    fclose(fp);
                    whenLoggedIn(fp, datName, accNo);
                    return;
                }
//                memset(login.password,0,strlen(login.password));
//                memset(acc.password,0,strlen(acc.password));
                passLenght=0;
                printf("Invalid Password\n");
                printf("|1- Try again\n");
                printf("|2- Main menu\n");
                invalidPass:
                scanf("%d",&izlaz);
                if(izlaz == 1)
                {
                    system("cls");
                    goto enterPass;

                }
                if(izlaz == 2)
                {
                    system("cls");
                    fclose(fp);
                    return;
                }
                printf("Input doesn't match any action. Try again ");
                goto invalidPass;
            case 2:
                printf("Enter password: ");
                fflush(stdin);
                scanf("%s",login.password);
                fflush(stdin);
                rewind(fp);
                for(int i=0; i<accNo; i++)
                {
                    fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
                }
                 //printf("%s %s\n", login.password, acc.password);
                if(strcmp(login.password, acc.password)==0)
                {
                    printf("Successfully logged in\n");
                    systemClear();
                    fclose(fp);
                    whenLoggedIn(fp, datName, accNo);
                    return;
                }
                printf("Invalid Password\n");
                printf("|1- Try again\n");
                printf("|2- Main menu\n");
                invalidPass2:
                scanf("%d",&izlaz);
                if(izlaz == 1)
                {
                    system("cls");
                    goto enterPass;

                }
                if(izlaz == 2)
                {
                    system("cls");
                    fclose(fp);
                    return;
                }
                printf("Input doesn't match any action. Try again ");
                goto invalidPass2;
                fclose(fp);
                break;
            default:
                printf("Input doesn't match any action. Try again ");
                goto invalidPassMode;
                fclose(fp);
                break;
            }

        }
    }
    fclose(fp);
    accNo=0;
    printf("Invalid Email address\n");
    printf("|1- Try again\n");
    printf("|2- Main menu\n");
    invalidEmail:
    scanf("%d",&izlaz);
    if(izlaz == 1)
    {
        system("cls");
        goto enterEmail;

    }
    if(izlaz == 2)
    {
        system("cls");
        return;
    }
    printf("Input doesn't match any action. Try again ");
    goto invalidEmail;
}

void editUsername(FILE *fp, char datName[], int accNo)
{
    account acc;
    int ctr = 0;
    FILE *fptr1, *fptr2;
    char temp[] = "temp.txt";
    fptr1 = fopen(datName, "r");

    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("ERROR");
        fclose(fptr1);
        return;
    }
    while (1)
    {
        fscanf(fptr1,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(feof(fp))
        {
            break;
        }
            ctr++;
        if (ctr != accNo)
        {
            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
        else
        {
            fflush(stdin);
            printf("Enter new username: ");
            scanf("%[^\n]s", acc.username);
            fflush(stdin);
            for(int i=0; i<30; i++)
            {
                if(acc.username[i] == ' ')
                {
                    acc.username[i] = '$';
                }
            }
            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(datName);
    rename(temp, datName);
}

void editEmail(FILE *fp, char datName[], int accNo)
{
    account acc;
    int ctr = 0;
    FILE *fptr1, *fptr2;
    char temp[] = "temp.txt";
    fptr1 = fopen(datName, "r");

    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("ERROR");
        fclose(fptr1);
        return;
    }
    while (1)
    {
        fscanf(fptr1,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(feof(fp))
        {
            break;
        }
            ctr++;
        if (ctr != accNo)
        {
            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
        else
        {
            fflush(stdin);
            printf("Enter new email: ");
            scanf("%[^\n]s", acc.email);
            fflush(stdin);
//            for(int i=0; i<40; i++)
//            {
//                if(acc.email[i] == ' ')
//                {
//                    acc.email[i] = '$';
//                }
//            }
            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(datName);
    rename(temp, datName);
}

void editPassword(FILE *fp, char datName[], int accNo, account accLoggedIn)
{
    int passModeChoose=0, passLenght=0, izlaz=0;
    account acc, login;
    int ctr = 0;
    FILE *fptr1, *fptr2;
    char temp[] = "temp.txt", temporary;
    fptr1 = fopen(datName, "r");

    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("ERROR");
        fclose(fptr2);
        return;
    }
    while (1)
    {
        fscanf(fptr1,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(feof(fp))
        {
            break;
        }
        ctr++;
        if (ctr != accNo)
        {
            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
        else
        {
//            for(int i=0; i<40; i++)
//            {
//                if(acc.email[i] == ' ')
//                {
//                    acc.email[i] = '$';
//                }
//            }
            enterPass:
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%cChoose a password input mode:%c\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c 1 Hide password\n%c 2 Show password\n",213,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,184,179,179,212,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,190,201,200);
            invalidPassMode:
            scanf("%d", &passModeChoose);
            switch(passModeChoose)
            {
            case 1:
                printf("Enter current password: ");
                fflush(stdin);
                while((temporary=getch())!='\r')
                {
                    login.password[passLenght]=temporary;
                    printf("*");
                    passLenght++;
                    fflush(stdin);
                }
                printf("\n");
                fflush(stdin);
                rewind(fp);
                for(int i=0; i<accNo; i++)
                {
                    fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
                }
                if(stringCompare(login.password, acc.password, strlen(acc.password))==0)
                {
                    fclose(fptr1);
                    fclose(fptr2);
                    acc = enterNewPassword(fp, datName, accNo);
                    fptr2 = fopen(temp, "a");
                    fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
                    fclose(fptr2);
                    remove(datName);
                    rename(temp, datName);
                    return;
                }
//                memset(login.password,0,strlen(login.password));
//                memset(acc.password,0,strlen(acc.password));
                passLenght=0;
                printf("Invalid Password\n");
                printf("|1- Try again\n");
                printf("|2- Main menu\n");
                invalidPass:
                scanf("%d",&izlaz);
                if(izlaz == 1)
                {
                    system("cls");
                    goto enterPass;

                }
                if(izlaz == 2)
                {
                    system("cls");
                    fclose(fp);
                    return;
                }
                printf("Input doesn't match any action. Try again ");
                goto invalidPass;
            case 2:
                printf("Enter current password: ");
                fflush(stdin);
                scanf("%s",login.password);
                fflush(stdin);
                rewind(fp);
                for(int i=0; i<accNo; i++)
                {
                    fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
                }
                 //printf("%s %s\n", login.password, acc.password);
                if(strcmp(login.password, acc.password)==0)
                {
                    fclose(fptr1);
                    fclose(fptr2);
                    acc = enterNewPassword(fp, datName, accNo);
                    fptr2 = fopen(temp, "a");
                    fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
                    fclose(fptr2);
                    remove(datName);
                    rename(temp, datName);
                    return;
                }
                printf("Invalid Password\n");
                printf("|1- Try again\n");
                printf("|2- Main menu\n");
                invalidPass2:
                scanf("%d",&izlaz);
                if(izlaz == 1)
                {
                    system("cls");
                    goto enterPass;

                }
                if(izlaz == 2)
                {
                    system("cls");
                    fclose(fp);
                    return;
                }
                printf("Input doesn't match any action. Try again ");
                goto invalidPass2;
                fclose(fp);
                break;
            default:
                printf("Input doesn't match any action. Try again ");
                goto invalidPassMode;
                fclose(fp);
                break;
            }
        }
    }
}

account enterNewPassword(FILE *fp, char datName[], int accNo)
{
    int passModeChoose=0, passLenght=0,k=0;
    account acc, login;
    int ctr = 0;
    FILE *fptr2;
    char temp[] = "temp.txt", temporary;
    fp = fopen(datName, "r");
    fptr2 = fopen(temp, "a");

    while (1)
    {
        fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(feof(fp))
        {
            break;
        }
        ctr++;
        if (ctr == accNo)
        {
//            for(int i=0; i<40; i++)
//            {
//                if(acc.email[i] == ' ')
//                {
//                    acc.email[i] = '$';
//                }
//            }
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%cChoose a password input mode:%c\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c 1 Hide password\n%c 2 Show password\n",213,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,184,179,179,212,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,190,201,200);
            invalidPassMode:
            scanf("%d", &passModeChoose);
            switch(passModeChoose)
            {
            case 1:
                printf("Enter new password: ");
                fflush(stdin);
                passLenght=0;
                while((temporary=getch())!='\r')
                {
                    login.password[passLenght]=temporary;
                    printf("*");
                    passLenght++;
                    fflush(stdin);
                }
                printf("\n");
                fflush(stdin);
                rewind(fp);
                for(int i=0; i<accNo; i++)
                {
                    fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
                }
                for(int i=0; i<passLenght; i++)
                {
                    acc.password[i]=login.password[i];
                    k=i;
                }
                acc.password[++k] = '\0';
                fclose(fp);
                fclose(fptr2);
                return acc;
            case 2:
                printf("Enter new password: ");
                fflush(stdin);
                scanf("%s",login.password);
                fflush(stdin);
                rewind(fp);
                for(int i=0; i<accNo; i++)
                {
                    fscanf(fp,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
                }
                strcpy(acc.password, login.password);
                fclose(fp);
                fclose(fptr2);
                return acc;
            default:
                printf("Input doesn't match any action. Try again ");
                goto invalidPassMode;
                fclose(fp);
                break;
            }
        }
    }
}

void editBirthYear(FILE *fp, char datName[], int accNo)
{
    account acc;
    int ctr = 0;
    FILE *fptr1, *fptr2;
    char temp[] = "temp.txt";
    fptr1 = fopen(datName, "r");

    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("ERROR");
        fclose(fptr1);
        return;
    }
    while (1)
    {
        fscanf(fptr1,"%s %s %s %d", acc.username, acc.email, acc.password, &acc.birthYear);
        if(feof(fp))
        {
            break;
        }
            ctr++;
        if (ctr != accNo)
        {
            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
        else
        {
            fflush(stdin);
            printf("Enter new birth year: ");
            scanf("%d", &acc.birthYear);
            fflush(stdin);
//            for(int i=0; i<40; i++)
//            {
//                if(acc.email[i] == ' ')
//                {
//                    acc.email[i] = '$';
//                }
//            }

            fprintf(fptr2, "%s %s %s %d\n", acc.username, acc.email, acc.password, acc.birthYear);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(datName);
    rename(temp, datName);
}

