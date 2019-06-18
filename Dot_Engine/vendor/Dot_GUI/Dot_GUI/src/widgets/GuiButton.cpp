#include "GuiButton.h"




GuiButton::GuiButton(const std::string& name, int winID)
	: m_text(new GuiText(name)),m_winID(winID)
{

}

GuiButton::~GuiButton()
{
	delete m_text;
	
}

void GuiButton::Init(unsigned int& VBO, unsigned int& IBO)
{

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 24, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 24,(const void*)8);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	
	glBindVertexArray(0);

}


void GuiButton::Draw(GuiShader& shader, GuiTransform& transform)
{
	UpdateData(transform);
	shader.Update(transform);
	shader.UpdateColor(glm::vec3(m_color, m_color, m_color));
	
	glBindVertexArray(m_vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	
}

void GuiButton::UpdateData(GuiTransform& transform)
{
	transform.SetRot(m_rotation);
	transform.SetScale(m_scale);
	transform.SetPos(glm::vec2(m_position.x - m_scale.x/2,
							   m_position.y + m_scale.y/2));
}

void GuiButton::SetData(glm::vec2 pos,glm::vec2 scale,glm::vec2 rot)
{
	m_rotation = rot;
	m_scale = scale;
	m_position = pos;
}


bool GuiButton::MouseHoover(glm::vec2 mousePos)
{
	
	if (mousePos.x >= GetCoords().x && mousePos.x <= GetCoords().z
		&& mousePos.y <= GetCoords().y && mousePos.y >= GetCoords().w)
	{
		return true;
		
	}
	else 
	{
		return false;	
	}
}



glm::vec4 GuiButton::GetCoords() 
{
	return glm::vec4(m_position.x - m_scale.x/2,
					 m_position.y + m_scale.y/2,
					 m_position.x + m_scale.x/2,
					 m_position.y - m_scale.y/2);
}
