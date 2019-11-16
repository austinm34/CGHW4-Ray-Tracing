#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;
	
	Vector3d Red(1, 0, 0);
	Vector3d Green(0, 1, 0);
	Vector3d Blue(0, 0, 1);
	Vector3d somecolor(0,1,1); somecolor.normalize();

    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, 2, Red, 0.01));

    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5, Blue, 0.01));

    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center, .5, Green, 0.01));

	Vector3d p;
	Vector3d n;
	p[0] = 0;
	p[1] = -2;
	p[2] = 0;

	n[0] = 0;
	n[1] = 1;
	n[2] = 0;
	n.normalize();

	scene.addShape(new Plane(p, n, somecolor, 0.5));

	Vector3d A, B, C;
	A[0] = 2.75;
	A[1] = 3;
	A[2] = 7;
	B[0] = 3;
	B[1] = 2;
	B[2] = 4;
	C[0] = 3.25;
	C[1] = 3;
	C[2] = 6;

	scene.addShape(new Triangle(A, B, C, Red, 0.01));

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
