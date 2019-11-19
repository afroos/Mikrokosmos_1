#ifndef MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_PARAMETERS_HPP
#define MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_PARAMETERS_HPP

//#include <Mikrokosmos/Physics/Dynamics/BodyType.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	struct RigidBodyParameters
	{
	public:

		//inline constexpr RigidBodyParameters& type(BodyType type) noexcept;

		inline constexpr RigidBodyParameters& withMass(Mass m) noexcept;
		inline constexpr RigidBodyParameters& withMomentOfInertia(MomentOfInertia i) noexcept;

		inline constexpr RigidBodyParameters& withPosition(Length2 r) noexcept;
		inline constexpr RigidBodyParameters& withOrientation(Angle theta) noexcept;
		inline constexpr RigidBodyParameters& withPose(const Pose& pose) noexcept;

		inline constexpr RigidBodyParameters& withLinearVelocity(LinearVelocity2 v) noexcept;
		inline constexpr RigidBodyParameters& withAngularVelocity(AngularVelocity omega) noexcept;

		/*inline constexpr RigidBodyParameters& linearDamping(Frequency linearDamping) noexcept;
		inline constexpr RigidBodyParameters& angularDamping(Frequency angularDamping) noexcept;*/

		/*inline constexpr RigidBodyParameters& canSleep(bool canSleep) noexcept;
		inline constexpr RigidBodyParameters& awake(bool awake) noexcept;*/

		//BodyType type_{ BodyType::Dynamic };
		InverseMass inverseMass{ 1 };
		InverseMomentOfInertia inverseMomentOfInertia{ 0 };
		Length2 position{ Length2{ 0.0_m, 0.0_m } };
		Angle orientation{ 0.0_deg };
		LinearVelocity2 linearVelocity{ LinearVelocity2{ 0.0_mps, 0.0_mps } };
		AngularVelocity angularVelocity{ 0.0_radps };
		/*Frequency linearDamping_{ 0.0_Hz };
		Frequency angularDamping_{ 0.0_Hz };*/
		/*bool canSleep_{ true };
		bool awake_{ true };*/
	};

	//inline constexpr RigidBodyParameters& RigidBodyParameters::type(BodyType type) noexcept
	//{
	//	type_ = type;
	//	return *this;
	//}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withMass(Mass m) noexcept
	{
		inverseMass = Real{ 1 } / m;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withMomentOfInertia(MomentOfInertia i) noexcept
	{
		inverseMomentOfInertia = Real{ 1 } / i;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withPosition(Length2 r) noexcept
	{
		position = r;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withOrientation(Angle theta) noexcept
	{
		orientation = theta;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withPose(const Pose& pose) noexcept
	{
		withPosition(pose.position());
		withOrientation(pose.orientation().angle());
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withLinearVelocity(LinearVelocity2 v) noexcept
	{
		linearVelocity = v;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::withAngularVelocity(AngularVelocity omega) noexcept
	{
		angularVelocity = omega;
		return *this;
	}

	/*inline constexpr RigidBodyParameters& RigidBodyParameters::linearDamping(Frequency linearDamping) noexcept
	{
		linearDamping_ = linearDamping;
		return *this;
	}

	inline constexpr RigidBodyParameters& RigidBodyParameters::angularDamping(Frequency angularDamping) noexcept
	{
		angularDamping_ = angularDamping;
		return *this;
	}*/

	//inline constexpr RigidBodyParameters& RigidBodyParameters::canSleep(bool canSleep) noexcept
	//{
	//	canSleep_ = canSleep;
	//	return *this;
	//}

	//inline constexpr RigidBodyParameters& RigidBodyParameters::awake(bool awake) noexcept
	//{
	//	awake_ = awake;
	//	return *this;
	//}

}



#endif