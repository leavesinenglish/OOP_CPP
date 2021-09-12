#include "gps_track.hpp"
#include "histogram.hpp"

GPS_track::GPS_track(const char *filename) {
    clear();
    pugi::xml_document doc;
    if (!doc.load_file(filename)) return;
    init(doc);
}

GPS_track::GPS_track(std::istream &stream) {
    clear();
    pugi::xml_document doc;
    if (!doc.load(stream)) return;
    init(doc);
}

void GPS_track::init(pugi::xml_document &doc) {
    pugi::xml_node tools = doc.child("gpx").child("trk").child("trkseg");
    for (pugi::xml_node trkpt : tools.children("trkpt")) {
        auto lat = trkpt.attribute("lat").as_double();
        auto lon = trkpt.attribute("lon").as_double();
        std::string time = trkpt.child_value("time");
        auto ele = trkpt.child("ele").text().as_double();
        Time_geopoint tmp_point(lat, lon, ele, time.c_str());
        add_point(tmp_point);
    }
    if (!points.empty())
        _start_time = points[0].time();
}

GPS_track::GPS_track() {
    clear();
}

void GPS_track::clear() {
    _movement_time = 0;
    _stops_time = 0;
    _max_speed = 0;
    _max_height = 0;
    _min_height = 0;
    _total_climb = 0;
    _total_descent = 0;
    _all_distance = 0;
    points.clear();
}

void GPS_track::add_point(Time_geopoint &point) {
    if (points.size() == 1) {
        _min_height = points[0].elevation();
        _max_height = points[0].elevation();
        _start_time = points[0].time();
        _end_time = points[0].time();
    }
    if (point.time() > _end_time)
        _end_time = point.time();
    if (point.elevation() < _min_height)
        _min_height = point.elevation();
    if (point.elevation() > _max_height)
        _max_height = point.elevation();
    if (!points.empty()) {
        const Time_geopoint &last_point = points.back();
        if (last_point.elevation() > point.elevation())
            _total_descent += fabs(point.elevation() - last_point.elevation());
        else
            _total_climb += fabs(point.elevation() - last_point.elevation());
        double dist = point.distanceTo(last_point);
        _all_distance += fabs(dist);
        double dt = point.time() - last_point.time();
        double speed;
        if (dt > .1)
            speed = dist / dt;
        else
            speed = 0;
        if (speed > _max_speed)
            _max_speed = speed;
        if (dist > .1 && speed > .5)
            speed_by_time.emplace_back(dt, speed);
        if (speed < .5)
            _stops_time += dt;
        else
            _movement_time += dt;
    }
    points.push_back(point);
}

std::map<const std::string, double> GPS_track::speed_histogram() {
    Histogram speed_hist(speed_by_time);
    return Histogram::get_hist(speed_hist);
}