#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
class Sphere : public Shape {	// private values are a vector pointing at the center, and a double for the radius intersect must be defined?
public:
	Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d col, double reflec) { c = center; r = radius; color = col; reflectivity = reflec; }

    virtual HitRecord intersect(const Ray &ray);
	

private:
	Eigen::Vector3d c;
    double r;
};
}

#endif
