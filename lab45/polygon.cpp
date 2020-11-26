#include "polygon.h"

Polygon::Polygon(const std::vector<QVector4D> &v) {
    vertices = v;
}

Polygon &Polygon::operator=(const std::vector<QVector4D> &v) {
    vertices = v;
    return *this;
}

QVector3D Polygon::get_normal() {
    QVector3D first{
        vertices[1][0] - vertices[0][0],
        vertices[1][1] - vertices[0][1],
        vertices[1][2] - vertices[0][2]
    };

    QVector3D second{
        vertices[2][0] - vertices[0][0],
        vertices[2][1] - vertices[0][1],
        vertices[2][2] - vertices[0][2]
    };

    QVector3D normal{
        first[1] * second[2] - first[2] * second[1],
        first[2] * second[0] - first[0] * second[2],
        first[0] * second[1] - first[1] * second[0]
    };

    return normal;
}
