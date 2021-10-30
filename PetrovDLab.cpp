
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
unordered_map <int, Pipe> pipes = {};
unordered_map <int, Station> stations = {};

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

void LoadFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations, int& retflag)
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
                    int pipe_keys = stoi(value);
                    getline(file, value);
                    pipe_total = stoi(value);
                    for (int i = 1; i <= pipe_keys; i++)
                    {
                        getline(file, value);
                        int dynam_key = stoi(value);
                        pipes.insert({ dynam_key, {} });
                        getline(file, value);
                        pipes[dynam_key].id = stoi(value);
                        getline(file, value);
                        pipes[dynam_key].d = stoi(value);
                        getline(file, value);
                        pipes[dynam_key].l = stof(value);
                        getline(file, value);
                        pipes[dynam_key].Repair = value == "1";
                    }
                }
                if (str == "station_data")
                {
                    string value;
                    getline(file, value);
                    int station_keys = stoi(value);
                    getline(file, value);
                    station_total = stoi(value);
                    for (int i = 1; i <= station_keys; i++)
                    {
                        getline(file, value);
                        int dynam_key = stoi(value);
                        stations.insert({ dynam_key,{} });
                        getline(file, value);
                        stations[dynam_key].id = stoi(value);
                        getline(file, value);
                        stations[dynam_key].station_name = value;
                        getline(file, value);
                        stations[dynam_key].total_divisions = stoi(value);
                        getline(file, value);
                        stations[dynam_key].working_divisions = stoi(value);
                        getline(file, value);
                        stations[dynam_key].efficiency = stoi(value);
                    }
                }
            }
            cout << "Loading complete" << endl;
            { retflag = 2; return; };
        }
    }
}

void SaveFile(int pipe_total, unordered_map<int, Pipe>& pipes, int station_total, unordered_map<int, Station>& stations)
{
    {
        ofstream file;
        file.open("data.txt", ios_base::out);
        if (file.good())
        {
            if (pipes.empty() == false)
            {
                file << "pipeline_data" << endl << pipes.size()<< endl << pipe_total << endl;
                for (auto kv : pipes)
                {
                    file << kv.first << endl << pipes[kv.first].id << endl << pipes[kv.first].d << endl << pipes[kv.first].l << endl << pipes[kv.first].Repair << endl;
                }
            }
            else
            {
                cout << "No pipelines created" << endl;
            }
            if (stations.empty() == false)
            {
                file << "station_data" << endl << stations.size() << endl << station_total << endl;
                for (auto kv : stations)
                {
                    file << kv.first << endl << stations[kv.first].id << endl << stations[kv.first].station_name << endl << stations[kv.first].total_divisions << endl << stations[kv.first].working_divisions << endl << stations[kv.first].efficiency << endl;
                }
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
    while (1)
    {
        int a = 0;
        cout << "Choose option:" << endl << endl << "1. Add pipe" << endl << "2. Add station" << endl << "3. List objects" << endl << "4. Edit pipe" << endl << "5. Edit station" << endl << "6. Delete pipe" << endl << "7. Delete station" << endl << "8. Save" << endl << "9. Load" << endl << "0. Exit" << endl;
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
            cout << "Total pipes created: " << pipe_total << endl << endl;
            if (pipes.empty() == false)
            {
                for (auto kv : pipes)
                {
                    cout << kv.first << endl;
                    PipeOutput(pipes[kv.first]);
                    cout << endl;
                }
            }
            cout << "Total stations created: " << station_total << endl << endl;
            if (stations.empty() == false)
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
            if (pipes.empty() == false)
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
                else
                {
                    cout << "No matching ID found" << endl;
                    break;
                }
            }
            else
            {
                cout << "No pipes to edit" << endl;
                break;
            }
        }
        case 5:
        {
            if (stations.empty() == false)
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
                else
                {
                    cout << "No matching ID found" << endl;
                    break;
                }
            }
            else
            {
                cout << "No stations to edit" << endl;
                break;
            }
        }
        case 6:
        {
            if (pipes.empty() == false)
            {
                cout << "Input pipe ID:" << endl;
                int input_id = intCheck();
                if (pipes.find(input_id) != pipes.end())
                {
                    pipes.erase(input_id);
                    break;
                }
                else
                {
                    cout << "No matching ID found";
                    break;
                }
            }
            else
            {
                cout << "No pipes to delete" << endl;
                break;
            }
        }
        case 7:
        {
            if  (stations.empty() == false)
            {
                cout << "Input station ID:" << endl;
                int input_id = intCheck();
                if (stations.find(input_id) != stations.end())
                {
                    stations.erase(input_id);
                    break;
                }
                else
                {
                    cout << "No matching ID found";
                    break;
                }
            }
            else
            {
                cout << "No stations to delete" << endl;
                break;
            }
        }

        case 8:
            SaveFile(pipe_total, pipes, station_total, stations);
            break;
        case 9:
            int retflag;
            LoadFile(pipes, stations, retflag);
            if (retflag == 2) break;
        }
    }
}





