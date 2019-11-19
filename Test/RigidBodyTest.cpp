#include "catch.hpp"
#include <Mikrokosmos/Physics/Dynamics/RigidBody.hpp>

using namespace Mikrokosmos;

TEST_CASE("RigidBody: Construction") {
	auto parameters = RigidBodyParameters{}.withMass(5.0_kg)
										   .withPosition(Length2{1.0_m, -2.5_m});

	RigidBody b1{ parameters };
}



