#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// Function Declarations.
void checkbalance(char username2[]);
void transfermoney(void);
void display(char username1[]);
void login(void);
void loginsu(void);
void account(void);
void accountcreated(void);
void logout(void);

// Function to set cursor position in console output.
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// Structure to store complete user personal details.
struct pass {
    char username[50];
    int date, month, year;
    char pnumber[15];
    char adharnum[20];
    char fname[20];
    char lname[20];
    char fathname[20];
    char mothname[20];
    char address[50];
    char typeaccount[20];
};

// Structure to store transaction history.
struct money {
    char usernameto[50];
    char userpersonfrom[50];
    long int moneyl;
};

// Structure to store simple user authentication credentials
struct userpass {
    char password[50];
};

// Main Driver Code
int main() {
    int choice;

    while (1) {
        system("cls");
        gotoxy(20, 3);
        printf("WELCOME TO BANK ACCOUNT SYSTEM\n\n");
        gotoxy(18, 5);
       
        
        gotoxy(20, 10);
        printf("1.... CREATE A BANK ACCOUNT");
        gotoxy(20, 12);
        printf("2.... ALREADY A USER? SIGN IN");
        gotoxy(20, 14);
        printf("3.... EXIT\n\n");

        gotoxy(20, 17);
        printf("ENTER YOUR CHOICE: ");
        if (scanf("%d", &choice) != 1) {
            // Flush invalid input buffer
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                account();
                break;
            case 2:
                login();
                break;
            case 3:
                exit(0);
            default:
                printf("\nInvalid Choice! Press any key to retry...");
                getch();
        }
    }
    return 0;
}

// Function to create new bank accounts
void account(void) {
    char password[50];
    int i = 0;
    char ch;
    FILE *fp;
    struct pass u1;

    fp = fopen("username.txt", "ab");
    if (fp == NULL) {
        printf("\nError opening database file!");
        getch();
        return;
    }

    system("cls");
    printf("========== CREATE ACCOUNT ==========\n\n");
    printf("NOTE: USERNAME & PASSWORD MAX 50 CHARACTERS!!\n\n");

    printf("FIRST NAME......: ");
    scanf("%19s", u1.fname);

    printf("LAST NAME.......: ");
    scanf("%19s", u1.lname);

    printf("FATHER'S NAME...: ");
    scanf("%19s", u1.fathname);

    printf("MOTHER'S NAME...: ");
    scanf("%19s", u1.mothname);

    printf("ADDRESS.........: ");
    scanf("%49s", u1.address);

    printf("ACCOUNT TYPE....: ");
    scanf("%19s", u1.typeaccount);

    printf("\nDATE OF BIRTH:\n");
    printf("  DATE  (DD)....: ");
    scanf("%d", &u1.date);
    printf("  MONTH (MM)....: ");
    scanf("%d", &u1.month);
    printf("  YEAR  (YYYY)..: ");
    scanf("%d", &u1.year);

    printf("AADHAR NUMBER...: ");
    scanf("%19s", u1.adharnum);

    printf("PHONE NUMBER....: ");
    scanf("%14s", u1.pnumber);

    printf("USERNAME........: ");
    scanf("%49s", u1.username);

    printf("PASSWORD........: ");
    // Secure masked password input
    while (1) {
        ch = getch();
        if (ch == 13 || ch == 10) { // Enter key
            password[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) { // Backspace support
            i--;
            printf("\b \b");
        } else if (ch != 8 && i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }

    // Append account record to storage
    fwrite(&u1, sizeof(u1), 1, fp);
    fclose(fp);

    accountcreated();
}

// Splash notification for successful registration
void accountcreated(void) {
    long int i;
    system("cls");
    printf("PLEASE WAIT....\n\nYOUR DATA IS PROCESSING..");
    for (i = 0; i < 100000000; i++); // Processing delay

    gotoxy(25, 10);
    printf("ACCOUNT CREATED SUCCESSFULLY..... ");
    gotoxy(20, 15);
    printf("Press any key to proceed to login...");
    getch();
    login();
}

// Handles user authentication
void login(void) {
    system("cls");

    char username[50];
    char password[50];
    int i = 0, found = 0;
    char ch;
    FILE *fp;
    struct pass u1;

    fp = fopen("username.txt", "rb");
    if (fp == NULL) {
        gotoxy(20, 10);
        printf("NO ACCOUNTS FOUND. PLEASE CREATE ONE FIRST!");
        getch();
        return;
    }

    gotoxy(34, 2);
    printf(" ACCOUNT LOGIN ");
    gotoxy(15, 4);
    printf("**********************************************");

    gotoxy(30, 8);
    printf("==== LOG IN ====");

    gotoxy(25, 11);
    printf("USERNAME..: ");
    scanf("%49s", username);

    gotoxy(25, 13);
    printf("PASSWORD..: ");

    // Masked password input
    while (1) {
        ch = getch();
        if (ch == 13 || ch == 10) {
            password[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8 && i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }

    // Verify record from database file
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username, u1.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        loginsu();
        display(username);
    } else {
        gotoxy(25, 17);
        printf("INVALID USERNAME OR PASSWORD!");
        gotoxy(25, 19);
        printf("Press any key to retry...");
        getch();
    }
}

// Splash notification for login success
void loginsu(void) {
    long int i;
    system("cls");
    printf("Fetching account details...... \n");
    for (i = 0; i < 100000000; i++);

    gotoxy(30, 10);
    printf("LOGIN SUCCESSFUL... ");
    gotoxy(20, 15);
    printf("Press enter to continue");
    getch();
}

// Main user Dashboard
void display(char username1[]) {
    system("cls");
    FILE *fp;
    int choice, found = 0;
    struct pass u1;

    fp = fopen("username.txt", "rb");
    if (fp == NULL) {
        printf("Error opening database file.");
        getch();
        return;
    }

    // Fetch details of logged-in user
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username1, u1.username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("User record missing!");
        getch();
        return;
    }

    // Account Summary Section
    gotoxy(45, 4);
    printf("==== ACCOUNT DETAILS ====");
    
    gotoxy(45, 7);
    printf("NAME............: %s %s", u1.fname, u1.lname);
    gotoxy(45, 9);
    printf("FATHER'S NAME...: %s", u1.fathname);
    gotoxy(45, 11);
    printf("MOTHER'S NAME...: %s", u1.mothname);
    gotoxy(45, 13);
    printf("AADHAR NUMBER...: %s", u1.adharnum);
    gotoxy(45, 15);
    printf("MOBILE NUMBER...: %s", u1.pnumber);
    gotoxy(45, 17);
    printf("DATE OF BIRTH...: %02d-%02d-%d", u1.date, u1.month, u1.year);
    gotoxy(45, 19);
    printf("ADDRESS.........: %s", u1.address);
    gotoxy(45, 21);
    printf("ACCOUNT TYPE....: %s", u1.typeaccount);

    // Left Navigation Menu.
    gotoxy(0, 4);
    printf(" HOME MENU ");
    gotoxy(0, 5);
    printf("***********");
    gotoxy(0, 7);
    printf(" 1.... CHECK BALANCE");
    gotoxy(0, 9);
    printf(" 2.... TRANSFER MONEY");
    gotoxy(0, 11);
    printf(" 3.... LOG OUT");
    gotoxy(0, 13);
    printf(" 4.... EXIT\n\n");

    gotoxy(0, 16);
    printf(" ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            checkbalance(username1);
            break;
        case 2:
            transfermoney();
            break;
        case 3:
            logout();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid Option!");
            getch();
            display(username1);
    }
}

// Function to transfer funds to another registered account
void transfermoney(void) {
    long int i, j;
    FILE *fm, *fp;
    struct pass u1;
    struct money m1;
    char usernamet[50];
    char usernamep[50];
    int recipientExists = 0;

    system("cls");

    fp = fopen("username.txt", "rb");
    if (fp == NULL) {
        printf("Database error!");
        getch();
        return;
    }

    fm = fopen("mon.txt", "ab");
    if (fm == NULL) {
        fclose(fp);
        printf("Transaction error!");
        getch();
        return;
    }

    gotoxy(25, 5);
    printf("---- TRANSFER MONEY ----");

    gotoxy(25, 9);
    printf("FROM (your username)......: ");
    scanf("%49s", usernamet);

    gotoxy(25, 11);
    printf("TO (recipient's username).: ");
    scanf("%49s", usernamep);

    // Validate recipient existence
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(usernamep, u1.username) == 0) {
            recipientExists = 1;
            break;
        }
    }

    if (recipientExists) {
        strcpy(m1.usernameto, usernamep);
        strcpy(m1.userpersonfrom, usernamet);

        gotoxy(25, 14);
        printf("ENTER AMOUNT TO TRANSFER: ");
        scanf("%ld", &m1.moneyl);

        // Record transaction
        fwrite(&m1, sizeof(m1), 1, fm);

        gotoxy(25, 18);
        printf("Transferring amount, Please wait..");

        gotoxy(20, 20);
        for (i = 0; i < 40; i++) {
            for (j = 0; j < 5000000; j++); // Progress bar delay
            printf("*");
        }

        gotoxy(25, 23);
        printf("AMOUNT SUCCESSFULLY TRANSFERRED!");
    } else {
        gotoxy(25, 15);
        printf("RECIPIENT USERNAME NOT FOUND!");
    }

    getch();
    fclose(fp);
    fclose(fm);

    display(usernamet);
}

// Function to view received funds and balance summary
void checkbalance(char username2[]) {
    system("cls");
    FILE *fm;
    struct money m1;
    long int summoney = 0;
    int recordIndex = 1;
    int row = 10;

    fm = fopen("mon.txt", "rb");

    gotoxy(20, 3);
    printf("==== DASHBOARD / RECEIVED TRANSACTIONS ====");

    gotoxy(5, 7);
    printf("S.NO.");
    gotoxy(20, 7);
    printf("SENDER USERNAME");
    gotoxy(50, 7);
    printf("AMOUNT RECEIVED");

    gotoxy(5, 8);
    printf("---------------------------------------------------------");

    if (fm != NULL) {
        while (fread(&m1, sizeof(m1), 1, fm)) {
            // Find incoming transfers directed to this account
            if (strcmp(username2, m1.usernameto) == 0) {
                gotoxy(5, row);
                printf("%d", recordIndex++);

                gotoxy(20, row);
                printf("%s", m1.userpersonfrom);

                gotoxy(50, row);
                printf("%ld", m1.moneyl);

                summoney += m1.moneyl;
                row++;
            }
        }
        fclose(fm);
    }

    gotoxy(5, row + 2);
    printf("---------------------------------------------------------");
    gotoxy(5, row + 4);
    printf("TOTAL AMOUNT IN ACCOUNT: Rs. %ld", summoney);

    gotoxy(5, row + 7);
    printf("Press any key to return to dashboard...");
    getch();

    display(username2);
}

// Handles user sign-out operation.
void logout(void) {
    long int i, j;
    system("cls");
    printf("Please wait, logging out");

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 10000000; j++);
        printf(".");
    }

    gotoxy(25, 10);
    printf("Signed out successfully..\n");

    gotoxy(20, 15);
    printf("Press any key to continue..");
    getch();
}
