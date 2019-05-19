#ifndef MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_HPP
#define MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos 
{

class Body
{
public:
	
	void setMass(Mass mass) noexcept;
	//void setMomentOfInertia(MomentOfInertia inertia) noexcept;

	Mass mass() const noexcept;
	MomentOfInertia momentOfInertia() const noexcept;

	Length2 centerOfMass() const noexcept;

	void applyForce(Force2& force) noexcept;
	void applyForceAtPoint(Force2& force, Length2& point) noexcept;
	void applyTorque(Torque& torque) noexcept;

	Length2 linearPosition() const noexcept;
	Angle angularPosition() const noexcept;

	LinearVelocity2 linearVelocity() const noexcept;
	AngularVelocity angularVelocity() const noexcept;
	
	//bool isAwake() const noexcept;

	/*
	void integrate(Time duration);

	void setPosition(LinearPosition2 p, AngularPosition theta) noexcept;
	void setVelocity(LinearVelocity2 v, AngularVelocity omega) noexcept;
	void setAcceleration(LinearAcceleration2 a, AngularAcceleration alpha) noexcept;

	void awaken() noexcept;
	void sleep() noexcept; */

private:

	InverseMass inverseMass_{ 0 };
	InverseMomentOfInertia inverseMomentOfInertia_{ 0 };

	Length2 linearPosition_{ 0.0_m, 0.0_m };
	Angle angularPosition_{ 0.0_rad };

	LinearVelocity2 linearVelocity_{ 0.0_mps, 0.0_mps };
	AngularVelocity angularVelocity_{ 0.0_radps };

	Force2 totalForce_{ 0.0_N, 0.0_N };
	Torque totalTorque_{ 0.0_Nm };

	//Frequency linearDamping;
	//Frequency angularDamping;

	//bool isAwake_{ true };

};

inline void Body::setMass(Mass mass) noexcept
{
	assert(mass.magnitude > Real{ 0 });
	inverseMass_ = Real{ 1 } / mass;
}

inline Mass Body::mass() const noexcept
{
	if (inverseMass_ == InverseMass{ 0 }) 
	{
		return Mass{ std::numeric_limits<Real>::max() };
	} 
	else 
	{
		return Real{ 1 } / inverseMass_;
	}
}

inline MomentOfInertia Body::momentOfInertia() const noexcept
{
	return Real{ 1 } / inverseMomentOfInertia_;
}

inline Length2 Body::centerOfMass() const noexcept
{
	return linearPosition_;
}

inline void Body::applyForce(Force2& force) noexcept
{
	applyForceAtPoint(force, centerOfMass());
}

inline void Body::applyForceAtPoint(Force2& force, Length2& point) noexcept
{
	const auto positionVector = point - centerOfMass();
	totalForce_ += force;
	totalTorque_ += perpDot(positionVector, force);
}

inline void Body::applyTorque(Torque& torque) noexcept
{
	totalTorque_ += torque;
}

inline Length2 Body::linearPosition() const noexcept
{
	return linearPosition_;
}

inline Angle Body::angularPosition() const noexcept
{
	return angularPosition_;
}

inline LinearVelocity2 Body::linearVelocity() const noexcept
{
	return linearVelocity_;
}

inline AngularVelocity Body::angularVelocity() const noexcept
{
	return angularVelocity_;
}

//inline bool Body::isAwake() const noexcept
//{
//	return isAwake_;
//}

}

#endif