#ifndef MIKROKOSMOS_PHYSICS_COLLISION_COLLIDER_HPP
#define MIKROKOSMOS_PHYSICS_COLLISION_COLLIDER_HPP

#include <memory>

class Shape;

namespace Mikrokosmos
{
	class Collider
	{
	public:

	private:
		std::shared_ptr<Shape> shape;
	};
}

#endif
