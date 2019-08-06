#include "catch.hpp"
#include <Mikrokosmos/Math/Algebra/Complex.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace Mikrokosmos;

bool nearlyEqual(const Complex& z1, const Complex& z2, Real margin = 1e-15)
{
	return z1.a() == Approx(z2.a()).margin(margin) && z1.b() == Approx(z2.b()).margin(margin);
}

bool nearlyEqual(const Length2& v1, const Length2& v2, Real margin = 1e-15)
{
	return v1.x().magnitude == Approx(v2.x().magnitude).margin(margin) && 
		v1.y().magnitude == Approx(v2.y().magnitude).margin(margin);
}

bool nearlyEqual(const Angle& a1, const Angle& a2, Real margin = 1e-15)
{
	return a1.magnitude == Approx(a2.magnitude);
}

TEST_CASE("Complex: Storage size") 
{
	REQUIRE(sizeof(Complex) == 2 * sizeof(Real));
}

TEST_CASE("Complex: Construction")
{
	Complex z1;
	Complex z2{ 1.0, 0.0 };
	Complex z3{ 0.0, 1.0 };
	Complex z4{ -1.0, 0.0 };
	Complex z5{ 0.0, -1.0 };
	Complex z6{ 1.0, 0.0_deg };
	Complex z7{ 1.0, 90.0_deg };
	Complex z8{ 1.0, 180.0_deg };
	Complex z9{ 1.0, 270.0_deg };

	REQUIRE(nearlyEqual(z1, z2));
	REQUIRE(nearlyEqual(z2, z6));
	REQUIRE(nearlyEqual(z3, z7));
	REQUIRE(nearlyEqual(z4, z8));
	REQUIRE(nearlyEqual(z5, z9));
}

TEST_CASE("Complex: Constants")
{
	REQUIRE(Complex::Identity() == Complex{ 1.0, 0.0_deg});
}

TEST_CASE("Complex: Assignment")
{
	Complex z1{ -1.0, -1.0 };
	Complex z2{ 0.0, 1.0 };
	z1 = z2;
	z2 = { 2.0, 3.0 };

	REQUIRE(z1 == Complex{ 0.0, 1.0 });
	REQUIRE(z2 == Complex{ 2.0, 3.0 });
}

TEST_CASE("Complex: Element access")
{
	Complex z1{ -1.0, -0.5 };

	REQUIRE(z1.a() == -1.0);
	REQUIRE(z1.b() == -0.5);
}

TEST_CASE("Complex: Multiplication")
{
	Complex z1{ 3.0, 2.0 };
	Complex z2{ 1.0, 7.0 };

	auto z3 = z1 * z2;

	REQUIRE(z3 == Complex{ -11.0, 23.0 });

	z3 *= Complex{-1.0, -2.0};

	REQUIRE(z3 == Complex{ 57.0, -1.0 });

	REQUIRE(z1 * z2 == z2 * z1);
}

TEST_CASE("Complex: Vector rotation")
{
	auto z1 = Complex::Identity();
	Complex z2{ 1.0, 90.0_deg };
	Complex z3{ 1.0, -90.0_deg };
	Complex z4{ 1.0, 45.0_deg };
	Complex z5{ 1.0, 225.0_deg };
	Complex z6{ 1.0, 405.0_deg };

	Length2 v{ 1.0, 1.0 };
	auto v1 = z1 * v;
	auto v2 = z2 * v;
	auto v3 = z3 * v;
	auto v4 = z4 * v;
	auto v5 = z5 * v;
	auto v6 = z6 * v;
	auto v7 = (z2 * z4) * v;
	auto v8 = (z4 * z2 * Complex{1.0, 15.0_deg}) * v;
	auto v9 = (z2 * z3) * v;

	REQUIRE(nearlyEqual(v1, v));
	REQUIRE(nearlyEqual(v2, Length2{ -1.0_m, 1.0_m }));
	REQUIRE(nearlyEqual(v3, Length2{ 1.0_m, -1.0_m }));
	REQUIRE(nearlyEqual(v4, Length2{ 0.0_m, 1.4142_m }));
	REQUIRE(nearlyEqual(v5, Length2{ 0.0_m, -1.4142_m }));
	REQUIRE(nearlyEqual(v6, v4));
	REQUIRE(nearlyEqual(v7, Length2{ -1.4142_m, 0.0_m}));
	REQUIRE(nearlyEqual(v8, Length2{ -1.3660_m, -0.3660_m }, 0.00005));
	REQUIRE(nearlyEqual(v9, v));
}

TEST_CASE("Complex: Ostream operator")
{
	Complex z{ -11.0, 23.0 };
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << z;
	REQUIRE(ss.str() == "(-11.0, 23.0)");
}

TEST_CASE("Complex: Argument")
{
	Complex z0{ 1.0, 0.0_deg };
	Complex z1{ 1.0, 45.0_deg };
	Complex z2{ 1.0, 90.0_deg };
	Complex z3{ 1.0, 135.0_deg };
	Complex z4{ 1.0, 180.0_deg };
	Complex z5{ 1.0, -45.0_deg };
	Complex z6{ 1.0, -90.0_deg };
	Complex z7{ 1.0, -135.0_deg };
	Complex z8{ 1.0, -180.0_deg };
	
	REQUIRE(nearlyEqual(arg(z0), 0.0_deg));
	REQUIRE(nearlyEqual(arg(z1), 45.0_deg));
	REQUIRE(nearlyEqual(arg(z2), 90.0_deg));
	REQUIRE(nearlyEqual(arg(z3), 135.0_deg));
	REQUIRE(nearlyEqual(arg(z4), 180.0_deg));
	REQUIRE(nearlyEqual(arg(z5), -45.0_deg));
	REQUIRE(nearlyEqual(arg(z6), -90.0_deg));
	REQUIRE(nearlyEqual(arg(z7), -135.0_deg));
	REQUIRE(nearlyEqual(arg(z8), -180.0_deg));
}

TEST_CASE("Complex: Conjugate")
{
	Complex z1{ 1.0, 45.0_deg };
	Complex z2{ -1.0, -2.0 };

	REQUIRE(conjugate(z1) == Complex{ 1.0, -45.0_deg });
	REQUIRE(conjugate(z2) == Complex{ -1.0, 2.0 });
}
