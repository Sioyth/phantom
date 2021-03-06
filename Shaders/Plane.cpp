#include "Plane.h"

//-----------------------------------------------------------------------------
Plane::Plane()
{
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;

	m_isLit = true;
	m_enabled = true;
	m_isTextured = false;

	m_material.SetMetallic(64.0f);
	m_collider.SetDimension(glm::vec3(0.3f));
}

//-----------------------------------------------------------------------------
void Plane::Create()
{
	GLfloat vertices[]{ -0.5f,  0.5f, 0.0f,
						 0.5f,  0.5f, 0.0f,
						 0.5f, -0.5f, 0.0f,
						-0.5f, -0.5f, 0.0f };


	//----------------------------- Data that represents colors for quad


	GLfloat colors[]{ m_color.r, m_color.g, m_color.b,
					  m_color.r, m_color.g, m_color.b,
					  m_color.r, m_color.g, m_color.b,
					  m_color.r, m_color.g, m_color.b, };


	//data that represents indices for quad
	GLfloat uvs[]{ 0.0f, 0.0f,
				   1.0f, 0.0f,
				   1.0f, 1.0f,
				   0.0f, 1.0f };

	GLint indices[] = { 0, 1, 3, 3, 1, 2 };

	m_material.CreateVertexArray();
	m_material.BindVertexArray();
	{
		m_material.CreateBuffer("vertexVBO");
		m_material.BindBuffer("vertexVBO");
		m_material.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(vertices, sizeof(vertices), "vertexIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateBuffer("colorVBO");
		m_material.BindBuffer("colorVBO");
		m_material.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(colors, sizeof(colors), "colorIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateBuffer("TextureVBO");
		m_material.BindBuffer("TextureVBO");
		m_material.BufferSetAttribute("textureIn", 2, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(uvs, sizeof(uvs), "textureIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateElementBuffer(sizeof(indices), indices, GL_DYNAMIC_DRAW);
	}
	m_material.UnbindVertexArray();

	// Uniforms
	m_material.BindUniform("isTextured");
	m_material.BindUniform("model");
	m_material.BindUniform("isLit");
	m_material.BindUniform("material.ambient");
	m_material.BindUniform("material.diffuse");
	m_material.BindUniform("material.specular");
	m_material.BindUniform("material.metallic");
}

//-----------------------------------------------------------------------------
void Plane::Render()
{
	if (!m_enabled)
		return;

	m_collider.SetPosition(m_transform.GetPosition());
	m_collider.CalculateMinMax();

	m_material.SendUniformData("isLit", m_isLit);
	m_material.SendUniformData("isTextured", m_isTextured);

	m_material.SendUniformData("material.ambient", m_material.GetAmbient());
	m_material.SendUniformData("material.diffuse", m_material.GetDiffuse());
	m_material.SendUniformData("material.specular", m_material.GetSpecular());
	m_material.SendUniformData("material.metallic", m_material.GetMetallic());

	m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());

	m_material.BindTexture();
	m_material.BindVertexArray();
	m_material.DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_material.UnbindVertexArray();
	m_material.UnbindTexture();
}

//-----------------------------------------------------------------------------
void Plane::Update()
{

	
}


