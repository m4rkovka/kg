#ifndef POLYGON_H
#define POLYGON_H

#include <QVector4D>
#include <vector>
#include <QVector3D>

class Polygon
{
public:
    std::vector<QVector4D> vertices;

    Polygon(const std::vector<QVector4D> &v);
    Polygon &operator=(const std::vector<QVector4D> &v);
    QVector3D get_normal();
};

#endif // POLYGON_H
