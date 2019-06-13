#include <Mikrokosmos/Physics/Material.hpp>

#include <cassert>
#include <cmath>

namespace Mikrokosmos
{

Material::Material(AreaDensity density, Real restitution, Real staticFriction, Real dynamicFriction) noexcept
{
	setDensity(density);
	setRestitution(restitution);
	setStaticFriction(staticFriction);
	setDynamicFriction(dynamicFriction);
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
	assert(std::isnormal(density.magnitude));
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

}