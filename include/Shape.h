#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;
};

class Shape;

struct HitRecord {
  Eigen::Vector3d position, normal, color;
  double t;
  double reflec;
};

class Shape {
public:
  virtual ~Shape(){}
  virtual HitRecord intersect(const Ray &ray) = 0;	//so we need to write the intersect function in shape.cpp? or is it just to be defined in the child classes?
  Eigen::Vector3d getColor() { return color; }
protected:
	Eigen::Vector3d color;
	double reflectivity;
};

}

#endif
