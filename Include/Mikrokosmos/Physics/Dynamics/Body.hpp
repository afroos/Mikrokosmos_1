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

	void integrate(Time duration);

	/*
	bool isAwake() const noexcept;

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

}

#endif