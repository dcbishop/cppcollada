#version 150

in vec4 MCVertex;
in vec3 MCNormal;

uniform mat4x4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

out vec4 FragColor;

struct light {
   vec4 position;
};

uniform light Lights[8];

void main(void) {
   vec4 MaterialDiffuse = vec4(1.0, 0.0, 0.0, 1.0);
   vec3 LightPosition = Lights[0].position.xyz;
   vec3 eye_normal = NormalMatrix * MCNormal;
   
   vec4 position4 = MVMatrix * MCVertex;
   vec3 position3 = position4.xyz / position4.w;
   
   vec3 light_direction = normalize(LightPosition - position3);
   float intensity = max(0.0, dot(eye_normal, light_direction));
   FragColor.xyz = intensity * MaterialDiffuse.xyz;
   FragColor.a = MaterialDiffuse.a;
   gl_Position = MVPMatrix * MCVertex;
}
