#include "glellipsoid.h"
#include <QVector4D>
#include <cmath>

GlEllipsoid::GlEllipsoid(float i, float j, float k) :
    a(i), b(j), c(k) {
    precision = 0.08f;
    ambient_color = new float(4);
    ambient_color[0] = 0.2f;
    ambient_color[1] = 0.2f;
    ambient_color[2] = 0.2f;
    ambient_color[3] = 1.f;
    diffuse_color = new float(4);
    diffuse_color[0] = 0.3f;
    diffuse_color[1] = 0.3f;
    diffuse_color[2] = 0.3f;
    diffuse_color[3] = 1.f;
    specular_color = new float(4);
    specular_color[0] = 1.f;
    specular_color[1] = 1.f;
    specular_color[2] = 1.f;
    specular_color[3] = 1.f;
    shininess = 90;
    create();
}

GlEllipsoid::~GlEllipsoid() {

}

GlEllipsoid &GlEllipsoid::operator=(const GlEllipsoid &other) {
    a = other.a;
    b = other.b;
    c = other.c;
    precision = other.precision;
    polygons = other.polygons;
    return *this;
}

float GlEllipsoid::get_a() {
    return a;
}

void GlEllipsoid::set_a(float i) {
    a = i;
}

float GlEllipsoid::get_b() {
    return b;
}

void GlEllipsoid::set_b(float j) {
    b = j;
}

float GlEllipsoid::get_c() {
    return c;
}

void GlEllipsoid::set_c(float k) {
    c = k;
}

float GlEllipsoid::get_precision() {
    return precision;
}

void GlEllipsoid::set_precision(float p) {
    precision = p;
}

const float *GlEllipsoid::get_ambient_color() {
    return ambient_color;
}

const float *GlEllipsoid::get_diffuse_color() {
    return diffuse_color;
}

const float *GlEllipsoid::get_specular_color() {
    return specular_color;
}

unsigned int GlEllipsoid::get_shininess() {
    return shininess;
}

std::vector<Polygon> &GlEllipsoid::get_polygons() {
    return this->polygons;
}

void GlEllipsoid::create() {
    std::vector<QVector4D> prevPoints{};
    QVector4D firstIter{0, 0, c * static_cast<float>(cos(0)), 1};
    QVector4D lastIter{0, 0, c * static_cast<float>(cos(M_PI)), 1};

    bool connectToOnePoint = true;
    double step = static_cast<double>(precision);
    for (double theta = step / 2.; theta < M_PI; theta += step / 2.) {
        if (connectToOnePoint) {
            QVector4D prevVertex;
            QVector4D firstVertex;
            for (double phi = 0.; phi < 2 * M_PI; phi += step) {
                if (phi == 0.) {
                    firstVertex = {
                        a * static_cast<float>(sin(theta) * cos(phi)),
                        b * static_cast<float>(sin(theta) * sin(phi)),
                        c * static_cast<float>(cos(theta)),
                        1
                    };
                    prevVertex = firstVertex;
                    prevPoints.push_back(prevVertex);
                    continue;
                }
                std::vector<QVector4D> toPushBack;
                QVector4D newVertex;
                newVertex = {
                    a * static_cast<float>(sin(theta) * cos(phi)),
                    b * static_cast<float>(sin(theta) * sin(phi)),
                    c * static_cast<float>(cos(theta)),
                    1
                };
                toPushBack = {
                    firstIter,
                    prevVertex,
                    newVertex
                };
                polygons.push_back(toPushBack);
                prevVertex = newVertex;
                prevPoints.push_back(prevVertex);
                if (phi + step >= 2 * M_PI) {
                    toPushBack = {
                        firstIter,
                        prevVertex,
                        firstVertex
                    };
                    polygons.push_back(toPushBack);
                    prevPoints.push_back(firstVertex);
                    connectToOnePoint = false;
                }
            }
        } else {
            QVector4D prevVertex;
            QVector4D firstVertex;
            std::vector<QVector4D> newPrevPoints{};
            size_t cnt = 0;
            for (double phi = 0.; phi < 2 * M_PI; phi += step, cnt++) {
                if (phi == 0.) {
                    firstVertex = {
                        a * static_cast<float>(sin(theta) * cos(phi)),
                        b * static_cast<float>(sin(theta) * sin(phi)),
                        c * static_cast<float>(cos(theta)),
                        1
                    };
                    prevVertex = firstVertex;
                    newPrevPoints.push_back(prevVertex);
                    continue;
                }
                std::vector<QVector4D> toPushBack;
                QVector4D newVertex;
                newVertex = {
                    a * static_cast<float>(sin(theta) * cos(phi)),
                    b * static_cast<float>(sin(theta) * sin(phi)),
                    c * static_cast<float>(cos(theta)),
                    1
                };
                toPushBack = {
                    prevPoints[cnt - 1],
                    prevVertex,
                    newVertex
                };
                polygons.push_back(toPushBack);
                toPushBack = {
                    prevPoints[cnt - 1],
                    newVertex,
                    prevPoints[cnt]
                };
                polygons.push_back(toPushBack);
                prevVertex = newVertex;
                newPrevPoints.push_back(prevVertex);
                if (phi + step > 2 * M_PI) {
                    cnt++;
                    toPushBack = {
                        prevPoints[cnt - 1],
                        prevVertex,
                        firstVertex
                    };
                    polygons.push_back(toPushBack);
                    toPushBack = {
                        prevPoints[cnt - 1],
                        firstVertex,
                        prevPoints[cnt]
                    };
                    polygons.push_back(toPushBack);
                    newPrevPoints.push_back(firstVertex);
                    prevPoints = newPrevPoints;
                }
            }
        }
    }
    std::vector<QVector4D> toPushBack;
    for (size_t i = 0; i < prevPoints.size() - 1; i++) {
        toPushBack = {
            prevPoints[i + 1],
            prevPoints[i],
            lastIter
        };
        polygons.push_back(toPushBack);
    }
}

void GlEllipsoid::clear_polygons() {
    polygons.clear();
}

size_t GlEllipsoid::get_polygons_size() {
    return polygons.size();
}
