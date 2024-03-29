#include "catch.hpp"
#include <Mikrokosmos/Physics/Material.hpp>

#include <memory>

using namespace Mikrokosmos;

TEST_CASE("Material: Construction") 
{
	auto parameters = MaterialParameters{}.withDensity(2.0_kgpm2)
										  .withRestitution(0.5)
									      .withStaticFriction(2.0)
										  .withDynamicFriction(1.0);

	Material m1{parameters};

	Material m2{ MaterialParameters{}.withDensity(2.0_kgpm2)
									 .withRestitution(0.5)
								     .withStaticFriction(2.0)
									 .withDynamicFriction(1.0) };

	auto m3 = std::make_shared<Material>(MaterialParameters{}.withDensity(2.0_kgpm2)
															 .withRestitution(0.5)
															 .withStaticFriction(2.0)
															 .withDynamicFriction(1.0));

	REQUIRE(m1 == m2);
	REQUIRE(m2 == *m3);
}

TEST_CASE("Material: Acessors")
{
	Material m;

	REQUIRE(m.density() == 0.0_kgpm2);
	REQUIRE(m.restitution() == 0.0);
	REQUIRE(m.staticFriction() == 0.5);
	REQUIRE(m.dynamicFriction() == 0.2);

	m.setDensity(10.0_kgpm2);
	m.setRestitution(0.0);
	m.setStaticFriction(1.5);
	m.setDynamicFriction(0.05);

	REQUIRE(m.density() == 10.0_kgpm2);
	REQUIRE(m.restitution() == 0.0);
	REQUIRE(m.staticFriction() == 1.5);
	REQUIRE(m.dynamicFriction() == 0.05);
}

