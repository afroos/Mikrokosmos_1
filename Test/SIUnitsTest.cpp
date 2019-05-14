#include "catch.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
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

TEST_CASE("SIUnits: Vector quantities")
{
	LinearAcceleration2 a{ 3.5_mps2, -7.0_mps2 };
	Mass m = 2.0_kg;
	Force2 f1 = { 7.0_N, -14.0_N };
	Force2 f2;

	REQUIRE(f1 == m * a);

	f2 = +f1;
	REQUIRE(f2 == f1);

	f2 = -f1;
	REQUIRE(f2 == Force2{ -7.0_N, 14.0_N });

	f2 += Force2{ Force{-1.0}, Force{-1.0} };
	REQUIRE(f2 == Force2{ -8.0_N, 13.0_N });
	
	f2 -= Force2{ 0.5_N, 0.5_N };
	REQUIRE(f2 == Force2{ -8.5_N, 12.5_N });
	
	//f2 *= Real2{ -1.0, 2.0 };
	//REQUIRE(f2 == Force2{ 8.5_N, 25.0_N });
	/*
	f2 /= Force2{ 0.5, 1.0, -2.5 };
	REQUIRE(f2 == Force2{ 1.0, 1.0, 3.0 });

	f2 *= 3.0;
	REQUIRE(f2 == Force2{ 3.0, 3.0, 9.0 });

	f2 /= -1.5;
	REQUIRE(f2 == Force2{ -2.0, -2.0, -6.0 });

	f2 = f1 + f2;
	REQUIRE(f2 == Force2{ 0.0, -1.0, 4.0 });

	f2 = f1 - f2;
	REQUIRE(f2 == Force2{ -2.0, -3.0, 2.0 });

	f2 = f1 * 1.5;
	REQUIRE(f2 == Force2{ -1.5, -3.0, 4.5 });

	f2 = -1.5 * f1;
	REQUIRE(f2 == Force2{ 1.5, 3.0, -4.5 });

	f2 = f2 / 0.5;
	REQUIRE(f2 == Force2{ 2.0, 2.0, 2.0 });

	*/

	REQUIRE(f1 * 2.0 == Force2{ 14.0_N, -28.0_N });
}

TEST_CASE("SIUnits: Storage size")
{
	REQUIRE(sizeof(Length{}) == sizeof(Real));
	REQUIRE(sizeof(MomentOfInertia{}) == sizeof(Real));
	REQUIRE(sizeof(Mass{} *LinearVelocity{}) == sizeof(Real));
	REQUIRE(sizeof(67.0_m2) == sizeof(Real));
}

TEST_CASE("SIUnits: Ostream operator")
{
	LinearVelocity v{ -1.8 };
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << v;
	REQUIRE(ss.str() == "-1.8 m^1*kg^0*s^-1");
}


