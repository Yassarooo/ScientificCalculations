#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "gltexture.h"
#include "Model_3DS.h"
#include "Camera.h"
#include "wheel.h"
#include "Engine.h"
#include "Car.h"

Car::Car(){
	gears[0] = 3.31;
	gears[1] = 1.95;
	gears[2] = 1.41;
	gears[3] = 1.13;
	gears[4] = 0.95;
	gears[5] = 0.81;
	gears[6] = 3.00;
	finalgear = 3.89;
	mass = 750;
	acceleration[0] = acceleration[1] = 0;
	v[0] = v[1] = 0;
	area[0] = 2;
	area[1] = 4;
	positionx = positionz = 0;
	theta = 0;
	angularacceleration = 0;
	yaw = 90;
	cd = 0.35;
	cr = 0.1;
	rho = 1.164;
	gravityconst = 10;
	cb = 5000;
	omega = 0;
	length = 3;
	b = 1.0 / 2.0 * length;
	c = 1.0 / 2.0 * length;
	ca = 867;
	carPos = glm::vec3(0.0f, 0.0f, 0.0f);
	carTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	carDirection = glm::normalize(carPos - carTarget);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	carRight = glm::normalize(glm::cross(up, carDirection));
	carUp = glm::cross(carDirection, carRight);
	carFront = glm::vec3(0.0f, 0.0f, -1.0f);
	currentgear = 0;
	dt = 0.2;
	eng = new M9721();
}

void Car::automaticgear(double rpm){
	if (rpm >= 2500)
		currentgear++;
	if (currentgear > 5)
		currentgear = 5;
	if (rpm <= 1750)
		currentgear--;
	if (currentgear < 0)
		currentgear = 0;
}

double Car::airresistance(int axis){
	return (0.5f * cd * rho * area[axis] * v[axis] * abs(v[axis]));
}

double Car::fraction(int axis){
	if (v[axis] != 0)
		return cr*v[axis];
	return 0;
}

double Car::weight(){
	return mass * gravityconst * sin(glm::radians(theta));
}



double Car::calfrontslipangle(){
	if (v[0] != 0)
		return atan((v[1] + omega*b) / v[0]) - frontwheels[0].getdelta()*(v[0] / abs(v[0]));
	return 0;
}

double Car::calrearslipangle(){
	if (v[0])
		return atan((v[1] + omega*c) / v[0]);
	return 0;
}

double Car::lateralforce(double alpha){
	double ret = ca*alpha;
	return ret;
}

glm::vec3 Car::getpos(){
	return carPos - 20.0f*carFront + 5.0f*glm::normalize(carUp);
}
glm::vec3 Car::getfro(){
	return carFront;
}
glm::vec3 Car::getup(){
	return carUp;
}