#version 450

layout (location = 0) in vec3 in_vertex_position;
layout (location = 1) in vec3 in_vertex_color;
layout (location = 0) out vec3 out_vertex_color;

layout (set = 0, binding = 0) uniform u_ViewProjBlock
{
	mat4 view;
	mat4 projection;
} u_ViewProj;

layout (set = 0, binding = 1) uniform u_TileDataBlock
{
	vec3 color;
} u_TileData;

layout (push_constant) uniform u_ModelMatrixBlock
{
	mat4 model;
} u_Model;

void main()
{
	gl_Position = u_ViewProj.projection * u_ViewProj.view * u_Model.model * vec4(in_vertex_position, 1.0f);
	out_vertex_color = u_TileData.color;
}