#include "catch.hpp"
#include <Mikrokosmos/Math/Algebra/Vector.hpp>
#include <Mikrokosmos/Math/Algebra/Vector2.hpp>
#include <Mikrokosmos/Math/Algebra/Vector3.hpp>

using namespace Mikrokosmos;

TEST_CASE("Vector: Storage size") 
{
	REQUIRE(sizeof(Real3) == 3 * sizeof(Real));
}

TEST_CASE("Vector: Construction")
{
	constexpr Vector<Real, 0> v0;
	constexpr Vector2<Real> v1;
	constexpr Vector2<Real> v2{};
	constexpr Vector2<Real> v3{ 0.0, 0.0 };
	constexpr Vector<Real, 5> v4{ -3.0, -1.5, 0.0, 1.5, 3.0 };
	constexpr Vector<Real, 5> v5(-3.0, -1.5, 0.0, 1.5, 3.0);
	constexpr Vector<Real, 5> v6({ -3.0, -1.5, 0.0, 1.5, 3.0 });
	constexpr Vector<Real, 5> v7 = { -3.0, -1.5, 0.0, 1.5, 3.0 };
	constexpr Vector3<int> v8{ -1, 0, 1 };
	constexpr auto v9{ v8 };
	constexpr auto v10{ std::move(v8) };

	REQUIRE(v1 == v2);
	REQUIRE(v2 == v3);
	REQUIRE(v4 == v5);
	REQUIRE(v5 == v6);
	REQUIRE(v6 == v7);
	REQUIRE(v8 == v9);
	REQUIRE(v8 == v10);
}

TEST_CASE("Vector: Constants")
{
	REQUIRE(Real3::Zero()  == Real3{ 0.0, 0.0, 0.0 });
	REQUIRE(Real3::UnitX() == Real3{ 1.0, 0.0, 0.0 });
	REQUIRE(Real3::UnitY() == Real3{ 0.0, 1.0, 0.0 });
	REQUIRE(Real3::UnitZ() == Real3{ 0.0, 0.0, 1.0 });
}

TEST_CASE("Vector: Assignment")
{
	Real2 v1{ -1.0, -1.0 };
	Real2 v2{ 0.0, 1.0 };
	v1 = v2;
	v2 = { 2.0, 3.0 };

	REQUIRE(v1 == Real2{ 0.0, 1.0 });
	REQUIRE(v2 == Real2{ 2.0, 3.0 });
}

TEST_CASE("Vector: Element access")
{
	constexpr Real3 v1{ -1.0, -0.5, 1.0 };
	Real3 v2;
	Real3 v3;

	v2[0] = v1[0];
	v2[1] = v1[1];
	v2[2] = v1[2];

	v3.setX(v2.x());
	v3.setY(v2.y());
	v3.setZ(v2.z());

	REQUIRE(v2 == Real3{ -1.0, -0.5, 1.0 });
	REQUIRE(v3 == v2);
}

TEST_CASE("Vector: Arithmetic operators")
{
	constexpr Real3 v1{ -1.0, -2.0, 3.0 };
	constexpr Real3 v2{ 1.0, 1.0, 1.0 };
	Real3 v3;

	v3 = +v1;
	REQUIRE(v3 == v1);

	v3 = -v1;
	REQUIRE(v3 == Real3{ 1.0, 2.0, -3.0 });

	v3 += Real3{ -1.0, -1.0, 1.0 };
	REQUIRE(v3 == Real3{ 0.0, 1.0, -2.0 });

	v3 -= Real3{ 0.5, 0.5, 0.5 };
	REQUIRE(v3 == Real3{ -0.5, 0.5, -2.5 });

	v3 *= Real3{ -1.0, 2.0, 3.0 };
	REQUIRE(v3 == Real3{ 0.5, 1.0, -7.5 });

	v3 *= 2.0;
	REQUIRE(v3 == Real3{ 1.0, 2.0, -15.0});

	v3 /= Real3{ 0.5, 1.0, -3.0 };
	REQUIRE(v3 == Real3{ 2.0, 2.0, 5.0 });

	v3 /= -0.5;
	REQUIRE(v3 == Real3{ -4.0, -4.0, -10.0 });

	v3 = v1 + v2;
	REQUIRE(v3 == Real3{ 0.0, -1.0, 4.0 });

	v3 = v1 - v2;
	REQUIRE(v3 == Real3{ -2.0, -3.0, 2.0 });

	v3 = v1 * 1.5;
	REQUIRE(v3 == Real3{ -1.5, -3.0, 4.5 });

	v3 = -1.5 * v1;
	REQUIRE(v3 == Real3{ 1.5, 3.0, -4.5 });

	v3 = v1 / 0.5;
	REQUIRE(v3 == Real3{ -2.0, -4.0, 6.0 });
}

TEST_CASE("Vector: Dot product")
{
	constexpr Real3 v1{ 1.0, 0.0, 0.0 };
	constexpr Real3 v2{ 0.0, 1.0, 0.0 };
	constexpr Real3 v3{ -1.0, 0.0, 0.0 };
	constexpr Real3 v4{ 0.0, -1.0, 0.0 };
	constexpr Real3 v5{ 1.0, 2.0, 3.0 };
	constexpr Real3 v6{ 4.0, 5.0, 6.0 };

	REQUIRE(dot(v1, v1) == Approx(1.0));
	REQUIRE(dot(v1, v2) == Approx(0.0));
	REQUIRE(dot(v1, v3) == Approx(-1.0));
	REQUIRE(dot(v1, v4) == Approx(0.0));
	REQUIRE(dot(v5, v6) == Approx(32.0));
}

TEST_CASE("Vector: Length")
{
	constexpr Real2 v1{ 0.0, 0.0 };
	constexpr Real2 v2{ 1.0, 0.0 };
	constexpr Real2 v3{ 0.0, 1.0 };
	constexpr Real2 v4{ 3.0, 4.0 };
	constexpr Real2 v5{ -3.0, -4.0 };

	REQUIRE(length(v1) == Approx(0.0));
	REQUIRE(length(v2) == Approx(1.0));
	REQUIRE(length(v2) == length(v3));
	REQUIRE(length(v4) == Approx(5.0));
	REQUIRE(length(v4) == length(v5));

	REQUIRE(lengthSquared(v1) == Approx(0.0));
	REQUIRE(lengthSquared(v2) == Approx(1.0));
	REQUIRE(lengthSquared(v2) == lengthSquared(v3));
	REQUIRE(lengthSquared(v4) == Approx(25.0));
	REQUIRE(lengthSquared(v4) == lengthSquared(v5));
}

TEST_CASE("Vector2: Perp operator")
{
	constexpr Real2 v1{ 1.0, 0.0 };
	constexpr Real2 v2{ 0.0, 1.0 };
	constexpr Real2 v3{ -1.0, 0.0 };
	constexpr Real2 v4{ 0.0, -1.0 };
	constexpr Real2 v5{ 1.0, 1.0 };
	constexpr Real2 v6{ -1.0, 1.0 };

	REQUIRE(perp(v1) == v2);
	REQUIRE(perp(v2) == v3);
	REQUIRE(perp(v3) == v4);
	REQUIRE(perp(v4) == v1);
	REQUIRE(perp(v5) == v6);
}

TEST_CASE("Vector2: Perp dot operator")
{
	constexpr Real2 v1{ 1.0, 0.0 };
	constexpr Real2 v2{ 0.0, 1.0 };
	constexpr Real2 v3{ -1.0, 0.0 };
	constexpr Real2 v4{ 0.0, -1.0 };
	constexpr Real2 v5{ 1.0, 1.0 };
	constexpr Real2 v6{ -1.0, 1.0 };

	REQUIRE(perpDot(v1, v1) == Real{ 0 });
	REQUIRE(perpDot(v1, v2) == Real{ 1 });
	REQUIRE(perpDot(v1, v3) == Real{ 0 });
	REQUIRE(perpDot(v1, v4) == Real{ -1 });
	REQUIRE(perpDot(v5, v6) == Approx(2.0));
	REQUIRE(perpDot(v5, v6) == -perpDot(v6, v5));
	REQUIRE(perpDot(v1, v2 + v3) == perpDot(v1, v2) + perpDot(v1, v3));
}