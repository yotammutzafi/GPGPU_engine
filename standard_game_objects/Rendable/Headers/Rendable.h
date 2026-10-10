#pragma once
#include "../../Locatable/Headers/Locatable.h"
#include "../../Camera/Headers/Camera.h"
//this is a virtual class that every Rendable has a function to create an array of Render_data for the camera to use
class Render_data
{
};

class Rendable_3D :public Locatable_3D

{
public:
 	std::vector<std::vector<Render_data*>*> render_datas;

	Rendable_3D();
	Rendable_3D(Model_matrix_dismantled model_matrix);
	virtual void recordRenderCommandBuffer(Camera* camera) = 0;

	virtual void Pre_draw() = 0;
	~Rendable_3D();


private:

};

