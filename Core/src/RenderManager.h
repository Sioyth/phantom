#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H
#include "Shader/Shader.h"
#include "Components/camera.h"

class RenderManager
{
public:
	RenderManager();
	static RenderManager* Instance();
	void SetModelMatrix(glm::mat4 model);
	void Update(Shader& shader);


private:
	int _width;
	int _height;
	glm::mat4 _mvp;
	glm::mat4 _proj;
	glm::mat4 _model;
	bool _needsToUpdate;
	static RenderManager* _instance;
};

#endif

