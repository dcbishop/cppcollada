#ifndef COLLADACPP_COLLADA_HPP_
#define COLLADACPP_COLLADA_HPP_

#include <iostream>
using namespace std;

#include "Renderable.hpp"

class Scene;

class Collada : public Renderable {
	public:
		#warning ['TODO']: Filename?
		#warning ['TODO']: Asset information... created by and so on...
		void setScene(Scene* scene);
		Scene* getScene();
		COLLADA_RENDER_FUNCTION

	private:
		Scene* scene_;
};

#endif /* COLLADACPP_COLLADA_HPP_ */
