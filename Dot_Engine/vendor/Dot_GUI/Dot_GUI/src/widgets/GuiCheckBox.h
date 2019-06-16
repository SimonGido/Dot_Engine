#pragma once
#include "GuiWidget.h"
#include "../GuiShader.h"
#include "../GuiBuffer.h"
#include "../GuiTransform.h"
#include "../glText/GuiText.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>


class GuiCheckBox : public GuiWidget
{
public:

	GuiCheckBox(const std::string& name);
	virtual ~GuiCheckBox() override;
	virtual void Init(unsigned int& VBO, unsigned int& IBO)override;
	virtual void Draw()override;
	
	
	virtual void UpdateData(GuiTransform& transform,glm::vec3 color)override;
	virtual void SetData(glm::vec2 pos, glm::vec2 scale = glm::vec2(0.1, 0.1), glm::vec2 rot = glm::vec2(3.14, 0))override;
	virtual void SetColor(glm::vec3 color)override;

	virtual bool MouseHoover(glm::vec2 mousePos)override;
	virtual bool &Clicked()override { return checked; }
	
	

	virtual glm::vec2 GetPosition() const override { return m_position; }
	virtual GuiText *GetText() override { return m_text; }

private:
	glm::vec4 GetCoords();

private:
	GLuint m_vao;

private:
	GuiText *m_text;

	glm::vec2 m_position = glm::vec2(0, 0);
	glm::vec2 m_scale;
	glm::vec2 m_rotation;
	glm::vec3 m_color;

	
	bool checked = false;
	const unsigned int indices[6] = {
		0,1,2,0,3,2
	};

	static constexpr unsigned int LENGTH = 1;
	static constexpr unsigned int HEIGHT = 1;
};

