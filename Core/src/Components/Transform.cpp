//#include <glm/gtx/transform.hpp>
//#include "Transform.h"
//
//Transform::Transform(Entity* entity) : Component(entity)
//{
//	// Identity
//	_scale = glm::vec3(1.0f);
//	_rotation = glm::vec3(0.0f);
//	_position = glm::vec3(0.0f);
//	_transformMatrix = glm::mat4(1.0f);
//
//	UpdateOrientation();
//}
//
//void Transform::Scale(glm::vec3 scale)
//{
//	_scale = scale;
//	_transformMatrix = glm::scale(_transformMatrix, scale);
//	UpdateOrientation();
//}
//
//void Transform::Rotate(glm::vec3 rotation)
//{
//	_rotation = rotation;
//	//glm::rotate()
//	UpdateOrientation();
//}
//
//void Transform::Translate(glm::vec3 translation)
//{
//	_position += translation;
//	_transformMatrix = glm::translate(_transformMatrix, translation);
//	//std::cout << _entity->Name() << _transformMatrix[3][2] << std::endl;
//	UpdateOrientation();
//}
//
//const glm::vec3& Transform::Up()
//{
//	return _up;
//}
//
//const glm::vec3& Transform::Right()
//{
//	return _right;
//}
//
//const glm::vec3& Transform::Forward()
//{
//	return _forward;
//}
//
//void Transform::Update()
//{
//	
//}
//
///*
//	
//	RT = right
//	UP = up
//	BK = back
//	POS = position/translation
//	US = uniform scale
//
//	     0      1      2     4
//	0 [RT.x] [UP.x] [BK.x] [POS.x]
//	1 [RT.y] [UP.y] [BK.y] [POS.y]
//	2 [RT.z] [UP.z] [BK.z] [POS.Z]
//	3 [    ] [    ] [    ] [US   ]
//*/
//
//void Transform::UpdateOrientation()
//{
//	_up      = glm::normalize(glm::vec3(_transformMatrix[1][0], _transformMatrix[1][1], _transformMatrix[1][2]));
//	_right   = glm::normalize(glm::vec3(_transformMatrix[0][0], _transformMatrix[0][1], _transformMatrix[0][2]));
//	_forward = glm::normalize(glm::vec3(_transformMatrix[2][0], _transformMatrix[2][1], -_transformMatrix[2][2])); //
//}
//
