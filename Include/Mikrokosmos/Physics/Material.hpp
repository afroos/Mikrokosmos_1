#ifndef MIKROKOSMOS_PHYSICS_MATERIAL_HPP
#define MIKROKOSMOS_PHYSICS_MATERIAL_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Material
	{
	public:

		AreaDensity density() const noexcept;
		Real restitution() const noexcept;
		Real staticFriction() const noexcept;
		Real dynamicFriction() const noexcept;

	private:

		AreaDensity density_{ 1.0_kgpm2 };
		Real restitution_{ 0.0 };
		Real staticFriction_{ 0.0 };
		Real dynamicFriction_{ 0.0 };
	};
}

#endif