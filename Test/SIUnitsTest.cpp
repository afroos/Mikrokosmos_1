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
	REQUIRE(watt == joule * (1 / second));
	REQUIRE(watt == (newton * meter) / second);
	REQUIRE(watt == (newton * meter) * (radian / second));
	REQUIRE(watt == pascal * (meter * meter * meter) / second);
}

TEST_CASE("SIUnits: Quantity constants")
{
	REQUIRE(36.0 * kilometer / hour == 10.0 * meter / second);
	REQUIRE(36.0_kmph == 10.0_mps);
}

TEST_CASE("SIUnits: Quantity construction") 
{
	constexpr Force f1;
	constexpr Force f2{};
	constexpr Force f3{ 0.0 };
	constexpr Force f4{ 0.0_N };
	constexpr Force f5{ 1.5e3 };
	constexpr Force f6{ 1500.0_N };
	constexpr Force f7(1.5_kN);
	constexpr Force f8 = 1.5 * kilo * newton;
	constexpr Force f9 = 1.5 * kilonewton;
	constexpr Force f10 = 1.5_kN;
	constexpr Force f11{ f10 };
	constexpr Force f12{ std::move(f10) };
	constexpr Force f13 = Mass{ 300.0 } *LinearAcceleration{ 5.0 };
	constexpr auto f14 = -1500.0_N;

	REQUIRE(f1 == f2);
	REQUIRE(f2 == f3);
	REQUIRE(f3 == f4);
	REQUIRE(f5 == f6);
	REQUIRE(f6 == f7);
	REQUIRE(f7 == f8);
	REQUIRE(f8 == f9);
	REQUIRE(f9 == f10);
	REQUIRE(f10 == f11);
	REQUIRE(f11 == f12);
	REQUIRE(f12 == f13);
	REQUIRE(f13 == -f14);
}

TEST_CASE("SIUnits: Quantity definition")
{
	using Energy = decltype(Force{} *Length{});
	using Power  = decltype(Energy{} / Time{});

	REQUIRE(Energy{ 12.0 } == Mass{ 3.0 } *LinearVelocity{ 2.0 } *LinearVelocity{ 2.0 });
	REQUIRE(Power{ 15.0 } == Force{ 30.0 } *Length{ 1.0 } / Time{ 2.0 });
}

TEST_CASE("SIUnits: Quantity operators")
{
	constexpr LinearVelocity v1 = 5.0_mps;
	constexpr auto v2 = -14.0 * meter / second;
	LinearVelocity v3;
	Frequency f1 = 0.4_Hz;
	Time t1 = 2.5_s;
	LinearAcceleration a1;
	constexpr LinearAcceleration a2{ 3.0 };

	v3 = +v1;
	REQUIRE(v3 == v1);

	v3 = -v1;
	REQUIRE(v3 == -5.0_mps);

	v3 += 4.0_mps;
	REQUIRE(v3 == -1.0_mps);

	v3 -= 2.0_mps;
	REQUIRE(v3 == -3.0_mps);
	
	v3 *= 3.0;
	REQUIRE(v3 == -9.0_mps);
	
	v3 /= -4.5;
	REQUIRE(v3 == 2.0_mps);
	
	v3 = v1 + v2;
	REQUIRE(v3 == -9.0_mps);

	v3 = v1 - v2;
	REQUIRE(v3 == 19.0_mps);
	
	a1 = v1 * f1;
	REQUIRE(a1 == 2.0_mps2);

	a1 = a2 * -4.0;
	REQUIRE(a1 == -12.0_mps2);

	a1 = -4.0 * a2;
	REQUIRE(a1 == -12.0_mps2);

	a1 = -12.0 * (meter / (second * second));
	REQUIRE(a1 == -12.0_mps2);

	a1 = (meter / (second * second)) * -12.0;
	REQUIRE(a1 == -12.0_mps2);

	a1 = 18.0_mps * hertz;
	REQUIRE(a1 == 18.0_mps2);

	a1 = v1 / t1;
	REQUIRE(a1 == 2.0_mps2);

	a1 = a2 / 3.0;
	REQUIRE(a1 == 1.0_mps2);

	a1 = 18.0_mps / second;
	REQUIRE(a1 == 18.0_mps2);

	REQUIRE(f1 == 1 / t1);
}

TEST_CASE("SIUnits: Ostream operator")
{
	LinearVelocity v{ -1.8 };
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << v;
	REQUIRE(ss.str() == "-1.8 m^1*kg^0*s^-1");
}

TEST_CASE("SIUnits: Vector quantities")
{
	constexpr LinearAcceleration2 a1{ 3.0_mps2, -1.0_mps2 };
	constexpr Mass m1 = 2.0_kg;
	constexpr Force2 f1 = { 7.0_N, -14.0_N };
	constexpr Force2 f2{ 1.0_N, 2.0_N };
	Force2 f3;


	f3 = +f1;
	REQUIRE(f3 == f1);

	f3 = -f1;
	REQUIRE(f3 == Force2{ -7.0_N, 14.0_N });

	f3 += Force2{ Force{-1.0}, Force{-1.0} };
	REQUIRE(f3 == Force2{ -8.0_N, 13.0_N });
	
	f3 -= Force2{ 0.5_N, 0.5_N };
	REQUIRE(f3 == Force2{ -8.5_N, 12.5_N });
	
	f3 *= 2.0;
	REQUIRE(f3 == Force2{ -17.0_N, 25.0_N });

	f3 /= 5.0;
	REQUIRE(f3 == Force2{ -3.4_N, 5.0_N });

	f3 = f1 + f2;
	REQUIRE(f3 == Force2{ 8.0_N, -12.0_N });

	f3 = f1 - f2;
	REQUIRE(f3 == Force2{ 6.0_N, -16.0_N });

	f3 = m1 * a1;
	REQUIRE(f3 == Force2{ 6.0_N, -2.0_N });

	f3 = f2 * 4.0;
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });

	f3 = 4.0 * f2;
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });

	f3 = Real2{ 4.0, 8.0 } * newton;
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });

	f3 = newton * Real2{ 4.0, 8.0 };
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });
	
	f3 = Real2{ 4.0, 8.0 } * newton;
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });

	f3 = LinearMomentum2{ 4.0_kgmps, 8.0_kgmps } * hertz;
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });

	f3 = f1 / -7.0;
	REQUIRE(f3 == Force2{ -1.0_N, 2.0_N });

	f3 = LinearMomentum2{ 4.0_kgmps, 8.0_kgmps } / second;
	REQUIRE(f3 == Force2{ 4.0_N, 8.0_N });	
}

TEST_CASE("SIUnits: Quantity storage size")
{
	REQUIRE(sizeof(Length{}) == sizeof(Real));
	REQUIRE(sizeof(MomentOfInertia{}) == sizeof(Real));
	REQUIRE(sizeof(Mass{} *LinearVelocity{}) == sizeof(Real));
	REQUIRE(sizeof(67.0_m2) == sizeof(Real));
}


