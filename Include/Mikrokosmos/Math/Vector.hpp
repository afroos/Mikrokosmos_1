#ifndef MIKROKOSMOS_MATH_VECTOR_HPP
#define MIKROKOSMOS_MATH_VECTOR_HPP

#include <algorithm>
#include <array>
#include <numeric>
#include <Mikrokosmos/Common/Real.hpp>

namespace Mikrokosmos
{
	template <typename T, std::size_t N>
	class Vector
	{
	public:

		using SizeType = std::size_t;
		using Reference = T&;
		using ConstReference = const T&;
		using Iterator = T*;
		using ConstIterator = const T*;

		constexpr Vector() noexcept = default;

		template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
		constexpr Vector(Args&&... args) noexcept
			: coords{ {args...} }
		{
		}

		static constexpr Vector zero() noexcept { return Vector(); }

		template<typename = std::enable_if_t<(N > 0)>>
		static constexpr Vector unitX() noexcept { return unitAt(0); }

		template<typename = std::enable_if_t<(N > 1)>>
		static constexpr Vector unitY() noexcept { return unitAt(1); }

		template<typename = std::enable_if_t<(N > 2)>>
		static constexpr Vector unitZ() noexcept { return unitAt(2); }

		constexpr ConstIterator begin() const noexcept { return coords.data(); }
		constexpr Iterator begin() noexcept { return coords.data(); }

		constexpr ConstIterator end() const noexcept { return coords.data() + coords.size(); }
		constexpr Iterator end() noexcept { return coords.data() + coords.size(); }

		constexpr ConstReference operator[](SizeType index) const noexcept
		{
			assert(index < coords.size());
			return coords[index];
		}

		constexpr Reference operator[](SizeType index) noexcept
		{
			assert(index < coords.size());
			return coords[index];
		}

		template<typename = std::enable_if_t<(N > 0)>>
		constexpr T x() const noexcept { return coords[0]; }

		template<typename = std::enable_if_t<(N > 1)>>
		constexpr T y() const noexcept { return coords[1]; }

		template<typename = std::enable_if_t<(N > 2)>>
		constexpr T z() const noexcept { return coords[2]; }

		template<typename = std::enable_if_t<(N > 0)>>
		void setX(T value) noexcept { coords[0] = value; }

		template<typename = std::enable_if_t<(N > 1)>>
		void setY(T value) noexcept { coords[1] = value; }

		template<typename = std::enable_if_t<(N > 2)>>
		void setZ(T value) noexcept { coords[2] = value; }

		constexpr Vector& operator+=(const Vector& rhs) noexcept
		{
			std::transform(begin(), end(), rhs.begin(), begin(), std::plus<Real>());
			return *this;
		}

		constexpr Vector& operator-=(const Vector& rhs) noexcept
		{
			std::transform(begin(), end(), rhs.begin(), begin(), std::minus<Real>());
			return *this;
		}

		constexpr Vector& operator*=(const Vector& rhs) noexcept
		{
			std::transform(begin(), end(), rhs.begin(), begin(), std::multiplies<Real>());
			return *this;
		}

		constexpr Vector& operator/=(const Vector& rhs) noexcept
		{
			std::transform(begin(), end(), rhs.begin(), begin(), std::divides<Real>());
			return *this;
		}

		constexpr Vector& operator*=(const T& rhs) noexcept
		{
			for (auto& coord : coords) { coord *= rhs; }
			return *this;
		}

		constexpr Vector& operator/=(const T& rhs) noexcept
		{
			for (auto& coord : coords) { coord /= rhs; }
			return *this;
		}

	private:
		std::array<T, N> coords{ };

		static constexpr Vector unitAt(SizeType index) noexcept
		{
			Vector v;
			v[index] = Real{ 1 };
			return v;
		}
	};

	template <typename T>
	using Vector2 = Vector<T, 2>;

	template <typename T>
	using Vector3 = Vector<T, 3>;

	using Real2 = Vector2<Real>;
	using Real3 = Vector3<Real>;

	template <typename T, std::size_t N>
	inline constexpr bool operator==(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, std::size_t N>
	inline constexpr bool operator!=(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		return !(rhs == lhs);
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator+(const Vector<T, N>& v) noexcept
	{
		return v;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator-(const Vector<T, N>& v) noexcept
	{
		Vector<T, N> result;
		std::transform(v.begin(), v.end(), result.begin(), std::negate<Real>());
		return result;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator+(Vector<T, N> lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs += rhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator-(Vector<T, N> lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs -= rhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator*(Vector<T, N> lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs *= rhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator/(Vector<T, N> lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs /= rhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator*(Vector<T, N> lhs, const T& rhs) noexcept
	{
		return lhs *= rhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator*(const T& lhs, Vector<T, N> rhs) noexcept
	{
		return rhs *= lhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator/(Vector<T, N> lhs, const T& rhs) noexcept
	{
		return lhs /= rhs;
	}

	template <typename T, std::size_t N>
	std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v)
	{
		os << '(';
		std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(os, ", "));
		os << v[N - 1];
		os << ')';
		return os;
	}

	template <typename T, std::size_t N>
	inline constexpr T dot(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		return static_cast<T>(std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0.0));
	}

	template <typename T, std::size_t N>
	inline constexpr T lengthSquared(const Vector<T, N>& v) noexcept
	{
		return dot(v, v);
	}

	template <typename T, std::size_t N>
	inline constexpr T length(const Vector<T, N>& v) noexcept
	{
		return std::sqrt(lengthSquared(v));
	}

}


#endif