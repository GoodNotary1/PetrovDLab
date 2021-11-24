#include <iostream>
#include <string>
#include <limits>


using namespace std;

int intCheck(int min = 0, int max = INT_MAX)
{
    while (1)
    {
        int num;
        cin >> num;
        if (cin.fail() or num < min or num > max or cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input" << endl << endl;
        }
        else
        {
            return num;
        }
    }
}

string stringCheck()
{
    while (1)
    {
        string str;
        cin >> ws;
        getline(cin, str);
        return str;
    }
}

float floatCheck(float min = 0, float max = FLT_MAX)
{
    while (1)
    {
        float num;
        cin >> num;
        if (cin.fail() or num < min or num > max or cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input. Plese input the number according to the format 'X.X'" << endl << endl;
        }
        else
        {
            return num;
        }
    }
}

bool booleanCheck()
{
    while (1)
    {
        bool boolean;
        cin >> boolean;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input." << endl << endl;
        }
        else
        {
            return boolean;
        }
    }
}