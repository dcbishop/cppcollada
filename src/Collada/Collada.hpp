#ifndef COLLADACPP_COLLADA_HPP_
#define COLLADACPP_COLLADA_HPP_

#include <iostream>
#include <unordered_map>
using namespace std;

#include "../GameData/SmartPointers.hpp"
#include "../Render/Renderable.hpp"
#include "../GameData/Rotation.hpp"
#include "../Collada/ColladaObject.hpp"

class Scene;


typedef unordered_map<string, ColladaObjectPtr> IdMap;
typedef IdMap::iterator IdMapIterator;
typedef pair<string, ColladaObjectPtr> IdMapPair;

class Collada : public Renderable {
   public:
      #warning ['TODO']: Asset information?... created by and so on...
      void setFilename(const string filename);
      string getFilename();
      void setScene(shared_ptr<Scene> scene);
      shared_ptr<Scene> getScene();
      COLLADA_RENDER_FUNCTION
      void addId(const string id, ColladaObjectPtr object);
      ColladaObjectPtr getId(const string id);

   private:
      shared_ptr<Scene> scene_; /** The Scene of this Collada object. */
      string filename_; /** The .dae filename of this Collada object. */
      IdMap ids_; /** A list of IDs contained in this Collada object. */
      
};
typedef shared_ptr<Collada> ColladaPtr;

#endif /* COLLADACPP_COLLADA_HPP_ */
