#ifndef COLLADACPP_COLLADA_HPP_
#define COLLADACPP_COLLADA_HPP_

#include <iostream>
using namespace std;

#include "../GameData/SmartPointers.hpp"
#include "../Render/Renderable.hpp"
#include "../GameData/Rotation.hpp"
#include "../Collada/ColladaObject.hpp"

#include "../Collada/Effect.hpp"
#include "../Collada/Geometry.hpp"
#include "../Collada/Image.hpp"
#include "../Collada/Material.hpp"
#include "../Collada/Geometry.hpp"
#include "../Collada/VisualScene.hpp"
#include "../Collada/ColladaCamera.hpp"
#include "../Collada/ColladaLight.hpp"
#include "../Collada/Scene.hpp"

class Scene;


typedef unordered_map<string, ColladaObjectPtr> IdMap;
typedef IdMap::iterator IdMapIterator;
typedef pair<string, ColladaObjectPtr> IdMapPair;

class Collada : public Renderable, public ColladaObject {
   public:
      #warning ['TODO']: Asset information?... created by and so on...
      void setFilename(const string filename);
      string getFilename();
      void setScene(ScenePtr scene);
      ScenePtr getScene();
      COLLADA_RENDER_FUNCTION
      void addId(const string id, ColladaObjectPtr object);
      ColladaObjectPtr getId(const string id);

      void addLibraryCamera(ColladaCameraPtr camera) { libraryCameras_.push_back(camera); }
      void addLibraryEffect(EffectPtr effect) { libraryEffects_.push_back(effect); }
      void addLibraryImage(ImagePtr image) { libraryImages_.push_back(image); }
      void addLibraryLight(ColladaLightPtr light) { libraryLights_.push_back(light); }
      void addLibraryMaterial(MaterialPtr material) { libraryMaterials_.push_back(material); }
      void addLibraryGeometry(GeometryPtr geometry) { libraryGeometries_.push_back(geometry); }
      void addLibraryVisualScene(VisualScenePtr visualScene) { libraryVisualScenes_.push_back(visualScene); }
      //void addLibraryPhysicsMaterial(PhysicsMaterialPtr physicsMaterial) { libraryPhysicsMaterials_.push_back(physicsMaterial); }
      //void addLibraryPhysicsModel(PhysicsModelPtr physicsModel) { libraryPhysicsModels_.push_back(physicsModel); }
      //void addLibraryPhysicsScene(PhysicsScenePtr physicsScene) { libraryPhysicsScens_.push_back(physicsScene); }

   private:
      ScenePtr scene_; /** The Scene of this Collada object. */
      string filename_; /** The .dae filename of this Collada object. */
      IdMap ids_; /** A list of IDs contained in this Collada object. */
      vector<ColladaCameraPtr> libraryCameras_;
      vector<EffectPtr> libraryEffects_;
      vector<ImagePtr> libraryImages_;
      vector<ColladaLightPtr> libraryLights_;
      vector<MaterialPtr> libraryMaterials_;
      vector<GeometryPtr> libraryGeometries_;
      vector<VisualScenePtr> libraryVisualScenes_;
      //vector<PhysicsMaterialPtr> libraryPhysicsMaterials_;
      //vector<PhysicsModelPtr> libraryPhysicsModels_;
      //vector<PhysicsScenePtr> libraryPhysicsScens_;
};
typedef shared_ptr<Collada> ColladaPtr;

#endif /* COLLADACPP_COLLADA_HPP_ */
