#include "catch.hpp"
#include <Mikrokosmos/Math/Geometry/Box.hpp>

using namespace Mikrokosmos;

TEST_CASE("Box: Construction") 
{
	Box b{ Length2{1.0_m, 2.0_m} };
}

TEST_CASE("Box: Accessors") 
{
	Box b{ Length2{0.5_m, 3.5_m} };

	REQUIRE(b.halfExtents().x() == 0.5_m);
	REQUIRE(b.halfExtents().y() == 3.5_m);

	b.setHalfExtents(Length2{ 4.5_m, 5.5_m });

	REQUIRE(b.halfExtents().x() == 4.5_m);
	REQUIRE(b.halfExtents().y() == 5.5_m);
}



