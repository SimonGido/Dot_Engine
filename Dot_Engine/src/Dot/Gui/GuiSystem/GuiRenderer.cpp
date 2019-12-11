#include "stdafx.h"
#include "GuiRenderer.h"

#include <GL/glew.h>

namespace Dot {
	GuiRenderer::SceneData GuiRenderer::m_SceneData;

	void GuiRenderer::BeginRender(const Ref<OrthoCamera> camera)
	{
		m_SceneData.ViewProjectionMatrix = camera->GetViewProjectionMatrix();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}

	void GuiRenderer::Render(const Ref<Shader> shader, const Ref<ArrayBuffer>& vao)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData.ViewProjectionMatrix);
		vao->Bind();

		glDrawArrays(GL_QUADS, 0, vao->GetVertexBuffer(0)->GetCount());
	}

	void GuiRenderer::EndRender()
	{
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR, GL_SRC_COLOR);
		glEnable(GL_DEPTH_TEST);
	}

}