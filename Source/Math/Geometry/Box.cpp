#include <Mikrokosmos/Math/Geometry/Box.hpp>
#include <cassert>
#include <cmath>

namespace Mikrokosmos
{

	Box::Box(Length2 halfExtents) noexcept
	{
		setHalfExtents(halfExtents);
	}

	Length2 Box::halfExtents() const noexcept
	{
		return halfExtents_;
	}

	void Box::setHalfExtents(Length2 halfExtents) noexcept
	{
		assert(std::isnormal(halfExtents.x().magnitude) && std::isnormal(halfExtents.y().magnitude));
		halfExtents_ = halfExtents;
	}

}