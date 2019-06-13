#ifndef MIKROKOSMOS_PHYSICS_MATERIAL_HPP
#define MIKROKOSMOS_PHYSICS_MATERIAL_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Material
	{
	public:

		Material() = delete;
		Material(AreaDensity density, Real restitution, Real staticFriction, Real dynamicFriction) noexcept;

		AreaDensity density() const noexcept;
		Real restitution() const noexcept;
		Real staticFriction() const noexcept;
		Real dynamicFriction() const noexcept;

		void setDensity(AreaDensity density) noexcept;
		void setRestitution(Real restitution) noexcept;
		void setStaticFriction(Real staticFriction) noexcept;
		void setDynamicFriction(Real dynamicFriction) noexcept;

	private:

		AreaDensity density_{ 1.0_kgpm2 };
		Real restitution_{ 0.0 };
		Real staticFriction_{ 0.0 };
		Real dynamicFriction_{ 0.0 };
	};
}

#endif