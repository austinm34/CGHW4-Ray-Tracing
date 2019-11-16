#include "Scene.h"
#include <cmath>
#include <iostream>

using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {	// for all the shapes in the scene
        HitRecord r = shapes[i]->intersect(ray);	// get a hit record for the shape and ray or "intersect ray with shape"?
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {	// if t > 0 and havent already found something or t < previus t
																									// this is because all intersect functions set t = -1 if no intersect.
            result = r;		// set this as the result
            foundSomething = true;

        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int depth) {								//so do we have to edit this to add phong/spectular and ambient?
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);

    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    if (r.t < numeric_limits<double>::epsilon()) return result;		// if we didn't hit anything, render black pixel.

	// so we hit something. now lets find out if we are in shadow or not. need to cast a ray at light.
	Vector3d lightDir = (lightPos - r.position).normalized();

	// make a shadow ray
	Ray point_to_light;
	point_to_light.origin = r.position + (100 * numeric_limits<double>::epsilon() * lightDir);
	point_to_light.direction = lightDir;
	HitRecord shadows = closestHit(point_to_light);
	bool inShadow = false;
	if (shadows.t > numeric_limits<double>::epsilon()) {
		inShadow = true;
		//cout << "in the shadows" << endl;
	}

	Vector3d light_color(1, 1, 1);
	Vector3d obj_color = r.color;

	//ambient
	double amb = 0.1;
	Vector3d ambient = amb * light_color;

	//diffuse
	Vector3d diffuse(0,0,0);
	if (!inShadow) {
		double diff = lightDir.dot(r.normal);
		if (diff < 0) diff = 0;
		diffuse = diff * light_color;
	}

	//Specular Lighting
	Vector3d specular(0, 0, 0);

	if (!inShadow) {
		double specularStrength = 0.1;
		Vector3d viewDir = (ray.origin - r.position);	// calculate the direction of the viewer
		Vector3d reflectDir = (-1 * lightDir) + 2 * (lightDir.dot(r.normal))*r.normal;	// calculate the reflection direction
		
		double spec = pow(max(viewDir.dot(reflectDir), 0.0), 12);
		specular = specularStrength * spec * light_color;
	}

	Vector3d reflected(0, 0, 0);		// calculte reflected vector
	if (depth < RECUS_DEPTH) {				// i don't know why it won't work
		Vector3d v = (ray.origin - r.position).normalized();
		Vector3d n = r.normal;
		Vector3d reflection_dir = 2*(n.dot(v))*n - v;
		Ray reflected_ray;
		reflected_ray.direction = reflection_dir.normalized();
		reflected_ray.origin = r.position + 200 * numeric_limits<double>::epsilon() * reflection_dir;
		reflected = r.reflec * trace(reflected_ray, depth + 1);
	}

	result = (ambient + diffuse + specular + reflected).cwiseProduct(obj_color);
    return result;
}

void Scene::render(Image &image) {									//so this is where raytracing alg actually happens?
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

	// from the slides: l = -1, r = 1	b = -1, t = 1
	// r - l = 2
	// t - b = 2
	// nx = ny = image.getWidth
	// each pixel (i,j) mapps to a (u,v) value in the image
	// the u value a pixel gets mapped to is found by: u = l + (r - l)(i + 0.5)/nx
	// or in this context: u = -1 + 2(i + 0.5)/width
	// however here we have a varible called pixelSize that takes care of (r - l) and nx
	// so we get: u = -1 + (i + 0.5) * pixelSize or u = (i + 0.5) * pixelSize - 1
	// a similar analysis can be done for v.

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;	// why 2/size? - is it because the square is width = height = 2 in world cords?
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;		//this is p in r(t) = p + td? and we assume it is at 0,0,0?

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay, 0);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}
