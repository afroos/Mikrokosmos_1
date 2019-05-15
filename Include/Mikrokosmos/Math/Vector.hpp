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
		static constexpr Vector unitX() noexcept { return unit(0); }

		template<typename = std::enable_if_t<(N > 1)>>
		static constexpr Vector unitY() noexcept { return unit(1); }

		template<typename = std::enable_if_t<(N > 2)>>
		static constexpr Vector unitZ() noexcept { return unit(2); }

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

	private:
		std::array<T, N> coords{ };

		static constexpr Vector unit(SizeType index) noexcept
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
		std::transform(v.begin(), v.end(), result.begin(), std::negate<T>());
		return result;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N>& operator+=(Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::plus<T>());
		return lhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N>& operator-=(Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), std::minus<T>());
		return lhs;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} *T2{}) > ::value >>
	inline constexpr Vector<T1, N>& operator*=(Vector<T1, N>& lhs, const Vector<T2, N>& rhs) noexcept
	{
		for (size_t i = 0; i < N; ++i) {
			lhs[i] *= rhs[i];
		}
		return lhs;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} *T2{}) > ::value >>
		inline constexpr Vector<T1, N> operator*=(Vector<T1, N>& lhs, const T2 rhs) noexcept
	{
		for (size_t i = 0; i < N; ++i) {
			lhs[i] *= rhs;
		}
		return lhs;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} / T2{}) > ::value >>
	inline constexpr Vector<T1, N>& operator/=(Vector<T1, N>& lhs, const Vector<T2, N>& rhs) noexcept
	{
		for (size_t i = 0; i < N; ++i) {
			lhs[i] /= rhs[i];
		}
		return lhs;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} / T2{}) > ::value >>
	inline constexpr Vector<T1, N> operator/=(Vector<T1, N>& lhs, const T2 rhs) noexcept
	{
		for (size_t i = 0; i < N; ++i) {
			lhs[i] /= rhs;
		}
		return lhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		auto result{ lhs };
		return result += rhs;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		auto result{ lhs };
		return result -= rhs;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} *T2{}), std::size_t N >
	inline constexpr Vector<T3, N> operator*(const Vector<T1, N>& lhs, const T2 rhs) noexcept
	{
		Vector<T3, N> result;
		for (size_t i = 0; i < N; ++i) {
			result[i] = lhs[i] * rhs;
		}
		return result;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} *T2{}), std::size_t N >
	inline constexpr Vector<T3, N> operator*(const T1 lhs, const Vector<T2, N>& rhs) noexcept
	{
		return rhs * lhs;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} / T2{}), std::size_t N>
	inline constexpr Vector<T3, N> operator/(const Vector<T1, N>& lhs, const T2 rhs) noexcept
	{
		Vector<T3, N> result;
		for (size_t i = 0; i < N; ++i) {
			result[i] = lhs[i] / rhs;
		}
		return result;
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