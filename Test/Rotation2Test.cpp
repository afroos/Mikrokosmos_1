#include "catch.hpp"
#include <Mikrokosmos/Math/Algebra/Rotation2.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace Mikrokosmos;

bool nearlyEqual(const Angle& theta1, const Angle& theta2, Real margin = 1e-15)
{
	return theta1.magnitude == Approx(theta2.magnitude).margin(margin);
}

bool nearlyEqual(const Rotation2& r1, const Rotation2& r2, Real margin = 1e-15)
{
	return nearlyEqual(r1.angle(), r2.angle(), margin);
}

bool nearlyEqual(const Length2& v1, const Length2& v2, Real margin = 1e-15)
{
	return v1.x().magnitude == Approx(v2.x().magnitude).margin(margin) && 
		v1.y().magnitude == Approx(v2.y().magnitude).margin(margin);
}

TEST_CASE("Rotation2: Storage size") 
{
	REQUIRE(sizeof(Rotation2) == 2 * sizeof(Real));
}

TEST_CASE("Rotation2: Construction")
{
	Rotation2 r1;
	Rotation2 r2{ 0.0_deg };
	Rotation2 r3{ 90.0_deg };
	Rotation2 r4{ 180.0_deg };
	Rotation2 r5{ 270.0_deg };
	Rotation2 r6{ 360.0_deg };
	Rotation2 r7{ 450.0_deg };
	Rotation2 r8{ -180.0_deg };
	Rotation2 r9{ -90.0_deg };

	REQUIRE(nearlyEqual(r1, r2));
	REQUIRE(nearlyEqual(r2, r6));
	REQUIRE(nearlyEqual(r3, r7));
	REQUIRE(nearlyEqual(r4, r8.inverse()));
	REQUIRE(nearlyEqual(r5, r9));
}

TEST_CASE("Rotation2: Constants")
{
	REQUIRE(Rotation2::Identity() == Rotation2{ 0.0_deg });
}

TEST_CASE("Rotation2: Assignment")
{
	Rotation2 r1{ -1.0_deg };
	Rotation2 r2{ 1.0_deg };
	r1 = r2;
	r2 = Rotation2{ 3.0_deg };

	REQUIRE(r1 == Rotation2{ 1.0_deg });
	REQUIRE(r2 == Rotation2{ 3.0_deg });
}

TEST_CASE("Rotation2: Angle")
{
	Rotation2 r0{ 0.0_deg };
	Rotation2 r1{ 45.0_deg };
	Rotation2 r2{ 90.0_deg };
	Rotation2 r3{ 135.0_deg };
	Rotation2 r4{ 180.0_deg };
	Rotation2 r5{ -45.0_deg };
	Rotation2 r6{ -90.0_deg };
	Rotation2 r7{ -135.0_deg };
	Rotation2 r8{ -180.0_deg };

	REQUIRE(nearlyEqual(r0.angle(), 0.0_deg));
	REQUIRE(nearlyEqual(r1.angle(), 45.0_deg));
	REQUIRE(nearlyEqual(r2.angle(), 90.0_deg));
	REQUIRE(nearlyEqual(r3.angle(), 135.0_deg));
	REQUIRE(nearlyEqual(r4.angle(), 180.0_deg));
	REQUIRE(nearlyEqual(r5.angle(), -45.0_deg));
	REQUIRE(nearlyEqual(r6.angle(), -90.0_deg));
	REQUIRE(nearlyEqual(r7.angle(), -135.0_deg));
	REQUIRE(nearlyEqual(r8.angle(), -180.0_deg));
}


TEST_CASE("Rotation2: Multiplication")
{
	Rotation2 r1{ 2.0_deg };
	Rotation2 r2{ 7.0_deg };

	auto r3 = r1 * r2;

	REQUIRE(nearlyEqual(r3, Rotation2{ 9.0_deg }));

	r3 *= Rotation2{-2.0_deg};

	REQUIRE(nearlyEqual(r3, Rotation2{ 7.0_deg }));

	REQUIRE(nearlyEqual(r1 * r2, r2 * r1));
}

TEST_CASE("Rotation2: Vector rotation")
{
	auto r1 = Rotation2::Identity();
	Rotation2 r2{ 90.0_deg };
	Rotation2 r3{ -90.0_deg };
	Rotation2 r4{ 45.0_deg };
	Rotation2 r5{ 225.0_deg };
	Rotation2 r6{ 405.0_deg };

	Length2 v{ 1.0_m, 1.0_m };
	auto v1 = r1 * v;
	auto v2 = r2 * v;
	auto v3 = r3 * v;
	auto v4 = r4 * v;
	auto v5 = r5 * v;
	auto v6 = r6 * v;
	auto v7 = (r2 * r4) * v;
	auto v8 = (r4 * r2 * Rotation2{15.0_deg}) * v;
	auto v9 = (r2 * r3) * v;

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

TEST_CASE("Rotation2: Ostream operator")
{
	Rotation2 r{ 23.0_deg };
	std::stringstream ss;
	//ss << std::fixed << std::setprecision(1) << r;
	REQUIRE(ss.str() == "");
}

TEST_CASE("Rotation2: Inverse")
{
	Rotation2 r1{ 45.0_deg };
	Rotation2 r2{ -2.0_deg };

	REQUIRE(r1.inverse() == Rotation2{ -45.0_deg });
	REQUIRE(r2.inverse() == Rotation2{ 2.0_deg });
}
