#include "print_to_file.hpp"
namespace {
    time_t seconds_per_day = 86400;
    time_t seconds_per_hour = 3600;
    time_t seconds_per_minute = 60;
    time_t minute_per_hour = 60;
    double to_km_h = 3.6; //conversion factor from meters to kilometers per hour
}



void print_result(std::ostream &stream, GPS_track &track){
        std::map<const std::string, double> hist = track.speed_histogram();

        stream << "duration: " << int(track.duration() / seconds_per_day) << " days " << int(track.duration() / seconds_per_hour) << " hours "
               << int(track.duration() / seconds_per_minute) - (int(track.duration() / seconds_per_hour)) * minute_per_hour << " minutes "
               << track.duration() - seconds_per_minute * int(track.duration() / seconds_per_minute) << " seconds\n";

        stream << "all distance: " << track.all_distance() << " m\n";

        stream << "movement time: " << int(track.movement_time() / seconds_per_day) << " days " << int(track.movement_time() / seconds_per_hour) << " hours "
               << int(track.movement_time() / seconds_per_minute) - (int(track.movement_time() / seconds_per_hour)) * minute_per_hour << " minutes "
               << track.movement_time() - seconds_per_minute * int(track.movement_time() / seconds_per_minute) << " seconds\n";

        stream << "stops time: " << int(track.stops_time() / seconds_per_day) << " days " << int(track.stops_time() / seconds_per_hour) << " hours "
               << int(track.stops_time() / seconds_per_minute) - (int(track.stops_time() / seconds_per_hour)) * minute_per_hour << " minutes "
               << track.stops_time() - seconds_per_minute * int(track.stops_time() / seconds_per_minute) << " seconds\n";

        stream << "average speed: " << track.average_speed() * to_km_h << " km/h\n";
        stream << "max speed: " << track.max_speed() * to_km_h << " km/h\n";
        stream << "min height: " << track.min_height() << " m\n";
        stream << "max height: " << track.max_height() << " m\n";
        stream << "total_climb: " << track.total_climb() << " m\n";
        stream << "total_descent: " << track.total_descent() << " m\n";
        stream << "\nspeed histogram:\n";
        for (auto & element : hist) {
            std::string range = element.first;
            stream << range;
            stream << " m/s : " << int(element.second / seconds_per_minute) << " minutes "
                   << element.second - seconds_per_minute * (int) (element.second / seconds_per_minute) << " seconds\n";
        }
    }