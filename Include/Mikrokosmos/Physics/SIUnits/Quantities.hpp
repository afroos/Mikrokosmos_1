#ifndef MIKROKOSMOS_PHYSICS_SIUNITS_QUANTITIES_HPP
#define MIKROKOSMOS_PHYSICS_SIUNITS_QUANTITIES_HPP

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
	constexpr decltype(auto) operator*(const Quantity<Unit<M1, K1, S1>>& q, const Unit<M2, K2, S2>& u) noexcept
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
	std::ostream& operator<<(std::ostream& os, const Quantity<Unit<M, K, S>>& q)
	{
		os << q.magnitude << " " << "m^" << M << "*" << "kg^" << K << "*" << "s^" << S;
		return os;
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

	constexpr auto millimeter = milli * meter;
	constexpr auto kilometer = kilo * meter;
	constexpr auto kilonewton = kilo * newton;
	constexpr auto millisecond = milli * second;
	constexpr auto minute = Real{ 60.0 } * second;
	constexpr auto hour = Real{ 60.0 } * minute;;

#define MIKROKOSMOS_UNIT_LITERAL(quantity, unit, name)				\
	constexpr quantity operator"" name(long double magnitude)		\
	{																\
		return static_cast<Real>(magnitude) * unit;					\
	}																\

	MIKROKOSMOS_UNIT_LITERAL(Length, meter, _m);
	MIKROKOSMOS_UNIT_LITERAL(Length, milli * meter, _mm);
	MIKROKOSMOS_UNIT_LITERAL(Length, kilometer, _km);
	MIKROKOSMOS_UNIT_LITERAL(Mass, kilogram, _kg);
	MIKROKOSMOS_UNIT_LITERAL(Mass, milli * kilogram, _g);
	MIKROKOSMOS_UNIT_LITERAL(Time, second, _s);
	MIKROKOSMOS_UNIT_LITERAL(Time, millisecond, _ms);
	MIKROKOSMOS_UNIT_LITERAL(Angle, radian, _rad);
	MIKROKOSMOS_UNIT_LITERAL(Area, meter * meter, _m2);
	MIKROKOSMOS_UNIT_LITERAL(AreaDensity, kilogram / (meter * meter), _kgpm2);
	MIKROKOSMOS_UNIT_LITERAL(MomentOfInertia, kilogram * meter * meter, _kgm2);
	MIKROKOSMOS_UNIT_LITERAL(Frequency, hertz, _Hz);
	MIKROKOSMOS_UNIT_LITERAL(Volume, meter * meter * meter, _m3);
	MIKROKOSMOS_UNIT_LITERAL(LinearVelocity, meter / second, _mps);
	MIKROKOSMOS_UNIT_LITERAL(LinearVelocity, kilometer / hour, _kmph);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, radian / second, _radps);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, Real{ 2.0 } * pi * radian / minute, _rpm);
	MIKROKOSMOS_UNIT_LITERAL(LinearAcceleration, meter / (second * second), _mps2);
	MIKROKOSMOS_UNIT_LITERAL(AngularAcceleration, radian / (second * second), _radps2);
	MIKROKOSMOS_UNIT_LITERAL(Force, newton, _N);
	MIKROKOSMOS_UNIT_LITERAL(Force, kilonewton, _kN);
	MIKROKOSMOS_UNIT_LITERAL(Torque, newton * meter, _Nm);
	MIKROKOSMOS_UNIT_LITERAL(Pressure, pascal, _Pa);
	MIKROKOSMOS_UNIT_LITERAL(SecondMomentOfArea, meter * meter * meter * meter, _m4);
	MIKROKOSMOS_UNIT_LITERAL(LinearMomentum, kilogram * meter / second, _kgmps);
	MIKROKOSMOS_UNIT_LITERAL(AngularMomentum, kilogram * meter * meter * radian / second, _kgm2ps);

	using Length2 = Vector2<Length>;
	using LinearVelocity2 = Vector2<LinearVelocity>;
	using LinearAcceleration2 = Vector2<LinearAcceleration>;
	using LinearMomentum2 = Vector2<LinearMomentum>;
	using Force2 = Vector2<Force>;

}
#endif