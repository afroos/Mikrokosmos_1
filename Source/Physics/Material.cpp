#include <Mikrokosmos/Physics/Material.hpp>

#include <cassert>
#include <cmath>

namespace Mikrokosmos
{

Material::Material(MaterialParameters parameters) noexcept
{
	setDensity(parameters.density_);
	setRestitution(parameters.restitution_);
	setStaticFriction(parameters.staticFriction_);
	setDynamicFriction(parameters.dynamicFriction_);
}

AreaDensity Material::density() const noexcept
{
	return density_;
}

Real Material::restitution() const noexcept
{
	return restitution_;
}

Real Material::staticFriction() const noexcept
{
	return staticFriction_;
}

Real Material::dynamicFriction() const noexcept
{
	return dynamicFriction_;
}

void Material::setDensity(AreaDensity density) noexcept
{
	assert(std::isfinite(density.magnitude) && density.magnitude >= 0.0);
	density_ = density;
}

void Material::setRestitution(Real restitution) noexcept
{
	assert(restitution >= 0.0 && restitution <= 1.0);
	restitution_ = restitution;
}

void Material::setStaticFriction(Real staticFriction) noexcept
{
	assert(std::isfinite(staticFriction) && staticFriction >= 0.0 && staticFriction >= dynamicFriction_);
	staticFriction_ = staticFriction;
}

void Material::setDynamicFriction(Real dynamicFriction) noexcept
{
	assert(std::isfinite(dynamicFriction) && dynamicFriction >= 0.0 && dynamicFriction <= staticFriction_);
	dynamicFriction_ = dynamicFriction;
}

bool operator==(const Material& m1, const Material& m2) noexcept
{
	return (m1.density() == m2.density() &&
			m1.restitution() == m2.restitution() &&
			m1.staticFriction() == m2.staticFriction() &&
			m1.dynamicFriction() == m2.dynamicFriction());	
}

}