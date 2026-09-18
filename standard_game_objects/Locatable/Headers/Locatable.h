#pragma once
#include <iostream>
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp> 

struct Model_matrix_dismantled
{
	glm::mat4 scale;
	glm::mat4 rotationANDoffset;
	Model_matrix_dismantled();
	Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset, glm::mat4 rotation);
	Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset, glm::vec3 rotation_axis, float rotation);
	Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset, float rotation);
	Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset);
	Model_matrix_dismantled(glm::vec3 scale, glm::mat4 rotationANDoffset);
	Model_matrix_dismantled(glm::mat4 scale, glm::mat4 rotationANDoffset);
	glm::mat4 Get_model_matrix();
	glm::vec3 Get_location();
	void Set_location(glm::vec3 location);
	void Change_loation(glm::vec3 offset);
};

class Locatable_3D
{
public:
	Model_matrix_dismantled positing;

	Locatable_3D();
	Locatable_3D(Model_matrix_dismantled positing);
	Locatable_3D(glm::vec3 location);
	virtual glm::mat4 Get_model_matrix();

private:

};
class Yaw_pitch_3D :public Locatable_3D
{
public:
	static const int MAX_PITCH = 89;
	static const int MIN_PITCH = -89;
	static const int MAX_Y_angle = 179;
	static const int MIN_Y_angle = 1;
	glm::vec3 yaw_axis;// -Y=glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 pitch_axis;//Z=glm::vec3(0.0f,0.0f,1.0f);
	float yaw;//= 270.0f;
	float pitch;//= 0;

	Yaw_pitch_3D(Model_matrix_dismantled model, glm::vec3 up, glm::vec3 front, float yaw, float pitch);
	void Change_yaw_pitch(float yaw_change, float pitch_change);
	virtual glm::mat4 Get_model_matrix();

private:

};
