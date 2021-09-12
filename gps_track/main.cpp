#include "gps_track.hpp"
#include <iostream>
#include "print_to_file.hpp"

int main() {
    GPS_track test("50467.gpx");
    std::ofstream result;
    result.open("RESULT.txt");
    print_result(result, test);
}
