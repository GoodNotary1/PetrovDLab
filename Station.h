#pragma once

#include <iostream>
#include <string>

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
    int connectnum;

    void StationOutput();

    void EditStation(std::string& name);

    void EditStation(int& eff);

    void EditStation(bool& flag);

    int give_id();

    int give_td();

    friend std::istream& operator >> (std::istream& in, Station& Station);

    friend std::ostream& operator << (std::ostream& out, const Station& station);

    Station();
};