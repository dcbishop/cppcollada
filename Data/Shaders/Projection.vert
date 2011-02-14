in vec4 MCvertex;
in vec3 MCnormal;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

void main(void) {
   gl_Position = MVPMatrix * gl_Vertex;
   gl_FrontColor = gl_Color;
}
