#pragma once

class Geopoint {
public:
    [[maybe_unused]] Geopoint(double _lat, double _lng, double _elev = 0)
            : lat(_lat), lng(_lng), elev(_elev) {}

    // Широта
    [[nodiscard]] double latitude() const { return lat; }

    // Долгота
    [[nodiscard]] double longitude() const { return lng; }

    // Высота над уровнем моря
    [[nodiscard]] double elevation() const { return elev; }

    // Расстояние до другой точки
    [[maybe_unused]] [[nodiscard]] double distanceTo(const Geopoint &other) const;

private:
    double lat, lng, elev;
};