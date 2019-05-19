#ifndef MIKROKOSMOS_MATH_VECTOR2_HPP
#define MIKROKOSMOS_MATH_VECTOR2_HPP

#include <Mikrokosmos/Math/Vector.hpp>

namespace Mikrokosmos
{

	template <typename T>
	using Vector2 = Vector<T, 2>;

	using Real2 = Vector2<Real>;

	template <typename T>
	inline constexpr Vector2<T> perp(const Vector2<T>& v)
	{
		return Vector2<T>{ -v.y(), v.x() };
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} * T2{}) >
	inline constexpr T3 perpDot(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return dot(perp(v1), v2);
	}

}


#endif