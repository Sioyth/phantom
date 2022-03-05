#include "DebugMovement.h"
#include <glfw/glfw3.h>
#include "Transform.h"
#include "../Input.h"

void DebugMovement::Update()
{
    _entity->GetComponent<Transform>();

    if(Input::Instance()->GetKey(GLFW_KEY_W, KeyState::PRESS))
        _entity->GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, 0.1f));

    if (Input::Instance()->GetKey(GLFW_KEY_S, KeyState::PRESS))
        _entity->GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, -0.1f));

    if (Input::Instance()->GetKey(GLFW_KEY_A, KeyState::PRESS))
        _entity->GetComponent<Transform>()->Translate(glm::vec3(0.1f, 0.0f, 0.0f));

     if (Input::Instance()->GetKey(GLFW_KEY_D, KeyState::PRESS))
         _entity->GetComponent<Transform>()->Translate(glm::vec3(-0.1f, 0.0f, 0.0f));

}
