#pragma once

#include <iostream>

class Station
{
private:
    int id;
public:
    static int NextID;
    std::string station_name;
    int total_divisions;
    int working_divisions;
    int efficiency;

    void StationOutput();

    void EditStation(int& a);

    int give_id();

    friend std::istream& operator >> (std::istream& in, Station& Station);

    Station();

    Station& Create_station(Station& s);
};