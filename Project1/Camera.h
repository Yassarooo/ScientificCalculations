#ifndef Camera_H
#define Camera_H

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Camera
{
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	void CarolLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
public:
	void lookCamera();
	void setcam(glm::vec3 pos, glm::vec3 fro, glm::vec3 up);
};


#endif Camera_H