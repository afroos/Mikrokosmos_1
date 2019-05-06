#ifndef MIKROKOSMOS_PHYSICS_SIUNITS_QUANTITIES_HPP
#define MIKROKOSMOS_PHYSICS_SIUNITS_QUANTITIES_HPP

#include <Mikrokosmos/Common/Real.hpp>
#include <Mikrokosmos/Math/Constants.hpp>
#include <Mikrokosmos/Math/Constants.hpp>
#include <Mikrokosmos/Physics/SIUnits/Prefixes.hpp>
#include <Mikrokosmos/Physics/SIUnits/Units.hpp>

namespace Mikrokosmos
{
	template <typename Unit>
	struct Quantity
	{
		Real magnitude{ 1.0 };
	};

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	constexpr bool operator== (const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>>& q2) noexcept
	{
		return (q1.magnitude == q2.magnitude) && (Unit<M1, K1, S1>{} == Unit<M2, K2, S2>{});
	}

	template <int M, int K, int S>
	constexpr decltype(auto) operator- (const Quantity<Unit<M, K, S>>& q) noexcept
	{
		return Quantity<Unit<M, K, S>>{ -q.magnitude };
	}

	template <int M, int K, int S>
	constexpr decltype(auto) operator+ (const Quantity<Unit<M, K, S>>& q1, const Quantity<Unit<M, K, S>>& q2) noexcept 
	{
		return Quantity<Unit<M, K, S>>{ q1.magnitude + q2.magnitude };
	}

	template <int M, int K, int S>
	constexpr decltype(auto) operator- (const Quantity<Unit<M, K, S>>& q1, const Quantity<Unit<M, K, S>> & q2) noexcept 
	{
		return Quantity<Unit<M, K, S>>{ q1.magnitude - q2.magnitude };
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	constexpr decltype(auto) operator* (const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>> & q2) noexcept 
	{
		return Quantity<Unit<M1 + M2, K1 + K2, S1 + S2>>{ q1.magnitude* q2.magnitude };
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	constexpr decltype(auto) operator/ (const Quantity<Unit<M1, K1, S1>>& q1, const Quantity<Unit<M2, K2, S2>> & q2) noexcept 
	{
		return Quantity<Unit<M1 - M2, K1 - K2, S1 - S2>>{ q1.magnitude / q2.magnitude };
	}

	template <int M, int K, int S>
	constexpr decltype(auto) operator/ (const int q1, const Quantity<Unit<M, K, S>>& q2) noexcept 
	{
		return Quantity<Unit<0, 0, 0>>{} / q2;
	}

	template <int M, int K, int S>
	constexpr decltype(auto) operator* (const Real magnitude, const Unit<M, K, S>& unit) noexcept
	{
		return Quantity<Unit<M, K, S>>{ magnitude };
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	constexpr decltype(auto) operator* (const Quantity<Unit<M1, K1, S1>>& q1, const Unit<M2, K2, S2>& q2) noexcept
	{
		return Quantity<Unit<M1 + M2, K1 + K2, S1 + S2>>{ q1.magnitude };
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	constexpr decltype(auto) operator/ (const Quantity<Unit<M1, K1, S1>>& q1, const Unit<M2, K2, S2>& q2) noexcept
	{
		return Quantity<Unit<M1 - M2, K1 - K2, S1 - S2>>{ q1.magnitude };
	}

	using Length = Quantity<Unit<1, 0, 0>>;
	using Mass   = Quantity<Unit<0, 1, 0>>;
	using Time   = Quantity<Unit<0, 0, 1>>;
	using Angle  = Quantity<Unit<0, 0, 0>>;

	using Area = decltype(Length{} *Length{});
	using AreaDensity = decltype(Mass{} / Area{});
	using InverseMass = decltype(1 / Length{});
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

#define MIKROKOSMOS_UNIT_LITERAL(quantity, unit, name)				\
	constexpr quantity operator"" name(long double magnitude)		\
	{																\
		return static_cast<Real>(magnitude) * unit;					\
	}																\

	MIKROKOSMOS_UNIT_LITERAL(Length, meter, _m);
	MIKROKOSMOS_UNIT_LITERAL(Length, milli * meter, _mm);
	MIKROKOSMOS_UNIT_LITERAL(Length, kilo * meter, _km);
	MIKROKOSMOS_UNIT_LITERAL(Mass, kilogram, _kg);
	MIKROKOSMOS_UNIT_LITERAL(Mass, milli * kilogram, _g);
	MIKROKOSMOS_UNIT_LITERAL(Time, second, _s);
	MIKROKOSMOS_UNIT_LITERAL(Time, milli * second, _ms);
	MIKROKOSMOS_UNIT_LITERAL(Angle, radian, _rad);
	MIKROKOSMOS_UNIT_LITERAL(Area, meter * meter, _m2);
	MIKROKOSMOS_UNIT_LITERAL(AreaDensity, kilogram / (meter * meter), _kgpm2);
	MIKROKOSMOS_UNIT_LITERAL(MomentOfInertia, kilogram * meter * meter, _kgm2);
	MIKROKOSMOS_UNIT_LITERAL(Frequency, hertz, _Hz);
	MIKROKOSMOS_UNIT_LITERAL(Volume, meter * meter * meter, _m3);
	MIKROKOSMOS_UNIT_LITERAL(LinearVelocity, meter / second, _mps);
	MIKROKOSMOS_UNIT_LITERAL(LinearVelocity, kilo * meter / (Real{ 3600.0 } * second), _kmph);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, radian / second, _radps);
	MIKROKOSMOS_UNIT_LITERAL(AngularVelocity, 2 * pi * radian / (Real{ 60 } * second), _rpm);
	MIKROKOSMOS_UNIT_LITERAL(LinearAcceleration, meter / (second * second), _mps2);
	MIKROKOSMOS_UNIT_LITERAL(AngularAcceleration, radian / (second * second), _radps2);
	MIKROKOSMOS_UNIT_LITERAL(Force, newton, _N);
	MIKROKOSMOS_UNIT_LITERAL(Force, kilo * newton, _kN);
	MIKROKOSMOS_UNIT_LITERAL(Torque, newton * meter, _Nm);
	MIKROKOSMOS_UNIT_LITERAL(Pressure, pascal, _Pa);
	MIKROKOSMOS_UNIT_LITERAL(SecondMomentOfArea, meter * meter * meter * meter, _m4);
	MIKROKOSMOS_UNIT_LITERAL(LinearMomentum, kilogram * meter / second, _kgmps);
	MIKROKOSMOS_UNIT_LITERAL(AngularMomentum, kilogram * meter * meter * radian / second, _kgm2ps);
}
#endif