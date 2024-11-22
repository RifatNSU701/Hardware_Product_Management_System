#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include <time.h>

#define ENTER 13
#define BKSP 8
#define SPACE 32
#define TAB 9
#define MAX 100


typedef struct
{
    char username[MAX];
    char password[MAX];
} User;

struct item
{
    char productname[40],productcomp[40],c;
    int productid;
    int price;
    int Qnt;
} st;

typedef struct
{
    char productName[50];
    int quantity;
    float price;
} Product;

typedef struct
{
    char username[30];
    float totalRevenue;
    int totalProductsSold;
} Account;

Product products[100];
int productCount = 0;
Account currentUser;


void wel_come(void);
void title(void);
void registerUser();
int loginUser();
void menu(void);
void title(void);
void gotoxy(short x, short y)
{
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void add_item();
void read_item();
void deleteproduct(void);
void search_item();
void edit_item();
void sellProduct();
void accountStatus();
void printInvoice(const char *productName, int quantity, float totalCost);
void main(void)

{
    wel_come(); //call for welcome screen function
    int choice;

    while (1)
    {
        printf("\n======================== *Hardware Product Management System* ========================");
        printf("                                                                                          ");
        printf("                                                                                          ");
        printf("\n\t1.\tRegister\n\t2.\tLogin\n\t3.\tExit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if (loginUser())
            {
                // Further actions after successful login
                printf("Welcome to the system!\n");
            }
            break;
        case 3:
            return 0; // Exit the program
        default:
            printf("!!Invalid choice. Please try again.!!\n");
        }
    }

    return 0;

}

void wel_come(void)
{

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t==================================\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|\t     WELCOME TO \t |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|  Hardware PRODUCT MGMT SYSTEM\t |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t==================================\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t            STOCK      \t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t   H_P_M_S\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|Press any key to continue.........\t\t\t\t\t\t\t\t\t\t|\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    getch();
    system("cls");
}


void registerUser()
{
    FILE *file = fopen("users.dat", "ab"); // Open file in append-binary mode
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    User newUser;

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t|\t     WELCOME--- \t |\t\t\t\t\t\t|\n");
    printf("\n\n\t\tRegister new account::\n");
    printf("\n\tEnter Username: ");
    scanf("%s", newUser.username);

    printf("\tEnter Password: ");
    scanf("%s", newUser.password);

    fwrite(&newUser, sizeof(User), 1, file); // Write user info to file
    printf("Registration successful!\n");
    getch();

    fclose(file);
    system("cls");
}

int loginUser()
{
    FILE *file = fopen("users.dat", "rb"); // Open file in read-binary mode
    if (file == NULL)
    {
        printf("**Error opening file.\n");
        return 0; // Indicating failure
    }

    char username[MAX], password[MAX];
    int found = 0;
    User user;

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t|\t     WELCOME--- \t |\t\t\t\t\t\t\n");
    printf("\n\n\t\tLog in to your account::\n");
    printf("\n\tEnter Username: ");
    scanf("%s", username);

    printf("\tEnter Password: ");
    scanf("%s", password);

    // Check if the entered credentials match any user in the file
    while (fread(&user, sizeof(User), 1, file))
    {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0)
        {
            found = 1; // Credentials match
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("  \n\n\n       WELCOME TO Hardware PRODUCT MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
        printf("\n\n\n\t\t\t\tPress any key to continue...");
        getch();
        menu();//holds the screen

    }
    else
    {
        printf("!Invalid username or password!!\n");
        printf("\n\n\n\t\t\t\tPress any key to continue...");
        getch();//holds the screen
    }

    system("cls");

}



void menu(void) //Main Menu Function
{
    int choice;
    system("cls");
main:
    printf("\n======================== Hardware Product Management System ========================");
    printf("                                                                                          ");
    printf("                                                                                          ");
    printf("\n\t\tPress <1> Add Products");
    printf("\n\t\tPress <2> Delete Products");
    printf("\n\t\tPress <3> Search Products");
    printf("\n\t\tPress <4> Read Items");
    printf("\n\t\tPress <5> Edit Items");
    printf("\n\t\tPress <6> Sell Items");
    printf("\n\t\tPress <7> View Account Status");
    printf("\n\t\tPress <8> Exit!");

    printf("\n\n\t\tEnter your choice[1-6]");
    scanf("%i", &choice);

    system("cls");

    switch(choice)  //Using switch for creating menu
    {
    case 1:
        add_item();
        break;
    case 2:
        deleteproduct();
        break;
    case 3:
        search_item();
        break;
    case 4:
        read_item();
        break;
    case 5:
        edit_item();
        break;
    case 6:
        sellProduct();
        break;
    case 7:
        accountStatus();
        break;
    case 8:
        printf("System Exit");
        exit(0);
        break;

    default:
        printf("Invalid Choice! System Exit\n");
        getch();
    }

}

void add_item() // Add any product,,
{
    int index, valid;
    char c;
    int a=0;

    FILE *fp;


    do
    {
        system("cls");
        printf("============ Enter Product Detail ============");
        int ID;//for comparing staff ID if file isnot NULL
        //declaration of file variable named as sfile
        fp = fopen("NextFile.dat","a+");//opening file and creating a staff.txt file to append or write

        if((fp = fopen("NextFile.dat","a+"))!=NULL)//if condition to check file is NULL or not
        {
I:
            printf("\nProduct Code\t :");
            scanf("%i",&ID);
            while(fscanf(fp,"%s %s %i %i %i", st.productname, st.productcomp, &st.price, &st.productid,&st.Qnt)!=EOF)
            {
                if(ID == st.productid)
                {
                    printf("\n\tTHE PRODUCT CODE ALREADY EXIST.\n");
                    goto I;
                }
            }
            st.productid = ID;
        }
        else    //runs if sfile is empty
        {
            printf("\nProduct Code\t :");
            scanf("%i",&st.productid);
        }

        //add product name
        do
        {

            printf("<<<<<<<<<<<<<<Enter Product Detail>>>>>>>>>>>>>");
            fflush(stdin);
            printf("\nProduct Name\t :");
            gets(st.productname); // get input string
            st.productname[0]=toupper(st.productname[0]);
            //iterate for every character in string
            for (index=0; index<strlen(st.productname); ++index)
            {
                //check if character is valid or not
                if(isalpha(st.productname[index]))
                    valid = 1;
                else
                {
                    valid = 0;
                    break;
                }
            }
            if (!valid)
            {
                printf("\n Name contain invalid character. Please 'Enter' again");
                getch();


            }
        }
        while(!valid);	//while end here


        //Product Company Name
        do
        {
            char productcomp[40];
            fflush(stdin);
            printf("\nProduct Company\t :");
            gets(st.productcomp); // get input string
            st.productcomp[0]=toupper(st.productcomp[0]);
            //iterate for every character in string
            for (index=0; index<strlen(st.productcomp); ++index)
            {
                //check if character is valid or not
                if(isalpha(st.productcomp[index]))
                    valid = 1;
                else
                {
                    valid = 0;
                    break;
                }
            }
            if (!valid)
            {
                printf("\n Name contain invalid character. Please 'Enter' again");
                getch();


            }
        }
        while(!valid);

        //product Id
        do
        {
            printf("\nPrice [10-70000]Taka:");
            scanf("%i",&st.price);
            if(st.price<10 || st.price>70000)
            {
                printf("\n\tYou Cannot Enter the price limit [10-70000].Re-Enter.");
            }
        }
        while(st.price<10 || st.price>70000);

        do
        {
            printf("\nQuantity [1-500]\t:");
            scanf("%i",&st.Qnt);
            if(st.Qnt<1 || st.Qnt>500)
            {
                printf("\n\tEnter Quantity[1-500] only.Re-Enter.");
            }
        }
        while(st.Qnt<1 || st.Qnt>500);

        //	printf("\nProduct Price\t :");
        //	scanf("%i", &st.price);
        //printf("\nProduct ID\t :");
        //scanf("%i", &st.productid);
        //	printf("\nProduct Quantity :");
        //	scanf("%i",&st.Qnt);

        fp=fopen("NextFile.dat","a");
        fprintf(fp,"\n%s %s %i %i %i", st.productname, st.productcomp,st.price, st.productid,st.Qnt);
        fclose(fp);
        printf("\nPress 'Enter' to add more item and any other key to go to main menu");

    }
    while((c = getch()) =='\r');
    menu();
}

void deleteproduct(void)
{
    FILE *fp, *tempFile;
    int productCode, found = 0;

    fp = fopen("NextFile.dat", "r");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    // Display all products with their codes
    printf("\nList of Products:\n");
    printf("Code\tProduct Name\n");
    printf("-------------------------\n");
    while (fscanf(fp, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        printf("%d\t%s\n", st.productid, st.productname);
    }
    fclose(fp);

    // Open the file again for deletion
    fp = fopen("NextFile.dat", "r");
    tempFile = fopen("TempFile.dat", "w");

    printf("\nEnter the Product Code to delete: ");
    scanf("%d", &productCode);

    while (fscanf(fp, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        if (st.productid == productCode)
        {
            found = 1;
            printf("\nProduct with Code %d is deleted successfully.\n", productCode);
        }
        else
        {
            fprintf(tempFile, "%s %s %d %d %d\n", st.productname, st.productcomp, st.price, st.productid, st.Qnt);
        }
    }

    fclose(fp);
    fclose(tempFile);

    if (!found)
    {
        printf("\nProduct with Code %d not found.\n", productCode);
    }

    remove("NextFile.dat");
    rename("TempFile.dat", "NextFile.dat");

    printf("\nPress any key to return to the main menu.");
    getch();
    menu();
}

void search_item()
{
    FILE *sfile;
    int productCode, found = 0;

    sfile = fopen("NextFile.dat", "r");
    if (sfile == NULL)
    {
        printf("No records found.\n");
        return;
    }

    // Display all products with their codes
    printf("\nList of Products:\n");
    printf("Code\tProduct Name\n");
    printf("-------------------------\n");
    while (fscanf(sfile, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        printf("%d\t%s\n", st.productid, st.productname);
    }
    fclose(sfile);

    // Open the file again for searching
    sfile = fopen("NextFile.dat", "r");

    printf("\nEnter the Product Code to search: ");
    scanf("%d", &productCode);

    while (fscanf(sfile, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        if (st.productid == productCode)
        {
            found = 1;
            printf("\nRecord Found:");
            printf("\nProduct Name\t\t: %s", st.productname);
            printf("\nProduct Company\t\t: %s", st.productcomp);
            printf("\nProduct Price\t\t: %d", st.price);
            printf("\nProduct Code\t\t: %d", st.productid);
            printf("\nProduct Quantity\t: %d\n", st.Qnt);
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct with Code %d not found.\n", productCode);
    }

    fclose(sfile);

    printf("\nPress any key to return to the main menu.");
    getch();
    menu();
}


void read_item()   //Read or see the products details
{
    FILE *f;
    int i, q;
    if((f=fopen("NextFile.dat","r"))==NULL)
    {

        gotoxy(10,3);
        printf("NO RECORDS");
        printf("\n\t\tPress any key to go back to Menu.");
        getch();
        menu();


    }
    else
    {

        gotoxy(0,5);
        for(i=0; i<100; i++)
        {
            printf("-");
        }
        gotoxy(5,6);
        printf("Product Name");
        gotoxy(25,6);
        printf("Product Price");
        gotoxy(40,6);
        printf("Product Company");
        gotoxy(60,6);
        printf("Product CODE");
        gotoxy(80,6);
        printf("Product Quantity\n");

        for(i=0; i<100; i++)
        {
            printf("-");
        }
        q=8;
        while(fscanf(f,"%s %s %i %i %i\n", st.productname,st.productcomp, &st.price, &st.productid,&st.Qnt)!=EOF)
        {
            gotoxy(5,q);
            printf("%s",st.productname);
            gotoxy(25,q);
            printf("%i",st.price);
            gotoxy(40,q);
            printf("%s",st.productcomp);
            gotoxy(60,q);
            printf("%i",st.productid);
            gotoxy(80,q);
            printf("%i",st.Qnt);

            q++;
        }
        printf("\n");
        for(i=0; i<100; i++)
            printf("-");
    }
    fclose(f);

    printf("\nPress any key to go to Main Menu!");
    //while((st.c = getch()) =='\r');
    getch();
    menu();
}

void edit_item()
{
    int productCode, found = 0;
    FILE *fp, *tempFile;

    // Open the file to display all products with their codes
    fp = fopen("NextFile.dat", "r");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\nList of Products:\n");
    printf("Code\tProduct Name\n");
    printf("-------------------------\n");
    while (fscanf(fp, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        printf("%d\t%s\n", st.productid, st.productname);
    }
    fclose(fp);

    // Open the file again for editing
    fp = fopen("NextFile.dat", "r");
    tempFile = fopen("TempFile.dat", "w");

    printf("\nEnter the Product Code to edit: ");
    scanf("%d", &productCode);

    while (fscanf(fp, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        if (st.productid == productCode)
        {
            found = 1;

            printf("\nRecord Found:");
            printf("\nProduct Name\t\t: %s", st.productname);
            printf("\nProduct Company\t\t: %s", st.productcomp);
            printf("\nProduct Price\t\t: %d", st.price);
            printf("\nProduct Code\t\t: %d", st.productid);
            printf("\nProduct Quantity\t: %d", st.Qnt);

            printf("\n\nEnter New Details for the Product:");

            // Input new product name
            printf("\nNew Product Name\t\t: ");
            fflush(stdin);
            gets(st.productname);
            st.productname[0] = toupper(st.productname[0]);

            // Input new product company
            printf("New Product Company\t\t: ");
            fflush(stdin);
            gets(st.productcomp);
            st.productcomp[0] = toupper(st.productcomp[0]);

            // Input new product price
            do
            {
                printf("New Product Price [10-70000]\t: ");
                scanf("%d", &st.price);
                if (st.price < 10 || st.price > 70000)
                {
                    printf("\nPrice must be within the range [10-70000]. Please try again.\n");
                }
            }
            while (st.price < 10 || st.price > 70000);

            // Input new quantity
            do
            {
                printf("New Quantity [1-500]\t\t: ");
                scanf("%d", &st.Qnt);
                if (st.Qnt < 1 || st.Qnt > 500)
                {
                    printf("\nQuantity must be within the range [1-500]. Please try again.\n");
                }
            }
            while (st.Qnt < 1 || st.Qnt > 500);

            // Confirm edit
            printf("Press 'Y' to save changes or any other key to cancel: ");
            char confirm = getche();
            if (confirm == 'Y' || confirm == 'y')
            {
                fprintf(tempFile, "%s %s %d %d %d\n", st.productname, st.productcomp, st.price, st.productid, st.Qnt);
                printf("\n\nProduct details updated successfully!\n");
            }
            else
            {
                fprintf(tempFile, "%s %s %d %d %d\n", st.productname, st.productcomp, st.price, st.productid, st.Qnt);
                printf("\nChanges discarded.\n");
            }
        }
        else
        {
            fprintf(tempFile, "%s %s %d %d %d\n", st.productname, st.productcomp, st.price, st.productid, st.Qnt);
        }
    }

    if (!found)
    {
        printf("\nProduct with Code %d not found.\n", productCode);
    }

    fclose(fp);
    fclose(tempFile);

    // Replace the original file with the updated file
    remove("NextFile.dat");
    rename("TempFile.dat", "NextFile.dat");

    printf("\nPress any key to return to the main menu.");
    getch();
    menu();
}

void sellProduct()
{
    int productID, quantity, found = 0;
    FILE *fp, *tempFile, *salesLog;
    time_t t;
    struct tm *tm_info;
    char date[20]; // To store the date in string format

    // Open the product file
    fp = fopen("NextFile.dat", "r");
    if (fp == NULL)
    {
        printf("\nError: Unable to open product file.\n");
        return;
    }

    // Display product list with their codes and names
    printf("\nList of Products:\n");
    printf("Code\tProduct Name\n");
    printf("-------------------------\n");
    while (fscanf(fp, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        printf("%d\t%s\n", st.productid, st.productname); // Display product code and name
    }

    // Close and reopen the file for further processing
    fclose(fp);
    fp = fopen("NextFile.dat", "r");
    tempFile = fopen("TempFile.dat", "w");

    // Open sales history log file for appending
    salesLog = fopen("salesHistory.txt", "a");
    if (salesLog == NULL)
    {
        printf("\nError: Unable to open sales history file.\n");
        fclose(fp);
        fclose(tempFile);
        return;
    }

    printf("\nEnter the Product ID to sell: ");
    scanf("%d", &productID);

    while (fscanf(fp, "%s %s %d %d %d\n", st.productname, st.productcomp, &st.price, &st.productid, &st.Qnt) != EOF)
    {
        if (st.productid == productID)
        {
            found = 1;

            // Display product details
            printf("\n\n\tProduct Found::");
            printf("\n\tProduct Name: %s", st.productname);
            printf("\n\tProduct Company: %s", st.productcomp);
            printf("\n\tAvailable Quantity: %d", st.Qnt);

            // Ask user for the quantity to sell
            printf("\n\nEnter the quantity to sell: ");
            scanf("%d", &quantity);

            if (quantity <= st.Qnt)
            {
                float totalCost = quantity * st.price;
                st.Qnt -= quantity; // Update the stock quantity

                // Update user account details
                currentUser.totalRevenue += totalCost;
                currentUser.totalProductsSold += quantity;

                // Print the invoice
                printInvoice(st.productname, quantity, totalCost);

                // Log the sale in sales history file
                time(&t);
                tm_info = localtime(&t);
                strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm_info); // Format the current date and time

                fprintf(salesLog, "Product: %s, Quantity: %d, Date: %s\n", st.productname, quantity, date);
            }
            else
            {
                printf("\nInsufficient stock. Available quantity is %d.\n", st.Qnt);
            }
        }

        // Write the current product to the temporary file (updated or not)
        fprintf(tempFile, "%s %s %d %d %d\n", st.productname, st.productcomp, st.price, st.productid, st.Qnt);
    }

    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", productID);
    }

    fclose(fp);
    fclose(tempFile);
    fclose(salesLog);

    // Replace the original file with the updated file
    remove("NextFile.dat");
    rename("TempFile.dat", "NextFile.dat");

    printf("\nPress any key to return to the main menu.");
    getch();
    menu();
}

void printInvoice(const char *productName, int quantity, float totalCost)
{
    printf("\n\n\t========== INVOICE ==========");
    printf("\n\tProduct Name: %s", productName);
    printf("\n\tQuantity Sold: %d", quantity);
    printf("\n\tTotal Cost: %.2f", totalCost);
    printf("\n\t=============================\n");
}

void accountStatus()
{
    FILE *salesLog;
    char line[256]; // To store each line of sales history

    printf("\n======================== *Hardware Product Management System* ========================");
    printf("\n========== ACCOUNT STATUS ==========");
    printf("\nUsername: %s", currentUser.username);
    printf("\nTotal Products Sold: %d", currentUser.totalProductsSold);
    printf("\nTotal Revenue: %.2f", currentUser.totalRevenue);
    printf("\n====================================\n");

    // Open sales history log file for reading
    salesLog = fopen("salesHistory.txt", "r");
    if (salesLog == NULL)
    {
        printf("\nError: Unable to open sales history file.\n");
        printf("\nNo sales history available.\n");
    }
    else
    {
        printf("\nSales History:\n");
        printf("-----------------------------\n");

        // Read and print each line of the sales history file
        while (fgets(line, sizeof(line), salesLog))
        {
            printf("%s", line);
        }
        fclose(salesLog);
    }

    printf("\nPress any key to return to the main menu.");
    getch();
    menu();
}
