#include "Plane.h"
#include <limits>
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Plane::intersect(const Ray &ray) {
	Eigen::Vector3d Pr = ray.origin;
	Eigen::Vector3d d = ray.direction;
	//Pp = p 
	//n = n
	// to find intersection with plane: t = (1 / (d*n)) * (Pp * n  -  Pr * n))
	// must check d*n != 0, this means plane is parallel to ray. 
	// if t returned is negative, the plane is behind the origin of the ray

	HitRecord result;
	result.t = -1;

	if (d.dot(n) == 0) {
		return result;
	}
	
	double t = (1 / d.dot(n)) * (p.dot(n) - Pr.dot(n));

	if (t < numeric_limits<double>::epsilon()) { // if t < 0 the plane is behind the camera.
		return result;
	}
	
	result.t = t;
	result.position = ray.origin + result.t * ray.direction;	// this is where the hit happened.
	result.normal = n.normalized();								// this is the surface normal. luckily its part of the definition of a plane
	result.color = color;										// return the objects color
	result.reflec = reflectivity;								// return the objects reflectivity

	return result;
}