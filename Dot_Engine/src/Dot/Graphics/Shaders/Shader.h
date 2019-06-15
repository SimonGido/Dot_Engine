#pragma once
#include <conio.h>
#include "Dot/Debug/Log.h"
#include "Dot/Graphics/Transform.h"
#include "Dot/Graphics/Camera.h"
#include <GL/glew.h>



struct Light
{
	float	 lightStrength;
	float	 specStrength;
	glm::vec3 lightColor;
	glm::vec3 lightPos;
	

	Light(float lightStr = 0.5, float specStr = 2, glm::vec3 lightC = glm::vec3(0.2, 0.2, 0.2),
		glm::vec3 lightP = glm::vec3(-5, 10, 0))
		:
		lightStrength(lightStr),specStrength(specStr),lightColor(lightC),lightPos(lightP)
	{}

};

class Shader
{
public:
	Shader();
	virtual ~Shader();

	virtual void Init(const std::string& filename);
	
	virtual void SetAttribs();
	virtual void SetUniforms();
	virtual void Update(const Transform& transform, Camera& camera);
	
	virtual void LinkShader();
	virtual void Bind();
	virtual void UnBind();



	static std::string LoadShader(const std::string& filename);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);



private:
	static const unsigned int NUM_SHADER = 2;
	
	enum
	{
		TRANSFORM_U,

		VIEW_POS_U,

		LIGHT_STR_U,

		SPEC_STR_U,

		LIGHT_COLOR_U,

		LIGHT_POS_U,

		NUM_UNIFORMS
	};

	Light BasicLight;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];

	

};
