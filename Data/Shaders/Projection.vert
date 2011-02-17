in vec4 MCVertex;
in vec3 MCNormal;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

void main(void) {
   gl_Position = MVPMatrix * MCVertex;
   gl_FrontColor = gl_Color;
}
