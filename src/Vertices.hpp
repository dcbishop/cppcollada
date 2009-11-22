#ifndef COLLADACPP_VERTICES_HPP_
#define COLLADACPP_VERTICES_HPP_

#include "Input.hpp"

class Vertices: public Input {
   public:
      void setPosition(shared_ptr<Source> position) {
         DEBUG_H("%s.setPosition('%s')", getId().c_str(), position->getId().c_str());
         setSource(position); }

   private:
      //shared_ptr<Input> position_;
};

#endif /* COLLADACPP_VERTICES_HPP_ */
