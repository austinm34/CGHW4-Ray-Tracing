#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

namespace Raytracer148 {
	class Plane : public Shape {
	public:

		Plane(Eigen::Vector3d point, Eigen::Vector3d normal, Eigen::Vector3d col, double reflec) { p = point; n = normal; color = col; reflectivity = reflec; }
		virtual HitRecord intersect(const Ray &ray);

	private:

		Eigen::Vector3d p, n;
		
	};
}

#endif
