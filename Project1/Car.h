#ifndef Car_H
#define Car_H
#include "wheel.h"
#include "Engine.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Car{
private:
	float yaw;
	glm::vec3 carPos;
	glm::vec3 carTarget;
	glm::vec3 carDirection;
	glm::vec3 up;
	glm::vec3 carRight;
	glm::vec3 carUp;
	glm::vec3 carFront;
	glm::vec3 direction;
	int currentgear = 0;
	double gears[7];
	double finalgear;
	double mass;
	double acceleration[2];
	double positionx, positionz;
	double v[2], omega;
	double theta, angularacceleration;
	double area[2];
	double cd, rho, ca;
	double cr, gravityconst;
	double cb, b, c, length;
	double dt;
	Engine *eng;
	Wheel frontwheels[2], rearwheels[2];
public:
	Car();
	void automaticgear(double rpm);

	double traction();

	double airresistance(int axis);

	double fraction(int axis);

	double weight();

	double breakforce(int axis);

	double calfrontslipangle();

	double calrearslipangle();

	double lateralforce(double alpha);

	void movecar();

	void drawcar();

	glm::vec3 getpos();

	glm::vec3 getfro();

	glm::vec3 getup();

	void settheta(double y){
		theta = y;
	}

	void setrho(double u){
		rho = u;
	}
	void setgravity(double u){
		gravityconst = u;
	}
	void setarea(double u,int i){
		area[i] = u;
	}
	void setcd(double u){
		cd = u;
	}
	void setcr(double u){
		cr = u;
	}
	void setcb(double u){
		cb = u;
	}
	void setLength(double u){
		length = u;
	}
	void setca(double u){
		ca = u;
	}
	void setwheel(double u)
	{
		frontwheels[0].setWheelRadius(u);
		frontwheels[1].setWheelRadius(u);
		rearwheels[0].setWheelRadius(u);
		rearwheels[1].setWheelRadius(u);
	}
	void setmass(double u){
		mass = u;
	}
};

#endif Car_H