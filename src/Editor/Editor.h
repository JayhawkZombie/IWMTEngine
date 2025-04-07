//
// Created by Kurt Slagle on 4/5/25.
//

#ifndef EDITOR_H
#define EDITOR_H

#include <imgui.h>
#include "../Engine/Engine.h"
#include <Reflection/GenReflection.h>

class Editor {
public:
    Engine *m_engineInstance;
    Editor(Engine *instance);


    void Render();

    void DisplayLevelDropdown();

};

RENGINE_REFLECT_CLASS_BEGIN(Editor)
RENGINE_REFLECT_CLASS_END(Editor)

#endif //EDITOR_H
