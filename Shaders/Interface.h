#pragma once

#include <vector>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Debug.h"

class Interface
{
public:

	static Interface* Instance();

public:

	void DrawUi();
	bool IsMouseOverUI();

private:

	void DrawConsole();
	void DrawMainMenuBar();
	
	void RightClickMenu();

	void ToolBar();
	void Inspector();

	void Ball();

private:

	bool m_click;
	bool m_cooldown;
	bool m_isRightMenuEnabled = false;

private:

	Interface();
	Interface(const Interface&);
	Interface operator=(const Interface);
};

