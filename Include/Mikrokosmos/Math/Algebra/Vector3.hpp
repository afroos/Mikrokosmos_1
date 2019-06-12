#ifndef MIKROKOSMOS_MATH_ALGEBRA_VECTOR3_HPP
#define MIKROKOSMOS_MATH_ALGEBRA_VECTOR3_HPP

#include <Mikrokosmos/Math/Algebra/Vector.hpp>

namespace Mikrokosmos
{
	template <typename T>
	using Vector3 = Vector<T, 3>;

	using Real3 = Vector3<Real>;
}


#endif