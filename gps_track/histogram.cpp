#include "histogram.hpp"
#include <iterator>

void Histogram::add_el(const std::pair< double, speed>& element){
    const std::string key = get_range(element.second);
    if (vocab.find(key) != vocab.end())
        vocab[key] += element.first;
    else
        vocab[key] = element.first;
}
Histogram::Histogram(std::vector<std::pair< double, speed>>& book) {
    for (auto & it : book) {
        add_el(it);
    }
}
std::map<const std::string, double> Histogram::get_hist(const Histogram& hist) {
    std::map<const std::string, double> result;
    std::copy(hist.vocab.begin(), hist.vocab.end(), std::inserter(result, result.end()));
    return result;
}

std::string Histogram::get_range(speed v) {
    int inf = int((int)v / 2)*2;
    int sup = inf + 2;
    std::string range;
    range.append(std::to_string(inf));
    range.push_back('-');
    range.append(std::to_string(sup));
    return range;
}