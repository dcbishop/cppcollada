#ifndef COLLADACPP_CONTAINER_HPP_
#define COLLADACPP_CONTAINER_HPP_

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Contained;

typedef vector<Contained*> ChildrenVector;
typedef ChildrenVector::iterator ChildrenIterator;

/**
 * An abstract class for things that can contain or own things.
 * Useabble for maps having objects, inventories with items, etc...
 */
class Container {
   public:
      virtual void add(Contained* child);
      virtual void remove(Contained* child);

      virtual ChildrenIterator getChildBegin();
      virtual ChildrenIterator getChildEnd();

   protected:
      ChildrenVector children_;
};

/**
 * An abstract class for things that can be contained or owned by other
 * things. Useabble for objects in maps, items in inventories, etc...
 */
class Contained {
   private:
      Container* parent_;

   public:
      Contained(): parent_(NULL){}
      virtual void setParent(Container* parent);
      Container* getParent();
};

#endif /* COLLADACPP_CONTAINER_HPP_ */
