#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <vector>

using namespace std;

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

class date;

//=============================================================
// class Task
class Task
{
private:
    string title;
    string detail;
    string level;
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    bool Done;
    friend void addTask();
    friend void editTask(int);
    friend void printTask(int);
    friend void deleteTask(int);
    friend void done_undone(int);
    friend void showDateTask(int, int, int);
    friend bool isGreen(int, int, int);

public:
    Task();
};

Task::Task()
{
    Done = false;
    hour = -1;
}

//=============================================================
// in this function we are using the formula which gives us the number of the week day with givven day , month and year
int dayofweek(int d, int m, int y)
{
    int mon;
	if(m > 2)
		mon = m;
	else{
		mon = (12+m);
		y--;
	}
	int year = y % 100;
	int c = y / 100;
	int w = (d + floor((13*(mon+1))/5) + year + floor(year/4) + floor(c/4) + (5*c));
	w = w % 7;
	return w - 1;
}

//=============================================================
// in this function we are showing the tasks that we take on a current date
void showDateTask(int, int, int);

//=============================================================
// checking if there is a task for a givven date or not
bool isGreen(int, int, int);

//=============================================================
// class date
class date
{
private:
    int year, month, day, weekDay;
    string nameOfMonth;

public:
    date();
    void display();
    void SetNameToMonth();
    int MaxDayOfMonth();
    void n();
    void p();
    void s();
    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }
} today;

//=============================================================
date::date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // gregorian dates
    year = 1900 + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
    weekDay = dayofweek(day, month, year);
    
    // setting the name of the month
    SetNameToMonth();
}
//=============================================================
void date::display()
{
    int maxDays = MaxDayOfMonth();
    int startDay;

    startDay = dayofweek(1, month, year);
    weekDay = dayofweek(day, month, year);

    this->SetNameToMonth();
    int blue = 31;
    int lightBlue = 3;
    int white = 15;
    int green = 2;
    int yellow = 14;
    int red = 4;
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, lightBlue);
    cout << "--------------------------" << endl;
    cout << "      " << nameOfMonth << " , " << year << endl;
    cout << "--------------------------" << endl;
    cout << "S   M   T   W   T   F   S    " << endl;
    for (int i = 0; i < startDay; i++)
    {
        cout << "    ";
    }
    for (int i = 0; i < maxDays; i++)
    {
        if (startDay == 6)
        {
            if (i + 1 == this->day)
            {
                SetConsoleTextAttribute(hConsole, blue);
                cout << i + 1 << endl;
                startDay = 0;
                SetConsoleTextAttribute(hConsole, lightBlue);
            }
            else
            {
                if (isGreen(i + 1, this->month, this->year))
                {
                    SetConsoleTextAttribute(hConsole, green);
                    cout << i + 1 << endl;
                    startDay = 0;
                    SetConsoleTextAttribute(hConsole, lightBlue);
                }
                else
                {
                    cout << i + 1 << endl;
                    startDay = 0;
                }
            }
        }
        else
        {
            if (i + 1 < 10)
            {
                if (i + 1 == this->day)
                {
                    SetConsoleTextAttribute(hConsole, blue);
                    cout << i + 1;
                    startDay++;
                    SetConsoleTextAttribute(hConsole, lightBlue);
                    cout << "   ";
                }
                else
                {
                    if (isGreen(i + 1, this->month, this->year))
                    {

                        SetConsoleTextAttribute(hConsole, green);
                        cout << i + 1;
                        startDay++;
                        SetConsoleTextAttribute(hConsole, lightBlue);
                        cout << "   ";
                    }
                    else
                    {
                        cout << i + 1 << "   ";
                        startDay++;
                    }
                }
            }
            else
            {
                if (i + 1 == this->day)
                {
                    SetConsoleTextAttribute(hConsole, blue);
                    cout << i + 1;
                    SetConsoleTextAttribute(hConsole, lightBlue);
                    cout << "  ";
                    startDay++;
                }
                else
                {
                    if (isGreen(i + 1, this->month, this->year))
                    {

                        SetConsoleTextAttribute(hConsole, green);
                        cout << i + 1;
                        startDay++;
                        SetConsoleTextAttribute(hConsole, lightBlue);
                        cout << "  ";
                    }
                    else
                    {
                        cout << i + 1 << "  ";
                        startDay++;
                    }
                }
            }
        }
    }
    cout << endl
         << "--------------------------" << endl;
    SetConsoleTextAttribute(hConsole, white);
    cout << "n-Next\np-Previous\ns-Select\nq-Quit\n";
    cout << "Option= ";
    cout << endl;
    SetConsoleTextAttribute(hConsole, white);
}

//=============================================================
void date::SetNameToMonth()
{
    switch (this->month)
    {
    case 1:
        this->nameOfMonth = "January";
        break;
        ;
    case 2:
        this->nameOfMonth = "February";
        break;
    case 3:
        this->nameOfMonth = "March";
        break;
    case 4:
        this->nameOfMonth = "April";
        break;
    case 5:
        this->nameOfMonth = "May";
        break;
    case 6:
        this->nameOfMonth = "June";
        break;
    case 7:
        this->nameOfMonth = "July";
        break;
    case 8:
        this->nameOfMonth = "August";
        break;
    case 9:
        this->nameOfMonth = "September";
        break;
    case 10:
        this->nameOfMonth = "October";
        break;
    case 11:
        this->nameOfMonth = "November";
        break;
    case 12:
        this->nameOfMonth = "December";
        break;
    default:
        break;
    }
}

//=============================================================
int date::MaxDayOfMonth()
{
    switch (this->month)
    {
    case 1:
        return 31;
        break;
    case 2:
        return 28;
        break;
    case 3:
        return 31;
        break;
    case 4:
        return 30;
        break;
    case 5:
        return 31;
        break;
    case 6:
        return 30;
        break;
    case 7:
        return 31;
        break;
    case 8:
        return 31;
        break;
    case 9:
        return 30;
        break;
    case 10:
        return 31;
        break;
    case 11:
        return 30;
        break;
    case 12:
        return 31;
        break;
    default:
        break;
    }
}

//=============================================================
void date::n()
{
    if (this->MaxDayOfMonth() != this->day)
        this->day++;
    else
    {
        if (this->month != 12)
        {
            this->month++;
            this->day = 1;
        }
        else
        {
            this->year++;
            this->month = 1;
            this->day = 1;
        }
    }
}

//=============================================================
void date::p()
{

    if (this->day != 1)
        this->day--;
    else
    {
        if (this->month != 1)
        {
            this->month--;
            this->day = this->MaxDayOfMonth();
        }
        else
        {
            this->year--;
            this->month = 12;
            this->day = this->MaxDayOfMonth();
        }
    }
}

//=============================================================
void date::s()
{
    system("cls");
    char x;
    bool flag = false;
    while (!flag)
    {
        showDateTask(this->day, this->month, this->year);
        x = getche();
        switch (x)
        {
        case 'q':
        case 'Q':
            flag = true;
            break;
        default:
            system("cls");
            break;
        }
    }
}

//=============================================================
void CalendarMenu()
{
    date G;
    system("cls");
    G.display();
    char x;
    bool flag = true;
    while (flag)
    {
        x = getche();
        switch (x)
        {
        case 'n':
            G.n();
            break;
        case 'p':
            G.p();
            break;
        case 's':
            G.s();
            break;
        case 'q':
            flag = false;
            break;
        default:
            system("cls");
            G.display();
            break;
        }
    }
}

// global vector for storing tasks
vector<Task> TaskList;

void printTask(int index)
{
    int blue = 31;
    int lightBlue = 3;
    int white = 15;
    int green = 2;
    int yellow = 14;
    int red = 4;
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, white);
    int size = TaskList.size();
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
            cout << "--------------------\n";
        int dif = (TaskList[i].year * 365 + TaskList[i].month * 30 + TaskList[i].day) - (today.getYear() * 365 + today.getMonth() * 30 + today.getDay());
        
        if (dif < 0)
        {
            SetConsoleTextAttribute(hConsole, red);
        }
        else if (dif > 1)
        {
            SetConsoleTextAttribute(hConsole, green);
        }
        else
        {
            SetConsoleTextAttribute(hConsole, yellow);
        }
        if (i == index)
            SetConsoleTextAttribute(hConsole, blue);
        cout << "Task tile: " << TaskList[i].title << endl;
        cout << "Detail: " << TaskList[i].detail << endl;
        cout << "Date: " << TaskList[i].month << "/" << TaskList[i].day << "/" << TaskList[i].year << endl;
        if (TaskList[i].hour != -1)
        {
            cout << "Time: " << TaskList[i].hour << ":" << TaskList[i].min << ":" << TaskList[i].sec << endl;
        }
        cout << "Level: " << TaskList[i].level << endl;
        if (TaskList[i].Done)
        {
            cout << "Status: Done X";
        }
        else
        {
            cout << "Status: Undone";
        }
        SetConsoleTextAttribute(hConsole, white);
        cout << "\n--------------------\n";
    }
    if (size == 0)
        cout << "task list is empty.\n";
}

//=============================================================
bool isFormatValid(string str)
{
    if (str.length() == 8)
    {
        if (str[2] != ':' || str[5] != ':' || str[0] < 48 || str[0] > 57 || str[1] < 48 || str[1] > 57 || str[3] < 48 || str[3] > 57 || str[4] < 48 || str[4] > 57 || str[6] < 48 || str[6] > 57 || str[7] < 48 || str[7] > 57)
        {
            return false;
        }
        int hour, min, sec;
        hour = (((int)str[0] - 48) * 10) + (int)str[1] - 48;
        min = (((int)str[3] - 48) * 10) + (int)str[4] - 48;
        sec = (((int)str[6] - 48) * 10) + (int)str[7] - 48;
        if (hour >= 0 && hour <= 24 && min >= 0 && min < 60 && sec >= 0 && sec < 60)
        {
            return true;
        }
        else
            return false;
    }
    else
    {
        return false;
    }
}

//=============================================================
void addTask()
{
    system("cls");
    Task newTask;
    cin.ignore();
    cout << "Enter the title of task: ";
    getline(cin, newTask.title);
    cout << "Enter the detail of task: ";
    getline(cin, newTask.detail);
    cout << "enter the level of this task:\nh-high\nm-medium\nl-low\nenter your option:  ";
    char x;
    bool flag = true;
    while (flag)
    {
        x = getch();
        switch (x)
        {
        case 'h':
        case 'H':
            newTask.level = "high";
            flag = false;
            break;
        case 'm':
        case 'M':
            newTask.level = "medium";
            flag = false;
            break;
        case 'l':
        case 'L':
            newTask.level = "low";
            flag = false;
            break;
        default:
            cout << "wrong input\n";
            break;
        }
    }
    system("cls");
    date G;
    flag = true;
    cout << "choose a date on calendar:\n";
    G.display();
    while (flag)
    {
        x = getche();
        switch (x)
        {
        case 'n':
        case 'N':
            G.n();
            break;
        case 'p':
        case 'P':
            G.p();
            break;
        case 's':
        case 'S':
            flag = false;
            newTask.year = G.getYear();
            newTask.month = G.getMonth();
            newTask.day = G.getDay();
            system("cls");
            break;
        default:
            system("cls");
            G.display();
            break;
        }
    }
    cout << "Enter time in hh:mm:ss format: ";
    string hourformat;
    getline(cin, hourformat);
    if (isFormatValid(hourformat))
    {
        newTask.hour = (((int)hourformat[0] - 48) * 10) + (int)hourformat[1] - 48;
        newTask.min = (((int)hourformat[3] - 48) * 10) + (int)hourformat[4] - 48;
        newTask.sec = (((int)hourformat[6] - 48) * 10) + (int)hourformat[7] - 48;
    }
    flag = true;
    while (flag)
    {
        cout << "S-Save\nQ-Quit\n";
        x = getch();
        switch (x)
        {
        case 83:
        case 115:
            TaskList.push_back(newTask);
            flag = false;
            break;
        case 81:
        case 113:
            flag = false;
            break;
        default:
            cout << "wrong input\n";
            break;
        }
    }
}

//=============================================================
void deleteTask(int index)
{
    TaskList.erase(TaskList.begin() + index);
}

//=============================================================
void editTask(int index)
{
    system("cls");
    Task newTask;
    cin.ignore();
    cout << "old title: " << TaskList[index].title << endl;
    cout << "Enter your new title of task: ";
    getline(cin, newTask.title);
    cout << "old detail: " << TaskList[index].detail << endl;
    cout << "Enter your new detail of task: ";
    getline(cin, newTask.detail);
    cout << "old level: " << TaskList[index].level << endl;
    cout << "enter new level of this task:\nh-high\nm-medium\nl-low\nenter your option:  ";
    char x;
    bool flag = true;
    while (flag)
    {
        x = getch();
        switch (x)
        {
        case 'h':
        case 'H':
            newTask.level = "high";
            flag = false;
            break;
        case 'm':
        case 'M':
            newTask.level = "medium";
            flag = false;
            break;
        case 'l':
        case 'L':
            newTask.level = "low";
            flag = false;
            break;
        default:
            cout << "wrong input\n";
            break;
        }
    }
    system("cls");
    date G;
    flag = true;
    cout << "old date: " << TaskList[index].month << "/" << TaskList[index].day << "/" << TaskList[index].year << endl;
    cout << "choose a date on calendar:\n";
    G.display();
    while (flag)
    {
        x = getche();
        switch (x)
        {
        case 'n':
            G.n();
            break;
        case 'p':
            G.p();
            break;
        case 's':
            flag = false;
            newTask.year = G.getYear();
            newTask.month = G.getMonth();
            newTask.day = G.getDay();
            system("cls");
            break;
        default:
            system("cls");
            G.display();
            break;
        }
    }
    if (TaskList[index].hour != -1)
    {
        cout << "old time: " << TaskList[index].hour << ":" << TaskList[index].min << ":" << TaskList[index].sec << endl;
    }
    cout << "Enter time in hh:mm:ss format: ";
    string hourformat;
    getline(cin, hourformat);
    if (isFormatValid(hourformat))
    {
        newTask.hour = (((int)hourformat[0] - 48) * 10) + (int)hourformat[1] - 48;
        newTask.min = (((int)hourformat[3] - 48) * 10) + (int)hourformat[4] - 48;
        newTask.sec = (((int)hourformat[6] - 48) * 10) + (int)hourformat[7] - 48;
    }
    flag = true;
    while (flag)
    {
        cout << "S-Save\nQ-Quit\n";
        x = getch();
        switch (x)
        {
        case 83:
        case 115:
            TaskList[index] = newTask;
            flag = false;
            break;
        case 81:
        case 113:
            flag = false;
            break;
        default:
            cout << "wrong input\n";
            break;
        }
    }
}

//=============================================================
void done_undone(int index)
{
    TaskList[index].Done = !TaskList[index].Done;
}

//=============================================================
// function that handle the task option in the menu
void TaskMenu()
{
    system("cls");
    char x;
    bool flag = true;
    int index = -1;
    if (TaskList.size() > 0)
        index = 0;

    int choice;
    while (flag)
    {
        printTask(index);
        choice = getch();
        if (index < 0)
            index = 0;
        switch (choice)
        {
        case KEY_UP:
            index--;
            if (index < 0)
                index = 0;
            system("cls");
            break;
        case KEY_DOWN:
            index++;

            if (index > TaskList.size() - 1)
                index = TaskList.size() - 1;
            system("cls");
            break;
        case 65:
        case 97:
            addTask();
            system("cls");
            break;
        case 68:
        case 100:
            deleteTask(index);
            index--;
            system("cls");
            break;
        case 69:
        case 101:
            editTask(index);
            system("cls");
            break;
        case 70:
        case 102:
            done_undone(index);
            system("cls");
            break;
        case 81:
        case 113:
            flag = false;
            break;
        default:
            system("cls");
            break;
        }
    }
}

//=============================================================
void showDateTask(int day, int month, int year)
{
    for (int i = 0; i < TaskList.size(); i++)
    {
        if (TaskList[i].year == year && TaskList[i].month == month && TaskList[i].day == day)
        {
            if (i == 0)
                cout << "--------------------\n";
            cout << "Task tile: " << TaskList[i].title << endl;
            cout << "Detail: " << TaskList[i].detail << endl;
            cout << "Date: " << TaskList[i].month << "/" << TaskList[i].day << "/" << TaskList[i].year << endl;
            if (TaskList[i].hour != -1)
            {
                cout << "Time: " << TaskList[i].hour << ":" << TaskList[i].min << ":" << TaskList[i].sec << endl;
            }
            if (TaskList[i].Done)
            {
                cout << "Status: Done X";
            }
            else
            {
                cout << "Status: Undone";
            }
            cout << "\n--------------------\n";
        }
    }
    if (TaskList.size() == 0)
        cout << "task listt is empty.\n";
}

//=============================================================
bool isGreen(int day, int month, int year)
{
    bool flag = false;
    for (int i = 0; i < TaskList.size(); i++)
    {
        if (TaskList[i].year == year && TaskList[i].month == month && TaskList[i].day == day)
        {
            flag = true;
        }
    }

    return flag;
}

//=============================================================
int main()
{

    int x;
    bool flag = true;
    while (flag)
    {
        cout << "1-Task" << endl
             << "2-Calendar" << endl
             << "3-Quit" << endl;
        cout << "Choose your option: ";
        cin >> x;
        switch (x)
        {
        case 1:
            TaskMenu();
            system("cls");
            break;
        case 2:
            CalendarMenu();
            system("cls");
            break;
        case 3:
            flag = false;
            break;
        default:
            system("cls");
            break;
        }
    }
    cin.get();
    return 0;
}