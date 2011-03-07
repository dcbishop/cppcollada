#version 330 compatibility

in vec4      MCvertex;
in vec3      MCnormal;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

smooth out vec3 VaryingNormal;
smooth out vec3 VaryingLightDir;


struct light {
   vec4 position;
};
uniform light Lights[8];

void main()
{
   // TODO: Bind normals correctly...
   vec3 MCnormal = gl_Normal;

   VaryingNormal = NormalMatrix * MCnormal;
   vec4 Position4 = MVMatrix * MCvertex;
   vec3 Position3 = Position4.xyz / Position4.w;
   VaryingLightDir = normalize(Lights[0].position.xyz - Position3);

   gl_Position = MVPMatrix * MCvertex;
}
