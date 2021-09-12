#pragma once

#include "geopoint.hpp"
#include "time_geopoint.hpp"
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <istream>
#include <fstream>

typedef double speed;

class GPS_track {
private:
    std::vector<Time_geopoint> points;
    time_t _start_time{}, _end_time{}, _movement_time{}, _stops_time{};
    double _max_speed{};
    double _min_height{}, _max_height{};
    double _total_climb{}, _total_descent{};
    double _all_distance{};
    std::vector<std::pair<double, speed>> speed_by_time;
public:
    explicit GPS_track(const char *filename);
    explicit GPS_track(std::istream &stream);
    GPS_track();
    ~GPS_track() = default;
    void add_point(Time_geopoint &point);
    [[nodiscard]] double all_distance() const { return _all_distance; }
    [[nodiscard]] double total_climb() const { return _total_climb; }
    [[nodiscard]] double total_descent() const { return _total_descent; }
    [[nodiscard]] double max_height() const { return _max_height; }
    [[nodiscard]] double min_height() const { return _min_height; }
    [[nodiscard]] double max_speed() const { return _max_speed; }
    [[nodiscard]] time_t duration() const { return (_end_time - _start_time); }
    [[nodiscard]] time_t movement_time() const { return _movement_time; }
    [[nodiscard]] time_t stops_time() const { return _stops_time; }
    [[nodiscard]] double average_speed() const {return (_all_distance / (_movement_time - _stops_time));};
    void clear();
    std::map<const std::string, double> speed_histogram();
    void init(pugi::xml_document &doc);
};