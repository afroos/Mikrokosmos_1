#include "catch.hpp"
#include <Mikrokosmos/Physics/Material.hpp>

using namespace Mikrokosmos;

TEST_CASE("Material: Construction") 
{
	Material m{ 2.0_kgpm2, 0.5, 2.0, 1.0 };
}

TEST_CASE("Material: Acessors")
{
	Material m{ 2.0_kgpm2, 0.5, 2.0, 1.0 };

	REQUIRE(m.density() == 2.0_kgpm2);
	REQUIRE(m.restitution() == 0.5);
	REQUIRE(m.staticFriction() == 2.0);
	REQUIRE(m.dynamicFriction() == 1.0);

	m.setDensity(10.0_kgpm2);
	m.setRestitution(0.0);
	m.setStaticFriction(1.5);
	m.setDynamicFriction(0.05);

	REQUIRE(m.density() == 10.0_kgpm2);
	REQUIRE(m.restitution() == 0.0);
	REQUIRE(m.staticFriction() == 1.5);
	REQUIRE(m.dynamicFriction() == 0.05);
}




