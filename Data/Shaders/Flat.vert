#version 130
uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;

in vec4 MCVertex;
in vec3 MCNormal;
in vec4 VertexColor;

smooth out vec4 FlatColor;

void main(void) {
   gl_Position = MVPMatrix * MCVertex;
   FlatColor = VertexColor;
}
