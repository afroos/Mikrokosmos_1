#include "catch.hpp"
#include <Mikrokosmos/Physics/Material.hpp>

#include <memory>

using namespace Mikrokosmos;

TEST_CASE("Material: Construction") 
{
	auto parameters = MaterialParameters{}.density(2.0_kgpm2)
										  .restitution(0.5)
									      .staticFriction(2.0)
										  .dynamicFriction(1.0);

	Material m1{parameters};

	Material m2 = MaterialParameters{}.density(2.0_kgpm2)
									  .restitution(0.5)
									  .staticFriction(2.0)
									  .dynamicFriction(1.0);

	Material m3{ MaterialParameters{}.density(2.0_kgpm2)
									 .restitution(0.5)
									 .staticFriction(2.0)
									 .dynamicFriction(1.0) };

	auto m4 = std::make_shared<Material>(MaterialParameters{}.density(2.0_kgpm2)
															 .restitution(0.5)
															 .staticFriction(2.0)
															 .dynamicFriction(1.0));

	REQUIRE(m1 == m2);
	REQUIRE(m2 == m3);
	REQUIRE(m3 == *m4);
}

TEST_CASE("Material: Acessors")
{
	Material m{ MaterialParameters{}.density(2.0_kgpm2)
									.restitution(0.5)
									.staticFriction(2.0)
									.dynamicFriction(1.0) };

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



