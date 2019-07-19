#ifndef MIKROKOSMOS_PHYSICS_DYNAMICS_RIGIDBODY_HPP
#define MIKROKOSMOS_PHYSICS_DYNAMICS_RIGIDBODY_HPP

#include <Mikrokosmos/Physics/Dynamics/RigidBodyParameters.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos 
{

class RigidBody
{
public:

	RigidBody() noexcept;
	RigidBody(const RigidBodyParameters& parameters) noexcept;

	BodyType type() const noexcept;
	bool isStatic() const noexcept;
	bool isKinematic() const noexcept;
	bool isDynamic() const noexcept;

	Mass mass() const noexcept;
	MomentOfInertia momentOfInertia() const noexcept;
	Length2 centerOfMass() const noexcept;

	Length2 linearPosition() const noexcept;
	Angle angularPosition() const noexcept;

	LinearVelocity2 linearVelocity() const noexcept;
	AngularVelocity angularVelocity() const noexcept;

	Frequency linearDamping() const noexcept;
	Frequency angularDamping() const noexcept;

	bool canSleep() const noexcept;
	bool isAwake() const noexcept;

	//void setType(BodyType type) noexcept;

	void setMass(const Mass mass) noexcept;
	//void setMomentOfInertia(MomentOfInertia inertia) noexcept;

	//inline void setLinearPosition(Length2 linearPosition) noexcept;
	//inline void setAngularPosition(Angle angularPosition) noexcept;
	// void setPose(const Transform& pose) noexcept;

	void setVelocity(const LinearVelocity2 linearVelocity, const AngularVelocity angularVelocity) noexcept;
	void setLinearVelocity(const LinearVelocity2 linearVelocity) noexcept;
	void setAngularVelocity(const AngularVelocity angularVelocity) noexcept;

	void setLinearDamping(const Frequency linearDamping) noexcept;
	void setAngularDamping(const Frequency angularDamping) noexcept;

	void allowSleep() noexcept;
	void forbidSleep() noexcept;

	void sleep() noexcept;
	void awaken() noexcept;

	void applyForce(const Force2& force) noexcept;
	void applyForce(const Force2& force, const Length2& point) noexcept;
	void applyTorque(const Torque& torque) noexcept;

	void applyLinearImpulse(const LinearImpulse2& linearImpulse) noexcept;
	void applyLinearImpulse(const LinearImpulse2& linearImpulse, const Length2& point) noexcept;
	void applyAngularImpulse(const AngularImpulse& angularImpulse) noexcept;

	//void integrate(const Time duration);

private:

	BodyType type_;

	InverseMass inverseMass_;
	InverseMomentOfInertia inverseMomentOfInertia_;

	Length2 linearPosition_;
	Angle angularPosition_;

	LinearVelocity2 linearVelocity_;
	AngularVelocity angularVelocity_;

	Frequency linearDamping_;
	Frequency angularDamping_;

	bool canSleep_;
	bool isAwake_;

	Force2 totalForce_{ 0.0_N, 0.0_N };
	Torque totalTorque_{ 0.0_Nm };

};

}

#endif