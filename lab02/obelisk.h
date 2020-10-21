#ifndef OBELISK_H
#define OBELISK_H

#include "polygon.h"

class Obelisk
{
private:
    std::vector<Polygon> polygons;
    bool displayHidenLines;
public:
    Obelisk();
    Obelisk(const std::vector<Polygon> &p);

    void set_displayHidenLines(bool b);
    bool get_displayHidenLines();
    void change_all_polygons(const std::vector<std::vector<double>> &v);
    void add_polygon(const Polygon &p);
    void draw(QPainter *ptr, int center_x, int center_y);
};

#endif // OBELISK_H
