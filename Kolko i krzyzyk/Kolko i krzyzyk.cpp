#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <windows.h>    //c++
#include <conio.h>
#include <stdlib.h>
#include <time.h>


void SetColor(int text, int bg)         //c++ 
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void fieldvivod();
void gamevscomp();
void gamevsplayer();
void playermove();
void computermove();
void checkfield(char symbol);
void history();
char field[10] = "012345678";
char symbol = ' ';
int step = 0;
void main()
{
    setlocale(LC_ALL, "");  //nie działają polskie napisy
    srand(time(NULL));
    system("color 70");
    printf("Welcome to \"Tic-tac-toe\"!\nPress any button to continue...");
    _getch();
    system("cls");
    for (;;)
    {
        printf("1-Instractions\n2-Rules\n3-New game\n4-Match history\n0-exit\n\n");
        switch (_getch())
        {
        case 49:
        {
            system("cls");
            printf("You are playing \"Tic-tac-toe\".\n1.Choose the game mode (with computer or with friend)\n2.Choose an empty cell from 1 to 8.\n\n");
            printf("   |   |   \n 0 | 1 | 2 \n___|___|___\n   |   |   \n 3 | 4 | 5 \n___|___|___\n   |   |   \n 6 | 7 | 8 \n   |   |   \n\n");
            printf("The game will end when someone would succeed in placing 3 marks in row\nor when there are no empty cells left.\n\n");
            break;
        }
        case 50:
        {
            system("cls");
            printf("You are playing \"Tic-tac-toe\". The rules are simple.\nPlayers take turns placing marks (X or O)\non the empty cells of 3x3 field.\nThe player who succeeds in placing three of their marks in a diagonal,\nhorizontal, or vertical row is the winner.\nThe first move is made by the player who puts the \"X\".\n\n");
            break;
        }
        case 51:
        {
            system("cls");
            step = 0;
            for (int i = 0; i < 9; i++)
                field[i] = i + 48;
            bool gamechoose = true;
            while (gamechoose)
            {
                printf("Choose game mode\n1-with computer\n2-with friend\n\n");
                int choice;
                scanf("%d", &choice);
                if (choice == 1)
                {
                    system("cls");
                    gamevscomp();
                    gamechoose = false;
                }
                else if (choice == 2)
                {
                    system("cls");
                    gamevsplayer();
                    gamechoose = false;
                }
                else
                    printf("There is no such choice!\n");
            }
            break;
        }
        case 52:
        {
            system("cls");
            history();
            break;
        }
        case 48:
        {
            system("cls");
            printf("Thenk you for playing! The program is ending it`s work...\n");
            return;
        }
        default:
        {
            system("cls");
            printf("There is no such choice!\n\n");
            break;
        }
        }
    }
}



void fieldvivod()
{
    printf("   |   |   \n");
    for (int i = 0;i < 9;i++)
    {
        if (field[i] == 'X')
        {
            SetColor(4, 7);
            printf(" %c ", field[i]);
            SetColor(0, 7);
        }
        else if (field[i] == 'O')
        {
            SetColor(1, 7);
            printf(" %c ", field[i]);
            SetColor(0, 7);
        }
        else
            printf(" %c ", field[i]);
        if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7)
        {
            printf("|");
        }
        else if (i == 2 || i == 5)
        {
            printf("\n___|___|___\n   |   |   \n");
        }
        else if (i == 8)
        {
            printf("\n");
        }
    }
    printf("   |   |   \n\n\n");
}
void checkfield(char symbol)
{   
    system("cls");
    FILE *plik;
    plik = fopen("history.txt", "a");
    if (field[0] == field[1] && field[0] == field[2] ||
        field[3] == field[4] && field[3] == field[5] ||
        field[6] == field[7] && field[6] == field[8] ||
        field[0] == field[3] && field[0] == field[6] ||
        field[1] == field[4] && field[1] == field[7] ||
        field[2] == field[5] && field[2] == field[8] ||
        field[0] == field[4] && field[0] == field[8] ||
        field[6] == field[4] && field[6] == field[2])
    {
        fieldvivod();
        printf("Game ends!\nThe winner is: %c\n\n", symbol);
        char nextline = '\n';
        fwrite(&symbol, sizeof(char), 1, plik);
        fwrite(&nextline, sizeof(char), 1, plik);
        //zapis v fail "Pobedili %c" i perehod na sledujuszuju stroku
        step = 100;
    }
    else if (step == 8)
    {
        fieldvivod();
        char re[8] = "no one&";
        int a = 0;
        printf("Draw!\n");

        while (a<7)
        {
            fwrite(&re[a], sizeof(char), 1, plik);
            a++;
        }

        step = 100;
    }
    fclose(plik);
}
void playermove()
{
    int k;
    bool check = false;
    while (check == false)
    {
        printf("Turn %c\nEnter cell number:\n", symbol);
        scanf("%d", &k);
        if (field[k] == 'X' || field[k] == 'O')
        {
            printf("The cell is not empty!Choose another cell!\n");
        }
        else if (k < 0 || k>8)
        {
            printf("There is no cell with that number!\n");
        }
        else
        {
            field[k] = symbol;
            check = true;
        }
    }
    checkfield(symbol);
}
void computermove()
{
    int kletkacomp;
    char playersymbol;
    if (symbol == 'X')
    {
        playersymbol = 'O';
    }
    else
    {
        playersymbol = 'X';
    }

    srand(time(NULL));
    bool checkcomp = false;
    
    if (field[0] == field[1] && field[1] == symbol && field[2] != playersymbol)
    {
        field[2] = symbol;
    }
    else if (field[0] == field[2] && field[2] == symbol && field[1] != playersymbol)
    {
        field[1] = symbol;
    }
    else if (field[1] == field[2] && field[2] == symbol && field[0] != playersymbol)
    {
        field[0] = symbol;
    }

    else if (field[3] == field[4] && field[4] == symbol && field[5] != playersymbol)
    {
        field[5] = symbol;
    }
    else if (field[3] == field[5] && field[5] == symbol && field[4] != playersymbol)
    {
        field[4] = symbol;
    }
    else if (field[4] == field[5] && field[5] == symbol && field[3] != playersymbol)
    {
        field[3] = symbol;
    }

    else if (field[6] == field[7] && field[7] == symbol && field[8] != playersymbol)
    {
        field[8] = symbol;
    }
    else if (field[6] == field[8] && field[8] == symbol && field[7] != playersymbol)
    {
        field[7] = symbol;
    }
    else if (field[7] == field[8] && field[8] == symbol && field[6] != playersymbol)
    {
        field[6] = symbol;
    }

    else if (field[0] == field[3] && field[3] == symbol && field[6] != playersymbol)
    {
        field[6] = symbol;
    }
    else if (field[0] == field[6] && field[6] == symbol && field[3] != playersymbol)
    {
        field[3] = symbol;
    }
    else if (field[3] == field[6] && field[6] == symbol && field[0] != playersymbol)
    {
        field[0] = symbol;
    }

    else if (field[1] == field[4] && field[4] == symbol && field[7] != playersymbol)
    {
        field[7] = symbol;
    }
    else if (field[1] == field[7] && field[7] == symbol && field[4] != playersymbol)
    {
        field[4] = symbol;
    }
    else if (field[4] == field[7] && field[7] == symbol && field[1] != playersymbol)
    {
        field[1] = symbol;
    }

    else if (field[2] == field[5] && field[5] == symbol && field[8] != playersymbol)
    {
        field[8] = symbol;
    }
    else if (field[2] == field[8] && field[8] == symbol && field[5] != playersymbol)
    {
        field[5] = symbol;
    }
    else if (field[5] == field[8] && field[8] == symbol && field[2] != playersymbol)
    {
        field[2] = symbol;
    }

    else if (field[0] == field[4] && field[4] == symbol && field[8] != playersymbol)
    {
        field[8] = symbol;
    }
    else if (field[0] == field[8] && field[8] == symbol && field[4] != playersymbol)
    {
        field[4] = symbol;
    }
    else if (field[4] == field[8] && field[8] == symbol && field[0] != playersymbol)
    {
        field[0] = symbol;
    }

    else if (field[2] == field[4] && field[4] == symbol && field[6] != playersymbol)
    {
        field[6] = symbol;
    }
    else if (field[2] == field[6] && field[6] == symbol && field[4] != playersymbol)
    {
        field[4] = symbol;
    }
    else if (field[4] == field[6] && field[6] == symbol && field[2] != playersymbol)
    {
        field[2] = symbol;
    }
    else
    {
        while (checkcomp == false)
        {
            kletkacomp = rand() % 9;
            if (field[kletkacomp] == 'X' || field[kletkacomp] == 'O')
            {
                checkcomp = false;
            }
            else
            {
                field[kletkacomp] = symbol;
                checkcomp = true;
            }
        }
    }
    checkfield(symbol);
}
void gamevscomp()
{
    
    int variant = 0, i1 = 0, i2 = 0, i3 = 0;                                                        
    char imie1[25], imie2[25] = ") vs. computer(", end[13]="): winner - ";                 //dla history
    printf("Player name:\n");
    scanf("%s", &imie1);
    system("cls");


    printf("Who would you play for?\n1-crosses\n2-noughts\n\n");
    scanf("%d", &variant);
    if (variant == 1)
    {
        printf("\n\nYou are playing for crosses (Х)\n\n");
        //zapis v fail "imya(X) vs. computer(O) "bez perehoda na novuju stroku
        FILE *plik;
        
        int f = 0;
        char rez[60];
        while (imie1[i1] != '\0' && i1 < 25)
        {
            rez[f] = imie1[i1];
            f++;
            i1++;
        }
        rez[f] = '(';
        f++;
        rez[f] = 'X';
        f++;
        while (imie2[i2] != '\0' && i2 < 25)
        {
            rez[f] = imie2[i2];
            f++;
            i2++;
        }
        rez[f] = 'O';
        f++;
        while (i3 < 12)
        {
            rez[f] = end[i3];
            f++;
            i3++;
        }
        rez[f] = '\0';
            
        int i = 0;
        plik = fopen("history.txt", "a");

        while (rez[i] != '\0' && i < 60)
        {
            fwrite(&rez[i], sizeof(char), 1, plik);
            i++;
        }
        fclose(plik);
        system("cls");
        for (step; step < 9;step++)
        {

            fieldvivod();
            if (step % 2 == 0)
            {
                symbol = 'X';
                playermove();
            }
            else
            {
                symbol = 'O';
                computermove();
            }
        }
    }
    else if (variant == 2)
    {
        printf("\n\nYou are playing for noughts (O)\n\n");
        //zapis v fail "computer(X) vs. imya(O) "bez perehoda na novuju stroku
        
        FILE *plik;

        int f = 0;
        char rez[60];
        while (imie1[i1] != '\0' && i1 < 25)
        {
            rez[f] = imie1[i1];
            f++;
            i1++;
        }
        rez[f] = '(';
        f++;
        rez[f] = 'O';
        f++;
        while (imie2[i2] != '\0' && i2 < 25)
        {
            rez[f] = imie2[i2];
            f++;
            i2++;
        }
        rez[f] = 'X';
        f++;
        while (i3 < 12)
        {
            rez[f] = end[i3];
            f++;
            i3++;
        }
        rez[f] = '\0';

        int i = 0;
        plik = fopen("history.txt", "a");

        while (rez[i] != '\0' && i < 60)
        {
            fwrite(&rez[i], sizeof(char), 1, plik);
            i++;
        }

        fclose(plik);
        system("cls");
        for (step; step < 9;step++)
        {
            
            fieldvivod();
            if (step % 2 == 0)
            {
                symbol = 'X';
                computermove();
            }
            else
            {
                symbol = 'O';
                playermove();
            }
        }
    }
    else
        printf("There is no such choice!\n");
}
void gamevsplayer()
{
    int variant = 0, i1 = 0, i2 = 0, i3 = 0;
    char imie1[25], imie2[25], vs[9] = "(X) vs. ", end[14] = "O): winner - ";
    printf("First player (X) name:\n");
    scanf("%s", &imie1);
    printf("Second player (O) name:\n");
    //scanf
    scanf("%s", &imie2);
    //zapis v fail vida "perviy(X) vs. vtoroy(O) " bez perehoda na druguju stroku

    FILE* plik;

    int f = 0;
    int i = 0;
    char rez[60];
    while (imie1[i1] != '\0' && i1 < 25)
    {
        rez[f] = imie1[i1];
        f++;
        i1++;
    }
    while (i < 8)
    {
        rez[f] = vs[i];
        f++;
        i++;
    }
    while (imie2[i2] != '\0' && i2 < 25)
    {
        rez[f] = imie2[i2];
        f++;
        i2++;
    }
    rez[f] = '(';
    f++;
    while (i3 < 13)
    {
        rez[f] = end[i3];
        f++;
        i3++;
    }
    rez[f] = '\0';

    i = 0;
    plik = fopen("history.txt", "a");

    while (rez[i] != '\0' && i < 60)
    {
        fwrite(&rez[i], sizeof(char), 1, plik);
        i++;
    }
    fclose(plik);
    system("cls");
    for (step; step < 9; step++)
    {
        
        fieldvivod();
        if (step % 2 == 0)
        {
            symbol = 'X';
            playermove();
        }
        else
        {
            symbol = 'O';
            playermove();
        }
    }
}
void history()
{
    FILE* plik;
    char str[256];
    plik = fopen("history.txt", "rt");
    if (plik == NULL)
    {
        printf("ERROR: Impossible to open file\n");
    }
    else
    {
        while (fgets(str, 256, plik)!=NULL)
        {
            printf("%s", str);
        }
    }
    fclose(plik);
    printf("\n\n");
}
