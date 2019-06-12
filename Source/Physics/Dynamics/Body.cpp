#include <Mikrokosmos/Physics/Dynamics/Body.hpp>

namespace Mikrokosmos 
{

void Body::setMass(Mass mass) noexcept
{
	assert(mass.magnitude > Real{ 0 });
	inverseMass_ = Real{ 1 } / mass;
}

Mass Body::mass() const noexcept
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

MomentOfInertia Body::momentOfInertia() const noexcept
{
	return Real{ 1 } / inverseMomentOfInertia_;
}

Length2 Body::centerOfMass() const noexcept
{
	return linearPosition_;
}

void Body::applyForce(Force2& force) noexcept
{
	totalForce_ += force;
}

void Body::applyForceAtPoint(Force2& force, Length2& point) noexcept
{
	const Length2 positionVector = point - centerOfMass();
	totalForce_ += force;
	totalTorque_ += perpDot(positionVector, force);
}

void Body::applyTorque(Torque& torque) noexcept
{
	totalTorque_ += torque;
}

Length2 Body::linearPosition() const noexcept
{
	return linearPosition_;
}

Angle Body::angularPosition() const noexcept
{
	return angularPosition_;
}

LinearVelocity2 Body::linearVelocity() const noexcept
{
	return linearVelocity_;
}

AngularVelocity Body::angularVelocity() const noexcept
{
	return angularVelocity_;
}

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
}

}

#endif