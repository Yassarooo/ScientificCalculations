
#define _CRT_SECURE_NO_WARNINGS

#include "Camera.h"

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

void Camera::CarolLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	gluLookAt(
		eye.x, eye.y, eye.z,
		center.x, center.y, center.z,
		up.x, up.y, up.z);
}

void Camera::lookCamera()
{
	CarolLookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::setcam(glm::vec3 pos, glm::vec3 fro, glm::vec3 up){
	cameraPos = pos;
	cameraFront = fro;
	cameraUp = up;
}