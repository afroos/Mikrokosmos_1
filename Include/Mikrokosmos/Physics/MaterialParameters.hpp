#ifndef MIKROKOSMOS_PHYSICS_MATERIAL_PARAMS_HPP
#define MIKROKOSMOS_PHYSICS_MATERIAL_PARAMS_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	struct MaterialParameters
	{
	public:

		inline constexpr MaterialParameters& density(AreaDensity density) noexcept;
		inline constexpr MaterialParameters& restitution(Real restitution) noexcept;
		inline constexpr MaterialParameters& staticFriction(Real staticFriction) noexcept;
		inline constexpr MaterialParameters& dynamicFriction(Real dynamicFriction) noexcept;

		AreaDensity density_{ 0.0_kgpm2 };
		Real restitution_{ 0.0 };
		Real staticFriction_{ 0.5 };
		Real dynamicFriction_{ 0.2 };
	};

	inline constexpr MaterialParameters& MaterialParameters::density(AreaDensity density) noexcept
	{
		density_ = density;
		return *this;
	}

	inline constexpr MaterialParameters& MaterialParameters::restitution(Real restitution) noexcept
	{
		restitution_ = restitution;
		return *this;
	}

	inline constexpr MaterialParameters& MaterialParameters::staticFriction(Real staticFriction) noexcept
	{
		staticFriction_ = staticFriction;
		return *this;
	}

	inline constexpr MaterialParameters& MaterialParameters::dynamicFriction(Real dynamicFriction) noexcept
	{
		dynamicFriction_ = dynamicFriction;
		return *this;
	}
}



#endif