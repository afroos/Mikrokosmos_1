#include <Mikrokosmos/Physics/Material.hpp>

#include <cassert>
#include <cmath>

namespace Mikrokosmos
{

Material::Material() noexcept
	: Material{ MaterialParameters{} }
{
}

Material::Material(const MaterialParameters& p) noexcept
{
	setDensity(p.density);
	setRestitution(p.restitution);
	setStaticFriction(p.staticFriction);
	setDynamicFriction(p.dynamicFriction);
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

void Material::setDensity(AreaDensity rho) noexcept
{
	assert(std::isfinite(rho.magnitude) && rho.magnitude >= 0.0);
	density_ = rho;
}

void Material::setRestitution(Real e) noexcept
{
	assert(e >= 0.0 && e <= 1.0);
	restitution_ = e;
}

void Material::setStaticFriction(Real mus) noexcept
{
	assert(std::isfinite(mus) && mus >= 0.0 && mus >= dynamicFriction_);
	staticFriction_ = mus;
}

void Material::setDynamicFriction(Real mud) noexcept
{
	assert(std::isfinite(mud) && mud >= 0.0 && mud <= staticFriction_);
	dynamicFriction_ = mud;
}

bool operator==(const Material& m1, const Material& m2) noexcept
{
	return (m1.density() == m2.density() &&
			m1.restitution() == m2.restitution() &&
			m1.staticFriction() == m2.staticFriction() &&
			m1.dynamicFriction() == m2.dynamicFriction());	
}

}