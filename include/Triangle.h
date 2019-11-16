#pragma once

#include "Shape.h"

namespace Raytracer148 {
	class Triangle : public Shape {
	public:

		Triangle(Eigen::Vector3d a, Eigen::Vector3d b, Eigen::Vector3d c, Eigen::Vector3d col, double reflec) { A = a; B = b; C = c; color = col; reflectivity = reflec; }
		virtual HitRecord intersect(const Ray &ray);


	private:
		Eigen::Vector3d A, B, C;	// verticies of the triangle and color
	};
}