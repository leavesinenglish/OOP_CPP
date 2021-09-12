#include "time_geopoint.hpp"

namespace {
    const std::string time_format{"%Y-%m-%dT%H:%M:%SZ"};
}

Time_geopoint::Time_geopoint(double _lat, double _lng, double _elev, const char *_time) : Geopoint(_lat, _lng, _elev) {
    tm = parsing_str_to_time(_time);
}

std::string Time_geopoint::time_to_str() const {
    std::ostringstream ss{};
    std::tm dt{};
    localtime_s(&dt, &tm);
    ss << std::put_time(&dt, time_format.c_str());
    return ss.str();
}

time_t Time_geopoint::parsing_str_to_time(const char *time) {
    std::istringstream ss{time};
    std::tm dt{};
    ss >> std::get_time(&dt, time_format.c_str());
    return std::mktime(&dt);
}