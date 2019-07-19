#ifndef MIKROKOSMOS_PHYSICS_MATERIAL_HPP
#define MIKROKOSMOS_PHYSICS_MATERIAL_HPP

#include <Mikrokosmos/Physics/MaterialParameters.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Material
	{
	public:

		Material() noexcept;
		Material(const MaterialParameters& parameters) noexcept;

		AreaDensity density() const noexcept;
		Real restitution() const noexcept;
		Real staticFriction() const noexcept;
		Real dynamicFriction() const noexcept;

		void setDensity(AreaDensity density) noexcept;
		void setRestitution(Real restitution) noexcept;
		void setStaticFriction(Real staticFriction) noexcept;
		void setDynamicFriction(Real dynamicFriction) noexcept;

	private:

		AreaDensity density_{0};
		Real restitution_{0};
		Real staticFriction_{0};
		Real dynamicFriction_{0};
	};

	bool operator==(const Material& m1, const Material& m2) noexcept;
}

#endif