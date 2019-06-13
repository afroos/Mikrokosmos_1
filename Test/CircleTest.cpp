#include "catch.hpp"
#include <Mikrokosmos/Math/Geometry/Circle.hpp>

using namespace Mikrokosmos;

TEST_CASE("Circle: Construction") 
{
	Circle c{1.0_m};
}

TEST_CASE("Circle: Accessors") 
{
	Circle c{ 6.6_m };

	REQUIRE(c.radius() == 6.6_m);

	c.setRadius(2.1_m);

	REQUIRE(c.radius() == 2.1_m);
}



