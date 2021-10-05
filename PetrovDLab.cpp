
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "PetrovDLab.h"

using namespace std;
struct Pipe
{
    int id;
    int d;
    float l;
    bool Repair;
};

struct Station
{
    int id;
    string station_name;
    int total_divisions;
    int working_divisions;
    int efficiency;
};

void PipeOutput(Pipe& p)
{
    cout << "Pipe ID:" << p.id << endl;
    cout << "Pipe diameter:" << p.d << endl;
    cout << "Pipe length:" << p.l << endl;
    cout << "Pipe repair status:" << p.Repair << endl;
}

void StationOutput(Station& s)
{
    cout << "Station ID:" << s.id << endl;
    cout << "Station name:" << s.station_name << endl;
    cout << "Total divisions:" << s.total_divisions << endl;
    cout << "Working divisions:" << s.working_divisions << endl;
    cout << "Efficiency:" << s.efficiency << endl;
}

string stringCheck()
{
    while (1)
    {
        string str;
        cin >> str;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Invalid input. Enter a string" << endl;
        }
        else
        {
            return str;
        }
    }
}

int intCheck()
{
    while (1)
    {
        int num;
        cin >> num;
        if (cin.fail() or num < 0)
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

float floatCheck()
{
    while (1)
    {
        float num;
        cin >> num;
        if (cin.fail() or num < 0)
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

int percentCheck()
{
    while (1)
    {
        int num;
        cin >> num;
        if (cin.fail() or num < 0 or num > 100)
        {
            cin.clear();
            cin.ignore(100000000, '\n');
            cout << "Invalid input. Please input percent from 0 to 100" << endl << endl;
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

Pipe Create_pipe()
{
    Pipe p = {};
    p.id = 0;
    p.Repair = false;
    cout << "Input pipe diameter: ";
    p.d = intCheck();
    cout << "Input pipe length: ";
    p.l = floatCheck();
    return p;
}

Station Create_station()
{
    Station s = {};
    s.id = 0;
    cout << "Input name: ";
    s.station_name = stringCheck();
    while (1)
    {
        cout << "Input total station divisions: ";
        s.total_divisions = intCheck();
        cout << "Input working divisions: ";
        s.working_divisions = intCheck();
        if (s.working_divisions <= s.total_divisions)
            break;
        else
            cout << "Input error. Can't be more working divisions than total divisions" << endl;
    }
    cout << "Input station efficiency: ";
    s.efficiency = percentCheck();
    return s;
}

void LoadFile(Pipe& p, Station& s, int& retflag)
{
    retflag = 1;
    {
        ifstream file;
        file.open("data.txt", ios::in);
        if (file.good())
        {
            while (!file.eof())
            {
                string str;
                getline(file, str);
                if (str == "pipeline_data")
                {
                    string value;
                    getline(file, value);
                    p.id = stoi(value);
                    getline(file, value);
                    p.l = stof(value);
                    getline(file, value);
                    p.d = stoi(value);
                    getline(file, value);
                    p.Repair = value == "1";
                }
                if (str == "station_data")
                {
                    string value;
                    getline(file, value);
                    s.id = stoi(value);
                    getline(file, value);
                    s.station_name = value;
                    getline(file, value);
                    s.total_divisions = stoi(value);
                    getline(file, value);
                    s.working_divisions = stoi(value);
                    getline(file, value);
                    s.efficiency = stoi(value);
                }
            }
            cout << "Loading complete" << endl;
            { retflag = 2; return; };
        }
    }
}

void SaveFile(int pipe_total, Pipe& p, int station_total, Station& s)
{
    {
        ofstream file;
        file.open("data.txt", ios_base::out);
        if (file.good())
        {
            if (pipe_total > 0)
            {
                file << "pipeline_data" << endl << p.id << endl << p.l << endl << p.d << p.Repair << endl;
            }
            else
            {
                cout << "No pipelines created";
            }
            if (station_total > 0)
            {
                file << "station_data" << endl << s.id << endl << s.station_name << endl << s.total_divisions << endl << s.working_divisions << endl << s.efficiency << endl;
            }
            else
            {
                cout << "No stations created" << endl;
            }
        }
        file.close();
        cout << "Save successful" << endl;
    }
}



int main()
{
    Pipe p = {};
    Station s = {};
    int pipe_total = 0;
    int station_total = 0;
    while (1)
    {
        int a = 0;
        cout << "Choose option:" << endl << endl << "1. Add pipe" << endl << "2. Add station" << endl << "3. List info on all objects" << endl << "4. Edit pipe" << endl << "5. Edit station" << endl << "6. Save" << endl << "7. Load" << endl << "0. Exit"<<endl;
        a = intCheck();
        switch (a)
        {
        case 0:
        {
            return 0;
            break;
        }
        case 1:
        {
            p = Create_pipe();
            cout << "Pipe created" << endl;
            pipe_total=1;
            break;
        }
        case 2:
        {
            s = Create_station();
            cout << "Station created" << endl;
            if (station_total == 0)
            {
                ++station_total;
            }
            break;
        }
        case 3:
        {
            cout << "Total pipes: " << pipe_total << endl << "Total stations: " << station_total << endl << endl;
            if (pipe_total > 0)
            {
                PipeOutput(p);
            }
            if (station_total > 0)
            {
                StationOutput(s);
            }
            break;
        }
        case 4:
        {
            if (pipe_total > 0)
            {
                cout << "Choose option:" << endl << endl << "1. Change diameter" << endl << "2. Change length" << endl << "3. Change repair status" << endl << "0. Back" << endl;
                a = intCheck();
                switch (a)
                {
                case 1:
                    cout << "Input diameter:" << endl;
                    p.d = intCheck();
                    break;
                case 2:
                    cout << "Input length:" << endl;
                    p.l = floatCheck();
                    break;
                case 3:
                    cout << "Input repair status (1 - curently repairing; 0 - not repairing):" << endl;
                    p.Repair = booleanCheck();
                    break;
                case 0:
                    break;
                }
            }
            else
            {
                cout << "No pipe to edit" << endl << endl;
                break;
            }
        }
        case 5:
        {
            if (station_total > 0)
            {
                cout << "Choose option:" << endl << endl << "0. Back" << endl << "2. Change efficiency" << endl << "3. Change stations" << endl;
                a = intCheck();
                switch (a)
                {
                case 0:
                    break;
                case 1:
                    cout << "Input name:" << endl;
                    s.station_name = stringCheck();
                    break;
                case 2:
                    cout << "Input efficiency:" << endl;
                    s.efficiency = percentCheck();
                    break;
                case 3:
                    while (1)
                    {
                        cout << "Input total station divisions: ";
                        s.total_divisions = intCheck();
                        cout << "Input working divisions: ";
                        s.working_divisions = intCheck();
                        if (s.working_divisions > s.total_divisions)
                            cout << "Input error. Can't be more working divisions than total divisions" << endl;
                        else break;
                    }
                }
            }
            else
            {
                cout << "No station to edit" << endl << endl;
                break;
            }
        }
        case 6:
            SaveFile(pipe_total, p, station_total, s);
        break;
        case 7:
            int retflag;
            LoadFile(p, s, retflag);
            if (retflag == 2) break;
        }
    }
}


