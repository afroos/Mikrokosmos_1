#include <Mikrokosmos/Physics/Dynamics/RigidBody.hpp>

namespace Mikrokosmos 
{

	RigidBody::RigidBody() noexcept
		: RigidBody{ RigidBodyParameters{} }
	{
	}

	RigidBody::RigidBody(const RigidBodyParameters& parameters) noexcept
	{

	}

	BodyType RigidBody::type() const noexcept
	{
		return type_;
	}

	bool RigidBody::isStatic() const noexcept
	{
		return type_ == BodyType::Static;
	}

	bool RigidBody::isKinematic() const noexcept
	{
		return type_ == BodyType::Kinematic;
	}

	bool RigidBody::isDynamic() const noexcept
	{
		return type_ == BodyType::Dynamic;
	}

	Mass RigidBody::mass() const noexcept
	{
		if (isZero(inverseMass_))
		{
			return Mass{ std::numeric_limits<Real>::infinity() };
		}
		else
		{
			return Real{ 1 } / inverseMass_;
		}
	}

	MomentOfInertia RigidBody::momentOfInertia() const noexcept
	{
		if (isZero(inverseMomentOfInertia_))
		{
			return MomentOfInertia{ std::numeric_limits<Real>::infinity() };
		}
		else
		{
			return Real{ 1 } / inverseMomentOfInertia_;
		}
	}

	Length2 RigidBody::centerOfMass() const noexcept
	{
		return linearPosition();
	}

	Length2 RigidBody::linearPosition() const noexcept
	{
		return pose_.translation();
	}

	Angle RigidBody::angularPosition() const noexcept
	{
		//return pose_.rotation.angle();
		return Angle();
	}

	LinearVelocity2 RigidBody::linearVelocity() const noexcept
	{
		return linearVelocity_;
	}

	AngularVelocity RigidBody::angularVelocity() const noexcept
	{
		return angularVelocity_;
	}

	Frequency RigidBody::linearDamping() const noexcept
	{
		return linearDamping_;
	}

	Frequency RigidBody::angularDamping() const noexcept
	{
		return angularDamping_;
	}

	bool RigidBody::canSleep() const noexcept
	{
		return canSleep_;
	}

	bool RigidBody::isAwake() const noexcept
	{
		return isAwake_;
	}

	//void Body::setType(BodyType type) noexcept
	//{
	//	//
	//}

	void RigidBody::setMass(Mass mass) noexcept
	{
		assert(mass > 0.0_kg);
		inverseMass_ = Real{ 1 } / mass;
	}

	void RigidBody::setMomentOfInertia(MomentOfInertia inertia) noexcept
	{
		assert(inertia > 0.0_kgm2);
		inverseMomentOfInertia_ = Real{ 1 } / inertia;
	}

	void RigidBody::setVelocity(const LinearVelocity2& linearVelocity, AngularVelocity angularVelocity) noexcept
	{
		assert(isFinite(linearVelocity) && isFinite(angularVelocity));

		if (!isZero(linearVelocity) || !isZero(angularVelocity))
		{
			if (isStatic())
			{
				return;
			}
			awaken();
		}
		linearVelocity_ = linearVelocity;
		angularVelocity_ = angularVelocity;
	}

	void RigidBody::setLinearVelocity(const LinearVelocity2& linearVelocity) noexcept
	{
		setVelocity(linearVelocity, angularVelocity_);
	}

	void RigidBody::setAngularVelocity(AngularVelocity angularVelocity) noexcept
	{
		setVelocity(linearVelocity_, angularVelocity);
	}

	// velocity = velocity / (1 + damping*dt)					  TUTORIAL  Hz
	// velocity *= real_pow(linearDamping, duration);             CYCLONE   ?
	// v *= b2Clamp(1.0f - h * b->m_linearDamping, 0.0f, 1.0f);   BOX2D  Hz
	// velocity.linear  /= Real{1 + h * body.GetLinearDamping()}; PLAYRHO    Hz
	// m_linearVelocity *= btPow(btScalar(1) - m_linearDamping, timeStep); BULLET   ?
	// linearVelocity*=oneMinusLinearDampingTimesDT;     PHYSX  Hz
	// Apply damping. PLAYRHO
		// Ordinary differential equation: dv/dt + c * v = 0
		//                       Solution: v(t) = v0 * exp(-c * t)
		// Time step: v(t + dt) = v0 * exp(-c * (t + dt)) = v0 * exp(-c * t) * exp(-c * dt) = v * exp(-c * dt)
		// v2 = exp(-c * dt) * v1
		// Pade approximation (see https://en.wikipedia.org/wiki/Pad%C3%A9_approximant ):
		// v2 = v1 * 1 / (1 + c * dt)
	void RigidBody::setLinearDamping(Frequency linearDamping) noexcept
	{
		assert(isNonNegative(linearDamping));
		linearDamping_ = linearDamping;
	}

	void RigidBody::setAngularDamping(Frequency angularDamping) noexcept
	{
		assert(isNonNegative(angularDamping));
		angularDamping_ = angularDamping;
	}

	void RigidBody::allowSleep() noexcept
	{
		canSleep_ = true;
	}

	void RigidBody::forbidSleep() noexcept
	{
		if (!isStatic())
		{
			canSleep_ = false;
			if (!isAwake())
			{
				awaken();
			}
		}
	}

	void RigidBody::sleep() noexcept
	{
		if (canSleep() && isAwake())
		{
			isAwake_ = false;
			setVelocity({0.0_mps, 0.0_mps}, 0.0_radps);
		}
	}

	void RigidBody::awaken() noexcept
	{
		if (!isStatic() && !isAwake())
		{
			isAwake_ = true;
		}
	}

	void RigidBody::applyForce(const Force2& force) noexcept
	{
		assert(isFinite(force));
		totalForce_ += force;
	}

	void RigidBody::applyForceAtPoint(const Force2& force, const Length2& point) noexcept
	{
		applyForce(force);
		applyTorque(perpDot(point - centerOfMass(), force));
	}

	void RigidBody::applyTorque(Torque torque) noexcept
	{
		assert(isFinite(torque));
		totalTorque_ += torque;
	}

	void RigidBody::applyLinearImpulse(const LinearImpulse2& linearImpulse) noexcept
	{
		assert(isFinite(linearImpulse));
		auto newLinearVelocity = linearVelocity_ + linearImpulse * inverseMass_;
		setLinearVelocity(newLinearVelocity);
	}

	void RigidBody::applyLinearImpulseAtPoint(const LinearImpulse2& linearImpulse, const Length2& point) noexcept
	{
		applyLinearImpulse(linearImpulse);
		applyAngularImpulse(perpDot(point - centerOfMass(), linearImpulse));
	}

	void RigidBody::applyAngularImpulse(AngularImpulse angularImpulse) noexcept
	{
		assert(isFinite(angularImpulse));
		auto newAngularVelocity = angularVelocity_ + angularImpulse * inverseMomentOfInertia_;
		setAngularVelocity(newAngularVelocity);
	}

/*


Body::integrate(Time duration)
{
	assert(duration >= 0.0_s);
	if (inverseMass_ <= InverseMass{ 0 }) return;

	const auto linearAcceleration = totalForce_ * inverseMass_;
	const auto angularAcceleration = totalTorque_ * inverseMomentOfInertia_;

	linearVelocity_ += linearAcceleration * duration;
	angularVelocity_ += angularAcceleration * duration;

	// drag

	linearPosition_ += linearVelocity_ * duration;
	angularPosition_ += angularPosition * duration;

	totalForce_ = 0.0_N;
	totalTorque_ = 0.0_Nm;
}*/

}
