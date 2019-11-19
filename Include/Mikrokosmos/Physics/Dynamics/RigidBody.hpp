#ifndef MIKROKOSMOS_PHYSICS_DYNAMICS_RIGIDBODY_HPP
#define MIKROKOSMOS_PHYSICS_DYNAMICS_RIGIDBODY_HPP

#include <Mikrokosmos/Math/Geometry/Pose.hpp>
#include <Mikrokosmos/Physics/Dynamics/RigidBodyParameters.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos 
{

class RigidBody
{
public:

	RigidBody() = delete;
	explicit RigidBody(const RigidBodyParameters& p) noexcept;

	/*BodyType type() const noexcept;
	bool isStatic() const noexcept;
	bool isKinematic() const noexcept;
	bool isDynamic() const noexcept;*/

	Mass mass() const noexcept;
	InverseMass inverseMass() const noexcept;
	MomentOfInertia momentOfInertia() const noexcept;
	InverseMomentOfInertia inverseMomentOfInertia() const noexcept;
	Length2 centerOfMass() const noexcept;

	Length2 position() const noexcept;
	Angle orientation() const noexcept;

	LinearVelocity2 linearVelocity() const noexcept;
	AngularVelocity angularVelocity() const noexcept;

	/*Frequency linearDamping() const noexcept;
	Frequency angularDamping() const noexcept;*/

	/*bool canSleep() const noexcept;
	bool isAwake() const noexcept;*/

	//void setType(BodyType type) noexcept;

	void setMass(Mass m) noexcept;
	void setInverseMass(InverseMass im) noexcept;
	void setMomentOfInertia(MomentOfInertia i) noexcept;
	void setInverseMomentOfInertia(InverseMomentOfInertia ii) noexcept;

	void setPose(const Pose& pose) noexcept;
	void setPosition(Length2 r) noexcept;
	void setOrientation(Angle theta) noexcept;

	void setVelocity(const LinearVelocity2& v, AngularVelocity omega) noexcept;
	void setLinearVelocity(const LinearVelocity2& v) noexcept;
	void setAngularVelocity(AngularVelocity omega) noexcept;

	/*void setLinearDamping(Frequency linearDamping) noexcept;
	void setAngularDamping(Frequency angularDamping) noexcept;*/

	/*void allowSleep() noexcept;
	void forbidSleep() noexcept;

	void sleep() noexcept;
	void awaken() noexcept;*/

	void applyForce(const Force2& f) noexcept;
	void applyForceAtPoint(const Force2& f, const Length2& r) noexcept;
	void applyTorque(Torque tau) noexcept;

	void applyLinearImpulse(const LinearImpulse2& j) noexcept;
	void applyLinearImpulseAtPoint(const LinearImpulse2& j, const Length2& r) noexcept;
	void applyAngularImpulse(AngularImpulse l) noexcept;

	void integrate(Time dt);

private:

	//BodyType type_;

	InverseMass inverseMass_;
	InverseMomentOfInertia inverseMomentOfInertia_;

	Pose pose_;

	LinearVelocity2 linearVelocity_;
	AngularVelocity angularVelocity_;

	Frequency linearDamping_;
	Frequency angularDamping_;

	/*bool canSleep_;
	bool isAwake_;*/

	Force2 totalForce_{ 0.0_N, 0.0_N };
	Torque totalTorque_{ 0.0_Nm };

	void clearForces() noexcept;

};

}

#endif