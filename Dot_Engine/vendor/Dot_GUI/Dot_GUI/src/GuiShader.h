#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include "GuiTransform.h"

class GuiShader
{
public:
	GuiShader();
	~GuiShader();

	void Init(const std::string& filename);

	void SetAttribs();
	void SetUniforms();

	void LinkShader();
	void Bind();
	void UnBind();

	void Update(GuiTransform& transform);

	static std::string LoadShader(const std::string& filename);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);

	

private:
	static const unsigned int NUM_SHADER = 2;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[2];

};

