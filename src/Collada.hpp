#ifndef COLLADACPP_COLLADA_HPP
#define COLLADACPP_COLLADA_HPP

#include "Container.hpp"
class Scene;

class Collada : public Container {
	public:
		#warning ['TODO']: Filename?
		#warning ['TODO']: Asset information... created by and so on...
		void setScene(Scene* scene);
	private:
		Scene* scene_;
};

#endif /* COLLADACPP_COLLADA_HPP */
