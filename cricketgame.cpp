#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <ctime>
#include <random>
#include <iomanip>
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO consoleinfo;
WORD saved_attributes;

int count_home = 0;

// functions

int cheek_length_mobile(int long long num);
void captcha();
int cheek_mail(char arr[30]);
void registration();
void login();
void forget_user();
void forget_pass();
void deleteaccount();

void home(char pass[10], char user[8]);                            // for home page
void profile(char pass[10], char user[8]);                         // for profile view
void cricket(char pass[10], char user[8]);                         // for playing cricket
void bat_1(int *count1, int *n_4, int *n_6, int over);             // for batting first
void ball_1(int *count2, int over);                                // for bowling first
void bat_2(int *count1, int target, int *n_4, int *n_6, int over); // for batting in 2nd innings
void ball_2(int *count2, int target, int over);                    // for bowling in 2nd innings
void rate();                                                       // for rate
void viewschore(char pass[10], char user[8]);                      // for view schore
void viewpoint(char pass[10], char user[8]);                       // for viewpoint
void edit(char pass[10], char user[8]);                            // for edit profile

// structure delaration

struct DOB // for any date
{
    int dd;
    int mm;
    int yyyy;
};
struct schore // to save schore
{
    double numberofmatch;
    double matchwon;
    double matchloss;
    double matchdrawn;
    double numberof50;
    double numberof100;
    double toprun;
    double toatlrun;
    double numberof4;
    double numberof6;
};
struct user // data for registration
{
    char name[20];
    int age;
    char sex;
    int long long mobile;
    char gmail[30];
    struct DOB date;
    char user[8];
    char pass[10];
    struct schore record;
    int point;
} u;

// defenation of funtions

int cheek_length_mobile(int long long num) // to cheek the mobile number
{
    int count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return (count);
}

void captcha() // to genarate and verify captcha code
{
    int i, c;
    char captcha[7], captcha_user[7];
    do
    {
        srand(time(0));
        for (i = 0; i <= 5; i++)
        {
            if (i >= 0 && i < 2)
                captcha[i] = (rand() % 26) + 65;
            else if (i >= 2 && i < 4)
                captcha[i] = (rand() % 10) + 48;
            else
                captcha[i] = (rand() % 26) + 97;
        }
        captcha[i] = '\0';
        SetConsoleTextAttribute(hConsole, 1);
        cout << "\n\nCAPTCHA :" << captcha << endl;
        cout << "ENTER THIS CAPTCHA CORRECTLY :";
        for (i = 0; i <= 5; i++)
        {
            captcha_user[i] = getch();
            if (captcha_user[i] == 13)
                break;
            else
                cout << " *";
        }
        captcha_user[i] = '\0';
        if (strcmp(captcha_user, captcha) == 0)
            break;
        else
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\nENTER THE CAPTCHA CAREFULLY!!" << endl;
            SetConsoleTextAttribute(hConsole, 1);
            c = 1;
        }
    } while (c == 1);
}

int cheek_mail(char arr[30]) // to cheek an email id correct or not
{
    int i = 0, count = 0;
    while (arr[i] != '\0')
    {
        if (arr[i] == '@')
            count += 1;
        i++;
    }
    return (count);
}

// main function
int main()
{
    int choise, count = 0;
    while (count == 0)
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 2);
        cout << "*************************| REGISTRATION PAGE |******************************" << endl;
        cout << "                      *PLEASE ENTER YOUR CHOISE*                   " << endl;
        cout << "\nPRESS 1-> NEW USER REGISTRATION" << endl;
        cout << "_________________________________" << endl;
        cout << "\nPRESS 2-> LOGIN" << endl;
        cout << "________________" << endl;
        cout << "\nPRESS 3-> FORGET USERNAME" << endl;
        cout << "__________________________" << endl;
        cout << "\nPRESS 4-> FORGET PASSWORD" << endl;
        cout << "_________________________\n";
        cout << "\nPRESS 5->DELETE ACCOUNT" << endl;
        cout << "__________________________" << endl;
        cout << "\nPress escape key(esc) to exit.." << endl;
        cout << "\n\nENTER YOUR CHOISE:";
        choise = getch();
        switch (choise)
        {
        case '1':
            registration(); // for registration
            break;
        case '2':
            login(); // for login
            break;
        case '3':
            forget_user(); // for forget username
            break;
        case '4':
            forget_pass(); // for forget password
            break;
        case '5':
            deleteaccount(); // for delete acoount
            break;
        case (27): // for exit
            count = 1;
            break;
        default:
            system("cls");
            cout << "Enter a correct input!!" << endl;
            cout << "Press any key to continue" << endl;
            getch();
        }
    }
}

void registration() // to register and save the data
{
    int long long temp_mobile;
    char temp_pass1[10];
    char temp_pass2[10];
    char temp_mail[30];
    int result, i = 0, c, result_mail;
    system("cls");
    FILE *f;
    f = fopen("registration.txt", "a+");
    if (f == 0)
    {
        f = fopen("registration.txt", "w+");
        system("cls");
        printf("Please hold on while we set our database in your computer!!");
        printf("\n Process completed press any key to continue!! ");
        getch();
    }
    SetConsoleTextAttribute(hConsole, 6);
    cout << "\nEnter your first Name :";
    fflush(stdin);
    gets(u.name);
    cout << "\nEnter your age :";
    fflush(stdin);
    cin >> u.age;
    cout << "\nEnter your sex(M/F/O) :";
    fflush(stdin);
    cin >> u.sex;
    do
    {
        cout << "\nEnter your mobile number:";
        fflush(stdin);
        cin >> temp_mobile;
        result = cheek_length_mobile(temp_mobile);
        if (result == 10)
            u.mobile = temp_mobile;
        else
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "Enter a correct mobile number!!!" << endl;
            SetConsoleTextAttribute(hConsole, 6);
        }
    } while (result != 10);
    do
    {
        cout << "\nEnter a valid email id :";
        fflush(stdin);
        cin >> temp_mail;
        result_mail = cheek_mail(temp_mail);
        if (result_mail == 1)
            strcpy(u.gmail, temp_mail);
        else
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\nEnter a correct email id!!!\nThere should one '@' in this email id" << endl;
            SetConsoleTextAttribute(hConsole, 6);
        }

    } while (result_mail != 1);
    cout << "\nEnter date of birth (DD MM YYYY) :";
    fflush(stdin);
    cin >> u.date.dd >> u.date.mm >> u.date.yyyy;
    cout << "\nEnter your Username :";
    fflush(stdin);
    cin >> u.user;
    do
    {
        cout << "\nEnter your Password:";
        fflush(stdin);
        i = 0;
        while (i < 10)
        {
            temp_pass1[i] = getch();
            if (temp_pass1[i] == 13)
                break;
            else
                cout << " *";
            i++;
        }
        temp_pass1[i] = '\0';
        i = 0;
        cout << "\nConfirm your Password:";
        fflush(stdin);
        while (i < 10)
        {
            temp_pass2[i] = getch();
            if (temp_pass2[i] == 13)
                break;
            else
                cout << " *";
            i++;
        }
        temp_pass2[i] = '\0';
        if (strcmp(temp_pass1, temp_pass2) == 0)
        {
            strcpy(u.pass, temp_pass1);
            c = 0;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\nPASSWORD IS NOT MATCHING !!" << endl;
            SetConsoleTextAttribute(hConsole, 6);
            c = 1;
        }
    } while (c == 1);
    captcha();
    u.record.matchdrawn = u.record.matchloss = u.record.matchwon = u.record.numberof100 = u.record.numberof50 = u.record.numberofmatch = u.record.toatlrun = u.record.toprun = u.point = 0;
    fwrite(&u, sizeof(u), 1, f);
    fclose(f);
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n\nYOU HAVE SUCCESFULLY REGISTERED" << endl;
    cout << "Press any key to exit" << endl;
    getch();
}

void login() // to login
{
    FILE *f;
    char user[8], pass[10], temp[10];
    char x;
    int i, c_u = 1, c_p = 1, count1 = 0, count2 = 0;
    system("cls");
    while (c_u <= 3 && c_p <= 3 && count2 == 0)
    {
        SetConsoleTextAttribute(hConsole, 6);
        cout << "\nEnter USERNAME:";
        cin >> user;
        f = fopen("registration.txt", "r+");
        while (fread(&u, sizeof(u), 1, f) == 1)
        {
            if (strcmp(u.user, user) == 0)
            {
                count1 = 1;
                strcpy(temp, u.pass);
                while (c_p <= 3)
                {
                    SetConsoleTextAttribute(hConsole, 6);
                    cout << "\nENTER PASSWORD :";
                    fflush(stdin);
                    i = 0;
                    while (i < 10)
                    {
                        pass[i] = getch();
                        if (pass[i] == 13)
                            break;
                        else
                            cout << " *";
                        i++;
                    }
                    pass[i] = '\0';
                    if (strcmp(pass, temp) == 0)
                    {
                        count2 = 1;
                        captcha();
                        SetConsoleTextAttribute(hConsole, 1);
                        cout << "\n\n\nYOU HAVE SUCCESFULLY LOGIN..." << endl;
                        fclose(f);
                        cout << "PRESS ANY KEY TO GO FORWARD!!" << endl;
                        getch();
                        SetConsoleTextAttribute(hConsole, 5);
                        home(pass, user);
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 1);
                        cout << "\n\nYOU HAVE SUCCESFULLY LOGOUT.." << endl;
                        cout << "PRESS ANY KEY TO EXIT..." << endl;
                        getch();
                        break;
                    }
                    else
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\nEnter a correcct password!!";
                        SetConsoleTextAttribute(hConsole, 6);
                    }
                    c_p++;
                }
            }
        }
        if (count1 == 0)
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "USERNAME IS NOT FOUND..." << endl;
            cout << "If you are a new user register at first.." << endl;
            cout << "\n\nPress escape key (esc) to exit and press any other key to retry.." << endl;
            cout << "enter your decision" << endl;
            x = getch();
            if (x == 27)
                break;
            else
                continue;
            SetConsoleTextAttribute(hConsole, 6);
        }
        count1 = 0;
        c_u++;
    }
    if (c_u == 4 || c_p == 4)
    {
        SetConsoleTextAttribute(hConsole, 9);
        cout << "\nYOU HAVE GO THROUGH 3 TIMES,PLEASE TRY AGAIN LATER !!\n OR IF YOU ARE A NEW USER PLEASE REGISTER." << endl;
        cout << "PRESS ANY KEY TO EXIT" << endl;
        getch();
    }
}

void forget_user() // to get the forget username
{
    FILE *f, *t;
    char name[20], pass[10];
    int i = 0, count = 0;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout << "      *BE CAREFUL! TRY TO REMEMBER USERNAME AND PASSWORD" << endl;
    f = fopen("registration.txt", "r");
    t = fopen("temp.txt", "w");
    cout << "\nENTER YOUR REGISTERED FIRST NAME:";
    gets(name);
    cout << "\nENTER PASSWORD :";
    fflush(stdin);
    i = 0;
    while (i < 10)
    {
        pass[i] = getch();
        if (pass[i] == 13)
            break;
        else
            cout << " *";
        i++;
    }
    pass[i] = '\0';
    while (fread(&u, sizeof(u), 1, f) == 1)
    {
        if (strcmp(name, u.name) == 0 && strcmp(pass, u.pass) == 0)
        {
            cout << "\n\nENTER YOUR NEW USERNAME : ";
            fflush(stdin);
            gets(u.user);
            count = 1;
            fwrite(&u, sizeof(u), 1, t);
        }
        else
            fwrite(&u, sizeof(u), 1, t);
    }
    fclose(t);
    fclose(f);
    remove("registration.txt");
    rename("temp.txt", "registration.txt");
    if (count == 0)
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\n\nWORNG NAME OR PASSWORD !!\nTRY AGAIN LATER..." << endl;
    }
    else
    {
        captcha();
        system("cls");
        SetConsoleTextAttribute(hConsole, 5);
        cout << "\n\nYOU USERNAME IS SUCCESFULLY UPDATED " << endl;
    }
    SetConsoleTextAttribute(hConsole, 2);
    cout << "\nPRESS ANY KEY TO EXIT.." << endl;
    getch();
}

void forget_pass() // to get the forget password
{
    FILE *f, *t;
    char name[20], user[8], temp_pass1[10], temp_pass2[10];
    int i = 0, count = 0, c;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout << "      *BE CAREFUL! TRY TO REMEMBER USERNAME AND PASSWORD" << endl;
    f = fopen("registration.txt", "r");
    t = fopen("temp.txt", "w");
    cout << "\nENTER YOUR REGISTERED FIRST NAME:";
    fflush(stdin);
    gets(name);
    cout << "\nENTER USERNAME :";
    fflush(stdin);
    cin >> user;
    while (fread(&u, sizeof(u), 1, f) == 1)
    {
        if (strcmp(name, u.name) == 0 && strcmp(user, u.user) == 0)
        {
            do
            {
                cout << "\n\nENTER YOUR NEW PASSWORD:";
                fflush(stdin);
                i = 0;
                while (i < 10)
                {
                    temp_pass1[i] = getch();
                    if (temp_pass1[i] == 13)
                        break;
                    else
                        cout << " *";
                    i++;
                }
                temp_pass1[i] = '\0';
                i = 0;
                cout << "\nCONFIRM YOUR PASSWORD:";
                fflush(stdin);
                while (i < 10)
                {
                    temp_pass2[i] = getch();
                    if (temp_pass2[i] == 13)
                        break;
                    else
                        cout << " *";
                    i++;
                }
                temp_pass2[i] = '\0';
                if (strcmp(temp_pass1, temp_pass2) == 0)
                {
                    strcpy(u.pass, temp_pass1);
                    c = 0;
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "\nPASSWORD IS NOT MATCHING !!" << endl;
                    SetConsoleTextAttribute(hConsole, 6);
                    c = 1;
                }
            } while (c == 1);
            count = 1;
            fwrite(&u, sizeof(u), 1, t);
        }
        else
            fwrite(&u, sizeof(u), 1, t);
    }
    fclose(t);
    fclose(f);
    remove("registration.txt");
    rename("temp.txt", "registration.txt");
    if (count == 0)
    {
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\n\nWORNG NAME OR USERNAME !!\nTRY AGAIN LATER..." << endl;
    }
    else
    {
        captcha();
        SetConsoleTextAttribute(hConsole, 5);
        system("cls");
        cout << "\n\nYOU PASSWORD IS SUCCESFULLY UPDATED" << endl;
    }
    SetConsoleTextAttribute(hConsole, 2);
    cout << "\nPRESS ANY KEY TO EXIT.." << endl;
    getch();
}

void deleteaccount() // for delete account
{
    SetConsoleTextAttribute(hConsole, 6);
    FILE *f, *t;
    char pass[10], user[8], name[20];
    int long long mobile;
    int j = 1, i;
    if ((t = fopen("temp1.txt", "w")) == NULL)
        exit(0);
    if ((f = fopen("registration.txt", "r")) == NULL)
        exit(0);
    system("cls");
    cout << "Enter some details of the account of you you want to delete.." << endl;
    cout << "\nEnter your name : ";
    gets(name);
    cout << "\nEnter mobile number : ";
    cin >> mobile;
    fflush(stdin);
    cout << "\nEnter username : ";
    gets(user);
    cout << "\nEnter your password :";
    fflush(stdin);
    i = 0;
    while (i < 10)
    {
        pass[i] = getch();
        if (pass[i] == 13)
            break;
        else
            cout << " *";
        i++;
    }
    pass[i] = '\0';
    fflush(stdin);
    while (fread(&u, sizeof(u), 1, f) == 1)
    {
        if (strcmp(u.pass, pass) == 0 && strcmp(u.name, name) == 0 && strcmp(u.user, user) == 0 && u.mobile == mobile)
        {
            j = 0;
            continue;
        }
        else
            fwrite(&u, sizeof(u), 1, t);
    }
    if (j == 1)
    {
        SetConsoleTextAttribute(hConsole, 4);
        system("cls");
        cout << "\n\nRECORDS OF ACCOUNT IS NOT FOUND!!\nENTER CORRECT INFORMATION..." << endl;
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\n\nPRESS ANY KEY TO EXIT..." << endl;
        getch();
        fclose(f);
        fclose(t);
    }
    else
    {
        fclose(f);
        fclose(t);
        captcha();
        remove("registration.txt");
        rename("temp1.txt", "registration.txt");
        SetConsoleTextAttribute(hConsole, 2);
        system("cls");
        cout << "\n\nTHIS ACCOUNT IS SUCCESSFULLY DELETED...." << endl;
        SetConsoleTextAttribute(hConsole, 6);
        cout << "\n\nPRESS ANY KEY TO EXIT..." << endl;
        getch();
    }
}

void home(char pass[10], char user[8]) // for home page after login
{
    char option;
    FILE *p;
    int i, x, count = 0;
    while (count == 0)
    {
        time_t t;
        time(&t);
        system("cls");
        SetConsoleTextAttribute(hConsole, 5);
        cout << "********************** |HOME PAGE| ***********************" << endl;
        for (i = 0; i <= 100; i++)
            cout << "-";
        SetConsoleTextAttribute(hConsole, 6);
        cout << "\nCURRENT DATE AND TIME IS :" << ctime(&t);
        SetConsoleTextAttribute(hConsole, 5);
        for (i = 0; i <= 100; i++)
            cout << "-";
        cout << "\n\nPRESS 1->VIEW PROFILE" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 2->ABOUT US" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 3->RATE US" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 4->LOGOUT" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 5->PLAY GAME" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 6->VIEW SCHORE" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 7->VIEW POINT" << endl;
        cout << "----------------------------" << endl;
        cout << "PRESS 8->EDIT PROFILE" << endl;
        cout << "----------------------------" << endl;
        cout << "ENTER YOUR CHOISE:";
        x = getch();
        switch (x)
        {
        case '1':
            profile(pass, user); // to view profile
            break;
        case '2':
            system("cls");
            SetConsoleTextAttribute(hConsole, 6);
            cout << "                    ABOUT US     " << endl;
            cout << "This is a app where you can play a cricket game which is so much interesting. it is devoloped by " << endl;
            cout << "Mr. KRISHNENDU BIR. He is now a student of B Tech first year of INDIAN INSTITUTE OF TECHNOLOGY" << endl;
            cout << "BHUBANESWAR (IIT BBS) which is one of the most famous and precious university of India.I have desined" << endl;
            cout << "it to play crickt but here is a desclaimer it should play in restricted way.It may be addicted\n\n"
                 << endl;
            cout << "Thank You for reading..." << endl;
            cout << "Enter any key to exit.." << endl;
            getch();
            break;
        case '3':
            rate(); // to rate
            break;
        case '4': // for logout
            system("cls");
            SetConsoleTextAttribute(hConsole, 6);
            cout << "DO YOU WANT TO LOGOUT" << endl;
            cout << "IF YES press 'Y', If NO press 'N'" << endl;
            cout << "Enter your disision: ";
            cin >> option;
            if (option == 'Y' || option == 'Y' + 32)
                count = 1;
            else if (option == 'N' || option == 'N' + 32)
                count = 0;
            else
            {
                cout << "\nEnter a correct input..\n press any key to exit.." << endl;
                getch();
            }
            break;
        case '5': // to play cricket
            cricket(pass, user);
            break;
        case '6':
            viewschore(pass, user); // to viewschore
            break;
        case '7':
            viewpoint(pass, user); // to viewpoint
            break;
        case '8':
            edit(pass, user); // to edit data
            break;
        default:
            system("cls");
            cout << "PRESS A CORRECT NUMBER..." << endl;
            cout << "\nPRESS ANY KEY TO EXIT.." << endl;
            getch();
        }
    }
}

void profile(char pass[10], char user[8]) // toview profile
{
    FILE *f;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    if ((f = fopen("registration.txt", "r")) == NULL)
        exit(0);
    while (fread(&u, sizeof(u), 1, f) == 1)
    {
        if (strcmp(pass, u.pass) == 0 && strcmp(user, u.user) == 0)
        {
            cout << "                      -: PERSONAL DETAILS :-" << endl;
            cout << "                NAME : " << u.name << endl;
            cout << "                AGE : " << u.age << endl;
            cout << "                GENDER : " << u.sex << endl;
            cout << "                MOBILE NO. : " << u.mobile << endl;
            cout << "                EMAIL ID : " << u.gmail << endl;
            cout << "                DATE OF BIRTH : " << u.date.dd << "/" << u.date.mm << "/" << u.date.yyyy << endl;
        }
    }
    fclose(f);
    cout << "\n\nPress any key to exit.." << endl;
    getch();
}

void rate() // for rate
{
    char sug[100];
    int x, r;
    system("cls");
    cout << "DO YOU WANT TO RATE US..." << endl;
    cout << "IF YES PRESS '1' IF NO PRESS '0'.." << endl;
    cout << "ENTER YOUR CHOISE :";
    cin >> x;
    switch (x)
    {
    case 1:
        cout << "\nGIVE A RATING OUT OF 5 :";
        cin >> r;
        if (r < 3)
        {
            cout << "GIVE A SUGGESION TO IMPREOVE.." << endl;
            cin >> sug;
            cout << "THANK YOU FOR YOUR VALUEABLE SUGGESION.." << endl;
            cout << "PRESS ANY KEY TO EXIT..." << endl;
            getch();
        }
        else
        {
            cout << "THANK YOU.." << endl;
            cout << "PRESS ANY KEY TO EXIT..." << endl;
            getch();
        }
        break;
    case 0:
        cout << "\nOK,THANK YOU..." << endl;
        cout << "PRESS ANY KEY TO MOVE.." << endl;
        getch();
        break;
    default:
        cout << "\nPRESS A COREECT INPUT .." << endl;
        cout << "PRESS ANY KEY TO MOVE.." << endl;
        getch();
        rate();
        break;
    }
}

void cricket(char pass[10], char user[8]) // for playing game
{
    int over;
    char select_over;
    time_t t;
    time(&t);
    SetConsoleOutputCP(CP_UTF8);
    char x;
    int c;
    do
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 5);
        cout << "---------------------------------------------------------------------------------------------------------------------------------"
             << "\n";
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "------------------------------------------------------";
        SetConsoleTextAttribute(hConsole, 6);
        cout << "HAND CRICKET GAME";
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << "----------------------------------------------------------"
             << "\n";
        SetConsoleTextAttribute(hConsole, 2);
        cout << "---------------------------------------------------------------------------------------------------------------------------------"
             << "\n\n";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "-:-:-:-:-:-:-:-:RULE-:-:-:-:-:-:-:-:-" << endl;
        cout << "1. AT THE TIME OF BOWLING YOU HAVE TO CHOOSE A NUMBER FROM 1 TO 6."
             << "\n"
             << "   IF YOU CHOOSE A WRONG NUMBER IT WILL BE A WIDE BALL." << endl;
        cout << "2. AT THE TIME OF BATTNG YOU HAVE TO CHOOSE A NUMBER FROM 0 TO 6."
             << "\n"
             << "   IF YOU CHOOSE A WRONG NUMBER YOU WILL BE OUT." << endl;
        SetConsoleTextAttribute(hConsole, 6);
        cout << "\n************************** REWARD **************************" << endl;
        cout << "    OVER             WIN               LOSS               DRAW" << endl;
        cout << "     2               +50               -50                  0  " << endl;
        cout << "     5               +100              -100                 0  " << endl;
        cout << "    10               +200              -200                 0  " << endl;
        cout << "    20              +500               -500                 0  " << endl;
        cout << "    50              +1000             -1000                 0  " << endl;
        cout << "Press any key to continue.." << endl;
        getch();
        system("cls");
        SetConsoleTextAttribute(hConsole, 9);
        cout << "\n       - : | Select Over | : -" << endl;
        cout << "Press 1 -> OVER '2'\n"
             << endl;
        cout << "Press 2 -> OVER '5'\n"
             << endl;
        cout << "Press 3 -> OVER '10'\n"
             << endl;
        cout << "Press 4 -> OVER '20'\n"
             << endl;
        cout << "Press 5 -> OVER '50'\n"
             << endl;
        do
        {
            SetConsoleTextAttribute(hConsole, 6);
            cout << "Enter your decision :";
            select_over = getch();
            switch (select_over)
            {
            case '1':
                over = 2;
                break;
            case '2':
                over = 5;
                break;
            case '3':
                over = 10;
                break;
            case '4':
                over = 20;
                break;
            case '5':
                over = 50;
                break;
            default:
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\nEnter correct input.." << endl;
            }
        } while (select_over < '1' || select_over > '5');

        int toss, toss_cp, select, count1 = 0, count2 = 0, n_4 = 0, n_6 = 0;
        system("cls");
        SetConsoleTextAttribute(hConsole, 1);
        cout << " ------------- MATCH DETAILS -------------" << endl;
        cout << "          YOU      VS      OPPONENT  " << endl;
        cout << "CURRENT DATE AND TIME IS :" << ctime(&t) << endl;
        cout << "           VENUE : EDEN GARDEN " << endl;
        cout << "             OVER : " << over << endl;
        cout << "\n\nPress any key continue.." << endl;
        getch();
        system("cls");
        SetConsoleTextAttribute(hConsole, 3);
        cout << "\n"
             << "-$-$-TOSS-$-$-" << endl;
        cout << "Enter '1' to select HEAD"
             << "\n"
             << "Enter '0' to select TAIL" << endl;
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\n"
             << "Enter your choise :";
        cin >> toss;
        srand(time(0));
        toss_cp = (rand() % 2) + 0;
        if (toss_cp == toss)
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\n"
                 << "You have won the toss" << endl;
            cout << "Enter '1' to choose Bat"
                 << "\n"
                 << "Enter '0' to choose Ball"
                 << "\n\n";
            SetConsoleTextAttribute(hConsole, 2);
            cout << "Enter your choise :";
            cin >> select;
            if (select == 1)
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "\n"
                     << "You have select to bat first."
                     << "\n";
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n"
                     << " -------------------- INNINGS 1 -------------------"
                     << "\n";
                bat_1(&count1, &n_4, &n_6, over);
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                cout << "\n"
                     << "-------------------- INNINGS 2 -------------------"
                     << "\n";
                ball_2(&count2, count1, over);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "\n"
                     << "You have select to ball first :"
                     << "\n";
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n"
                     << "-------------------- INNINGS 1 -------------------"
                     << "\n";
                ball_1(&count2, over);
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                cout << "\n"
                     << "-------------------- INNINGS 2 -------------------"
                     << "\n";
                bat_2(&count1, count2, &n_4, &n_6, over);
            }
        }
        else
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\n"
                 << "You have loss the toss" << endl;
            srand(time(0));
            select = (rand() % 2) + 0;
            if (select == 1)
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "\n"
                     << "Opponent have select to ball first."
                     << "\n";
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n"
                     << "-------------------- INNINGS 1 -------------------"
                     << "\n";
                bat_1(&count1, &n_4, &n_6, over);
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                cout << "\n"
                     << "-------------------- INNINGS 2 -------------------"
                     << "\n";
                ball_2(&count2, count1, over);
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << "\n"
                     << "Opponent have select to bat first."
                     << "\n";
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                SetConsoleTextAttribute(hConsole, 7);
                cout << "\n"
                     << "-------------------- INNINGS 1 -------------------"
                     << "\n";
                ball_1(&count2, over);
                cout << "Press any key to continue.." << endl;
                getch();
                system("cls");
                cout << "\n"
                     << "-------------------- INNINGS 2 -------------------"
                     << "\n";
                bat_2(&count1, count2, &n_4, &n_6, over);
            }
        }
        cout << "Press any key to continue.." << endl;
        getch();
        system("cls");
        SetConsoleTextAttribute(hConsole, 6);
        if (count1 > count2)
        {
            cout << "\n"
                 << "    CONGRACHULATION!!\nYOU HAVE WON THE MATCH.";
            std::cout << "\xF0\x9F\x98\x84" << std::endl;
            SetConsoleTextAttribute(hConsole, 2);
            switch (over)
            {
            case (2):
                cout << "YOU EARN 50 COINS." << endl;
                break;
            case (5):
                cout << "YOU EARN 100 COINS." << endl;
                break;
            case (10):
                cout << "YOU EARN 200 COINS." << endl;
                break;
            case (20):
                cout << "YOU EARN 500 COINS." << endl;
                break;
            case (50):
                cout << "YOU EARN 1000 COINS." << endl;
                break;
            }
            c = 0;
        }
        else if (count1 < count2)
        {
            cout << "\n"
                 << "YOU HAVE LOSSED THE MATCH\nBETTER LUCK NEXT TIME.";
            std::cout << "\xF0\x9F\x98\xA5" << std::endl;
            SetConsoleTextAttribute(hConsole, 4);
            switch (over)
            {
            case (2):
                cout << "YOU LOSSED 50 COINS." << endl;
                break;
            case (5):
                cout << "YOU LOSSED 100 COINS." << endl;
                break;
            case (10):
                cout << "YOU LOSSED 200 COINS." << endl;
                break;
            case (20):
                cout << "YOU LOSSED 500 COINS." << endl;
                break;
            case (50):
                cout << "YOU LOSSED 1000 COINS." << endl;
                break;
            }
            c = 0;
        }
        else
        {
            cout << "\n"
                 << "MATCH DRAW" << endl;
            x = 1;
            c = 1;
        }
        SetConsoleTextAttribute(hConsole, 8);
        if (c == 0)
        {
            cout << "\n"
                 << "Will you want to play this game again :"
                 << "\n"
                 << "If YES press ANY KEY & If NO press ESCAPE KEY(esc)" << endl;
            x = getch();
        }
        FILE *f, *t;
        if ((t = fopen("temp.txt", "w")) == NULL)
            exit(0);
        if ((f = fopen("registration.txt", "r")) == NULL)
            exit(0);
        while (fread(&u, sizeof(u), 1, f) == 1)
        {
            if (strcmp(pass, u.pass) == 0 && strcmp(user, u.user) == 0)
            {
                u.record.numberofmatch += 1;
                if (count1 > count2)
                {
                    u.record.matchwon += 1;
                    switch (over)
                    {
                    case 2:
                        u.point += 50;
                        break;
                    case 5:
                        u.point += 100;
                        break;
                    case 10:
                        u.point += 200;
                        break;
                    case 20:
                        u.point += 500;
                        break;
                    case 50:
                        u.point += 1000;
                        break;
                    default:
                        break;
                    }
                }
                else if (count1 < count2)
                {
                    u.record.matchloss += 1;
                    switch (over)
                    {
                    case 2:
                        u.point -= 50;
                        break;
                    case 5:
                        u.point -= 100;
                        break;
                    case 10:
                        u.point -= 200;
                        break;
                    case 20:
                        u.point -= 500;
                        break;
                    case 50:
                        u.point -= 1000;
                        break;
                    default:
                        break;
                    }
                }
                else
                    u.record.matchdrawn += 1;
                if (count1 >= 50 && count1 < 100)
                    u.record.numberof50 += 1;
                if (count1 >= 100)
                    u.record.numberof100 += 1;
                u.record.toatlrun += count1;
                if (u.record.toprun < count1)
                    u.record.toprun = count1;
                u.record.numberof4 += n_4;
                u.record.numberof6 += n_6;
                fwrite(&u, sizeof(u), 1, t);
            }
            else
                fwrite(&u, sizeof(u), 1, t);
        }
        fclose(f);
        fclose(t);
        remove("registration.txt");
        rename("temp.txt", "registration.txt");
    } while (x != 27);
}

void bat_1(int *count1, int *n_4, int *n_6, int over) // for batting first of the user
{
    int a, b, i, j, wicket = 0, w = 0;
    srand(time(0));
    for (i = 0; (i < over) && (wicket < 10); i++)
    {
        for (j = 0, w = 1; (j < 6) && (wicket < 10); j++, w = 1)
        {
            SetConsoleTextAttribute(hConsole, 6);
            cout << "\nschore : " << *count1 << "-" << wicket << endl;
            cout << "over : " << i << "." << j << endl;
            SetConsoleTextAttribute(hConsole, 2);
            cout << "\n"
                 << "Enter a choise (between 0 to 6) :";
            cin >> a;
            if (a < 0 || a > 6)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n"
                     << "OUT!!!!(FOR WRONG INPUT)" << endl;
                wicket++;
                w = 0;
            }
            b = (rand() % 6) + 1;
            if (a == b)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n"
                     << "OUT!!!!" << endl;
                wicket++;
                w = 0;
            }
            else if (a != b && w == 1)
            {
                *count1 += a;
                if (a == 4)
                    *n_4 += 1;
                else if (a == 6)
                    *n_6 += 1;
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n"
         << "         -: schore :-"
         << "\n";
    SetConsoleTextAttribute(hConsole, 6);
    cout << "Your run is : " << *count1 << "-" << wicket << "\n"
         << "over :";
    if (j == 6)
        cout << i << endl;
    else
        cout << (i - 1) << "." << j << endl;
    cout << "\nTarget of opponet : " << (*count1 + 1) << " Run in " << over << " Over" << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void ball_1(int *count2, int over) // for bowling first of the user
{
    int a, b, i, j, wicket = 0, w;
    srand(time(0));
    for (i = 0; (i < over) && (wicket < 10); i++)
    {
        for (j = 0, w = 1; (j < 6) && (wicket < 10); j++, w = 1)
        {
            SetConsoleTextAttribute(hConsole, 6);
            cout << "\nschore : " << *count2 << "-" << wicket << endl;
            cout << "over : " << i << "." << j << endl;
            SetConsoleTextAttribute(hConsole, 2);
            cout << "\n"
                 << "Enter a choise (between 1 to 6):";
            cin >> a;
            if (a < 1 || a > 6)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "WIDE BALL !!" << endl;
                *count2 += 1;
                j--;
                continue;
            }
            b = (rand() % 7) + 0;
            if (a == b)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n"
                     << "OUT!!!!" << endl;
                wicket++;
                w = 0;
            }
            else if (a != b && w == 1)
            {
                *count2 += b;
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n"
         << "        -: schore :-"
         << "\n";
    SetConsoleTextAttribute(hConsole, 6);
    cout << "Opponent's run is : " << *count2 << "-" << wicket << "\n"
         << "over :";
    if (j == 6)
        cout << i << endl;
    else
        cout << (i - 1) << "." << j << endl;
    cout << "\nTarget of yours : " << (*count2 + 1) << " Run in " << over << " Over" << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void bat_2(int *count1, int target, int *n_4, int *n_6, int over) // for batting in 2nd innings of the user
{
    int a, b, i, j, wicket = 0, w;
    srand(time(0));
    for (i = 0; (i < over) && (*count1 <= target) && (wicket < 10); i++)
    {
        for (j = 0, w = 1; (j < 6) && (*count1 <= target) && (wicket < 10); j++, w = 1)
        {
            SetConsoleTextAttribute(hConsole, 6);
            cout << "\nschore : " << *count1 << "-" << wicket << endl;
            cout << "over : " << i << "." << j << endl;
            SetConsoleTextAttribute(hConsole, 2);
            cout << "\n"
                 << "Enter a choise (between 0 to 6) :";
            cin >> a;
            if (a < 0 || a > 6)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n"
                     << "OUT!!!!(FOR WRONG INPUT)" << endl;
                wicket++;
                w = 0;
            }
            b = (rand() % 6) + 1;
            if (a == b)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n"
                     << "OUT!!!!" << endl;
                wicket++;
                w = 0;
            }
            else if (a != b && w == 1)
            {
                *count1 += a;
                if (a == 4)
                    *n_4 += 1;
                else if (a == 6)
                    *n_6 += 1;
                if (*count1 > target)
                {
                    j++;
                    break;
                }
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n"
         << "       -: schore :-"
         << "\n";
    SetConsoleTextAttribute(hConsole, 6);
    cout << "Your run is : " << *count1 << "-" << wicket << "\n"
         << "over :";
    if (j == 6)
        cout << i << endl;
    else
        cout << (i - 1) << "." << j << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void ball_2(int *count2, int target, int over) // for bowling in the 2nd innings of the user
{
    int a, b, i, j, wicket = 0, w;
    srand(time(0));
    for (i = 0; (i < over) && (*count2 <= target) && (wicket < 10); i++)
    {
        for (j = 0, w = 1; (j < 6) && (*count2 <= target) && (wicket < 10); j++, w = 1)
        {
            SetConsoleTextAttribute(hConsole, 6);
            cout << "\nschore : " << *count2 << "-" << wicket << endl;
            cout << "over : " << i << "." << j << endl;
            SetConsoleTextAttribute(hConsole, 2);
            cout << "\n"
                 << "Enter a choise (between 1 to 6):";
            cin >> a;
            if (a < 1 || a > 6)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "WIDE BALL !!" << endl;
                *count2 += 1;
                j--;
                continue;
            }
            b = (rand() % 7) + 0;
            if (a == b)
            {
                SetConsoleTextAttribute(hConsole, 4);
                cout << "\n"
                     << "OUT!!!!" << endl;
                wicket++;
                w = 0;
            }
            else if (a != b && w == 1)
            {
                *count2 += b;
                if (*count2 > target)
                {
                    j++;
                    break;
                }
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 5);
    cout << "\n"
         << "        -: schore :-"
         << "\n";
    SetConsoleTextAttribute(hConsole, 6);
    cout << "Opponent's run is : " << *count2 << "-" << wicket << "\n"
         << "over :";
    if (j == 6)
        cout << i << endl;
    else
        cout << (i - 1) << "." << j << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void viewschore(char pass[10], char user[8]) // to view schore
{
    FILE *f;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    if ((f = fopen("registration.txt", "r")) == NULL)
        exit(0);
    while (fread(&u, sizeof(u), 1, f) == 1)
    {
        if (strcmp(pass, u.pass) == 0 && strcmp(user, u.user) == 0)
        {
            cout << "                      -: SCHORE DETAILS :-" << endl;
            cout << "                NUMBER OF TOTAL MATCH : " << u.record.numberofmatch << endl;
            cout << "                NUMBER OF MATCH WON : " << u.record.matchwon << endl;
            cout << "                NUMBER OF MATCH LOSS : " << u.record.matchloss << endl;
            cout << "                NUMBER OF MATCH DRAWN : " << u.record.matchdrawn << endl;
            cout << "                NUMBER OF HALF-CENTURY : " << u.record.numberof50 << endl;
            cout << "                NUMBER OF CENTURY : " << u.record.numberof100 << endl;
            cout << "                TOATL RUN : " << u.record.toatlrun << endl;
            cout << "                AVARAGE RUN PER MATCH : " << setprecision(5) << (u.record.toatlrun / u.record.numberofmatch) << endl;
            cout << "                TOP RUN : " << u.record.toprun << endl;
            cout << "                NUMBER OF FOUR : " << u.record.numberof4 << endl;
            cout << "                NUMBER OF SIX : " << u.record.numberof6 << endl;
            cout << "                AVARAGE FOUR PER MATCH : " << setprecision(5) << (u.record.numberof4 / u.record.numberofmatch) << endl;
            cout << "                AVARAGE SIX PER MATCH : " << setprecision(5) << (u.record.numberof6 / u.record.numberofmatch) << endl;
        }
    }
    fclose(f);
    cout << "\n\nPress any key to exit.." << endl;
    getch();
}

void viewpoint(char pass[10], char user[8]) // to view point
{
    FILE *f;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    if ((f = fopen("registration.txt", "r")) == NULL)
        exit(0);
    while (fread(&u, sizeof(u), 1, f) == 1)
    {
        if (strcmp(pass, u.pass) == 0 && strcmp(user, u.user) == 0)
        {
            cout << "\n\n\n          YOUR POINT IS : " << u.point;
        }
    }
    fclose(f);
    cout << "\n\nPress any key to exit.." << endl;
    getch();
}

void edit(char pass[10], char user[8]) // for edit data
{
    char num, x;
    int long long temp_mobile;
    int result, result_mail, i = 0, c;
    char temp_mail[30], temp_pass1[10], temp_pass2[10];
    FILE *f, *t;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout << "WHICH DATA YOU WANT TO EDIT..." << endl;
    SetConsoleTextAttribute(hConsole, 9);
    cout << "\nPRESS 1-> PERSONAL DETAILS" << endl;
    cout << "\nPRESS 2-> CONTACT DETAILS" << endl;
    cout << "\n\nENTER YOUR DESICION :";
    num = getch();
    SetConsoleTextAttribute(hConsole, 6);
    switch (num)
    {
    case '1':
        system("cls");
        if ((f = fopen("registration.txt", "r")) == NULL)
            exit(0);
        if ((t = fopen("temp.txt", "w")) == NULL)
            exit(0);
        i = 1;
        while (fread(&u, sizeof(u), 1, f) == 1)
        {
            if (strcmp(pass, u.pass) == 0 && strcmp(user, u.user) == 0)
            {
                cout << "\nENTER YOUR NAME : ";
                fflush(stdin);
                gets(u.name);
                cout << "\nENTER YOUR AGE : ";
                fflush(stdin);
                cin >> u.age;
                cout << "\nENTER YOUR GENDER (M/F/O) : ";
                fflush(stdin);
                cin >> u.sex;
                cout << "\nENTER YOUR DATE OF BIRTH (dd mm yyyy) : ";
                fflush(stdin);
                cin >> u.date.dd >> u.date.mm >> u.date.yyyy;
                fwrite(&u, sizeof(u), 1, t);
            }
            else
                fwrite(&u, sizeof(u), 1, t);
        }
        break;
    case '2':
        system("cls");
        if ((f = fopen("registration.txt", "r")) == NULL)
            exit(0);
        if ((t = fopen("temp.txt", "w")) == NULL)
            exit(0);
        i = 1;
        while (fread(&u, sizeof(u), 1, f) == 1)
        {
            if (strcmp(pass, u.pass) == 0 && strcmp(user, u.user) == 0)
            {
                do
                {
                    cout << "\nENTER YOUR MOBILE NUMBER:";
                    fflush(stdin);
                    cin >> temp_mobile;
                    result = cheek_length_mobile(temp_mobile);
                    if (result == 10)
                        u.mobile = temp_mobile;
                    else
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "ENTER A CORRECT MOBILE NUMBER!!!" << endl;
                        SetConsoleTextAttribute(hConsole, 6);
                    }
                } while (result != 10);
                do
                {
                    cout << "\nENTER A VALID EMAIL ID :";
                    fflush(stdin);
                    cin >> temp_mail;
                    result_mail = cheek_mail(temp_mail);
                    if (result_mail == 1)
                        strcpy(u.gmail, temp_mail);
                    else
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "\nENTER A CORRECT EMAIL ID!!!\nTHERE SHOULD ONE '@' IN THIS EMAIL ID" << endl;
                        SetConsoleTextAttribute(hConsole, 6);
                    }
                } while (result_mail != 1);
                fwrite(&u, sizeof(u), 1, t);
            }
            else
                fwrite(&u, sizeof(u), 1, t);
        }
        break;
    default:
        SetConsoleTextAttribute(hConsole, 4);
        cout << "\nENTER CORRECT INPUT.." << endl;
        cout << "\n\nPRESS ANY KEY TO EXIT.." << endl;
        getch();
    }
    if (i == 1)
    {
        fclose(t);
        fclose(f);
        remove("registration.txt");
        rename("temp.txt", "registration.txt");
        captcha();
        SetConsoleTextAttribute(hConsole, 2);
        system("cls");
        cout << "\n\nYOUR DETAILS HAS SUCCESFULLY EDITED...." << endl;
        cout << "\n\nPRESS ESCAPE KEY(esc) TO EXIT & PRESS ANY TO TO EDIT ANOTHER DATA.." << endl;
        x = getch();
        if (x != 27)
            edit(pass, user);
    }
}