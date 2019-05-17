#ifndef MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_HPP
#define MIKROKOSMOS_PHYSICS_DYNAMICS_BODY_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos 
{

class Body
{
public:
	
	Mass mass() const noexcept;
	InverseMass inverseMass() const noexcept;
	/*
	MomentOfInertia momentOfInertia() const noexcept;
	InverseMomentOfInertia inverseMomentOfInertia() const noexcept;

	Length2 linearPosition() const noexcept;
	Angle angularPosition() const noexcept;

	LinearVelocity2 linearVelocity() const noexcept;
	AngularVelocity angularVelocity() const noexcept;

	LinearAcceleration2 linearAcceleration() const noexcept;
	AngularAcceleration angularAcceleration() const noexcept;

	void integrate(Time duration);

	void setPosition(LinearPosition2 p, AngularPosition theta) noexcept;
	void setVelocity(LinearVelocity2 v, AngularVelocity omega) noexcept;
	void setAcceleration(LinearAcceleration2 a, AngularAcceleration alpha) noexcept;

	void awaken() noexcept;
	void sleep() noexcept;

	Length2 worldCenterOfMass() const noexcept;
	Length2 localCenterOfMass() const noexcept;

	bool isAwake() const noexcept;

	void setForce(Force2& force, Length2 point);
	void applyForce(Force2& force, Length2 point);
	void applyForceAtCM(Force2& force);

	void setTorque(Torque& torque);
	void applyTorque(Torque& torque);*/

private:

	InverseMass inverseMass_ = InverseMass{ 0 };
	InverseMomentOfInertia inverseMomentOfInertia_ = InverseMomentOfInertia{ 0 };

	Length2 linearPosition = { 0.0_m, 0.0_m };
	Angle angularPosition = 0.0_rad;

	LinearVelocity2 linearVelocity = { 0.0_mps, 0.0_mps };
	AngularVelocity angularVelocity = 0.0_radps;

	LinearAcceleration2 linearAcceleration = { 0.0_mps2, 0.0_mps2 };
	AngularAcceleration angularAcceleration =  0.0_radps2;

	Force2 totalForce = { 0.0_N, 0.0_N };;
	Torque totalTorque = 0.0_Nm;

	bool isAwake = true;

};

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

inline InverseMass Body::inverseMass() const noexcept
{
	return inverseMass_;
}

}

#endif