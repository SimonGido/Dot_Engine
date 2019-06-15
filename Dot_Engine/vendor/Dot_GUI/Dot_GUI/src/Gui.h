#pragma once
#include "GuiShader.h"
#include "events/GuiEvent.h"
#include "glText/GuiText.h"
#include "GuiBuffer.h"
#include "data/GuiData.h"
#include "widgets/GuiWidget.h"
#include "widgets/GuiButton.h"
#include "widgets/GuiCheckBox.h"
#include <GLFW\glfw3.h>
#include "GuiTransform.h"



class Gui
{
public:

	typedef std::function<void()> func_ptr;

	static void Init(GLFWwindow* handler, glm::vec3 color);
	
	static void Render();
	static void Update();
	static void Clear();
	
	static void HandleWidgetCallbacks();
	static void HandlePressWidget(GuiEvent& event);
	static void HandleReleaseButtons(GuiEvent& event);

	static void Gui_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void Gui_MousePositionCallback(GLFWwindow* window,double xPos, double yPos);
	static void Gui_WindowSizeCallback(GLFWwindow* window, int width, int height);
	
	
	static void AddButton(func_ptr func,const std::string& name);
	static void AddCheckBox(func_ptr func, const std::string& name);

	static void SetDarkTheme();

private:
	static std::vector<GuiWidget*> m_widgets;
	static std::vector<func_ptr> m_user_callbacks;


	static unsigned int num_buttons;
	static unsigned int num_checkboxes;
	
	

	static GuiShader* guiShader;
	static GuiTransform *transform;
	static GLFWwindow* m_handler;

	static GLFWmousebuttonfun m_handler_mouseButtonCLB;
	static GLFWcursorposfun m_handler_cursorPosCLB;
	static GLFWframebuffersizefun m_handler_winSizeCLB;

	
	static bool EDIT_MODE;
	static int attachedWidget;

	static int winWidth;
	static int winHeight;

	static float m_mousePosX;
	static float m_mousePosY;
	
	static GuiIndexBuffer* m_index;
	static GuiVertexBuffer* m_vertex_b;


	static GuiVertexBuffer* m_vertex_chb;
	
};

