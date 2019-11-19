#include <Mikrokosmos/Physics/Dynamics/RigidBody.hpp>

namespace Mikrokosmos 
{

	RigidBody::RigidBody(const RigidBodyParameters& p) noexcept
	{
		setMass(Real{ 1 } / p.inverseMass);
	}

	//BodyType RigidBody::type() const noexcept
	//{
	//	return type_;
	//}

	//bool RigidBody::isStatic() const noexcept
	//{
	//	return type_ == BodyType::Static;
	//}

	//bool RigidBody::isKinematic() const noexcept
	//{
	//	return type_ == BodyType::Kinematic;
	//}

	//bool RigidBody::isDynamic() const noexcept
	//{
	//	return type_ == BodyType::Dynamic;
	//}

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

	InverseMass RigidBody::inverseMass() const noexcept
	{
		return inverseMass_;
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

	InverseMomentOfInertia RigidBody::inverseMomentOfInertia() const noexcept
	{
		return inverseMomentOfInertia_;
	}

	Length2 RigidBody::centerOfMass() const noexcept
	{
		return position();
	}

	Length2 RigidBody::position() const noexcept
	{
		return pose_.position();
	}

	Angle RigidBody::orientation() const noexcept
	{
		return pose_.orientation().angle();
	}

	LinearVelocity2 RigidBody::linearVelocity() const noexcept
	{
		return linearVelocity_;
	}

	AngularVelocity RigidBody::angularVelocity() const noexcept
	{
		return angularVelocity_;
	}

	/*Frequency RigidBody::linearDamping() const noexcept
	{
		return linearDamping_;
	}

	Frequency RigidBody::angularDamping() const noexcept
	{
		return angularDamping_;
	}*/

	/*bool RigidBody::canSleep() const noexcept
	{
		return canSleep_;
	}

	bool RigidBody::isAwake() const noexcept
	{
		return isAwake_;
	}*/

	//void Body::setType(BodyType type) noexcept
	//{
	//	//
	//}

	void RigidBody::setMass(Mass m) noexcept
	{
		setInverseMass(Real{ 1 } / m);
	}

	void RigidBody::setInverseMass(InverseMass im) noexcept
	{
		assert(isNonNegative(im) && isFinite(im));
		inverseMass_ = im;
	}

	void RigidBody::setMomentOfInertia(MomentOfInertia i) noexcept
	{
		setInverseMomentOfInertia(Real{ 1 } / i);
	}

	void RigidBody::setInverseMomentOfInertia(InverseMomentOfInertia ii) noexcept
	{
		assert(isNonNegative(ii) && isFinite(ii));
		inverseMomentOfInertia_ = ii;
	}

	void RigidBody::setPose(const Pose& pose) noexcept
	{
		assert(isFinite(pose));
		
		pose_ = pose;
	}

	void RigidBody::setPosition(Length2 r) noexcept
	{
		setPose(Pose{ r, pose_.orientation() });
	}

	void RigidBody::setOrientation(Angle theta) noexcept
	{
		setPose(Pose{ pose_.position(), Rotation2{theta} });
	}

	void RigidBody::setVelocity(const LinearVelocity2& v, AngularVelocity omega) noexcept
	{
		assert(isFinite(v) && isFinite(omega));

		//if (!isZero(linearVelocity) || !isZero(angularVelocity))
		//{
		//	if (isStatic())
		//	{
		//		return;
		//	}
		//	awaken();
		//}
		linearVelocity_ = v;
		angularVelocity_ = omega;
	}

	void RigidBody::setLinearVelocity(const LinearVelocity2& v) noexcept
	{
		setVelocity(v, angularVelocity_);
	}

	void RigidBody::setAngularVelocity(AngularVelocity omega) noexcept
	{
		setVelocity(linearVelocity_, omega);
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
	//void RigidBody::setLinearDamping(Frequency linearDamping) noexcept
	//{
	//	assert(isNonNegative(linearDamping));
	//	linearDamping_ = linearDamping;
	//}

	//void RigidBody::setAngularDamping(Frequency angularDamping) noexcept
	//{
	//	assert(isNonNegative(angularDamping));
	//	angularDamping_ = angularDamping;
	//}

	/*void RigidBody::allowSleep() noexcept
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
	}*/

	//void RigidBody::sleep() noexcept
	//{
	//	if (canSleep() && isAwake())
	//	{
	//		isAwake_ = false;
	//		setVelocity({0.0_mps, 0.0_mps}, 0.0_radps);
	//	}
	//}

	//void RigidBody::awaken() noexcept
	//{
	//	if (!isStatic() && !isAwake())
	//	{
	//		isAwake_ = true;
	//	}
	//}

	void RigidBody::applyForce(const Force2& f) noexcept
	{
		assert(isFinite(f));
		totalForce_ += f;
	}

	void RigidBody::applyForceAtPoint(const Force2& f, const Length2& r) noexcept
	{
		applyForce(f);
		applyTorque(perpDot(r - centerOfMass(), f));
	}

	void RigidBody::applyTorque(Torque tau) noexcept
	{
		assert(isFinite(tau));
		totalTorque_ += tau;
	}

	void RigidBody::applyLinearImpulse(const LinearImpulse2& j) noexcept
	{
		assert(isFinite(j));
		auto v = linearVelocity_ + j * inverseMass_;
		setLinearVelocity(v);
	}

	void RigidBody::applyLinearImpulseAtPoint(const LinearImpulse2& j, const Length2& r) noexcept
	{
		applyLinearImpulse(j);
		applyAngularImpulse(perpDot(r - centerOfMass(), j));
	}

	void RigidBody::applyAngularImpulse(AngularImpulse l) noexcept
	{
		assert(isFinite(l));
		auto omega = angularVelocity_ + l * inverseMomentOfInertia_;
		setAngularVelocity(omega);
	}

	void RigidBody::integrate(Time dt)
	{
		if (isZero(inverseMass_)) return;

		const auto linearAcceleration = totalForce_ * inverseMass_;
		const auto angularAcceleration = totalTorque_ * inverseMomentOfInertia_;

		linearVelocity_ += linearAcceleration * dt;
		angularVelocity_ += angularAcceleration * dt;

		// drag

		pose_.translate(linearVelocity_ * dt);
		pose_.rotate(angularVelocity_ * dt);

		clearForces();
	}

	void RigidBody::clearForces() noexcept
	{
		totalForce_ = Force2{ 0.0_N, 0.0_N };
		totalTorque_ = 0.0_Nm;
	}

}
