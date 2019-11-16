#include "Triangle.h"
#include <limits>
#include <iostream>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Triangle::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	Eigen::Vector3d d = ray.direction;
	Eigen::Vector3d p = ray.origin;

	// triangle time

	Eigen::Matrix3d bary_coef;		// this matrix stores a linear system of equations to be solved
	bary_coef << A[0] - B[0], A[0] - C[0], d[0],
		A[1] - B[1], A[1] - C[1], d[1],
		A[2] - B[2], A[2] - B[2], d[2];

	Eigen::Vector3d sol_vec(A[0] - p[0], A[1] - p[1], A[2] - p[2]);	// solution to the system

	// the coefficients are beta, gamma, and t.
	// we will invert A and multiply by the solution vector even though cramers is faster

	Eigen::Vector3d coef = bary_coef.inverse() * sol_vec;

	// coef[0] = beta, coef[1] = gamma, coef[2] = t

	bool inside1 = coef[0] > 0;				// these are the three conditions that must be met for the ray to intersect
	bool inside2 = coef[1] > 0;
	bool inside3 = coef[0] + coef[1] < 1;

	if (inside1 && inside2 && inside3) {	// we hit the triangle
		double t = coef[2];
		result.t = t;
		result.position = p + t * d;
		result.normal = (A - C).cross(A - B).normalized();
		result.color = color;				// return the objects color
		result.reflec = reflectivity;		// return the objects reflectivity

		return result;
	}
	else {
		return result;
	}
}