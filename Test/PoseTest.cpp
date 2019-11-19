#include "catch.hpp"
#include <Mikrokosmos/Math/Geometry/Pose.hpp>

using namespace Mikrokosmos;

TEST_CASE("Pose: Storage size")
{
	REQUIRE(sizeof(Pose) == 4 * sizeof(Real));
}

TEST_CASE("Pose: Construction")
{
	Pose m1;
	Pose m2{ Length2::Zero(), Rotation2::Identity() };
	Pose m3{ 0.0_m, 0.0_m, 0.0_deg };
	Pose m4 = Pose::Identity();
	Pose m5 = Translation(Length2{ 0.0_m, 0.0_m });
	Pose m6 = Translation(0.0_m, 0.0_m);
	Pose m7 = Rotation(Rotation2{ 0.0_deg });
	Pose m8 = Rotation(0.0_deg);

	REQUIRE(m1 == m2);
	REQUIRE(m2 == m3);
	REQUIRE(m3 == m4);
	REQUIRE(m4 == m5);
	REQUIRE(m5 == m6);
	REQUIRE(m6 == m7);
	REQUIRE(m7 == m8);
}

TEST_CASE("Pose: Setters and getters")
{
	Pose m{ 0.56_m, -9.5_m, 33.0_deg };
	REQUIRE(m.position() == Length2{ 0.56_m, -9.5_m });
	REQUIRE(m.orientation() == Rotation2{ 33.0_deg });

	m.setPosition(Length2{ -0.1_m, -6.6_m });
	m.setOrientation(Rotation2{ -50.6_deg });
	REQUIRE(nearlyEqual(m, Pose{ -0.1_m, -6.6_m, -50.6_deg }));

	m.setPosition(0.1_m, 6.6_m);
	m.setOrientation(0.0_deg);
	REQUIRE(nearlyEqual(m, Pose{ 0.1_m, 6.6_m, 0.0_deg }));

	m.translate(Length2{ 1.0_m, 1.0_m });
	REQUIRE(nearlyEqual(m, Pose{ 1.1_m, 7.6_m, 0.0_deg }));

	m.translate(-1.1_m, -7.6_m);
	m.rotate(-20.0_deg);
	REQUIRE(nearlyEqual(m, Pose{ 0.0_m, 0.0_m, -20.0_deg }));
}

TEST_CASE("Pose: Concatenation")
{
	Pose m1, m2;
	auto sqrt3_m = std::sqrt(Real{ 3.0 }) * meter;
	m1.rotate(-30.0_deg).translate(2.0_m, 0.0_m);
	m2.translate(sqrt3_m, -1.0_m).rotate(-30.0_deg);
	auto m3 = Pose{ sqrt3_m, -1.0_m, -30.0_deg };
	REQUIRE(nearlyEqual(m1, m2));
	REQUIRE(nearlyEqual(m2, m3));

	auto m4 = Translation(sqrt3_m, -1.0_m) * Rotation(-30.0_deg);
	auto m5 = Rotation(-30.0_deg) * Translation(2.0_m, 0.0_m);
	REQUIRE(nearlyEqual(m3, m4));
	REQUIRE(nearlyEqual(m4, m5));

	m5 *= Pose::Identity();
	REQUIRE(nearlyEqual(m4, m5));

	Pose m6;
	m6.translate(2.0_m, -1.0_m).translate(-5.6_m, 11.0_m);
	auto m7 = Translation(2.0_m, -1.0_m) * Translation(-5.6_m, 11.0_m);
	auto m8 = Translation(-3.6_m, 10.0_m);
	REQUIRE(nearlyEqual(m6, m7));
	REQUIRE(nearlyEqual(m7, m8));

	Pose m9;
	m9.rotate(2.0_deg).rotate(-99.5_deg);
	auto m10 = Rotation(2.0_deg) * Rotation(-99.5_deg);
	auto m11 = Rotation(-97.5_deg);
	REQUIRE(nearlyEqual(m9, m10));
	REQUIRE(nearlyEqual(m10, m11));
}

TEST_CASE("Pose: Vector transformation")
{
	auto sqrt2_m = std::sqrt(Real{ 2.0 }) * meter;
	Pose m1 = Translation(2.5_m, 3.5_m);
	Pose m2 = Rotation(45.0_deg);
	Length2 v{2.0_m, 2.0_m};

	REQUIRE(nearlyEqual(m1 * v, Length2{4.5_m, 5.5_m}));
	REQUIRE(nearlyEqual(m2 * v, Length2{ 0.0_m, 2.0 * sqrt2_m }));
	REQUIRE(nearlyEqual(m1 * m2 * v, Length2{ 2.5_m, 3.5_m + 2.0 * sqrt2_m }));
	REQUIRE(nearlyEqual(m2 * m1 * v, Length2{ -0.5 * sqrt2_m, 5.0 * sqrt2_m }));
}

TEST_CASE("Pose: Inverse")
{
	Pose m1 = Translation(2.5_m, 3.5_m);
	Pose m2 = Rotation(45.0_deg);

	REQUIRE(nearlyEqual(inverse(m1), Translation(-2.5_m, -3.5_m)));
	REQUIRE(nearlyEqual(inverse(m2), Rotation(-45.0_deg)));
	REQUIRE(nearlyEqual(inverse(m1 * m2), Rotation(-45.0_deg) * Translation(-2.5_m, -3.5_m)));
	REQUIRE(nearlyEqual(inverse(m2 * m1), Translation(-2.5_m, -3.5_m) * Rotation(-45.0_deg)));
}