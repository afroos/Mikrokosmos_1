#ifndef MIKROKOSMOS_COMMON_REAL_HPP
#define MIKROKOSMOS_COMMON_REAL_HPP

#include <algorithm>
#include <cmath>

namespace Mikrokosmos 
{

	using Real = double;

	inline bool isFinite(Real r)
	{
		return std::isfinite(r);
	}

	inline bool isZero(Real r)
	{
		return (r == Real{ 0 });
	}

	inline bool isPositive(Real r)
	{
		return (r > Real{ 0 } && isFinite(r));
	}

	inline bool isNegative(Real r)
	{
		return (r < Real{ 0 } && isFinite(r));
	}

	inline bool isNonPositive(Real r)
	{
		return (isZero(r) || isNegative(r));
	}

	inline bool isNonNegative(Real r)
	{
		return (isZero(r) || isPositive(r));
	}

	inline bool nearlyEqual(Real a, Real b, Real tolerance = Real{ 1e-15 }) noexcept
	{
		return (std::abs(a - b) <= tolerance * std::max(Real{ 1 }, std::max(std::abs(a), std::abs(b))));
	}

}

#endif