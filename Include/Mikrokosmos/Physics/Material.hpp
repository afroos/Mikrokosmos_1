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
		explicit Material(const MaterialParameters& p) noexcept;

		AreaDensity density() const noexcept;
		Real restitution() const noexcept;
		Real staticFriction() const noexcept;
		Real dynamicFriction() const noexcept;

		void setDensity(AreaDensity rho) noexcept;
		void setRestitution(Real e) noexcept;
		void setStaticFriction(Real mus) noexcept;
		void setDynamicFriction(Real mud) noexcept;

	private:

		AreaDensity density_{0};
		Real restitution_{0};
		Real staticFriction_{0};
		Real dynamicFriction_{0};
	};

	bool operator==(const Material& m1, const Material& m2) noexcept;
}

#endif