#ifndef MIKROKOSMOS_PHYSICS_SIUNITS_UNITS_HPP
#define MIKROKOSMOS_PHYSICS_SIUNITS_UNITS_HPP

#include <Mikrokosmos/Common/Real.hpp>

namespace Mikrokosmos
{   
	template <int M, int K, int S>
	struct Unit { };

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator==(const Unit<M1, K1, S1>& u1, const Unit<M2, K2, S2>& u2) noexcept
	{
		return (M1 == M2 && K1 == K2 && S1 == S2);
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr bool operator!=(const Unit<M1, K1, S1>& u1, const Unit<M2, K2, S2>& u2) noexcept
	{
		return !(u1 == u2);
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr decltype(auto) operator*(const Unit<M1, K1, S1>& u1, const Unit<M2, K2, S2>& u2) noexcept
	{
		return Unit<M1 + M2, K1 + K2, S1 + S2>{};
	}

	template <int M1, int K1, int S1, int M2, int K2, int S2>
	inline constexpr decltype(auto) operator/(const Unit<M1, K1, S1>& u1, const Unit<M2, K2, S2>& u2) noexcept
	{
		return Unit<M1 - M2, K1 - K2, S1 - S2>{};
	}

	template <int M, int K, int S>
	inline constexpr decltype(auto) operator/(const Real s, const Unit<M, K, S>& u) noexcept
	{
		assert(s == Real{1});
		return adimensional / Unit<M, K, S>{};
	}

	constexpr auto adimensional = Unit<0, 0, 0>{};
	constexpr auto meter    = Unit<1, 0, 0>{};
	constexpr auto kilogram = Unit<0, 1, 0>{};
	constexpr auto second   = Unit<0, 0, 1>{};

	constexpr auto hertz    = 1 / second;
	constexpr auto radian   = meter / meter;
	constexpr auto newton   = kilogram * meter / (second * second);
	constexpr auto pascal   = newton / (meter * meter);

}

#endif