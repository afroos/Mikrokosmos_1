#ifndef MIKROKOSMOS_MATH_GEOMETRY_CIRCLE_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_CIRCLE_HPP

#include <Mikrokosmos/Math/Geometry/Shape.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Circle : Shape
	{
	public:
		Circle() = delete;
		Circle(Length radius) noexcept;

		Length radius() const noexcept;
		void setRadius(Length radius) noexcept;

	private:
		Length radius_{ 0.0_m };
	};
}

#endif
