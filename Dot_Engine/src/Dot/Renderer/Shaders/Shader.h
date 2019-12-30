#pragma once
#include <conio.h>
#include <glm/glm.hpp>

#include "Dot/Debug/Log.h"

namespace Dot {
	struct ShaderElement
	{
		ShaderElement(unsigned int Index, const std::string& Name)
			:index(Index), name(Name)
		{}
		std::string name;
		unsigned int index;
	};

	class ShaderQueue
	{
	public:
		ShaderQueue() {};
		ShaderQueue(const std::initializer_list<ShaderElement>& elements)
			: m_Elements(elements)
		{}


	private:
		std::vector<ShaderElement> m_Elements;
	};
	class Shader
	{
	public:
		~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Compute(unsigned int groupX, unsigned int groupY = 1, unsigned int groupZ = 1) const = 0;
		virtual void Unbind() const = 0;
	
		virtual const std::string& GetName() const = 0;
	
		virtual void AddUniformBufferObject(const std::string& name, unsigned int bindIndex, unsigned int size) = 0;
		virtual void AddUniform(const std::string& name) = 0;
	
		virtual void UpdateUniformBufferObject(const std::string& name, const void* data, unsigned int size) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;
		
		virtual void UploadUniformFloat(const std::string& name, float value) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value)= 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value)= 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value)= 0;
	 
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix)= 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix)= 0;

		static Ref<Shader> Create(const std::string& name, const std::string& filepath);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}