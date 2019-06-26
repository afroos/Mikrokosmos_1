#ifndef MIKROKOSMOS_MATH_GEOMETRY_BOX_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_BOX_HPP

#include <Mikrokosmos/Math/Geometry/Shape.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Box : public Shape
	{
	public:
		Box() = delete;
		Box(Length2 halfExtents) noexcept;

		Length2 halfExtents() const noexcept;
		void setHalfExtents(Length2 halfExtents) noexcept;

	private:
		Length2 halfExtents_{ 0.0_m, 0.0_m };
	};
}

#endif
