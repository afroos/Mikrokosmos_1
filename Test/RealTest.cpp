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

TEST_CASE("Real: Equality")
{
	Real tol = Real{ 0.00001f };
	REQUIRE(nearlyEqual(Real{ -1234.5678f }, Real{ -1234.5678f }));
	REQUIRE(nearlyEqual(Real{ 1000000.0f }, Real{ 1000001.0f }, tol));
	REQUIRE(!nearlyEqual(Real{ -10001.0f }, Real{ -10000.0f }, tol));
	REQUIRE(nearlyEqual(Real{ 1.0000002f }, Real{ 1.0000001f }, tol));
	REQUIRE(!nearlyEqual(Real{ -1.0001f }, Real{ -1.0002f }, tol));
	REQUIRE(nearlyEqual(Real{ 0.000000001000001f }, Real{ 0.000000001000002f }, tol));
	REQUIRE(nearlyEqual(Real{ -0.000000001000001f }, Real{ -0.000000001000002f }, tol));
	REQUIRE(nearlyEqual(Real{ 0.3f }, Real{ 0.30000003f }, tol));
	REQUIRE(nearlyEqual(Real{ -0.00000001f }, Real{ 0.0f }, tol));
	REQUIRE(!nearlyEqual(Real{ 1.0000001f }, Real{ -1.0f }, tol));
	REQUIRE(!nearlyEqual(Real{ -0.00000001f }, Real{ -1.0f }, tol));
}