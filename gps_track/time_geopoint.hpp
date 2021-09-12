#pragma once
#include "geopoint.hpp"
#include <sstream>
#include <locale>
#include <iomanip>

class Time_geopoint: public Geopoint
{
public:
    Time_geopoint(double _lat, double _lng, double _elev, const char* _time);
    [[nodiscard]] time_t time() const { return tm; }
    [[nodiscard]] std::string time_to_str() const;
private:
    time_t tm{};
    static time_t parsing_str_to_time(const char* time);
};


