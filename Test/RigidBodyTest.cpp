#include "catch.hpp"
#include <Mikrokosmos/Physics/Dynamics/RigidBody.hpp>

using namespace Mikrokosmos;

TEST_CASE("RigidBody: Construction") {
	auto parameters = RigidBodyParameters{}.type(BodyType::Static);

	RigidBody b1{ parameters };
}



