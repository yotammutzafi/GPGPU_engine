#include "../Headers/Locatable.h"
#include <algorithm>

Model_matrix_dismantled::Model_matrix_dismantled() :
    scale{ 1.0f },
    rotationANDoffset{ 1.0f }
{
}

Model_matrix_dismantled::Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset, glm::mat4 rotation) :
    scale{ glm::diagonal4x4(glm::vec4(scale,1.0f)) },
    rotationANDoffset{ glm::translate(rotation,offset) }
{
}
Model_matrix_dismantled::Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset, glm::vec3 rotation_axis, float rotation) :
    scale{ glm::diagonal4x4(glm::vec4(scale,1.0f)) },
    rotationANDoffset{ glm::translate(glm::rotate(glm::mat4(1.0f),rotation,rotation_axis) ,offset) }
{
}
Model_matrix_dismantled::Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset, float rotation) :
    scale{ glm::diagonal4x4(glm::vec4(scale,1.0f)) },
    rotationANDoffset{ glm::translate(glm::rotate(glm::mat4(1.0f),rotation,glm::vec3(0.0f,1.0f,0.0f)) ,offset) }
{
}

Model_matrix_dismantled::Model_matrix_dismantled(glm::vec3 scale, glm::vec3 offset) :
    scale{ glm::diagonal4x4(glm::vec4(scale,1.0f)) },
    rotationANDoffset{ glm::translate(glm::mat4(1.0f),offset) }
{
}

Model_matrix_dismantled::Model_matrix_dismantled(glm::vec3 scale, glm::mat4 rotationANDoffset) :
    scale{ glm::diagonal4x4(glm::vec4(scale,1.0f)) },
    rotationANDoffset{ rotationANDoffset }
{
}

Model_matrix_dismantled::Model_matrix_dismantled(glm::mat4 scale, glm::mat4 rotationANDoffset) :
    scale{ scale },
    rotationANDoffset{ rotationANDoffset }
{
}

glm::mat4 Model_matrix_dismantled::Get_model_matrix()
{
    return rotationANDoffset * scale;
}

glm::vec3 Model_matrix_dismantled::Get_location()
{
    return glm::vec3(rotationANDoffset[3][0], rotationANDoffset[3][1], rotationANDoffset[3][2]);
}
void Model_matrix_dismantled::Set_location(glm::vec3 location)
{
    rotationANDoffset[3][0] = location.x;
    rotationANDoffset[3][1] = location.y;
    rotationANDoffset[3][2] = location.z;
}

void Model_matrix_dismantled::Change_loation(glm::vec3 offset)
{
    rotationANDoffset[3][0] += offset.x;
    rotationANDoffset[3][1] += offset.y;
    rotationANDoffset[3][2] += offset.z;

}
Locatable_3D::Locatable_3D() :
    positing{ glm::vec3{1.0f},glm::mat4{1.0f} }
{
    std::cout << "I'm Locatable" << std::endl;
}
Locatable_3D::Locatable_3D(Model_matrix_dismantled positing) :
    positing{ positing }
{
    std::cout << "I'm Locatable" << std::endl;
}
Locatable_3D::Locatable_3D(glm::vec3 location) :
    positing{ glm::vec3(1.0f),glm::translate(glm::mat4(1.0f),location) }
{
    std::cout << "I'm Locatable" << std::endl;
}
glm::mat4 Locatable_3D::Get_model_matrix()
{

    return positing.Get_model_matrix();

}

//front = X_axis
//pitch_axis = "z"
//yaw_axis = "-y"
Yaw_pitch_3D::Yaw_pitch_3D(Model_matrix_dismantled model, glm::vec3 up, glm::vec3 front, float yaw, float pitch) :
    Locatable_3D(model),
    pitch_axis{ glm::cross(front,up) },
    yaw_axis{ -up },
    yaw{ yaw },
    pitch{ pitch }
{
}

void Yaw_pitch_3D::Change_yaw_pitch(float yaw_change, float pitch_change)
{
    yaw += yaw_change;
    pitch += pitch_change;
    if (yaw >= 360.0f)
        yaw -= 360.0f;
    if (yaw < 0.0f)
        yaw += 360.0f;

    pitch = std::clamp(pitch, static_cast<float>(MIN_PITCH), static_cast<float>(MAX_PITCH));
}
glm::mat4 Yaw_pitch_3D::Get_model_matrix()
{

    return positing.rotationANDoffset * glm::rotate(glm::rotate(positing.scale, glm::radians(yaw), yaw_axis), glm::radians(pitch), pitch_axis);


}
