#ifndef MIKROKOSMOS_PHYSICS_MATERIAL_PARAMETERS_HPP
#define MIKROKOSMOS_PHYSICS_MATERIAL_PARAMETERS_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	struct MaterialParameters
	{
	public:

		inline constexpr MaterialParameters& withDensity(AreaDensity rho) noexcept;
		inline constexpr MaterialParameters& withRestitution(Real e) noexcept;
		inline constexpr MaterialParameters& withStaticFriction(Real mu) noexcept;
		inline constexpr MaterialParameters& withDynamicFriction(Real mu) noexcept;

		AreaDensity density{ 0.0_kgpm2 };
		Real restitution{ 0.0 };
		Real staticFriction{ 0.5 };
		Real dynamicFriction{ 0.2 };
	};

	inline constexpr MaterialParameters& MaterialParameters::withDensity(AreaDensity rho) noexcept
	{
		density = rho;
		return *this;
	}

	inline constexpr MaterialParameters& MaterialParameters::withRestitution(Real e) noexcept
	{
		restitution = e;
		return *this;
	}

	inline constexpr MaterialParameters& MaterialParameters::withStaticFriction(Real mus) noexcept
	{
		staticFriction = mus;
		return *this;
	}

	inline constexpr MaterialParameters& MaterialParameters::withDynamicFriction(Real mud) noexcept
	{
		dynamicFriction = mud;
		return *this;
	}
}



#endif