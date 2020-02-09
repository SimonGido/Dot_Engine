#include "stdafx.h"
#include "Button.h"
#include "Dot/Gui/Gui/GuiApplication.h"

namespace Dot {
	Button::Button(const std::string& label, const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
		:
		m_Label("Arial", label, glm::vec2(position.x, position.y - Font::GetFont("Arial")->GetData().lineHeight*0.2f), glm::vec2(0.2f), glm::vec3(0.2, 1, 0.5), MAX_CHAR_PER_LABEL),
		m_Text("Arial", label, glm::vec2(position.x + size.x + 3, position.y + size.y / 4.0f), glm::vec2(0.18f), glm::vec3(0.2, 1, 0.5), MAX_TEXT_CHAR),
		m_Position(position),
		m_Size(size)
	{	
		glm::vec2 texCoords[4] = {
				   glm::vec2(0.0f,		 0.0f),
				   glm::vec2(1.0f / 8.0f,0.0f),
				   glm::vec2(1.0f / 8.0f,1.0f / 8.0f),
				   glm::vec2(0.0f,		 1.0f / 8.0f)
		};

		m_Quad = QuadVertex2D(position, size, color, &texCoords[0]);
		m_Index = GuiApplication::Get()->PopIndex();
		updateBuffers();
	}
	Button::~Button()
	{
		Clean();
	}

	void Button::Clean()
	{
		GuiApplication::Get()->PushIndex(m_Index);
		GuiApplication::Get()->UpdateVertexBuffer(m_Index, &QuadVertex2D());

		std::vector<QuadVertex2D> quad;
		quad.resize(MAX_CHAR_PER_LABEL);
		GuiApplication::Get()->UpdateLabelBuffer(m_Index, &quad[0], MAX_CHAR_PER_LABEL);
		quad.resize(MAX_TEXT_CHAR);
		GuiApplication::Get()->UpdateTextBuffer(m_Index, &quad[0], MAX_TEXT_CHAR);
	}
	
	bool Button::OnLeftClick(const glm::vec2& mousePos)
	{
		if (MouseHoover(mousePos))
		{
			m_Clicked = true;
			m_Quad.SetColor(glm::vec3(0.3, 0.3, 1));
			GuiApplication::Get()->UpdateVertexBuffer(m_Index, &m_Quad);

			return true;
		}
		return false;
	}
	bool Button::MouseHoover(const glm::vec2& mousePos)
	{
		glm::vec4 coords = getCoords();

		if (mousePos.x >= coords.x && mousePos.x <= coords.z
			&& mousePos.y <= coords.y && mousePos.y >= coords.w)
		{		
			return true;
		}
		m_Clicked = false;
		return false;
	}
	void Button::Move(const glm::vec2& pos)
	{
		m_Position += pos;
		updateBuffers();
	}
	void Button::SetPosition(const glm::vec2& pos)
	{
		m_Position = pos;	
		updateBuffers();
	}
	bool Button::Release()
	{	
		m_Quad.SetColor(glm::vec3(1, 1, 1));
		GuiApplication::Get()->UpdateVertexBuffer(m_Index, &m_Quad);
		return false;
	}
	void Button::SetColor(const glm::vec3& color)
	{
		m_Quad.SetColor(color);
		updateBuffers();
	}
	void Button::SetSize(const glm::vec2& size)
	{
		m_Size = size;
		m_Quad.SetPosition(m_Position, m_Size);
		m_Label.SetPosition(glm::vec2(m_Position.x + m_Size.x, m_Size.y));
		updateBuffers();
	}
	void Button::StopRender()
	{
		m_Position = glm::vec2(-100 )+m_Size;
		updateBuffers();
	}
	const glm::vec2& Button::GetSize()
	{
		return glm::vec2(m_Size.x + m_Text.GetSize().x, m_Size.y + m_Label.GetSize().y);
	}
	const bool Button::Clicked()
	{
		if (m_Clicked)
		{
			m_Clicked = false;
			return true;
		}
		return false;
	}

	Ref<Widget> Button::Create(const std::string& label, const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
	{
		return std::make_shared<Button>(label, position, size, color);
	}
	
	void Button::updateBuffers()
	{
		m_Quad.SetPosition(m_Position, m_Size);
		m_Text.SetPosition(glm::vec2(m_Position.x + m_Size.x + 3, m_Position.y + m_Size.y / 4.0f));
		m_Label.SetPosition(glm::vec2(m_Position.x, m_Position.y - Font::GetFont("Arial")->GetData().lineHeight * 0.2f));

		GuiApplication::Get()->UpdateVertexBuffer(m_Index, &m_Quad);
		GuiApplication::Get()->UpdateLabelBuffer(m_Index, m_Label.GetVertice(0), m_Label.GetNumChar());
		GuiApplication::Get()->UpdateTextBuffer(m_Index, m_Text.GetVertice(0), m_Text.GetNumChar());
	}

	glm::vec4 Button::getCoords()
	{
		return glm::vec4(m_Position.x,
			m_Position.y + m_Size.y,
			m_Position.x + m_Size.x,
			m_Position.y);
	}
}