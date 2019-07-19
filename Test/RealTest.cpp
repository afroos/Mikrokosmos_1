#include "catch.hpp"
#include <Mikrokosmos/Common/Real.hpp>

using namespace Mikrokosmos;

TEST_CASE("Real: Operators") 
{
	Real r0 = 3.5;
	REQUIRE(isFinite(r0));

	Real r1 = std::numeric_limits<Real>::quiet_NaN();
	REQUIRE(!isFinite(r1));

	Real r2 = std::numeric_limits<Real>::infinity();
	REQUIRE(!isFinite(r2));

	Real r3 = 0.0;
	REQUIRE(isZero(r3));
	REQUIRE(isNonPositive(r3));
	REQUIRE(isNonNegative(r3));

	Real r4 = 66.5;
	REQUIRE(isPositive(r4));
	REQUIRE(isNonNegative(r4));

	Real r5 = -66.5;
	REQUIRE(isNegative(r5));
	REQUIRE(isNonPositive(r5));

}



