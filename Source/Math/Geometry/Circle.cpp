#include <Mikrokosmos/Math/Geometry/Circle.hpp>
#include <cassert>
#include <cmath>

namespace Mikrokosmos
{

	Circle::Circle(Length radius) noexcept
	{
		setRadius(radius);
	}

	Length Circle::radius() const noexcept
	{
		return radius_;
	}

	void Circle::setRadius(Length radius) noexcept
	{
		assert(std::isnormal(radius.magnitude));
		radius_ = radius;
	}

}