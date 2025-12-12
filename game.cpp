#include <iostream>
#include <windows.h>
#include <conio.h>
#include <limits>
#include <climits>
using namespace std;

void saveTemp(int temp, bool player1);
string savingPermanent(string temp, int width, int height, bool player1);
void printPlayerInput(int width, int height, bool player1);
int PlayerWin();
bool isArrayFull();

void header();
int takingIntegerInput(int min, int max);
int integerVerification(string input);
string emptyverification(int w, int h);
bool checkPipe(const string &input);
string trimSpaces(string str);
void addAccountInformation(string temp, string filename);
void setColor(string hexcolor);
void gotoxy(int x, int y);
void getconsolemeasures(int &width, int &height);
void getCursorPosition();
void clear_cin();
void hideCursor();
void showCursor();
void setCursorSize(int size);

// =============================== global variables ===============================================================
// --- default ---
int width, height, currentWidth, currentHeight;
string optioncolor = "4", headingcolor = "3", headingBarColor = "B5";
string gameRecords[3][3] = {""};
bool player1 = true;
int main()
{
    int temp, x;
    getconsolemeasures(width, height);
    hideCursor();
    while (true)
    {
        header();
        setColor(optioncolor);
        gotoxy(width - 12, 2);
        cout << "1 | 2 | 3";
        for (int i = 0; i < 3; i++)
        {
            gameRecords[i][0] = gameRecords[i][1] = gameRecords[i][2] = "";
        }
        gotoxy(width - 12, 3);
        cout << "---------";
        gotoxy(width - 12, 4);
        cout << "4 | 5 | 6";
        gotoxy(width - 12, 5);
        cout << "---------";
        gotoxy(width - 12, 6);
        cout << "7 | 8 | 9";
        setColor("02");
        gotoxy(width / 2 - 12, height / 2 - 5);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2 - 4);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2 - 3);
        cout << "     |      |     ";
        gotoxy(width / 2 - 15, height / 2 - 2);
        cout << "------------------------";
        gotoxy(width / 2 - 12, height / 2 - 1);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2 + 1);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2 + 2);
        cout << "     |      |     ";
        gotoxy(width / 2 - 15, height / 2 + 3);
        cout << "------------------------";
        gotoxy(width / 2 - 12, height / 2 + 4);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2 + 5);
        cout << "     |      |     ";
        gotoxy(width / 2 - 12, height / 2 + 6);
        cout << "     |      |     ";
        for (int i = 0; true; i++)
        {
            setColor("05");
            gotoxy(2, height / 2 + 10);
            if (player1)
                cout << "Player 1st turn: ";
            else
                cout << "Player 2nd turn: ";
            getCursorPosition();
            temp = takingIntegerInput(1, 9);
            gotoxy(currentWidth, currentHeight);
            cout << "  ";
            setColor("08");
            if (player1)
                saveTemp(temp, player1);
            else
                saveTemp(temp, player1);
            x = PlayerWin();
            if (x == 1 || x == 2)
            {
                header();
                gotoxy(width / 2 - 10, height / 2 - 3);
                cout << "Player " << x << " is the winner.";
                gotoxy(width / 2 - 10, height - 2);
                cout << "Press any key to continue...";
                _getch();
                break;
            }
            else if (isArrayFull())
            {
                header();
                gotoxy(width / 2 - 6, height / 2 - 3);
                cout << "Match draw.";
                gotoxy(width / 2 - 10, height - 2);
                cout << "Press any key to continue...";
                _getch();
                break;
            }
        }
    }
    return 0;
}
// ------------- checking player win --------------------
int PlayerWin()
{
    int counthorizontal1 = 0, countvertical1 = 0, counthorizontal2 = 0, countvertical2 = 0, countdiagonal1 = 0, countdiagonal2 = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameRecords[i][j] == "x")
                counthorizontal1++;

            if (gameRecords[j][i] == "x")
                countvertical1++;

            if (gameRecords[i][j] == "o")
                counthorizontal2++;

            if (gameRecords[j][i] == "o")
                countvertical2++;

            if (i == j)
            {
                if (gameRecords[i][j] == "x")
                    countdiagonal1++;
                if (gameRecords[i][j] == "o")
                    countdiagonal2++;
            }
        }
        if (counthorizontal1 == 3 || countvertical1 == 3 || countdiagonal1 == 3)
            return 1;
        else if (counthorizontal2 == 3 || countvertical2 == 3 || countdiagonal2 == 3)
            return 2;
        else
            counthorizontal1 = countvertical1 = counthorizontal2 = countvertical2 = 0;
    }
    if (gameRecords[0][2] == gameRecords[1][1] && gameRecords[1][1] == gameRecords[2][0])
    {
        if (gameRecords[0][2] == "x")
            return 1;
        else if (gameRecords[0][2] == "o")
            return 2;
    }
    return 0;
}

// ----------------- Header -----------------------------
void header()
{
    system("cls");
    setColor(headingcolor);
    for (int i = 0; i < width; i++)
    {
        cout << "/";
    }
    gotoxy(width / 2 - 23, 0);
    cout << "(~~~~~~~~~~~~~~  Tic Tac Toe ~~~~~~~~~~~~~~~)" << endl;
    for (int i = 0; i < width - 1; i++)
    {
        gotoxy(i, height - 1);
        cout << "_";
    }
    for (int i = 0; i < height; i++)
    {
        gotoxy(0, i);
        cout << "|";
        gotoxy(width - 1, i);
        cout << "|";
    }
}
// ----------------- saving input in array --------------
string savingPermanent(string temp, int width, int height, bool player1)
{
    if (temp.empty())
    {
        printPlayerInput(width, height, player1);
        if (player1)
        {
            ::player1 = false;
            return "x";
        }
        else
        {
            ::player1 = true;
            return "o";
        }
    }
    else
    {
        gotoxy(currentWidth, currentHeight);
        cout << "invalid input";
        Sleep(1000);
        gotoxy(currentWidth, currentHeight);
        cout << "             ";
        return temp;
    }
}
void saveTemp(int temp, bool player1)
{
    if (temp == 1)
    {
        gameRecords[0][0] = savingPermanent(gameRecords[0][0], width / 2 - 12, height / 2 - 5, player1);
    }
    else if (temp == 2)
    {
        gameRecords[0][1] = savingPermanent(gameRecords[0][1], width / 2 - 4, height / 2 - 5, player1);
    }
    else if (temp == 3)
    {
        gameRecords[0][2] = savingPermanent(gameRecords[0][2], width / 2 + 4, height / 2 - 5, player1);
    }
    else if (temp == 4)
    {
        gameRecords[1][0] = savingPermanent(gameRecords[1][0], width / 2 - 12, height / 2, player1);
    }
    else if (temp == 5)
    {
        gameRecords[1][1] = savingPermanent(gameRecords[1][1], width / 2 - 4, height / 2, player1);
    }
    else if (temp == 6)
    {
        gameRecords[1][2] = savingPermanent(gameRecords[1][2], width / 2 + 4, height / 2, player1);
    }
    else if (temp == 7)
    {
        gameRecords[2][0] = savingPermanent(gameRecords[2][0], width / 2 - 12, height / 2 + 4, player1);
    }
    else if (temp == 8)
    {
        gameRecords[2][1] = savingPermanent(gameRecords[2][1], width / 2 - 4, height / 2 + 4, player1);
    }
    else if (temp == 9)
    {
        gameRecords[2][2] = savingPermanent(gameRecords[2][2], width / 2 + 4, height / 2 + 4, player1);
    }
}
// --------------------------- printing player input ---------------------
void printPlayerInput(int width, int height, bool player1)
{
    if (player1)
    {
        gotoxy(width, height);
        cout << "\\/";
        gotoxy(width, height + 1);
        cout << "/\\";
    }
    else
    {
        gotoxy(width, height);
        cout << "/\\";
        gotoxy(width, height + 1);
        cout << "\\/";
    }
}
// ================================================= Default functions =========================================================================
// -------------------- integer input verification ----------------------
int takingIntegerInput(int min, int max)
{
    string a;
    int action;
    getCursorPosition();
    while (true)
    {
        a = emptyverification(currentWidth, currentHeight);
        action = integerVerification(a);
        if (action >= min && action <= max)
            break;
        else
        {
            gotoxy(currentWidth, currentHeight);
            for (int i = 0; i < a.length(); i++)
            {
                cout << " ";
            }
            gotoxy(currentWidth, currentHeight);
            cout << "invalid input";
            Sleep(1000);
            gotoxy(currentWidth, currentHeight);
            cout << "             ";
        }
    }
    return action;
}

int integerVerification(string input)
{
    for (char c : input)
    {
        if (!isdigit(c))
            return INT_MIN;
    }
    try
    {
        int value = stoi(input);
        return value;
    }
    catch (const std::exception &e)
    {
        return INT_MIN;
    }
}

// ---------------- Empty verification ---------------------
string emptyverification(int w, int h)
{
    string temp;
    while (true)
    {
        gotoxy(w, h);
        getline(cin, temp);
        if (!temp.empty())
        {
            temp = trimSpaces(temp);
            break;
        }
        else
        {
            gotoxy(w, h);
            cout << "This credential cannot be empty.";
            Sleep(1000);
            gotoxy(w, h);
            cout << "                                ";
        }
    }
    return temp;
}
// ----------------- trim spaces ------------------------------
string trimSpaces(string str)
{
    string result = "";
    bool lastWasSpace = false;

    for (char c : str)
    {
        if (isspace(c))
        {
            if (!lastWasSpace)
            {
                result += ' ';
                lastWasSpace = true;
            }
        }
        else
        {
            result += c;
            lastWasSpace = false;
        }
    }
    return result;
}
// ----------------- set color function --------------------------
void setColor(string hexcolor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = stoi(hexcolor, nullptr, 16);
    SetConsoleTextAttribute(hConsole, color);
}
// ----------------- gotoxy fuction --------------------------
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// ------------- console measures -------------------------
void getconsolemeasures(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
// -------------------- get cursor current position -------------------
void getCursorPosition()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        currentWidth = csbi.dwCursorPosition.X;
        currentHeight = csbi.dwCursorPosition.Y;
    }
}
// ------------------------------- cursor handling -------------------------------------------
void hideCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);

    cursorInfo.bVisible = FALSE; // hide cursor
    SetConsoleCursorInfo(out, &cursorInfo);
}
void showCursor()
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);

    cursorInfo.bVisible = TRUE; // show cursor
    SetConsoleCursorInfo(out, &cursorInfo);
}
void setCursorSize(int size)
{
    if (size < 1)
        size = 1;
    if (size > 100)
        size = 100;

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);

    cursorInfo.dwSize = size;
    SetConsoleCursorInfo(out, &cursorInfo);
}
// ----------- checking that all array elements are used up --------------------
bool isArrayFull()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameRecords[i][j].empty())
                return false;
        }
    }
    return true;
}
