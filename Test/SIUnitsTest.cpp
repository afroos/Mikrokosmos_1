#include "catch.hpp"
#include <Mikrokosmos/Physics/SIUnits.hpp>

using namespace Mikrokosmos;

TEST_CASE("SIUnits: Prefixes") {
	REQUIRE(mega  == kilo * kilo);
	REQUIRE(milli == nano / micro);
	REQUIRE(nano / Real{ 1e3 } == femto * Real{ 1e3 });
	REQUIRE(peta * Real{ 1e-3 } == giga / Real{ 1e-3 });
}

TEST_CASE("SIUnits: Units") {
	constexpr auto joule = newton * meter;
	constexpr auto watt = joule / second;

	REQUIRE(joule == kilogram * (meter * meter) / (second * second));
	REQUIRE(watt == (newton * meter) / second);
	REQUIRE(watt == (newton * meter) * (radian / second));
	REQUIRE(watt == pascal * (meter * meter * meter) / second);
}

TEST_CASE("SIUnits: Quantities") {
	constexpr Force f1{ 1.5e3 };
	constexpr Force f2 = 1.5 * kilo * newton;
	constexpr Force f3 = 1.5_kN;
	constexpr Force f4 = 1500.0 * kilogram * meter / (second * second);
	constexpr Force f5 = 750.0 * newton + 750.0 * newton;
	constexpr auto f6 = 750.0_N + 750.0_N;
	constexpr Force f7 = Mass{ 300.0 } * LinearAcceleration{ 5.0 };
	constexpr auto f8 = -1500.0_N;

	REQUIRE(f1 == f2);
	REQUIRE(f2 == f3);
	REQUIRE(f3 == f4);
	REQUIRE(f4 == f5);
	REQUIRE(f5 == f6);
	REQUIRE(f6 == f7);
	REQUIRE(f7 == -f8);
	REQUIRE(36.0_kmph == 10.0_mps);

	using Energy = decltype(Force{} * Length{});
	using Power  = decltype(Energy{} / Time{});

	REQUIRE(Energy{ 12.0 } == Mass{ 3.0 } * LinearVelocity{ 2.0 } * LinearVelocity{ 2.0 });
	REQUIRE(Power{ 15.0 } == Force{ 30.0 } * Length{ 1.0 } / Time{ 2.0 });
}

TEST_CASE("SIUnits: Storage size")
{
	REQUIRE(sizeof(Length{}) == sizeof(Real));
	REQUIRE(sizeof(MomentOfInertia{}) == sizeof(Real));
	REQUIRE(sizeof(Mass{} *LinearVelocity{}) == sizeof(Real));
	REQUIRE(sizeof(67.0_m2) == sizeof(Real));
}


