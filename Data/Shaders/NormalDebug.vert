// Renders normals as color
#version 330 compatibility

/*in vec4      MCvertex;
in vec3      MCnormal;*/

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

smooth out vec4 FlatColor;

void main()
{
   vec3 MCnormal = gl_Normal;
   vec4 MCvertex = gl_Vertex;
   gl_Position     = MVPMatrix * MCvertex;
   FlatColor.rgb = MCnormal.xyz;
}
