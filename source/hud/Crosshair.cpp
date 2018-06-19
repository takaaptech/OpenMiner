/*
 * =====================================================================================
 *
 *       Filename:  Crosshair.cpp
 *
 *    Description:
 *
 *        Created:  14/06/2018 18:10:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Crosshair.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

Crosshair::Crosshair() {
	// float cross[4][4] = {
	// 	{-0.04, 0, 0, 1},//, 13},
	// 	{ 0.04, 0, 0, 1},//, 13},
	// 	{0, -0.05, 0, 1},//, 13},
	// 	{0,  0.05, 0, 1},//, 13}
	// };

	Vertex vertices[4] = {
		{{-0.04, 0, 0, 1}},//, 13},
		{{ 0.04, 0, 0, 1}},//, 13},
		{{0, -0.05, 0, 1}},//, 13},
		{{0,  0.05, 0, 1}},//, 13}
	};

	VertexBuffer::bind(&m_vbo);
	// m_vbo.setData(sizeof(cross), cross, GL_DYNAMIC_DRAW);
	m_vbo.setData(sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	VertexBuffer::bind(nullptr);
}

void Crosshair::draw(RenderTarget &target, RenderStates states) const {
	states.projectionMatrix = nullptr;
	states.viewMatrix = nullptr;

	glDisable(GL_DEPTH_TEST);

	target.draw(m_vbo, states);

	glEnable(GL_DEPTH_TEST);
}

