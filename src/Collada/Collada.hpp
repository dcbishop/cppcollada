#ifndef COLLADACPP_COLLADA_HPP_
#define COLLADACPP_COLLADA_HPP_

#include <iostream>
#include <unordered_map>
using namespace std;

#include "../GameData/SmartPointers.hpp"
#include "../Render/Renderable.hpp"
#include "../GameData/Rotation.hpp"

class Scene;
class ColladaObject;

typedef unordered_map<string, shared_ptr<ColladaObject>> IdMap;
typedef IdMap::iterator IdMapIterator;
typedef pair<string, shared_ptr<ColladaObject>> IdMapPair;

class Collada : public Renderable {
   public:
      #warning ['TODO']: Asset information?... created by and so on...
      void setFilename(const string filename);
      string getFilename();
      void setScene(shared_ptr<Scene> scene);
      shared_ptr<Scene> getScene();
      COLLADA_RENDER_FUNCTION
      void addId(const string id, shared_ptr<ColladaObject> object);
      shared_ptr<ColladaObject> getId(const string id);

   private:
      shared_ptr<Scene> scene_; /** The Scene of this Collada object. */
      string filename_; /** The .dae filename of this Collada object. */
      IdMap ids_; /** A list of IDs contained in this Collada object. */
      
};

#endif /* COLLADACPP_COLLADA_HPP_ */
