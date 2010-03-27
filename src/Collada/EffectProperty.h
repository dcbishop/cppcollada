      ColorRGBA emission_;
      ColorRGBA ambient_;
      ColorRGBA diffuse_;
      ColorRGBA specular_;
      float shininess_;
      ColorRGBA reflective_;
      float reflectivity_;
      ColorRGBA transparent_;
      float transparency_;

#define COLLADA_EMISSION_RENDER_FUNCTION virtual void renderDiffuse() { getRenderer()->renderEmission(this); }
#define COLLADA_AMBIENT_RENDER_FUNCTION virtual void renderAmbient() { getRenderer()->renderAmbient(this); }
#define COLLADA_DIFFUSE_RENDER_FUNCTION virtual void renderDiffuse() { getRenderer()->renderDiffuse(this); }
#define COLLADA_SPECULAR_RENDER_FUNCTION virtual void renderSpecular() { getRenderer()->renderSpecular(this); }
#define COLLADA_SHININESS_RENDER_FUNCTION virtual void renderShininess() { getRenderer()->renderShininess(this); }
#define COLLADA_EFFECTRENDER_FUNCTIONS COLLADA_DIFFUSERENDER_FUNCTION

class EffectProperty {
   COLLADA_EFFECTRENDER_FUNCTIONS
};
