
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "PetrovDLab.h"
#include <limits>
#include <unordered_map>
#include <vector>

using namespace std;

int pipe_total = 0;
int station_total = 0;

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
        cin >> ws;
        getline(cin, str);
            return str;
    }
}

int intCheck(int min=0, int max=INT_MAX)
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

float floatCheck(float min=0, float max=FLT_MAX)
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

Pipe Create_pipe()
{
    Pipe p = {};
    p.id = pipe_total;
    p.Repair = false;
    cout << "Input pipe diameter: ";
    p.d = intCheck();
    cout << "Input pipe length: ";
    p.l = floatCheck(0);
    return p;
}

Station Create_station()
{
    Station s = {};
    s.id = station_total;
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
    s.efficiency = intCheck(0, 100);
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
                file << "pipeline_data" << endl << p.id << endl << p.l << endl << p.d << endl << p.Repair << endl;
            }
            else
            {
                cout << "No pipelines created" << endl;
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

void EditStation(int station_total, int& a, Station& s, int& retflag)
{
    retflag = 1;
    {
            cout << "Choose option:" << endl << endl << "0. Back" << endl << "1. Change name" << endl << "2. Change efficiency" << endl << "3. Change stations" << endl;
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
                s.efficiency = intCheck(0, 100);
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
}

void EditPipe(int pipe_total, int& a, Pipe& p, int& retflag)
{
    retflag = 1;
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
}

int main()
{
    unordered_map <int, Pipe> pipes = {};
    unordered_map <int, Station> stations = {};
    while (1)
    {
        int a = 0;
        cout << "Choose option:" << endl << endl << "1. Add pipe" << endl << "2. Add station" << endl << "3. List objects" << endl << "4. Edit pipe" << endl << "5. Edit station" << endl << "6. Save" << endl << "7. Load" << endl << "0. Exit"<<endl;
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
            pipes.insert({pipe_total , Create_pipe() });
            cout << "Pipe created" << endl;
            ++pipe_total;
            break;
        }
        case 2:
        {
            stations.insert({station_total , Create_station() });
            cout << "Station created" << endl;
            ++station_total;
            break;
        }
        case 3:
        {
            cout << "Total pipes: " << pipe_total << endl << endl;
            if (pipe_total > 0)
            {
                for (auto kv : pipes)
                {
                    cout << kv.first << endl;
                    PipeOutput(pipes[kv.first]);
                    cout << endl;
                }
            }
            cout << "Total stations: " << station_total << endl << endl;
            if (station_total > 0)
            {
                for (auto kv : stations)
                {
                    cout << kv.first << endl;
                    StationOutput(stations[kv.first]);
                    cout << endl;
                }
            }
            break;
        }
        case 4:
        {
            if (pipe_total != 0)
            {
                cout << "Input pipe ID to edit: " << endl;
                int input_id = intCheck();
                if (pipes.find(input_id) != pipes.end())
                {
                    int retflag;
                    EditPipe(pipe_total, a, pipes[input_id], retflag);
                    if (retflag == 2) break;
                    break;
                }
                else break;
            }
            else cout << "No pipes to edit" << endl;
        }
        case 5:
        {
            if (station_total != 0)
            {
                cout << "Input station ID to edit: " << endl;
                int input_id = intCheck();
                if (stations.find(input_id) != stations.end())
                {
                    int retflag;
                    EditStation(station_total, a, stations[input_id], retflag);
                    if (retflag == 2) break;
                    break;
                }
                else break;
            }
            else cout << "No stations to edit" << endl;
        }
        /*
                case 6:
            SaveFile(pipe_total, p, station_total, s);
        break;
        case 7:
            int retflag;
            LoadFile(p, s, retflag);
            if (retflag == 2) break;
        */
        }
    }
}





