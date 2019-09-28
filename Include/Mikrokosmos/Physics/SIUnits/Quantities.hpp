#ifndef MIKROKOSMOS_PHYSICS_SIUNITS_QUANTITIES_HPP
#define MIKROKOSMOS_PHYSICS_SIUNITS_QUANTITIES_HPP

#include <cassert>

#include <Mikrokosmos/Common/Real.hpp>
#include <Mikrokosmos/Math/Constants.hpp>
#include <Mikrokosmos/Math/Constants.hpp>
#include <Mikrokosmos/Math/Algebra/Vector2.hpp>
#include <Mikrokosmos/Physics/SIUnits/Prefixes.hpp>
#include <Mikrokosmos/Physics/SIUnits/Units.hpp>

namespace Mikrokosmos
{
	template <typename Unit>
	struct Quantity
	{
		Real magnitude{ 0.0 };
	};

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator==(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return (q1.magnitude == q2.magnitude) && (Unit<M1, K1, S1>{} == Unit<M2, K2, S2>{});
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator!=(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return !(q1 == q2);
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator<(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return q1.magnitude < q2.magnitude;
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator>(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return q2 < q1;
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator<=(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return !(q1 > q2);
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator>=(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return !(q1 < q2);
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator+(const Quantity<Unit<M, K, S>>& q) noexcept
	{
		return q;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator-(const Quantity<Unit<M, K, S>>& q) noexcept
	{
		return Quantity<Unit<M, K, S>>{ -q.magnitude };
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator+=(Quantity<Unit<M, K, S>>& q1, const Quantity<Unit<M, K, S>>& q2) noexcept
	{
		q1.magnitude += q2.magnitude;
		return q1;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator-=(Quantity<Unit<M, K, S>>& q1, const Quantity<Unit<M, K, S>>& q2) noexcept
	{
		q1.magnitude -= q2.magnitude;
		return q1;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator*=(Quantity<Unit<M, K, S>>& q, const Real s) noexcept
	{
		q.magnitude *= s;
		return q;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator/=(Quantity<Unit<M, K, S>>& q, const Real s) noexcept
	{
		q.magnitude /= s;
		return q;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator+(const Quantity<Unit<M, K, S>>& q1, const Quantity<Unit<M, K, S>>& q2) noexcept
	{
		auto result{ q1 };
		result += q2;
		return result;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator-(const Quantity<Unit<M, K, S>>& q1, const Quantity<Unit<M, K, S>>& q2) noexcept
	{
		auto result{ q1 };
		result -= q2;
		return result;
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr decltype(auto) operator*(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return Quantity<Unit<M1 + M2, K1 + K2, S1 + S2>>{ q1.magnitude* q2.magnitude };
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator*(const Quantity<Unit<M, K, S>>& q, const Real s) noexcept
	{
		auto result{ q };
		result *= s;
		return result;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator*(const Real s, const Quantity<Unit<M, K, S>>& q) noexcept
	{
		return q * s;
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator*(const Real s, const Unit<M, K, S>& u) noexcept
	{
		return Quantity<Unit<M, K, S>>{ s };
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator*(const Unit<M, K, S>& u, const Real s) noexcept
	{
		return s * u;
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr decltype(auto) operator*(const Quantity<Unit<M1, K1, S1>>& q, const Unit<M2, K2, S2>& u) noexcept
	{
		return Quantity<Unit<M1 + M2, K1 + K2, S1 + S2>>{ q.magnitude };
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr decltype(auto) operator/(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return Quantity<Unit<M1 - M2, K1 - K2, S1 - S2>>{ q1.magnitude / q2.magnitude };
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator/(const Quantity<Unit<M, K, S>>& q, const Real s) noexcept
	{
		auto result{ q };
		result /= s;
		return result;
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr decltype(auto) operator/(const Quantity<Unit<M1, K1, S1>>& q, const Unit<M2, K2, S2>& u) noexcept
	{
		return Quantity<Unit<M1 - M2, K1 - K2, S1 - S2>>{ q.magnitude };
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator/(const Real s, const Quantity<Unit<M, K, S>>& q) noexcept
	{
		assert(s == 1);
		return Quantity<Unit<0, 0, 0>>{1.0} / q;
	}

	template <int M, int K, int S>
	inline std::ostream& operator<<(std::ostream& os, const Quantity<Unit<M, K, S>>& q)
	{
		os << q.magnitude << " " << "m^" << M << "*" << "kg^" << K << "*" << "s^" << S;
		return os;
	}

	template <int M, int K, int S>
	inline bool isFinite(const Quantity<Unit<M, K, S>>& q)
	{
		return isFinite(q.magnitude);
	}

	template <int M, int K, int S>
	inline bool isZero(const Quantity<Unit<M, K, S>>& q)
	{
		return isZero(q.magnitude);
	}

	template <int M, int K, int S>
	inline bool isPositive(const Quantity<Unit<M, K, S>>& q)
	{
		return isPositive(q.magnitude);
	}

	template <int M, int K, int S>
	inline bool isNegative(const Quantity<Unit<M, K, S>>& q)
	{
		return isNegative(q.magnitude);
	}

	template <int M, int K, int S>
	inline bool isNonPositive(const Quantity<Unit<M, K, S>>& q)
	{
		return isNonPositive(q.magnitude);
	}

	template <int M, int K, int S>
	inline bool isNonNegative(const Quantity<Unit<M, K, S>>& q)
	{
		return isNonNegative(q.magnitude);
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline bool nearlyEqual(const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2, Real tolerance = Real{ 1e-15 }) noexcept
	{
		return nearlyEqual(q1.magnitude, q2.magnitude, tolerance);
	}

	using Length = Quantity<Unit<1, 0, 0>>;
	using Mass   = Quantity<Unit<0, 1, 0>>;
	using Time   = Quantity<Unit<0, 0, 1>>;
	using Angle  = Quantity<Unit<0, 0, 0>>;

	using Area = decltype(Length{} *Length{});
	using AreaDensity = decltype(Mass{} / Area{});
	using InverseMass = decltype(1 / Mass{});
	using MomentOfInertia = decltype(Mass{} * Area{});
	using InverseMomentOfInertia = decltype(1 / MomentOfInertia{});
	using Frequency	= decltype(1 / Time{});
	using Volume = decltype(Area{} * Length{});
	using LinearVelocity = decltype(Length{} / Time{});
	using AngularVelocity = decltype(Angle{} / Time{});
	using LinearAcceleration = decltype(LinearVelocity{} / Time{});
	using AngularAcceleration = decltype(AngularVelocity{} / Time{});
	using Force = decltype(Mass{} * LinearAcceleration{});
	using Torque = decltype(MomentOfInertia{} * AngularAcceleration{});
	using Pressure = decltype(Force{} / Area{});
	using SecondMomentOfArea = decltype(Area{} * Area{});
	using LinearMomentum = decltype(Mass{} * LinearVelocity{});
	using AngularMomentum = decltype(MomentOfInertia{} * AngularVelocity{});
	using LinearImpulse = decltype(Force{} * Time{});
	using AngularImpulse = decltype(Torque{} * Time{});

	constexpr auto millimeter = milli * meter;
	constexpr auto kilometer = kilo * meter;
	constexpr auto kilonewton = kilo * newton;
	constexpr auto millisecond = milli * second;
	constexpr auto minute = Real{ 60.0 } * second;
	constexpr auto hour = Real{ 60.0 } * minute;
	constexpr auto degree = pi * radian / Real{ 180.0 };

#define MIKROKOSMOS_UNIT_LITERAL(quantity, unit, name)										\
	inline constexpr quantity operator"" _ ## name(long double magnitude)					\
	{																						\
		return static_cast<Real>(magnitude) * unit;											\
	}																						\


	MIKROKOSMOS_UNIT_LITERAL(Length, meter, m);
	MIKROKOSMOS_UNIT_LITERAL(Length, milli * meter, mm);
	MIKROKOSMOS_UNIT_LITERAL(Length, kilometer, km);
	MIKROKOSMOS_UNIT_LITERAL(Mass, kilogram, kg);
	MIKROKOSMOS_UNIT_LITERAL(Mass, milli * kilogram, g);
	MIKROKOSMOS_UNIT_LITERAL(Time, second, s);
	MIKROKOSMOS_UNIT_LITERAL(Time, millisecond, ms);
	MIKROKOSMOS_UNIT_LITERAL(Angle, radian, rad);
	MIKROKOSMOS_UNIT_LITERAL(Angle, degree, deg);
	MIKROKOSMOS_UNIT_LITERAL(Area, meter * meter, m2);
	MIKROKOSMOS_UNIT_LITERAL(AreaDensity, kilogram / (meter * meter), kgpm2);
	MIKROKOSMOS_UNIT_LITERAL(MomentOfInertia, kilogram * meter * meter, kgm2);
	MIKROKOSMOS_UNIT_LITERAL(Frequency, hertz, Hz);
	MIKROKOSMOS_UNIT_LITERAL(Volume, meter * meter * meter, m3);
	MIKROKOSMOS_UNIT_LITERAL(LinearVelocity, meter / second, mps);
	MIKROKOSMOS_UNIT_LITERAL(LinearVelocity, kilometer / hour, kmph);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, radian / second, radps);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, degree / second, degps);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, Real{ 2.0 } * pi * radian / minute, rpm);
	MIKROKOSMOS_UNIT_LITERAL(LinearAcceleration, meter / (second * second), mps2);
	MIKROKOSMOS_UNIT_LITERAL(AngularAcceleration, radian / (second * second), radps2)
	MIKROKOSMOS_UNIT_LITERAL(AngularAcceleration, degree / (second * second), degps2);
	MIKROKOSMOS_UNIT_LITERAL(Force, newton, N);
	MIKROKOSMOS_UNIT_LITERAL(Force, kilonewton, kN);
	MIKROKOSMOS_UNIT_LITERAL(Torque, newton * meter, Nm);
	MIKROKOSMOS_UNIT_LITERAL(Pressure, pascal, Pa);
	MIKROKOSMOS_UNIT_LITERAL(SecondMomentOfArea, meter * meter * meter * meter, m4);
	MIKROKOSMOS_UNIT_LITERAL(LinearMomentum, kilogram * meter / second, kgmps);
	MIKROKOSMOS_UNIT_LITERAL(AngularMomentum, kilogram * meter * meter * radian / second, kgm2ps);
	MIKROKOSMOS_UNIT_LITERAL(LinearImpulse, newton * second, Ns);
	MIKROKOSMOS_UNIT_LITERAL(AngularImpulse, newton * meter * second, Nms);

	using Length2 = Vector2<Length>;
	using LinearVelocity2 = Vector2<LinearVelocity>;
	using LinearAcceleration2 = Vector2<LinearAcceleration>;
	using LinearMomentum2 = Vector2<LinearMomentum>;
	using LinearImpulse2 = Vector2<LinearImpulse>;
	using Force2 = Vector2<Force>;

}
#endif