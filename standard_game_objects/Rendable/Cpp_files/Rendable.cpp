#include "../Headers/Rendable.h"

Rendable_3D::Rendable_3D() :
	Locatable_3D({ {1,1,1}, {0,0,0} })
{
}

Rendable_3D::Rendable_3D(Model_matrix_dismantled model_matrix):
	Locatable_3D(model_matrix)
{

}



Rendable_3D::~Rendable_3D()
{
}