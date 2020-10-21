#include "obelisk.h"

Obelisk::Obelisk() : displayHidenLines(false)
{

}

Obelisk::Obelisk(const std::vector<Polygon> &p) : Obelisk() {
    polygons = p;
}

void Obelisk::set_displayHidenLines(bool b) {
    displayHidenLines = b;
}

bool Obelisk::get_displayHidenLines() {
    return displayHidenLines;
}

void Obelisk::change_all_polygons(const std::vector<std::vector<double>> &v) {
    for (auto &it: polygons) {
        it.change_verticies(v);
    }
}

void Obelisk::add_polygon(const Polygon &p) {
    polygons.push_back(p);
}

void Obelisk::draw(QPainter *ptr, int center_x, int center_y) {
    for (auto p : polygons) {
        auto p_normal = p.get_normal();
        if (p_normal[2] > 0) {
            p.draw(ptr, center_x, center_y);
        } else {
            if (displayHidenLines) {
                QPen new_pen(Qt::gray, 1, Qt::DashLine);
                QPen old_pen = ptr->pen();
                ptr->setPen(new_pen);
                p.draw(ptr, center_x, center_y);
                ptr->setPen(old_pen);
            }
        }
    }
}
