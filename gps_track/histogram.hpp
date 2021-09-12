#pragma once
#include "gps_track.hpp"
class Histogram {
public:
    Histogram() = default;;
    explicit Histogram(std::vector<std::pair< double, speed>>& book);
    ~Histogram()=default;

    static std::map<const std::string, double> get_hist(const Histogram& hist);
    static std::string get_range(speed v);
    void add_el(const std::pair< double, speed>& element);
private:
    std::map<const std::string, double> vocab;
};
