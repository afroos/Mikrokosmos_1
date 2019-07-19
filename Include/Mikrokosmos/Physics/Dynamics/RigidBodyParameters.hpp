#ifndef MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_PARAMETERS_HPP
#define MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_PARAMETERS_HPP

#include <Mikrokosmos/Physics/Dynamics/BodyType.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	struct RigidBodyParameters
	{
	public:

		inline constexpr RigidBodyParameters& type(BodyType type) noexcept;

		inline constexpr RigidBodyParameters& mass(Mass mass) noexcept;
		inline constexpr RigidBodyParameters& momentOfInertia(MomentOfInertia inertia) noexcept;

		inline constexpr RigidBodyParameters& linearPosition(Length2 linearPosition) noexcept;
		inline constexpr RigidBodyParameters& angularPosition(Angle angularPosition) noexcept;
		//inline constexpr RigidBodyParameters& pose(const Transform& pose) noexcept;

		inline constexpr RigidBodyParameters& linearVelocity(LinearVelocity2 linearVelocity) noexcept;
		inline constexpr RigidBodyParameters& angularVelocity(AngularVelocity angularVelocity) noexcept;

		inline constexpr RigidBodyParameters& linearDamping(Frequency linearDamping) noexcept;
		inline constexpr RigidBodyParameters& angularDamping(Frequency angularDamping) noexcept;

		inline constexpr RigidBodyParameters& canSleep(bool canSleep) noexcept;
		inline constexpr RigidBodyParameters& awake(bool awake) noexcept;

		BodyType type_{ BodyType::Dynamic };
		InverseMass inverseMass_{ 1 };
		InverseMomentOfInertia inverseMomentOfInertia_{ 0 };
		Length2 linearPosition_{ Length2{ 0.0_m, 0.0_m } };
		Angle angularPosition_{ 0.0_deg };
		LinearVelocity2 linearVelocity_{ LinearVelocity2{ 0.0_mps, 0.0_mps } };
		AngularVelocity angularVelocity_{ 0.0_radps };
		Frequency linearDamping_{ 0.0_Hz };
		Frequency angularDamping_{ 0.0_Hz };
		bool canSleep_{ true };
		bool awake_{ true };
	};

	inline constexpr RigidBodyParameters& RigidBodyParameters::type(BodyType type) noexcept
	{
		type_ = type;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::mass(Mass mass) noexcept
	{
		inverseMass_ = Real{ 1 } / mass;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::momentOfInertia(MomentOfInertia inertia) noexcept
	{
		inverseMomentOfInertia_ = Real{ 1 } / inertia;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::linearPosition(Length2 linearPosition) noexcept
	{
		linearPosition_ = linearPosition;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::angularPosition(Angle angularPosition) noexcept
	{
		angularPosition_ = angularPosition;
		return *this;
	}

	//inline constexpr RigidBodyParameters& pose(const Transform& pose) noexcept

	inline constexpr RigidBodyParameters& RigidBodyParameters::linearVelocity(LinearVelocity2 linearVelocity) noexcept
	{
		linearVelocity_ = linearVelocity;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::angularVelocity(AngularVelocity angularVelocity) noexcept
	{
		angularVelocity_ = angularVelocity;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::linearDamping(Frequency linearDamping) noexcept
	{
		linearDamping_ = linearDamping;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::angularDamping(Frequency angularDamping) noexcept
	{
		angularDamping_ = angularDamping;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::canSleep(bool canSleep) noexcept
	{
		canSleep_ = canSleep;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::awake(bool awake) noexcept
	{
		awake_ = awake;
		return *this;
	}

}



#endif