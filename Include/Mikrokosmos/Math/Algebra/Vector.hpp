#ifndef MIKROKOSMOS_MATH_ALGEBRA_VECTOR_HPP
#define MIKROKOSMOS_MATH_ALGEBRA_VECTOR_HPP

#include <Mikrokosmos/Common/Real.hpp>
#include <array>
#include <cassert>

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

		static constexpr Vector Zero() noexcept { return Vector(); }

		template<typename = std::enable_if_t<(N > 0)>>
		static constexpr Vector UnitX() noexcept { return unit(0); }

		template<typename = std::enable_if_t<(N > 1)>>
		static constexpr Vector UnitY() noexcept { return unit(1); }

		template<typename = std::enable_if_t<(N > 2)>>
		static constexpr Vector UnitZ() noexcept { return unit(2); }

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

	template <typename T, std::size_t N>
	inline constexpr bool operator==(const Vector<T, N>& v1, const Vector<T, N>& v2) noexcept
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (v1[i] != v2[i])
			{
				return false;
			}
		}
		return true;
	}

	template <typename T, std::size_t N>
	inline constexpr bool operator!=(const Vector<T, N>& v1, const Vector<T, N>& v2) noexcept
	{
		return !(v1 == v2);
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator+(const Vector<T, N>& v) noexcept
	{
		return v;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator-(const Vector<T, N>& v) noexcept
	{
		auto result = v;
		for (size_t i = 0; i < N; ++i)
		{
			result[i] = -v[i];
		}
		return result;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N>& operator+=(Vector<T, N>& v1, const Vector<T, N>& v2) noexcept
	{
		for (size_t i = 0; i < N; ++i)
		{
			v1[i] += v2[i];
		}
		return v1;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N>& operator-=(Vector<T, N>& v1, const Vector<T, N>& v2) noexcept
	{
		for (size_t i = 0; i < N; ++i)
		{
			v1[i] -= v2[i];
		}
		return v1;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} *T2{}) > ::value >>
	inline constexpr Vector<T1, N>& operator*=(Vector<T1, N>& v1, const Vector<T2, N>& v2) noexcept
	{
		for (size_t i = 0; i < N; ++i) 
		{
			v1[i] *= v2[i];
		}
		return v1;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} *T2{}) > ::value >>
		inline constexpr Vector<T1, N> operator*=(Vector<T1, N>& v1, const T2 s) noexcept
	{
		for (size_t i = 0; i < N; ++i) 
		{
			v1[i] *= s;
		}
		return v1;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} / T2{}) > ::value >>
	inline constexpr Vector<T1, N>& operator/=(Vector<T1, N>& v1, const Vector<T2, N>& v2) noexcept
	{
		for (size_t i = 0; i < N; ++i) 
		{
			v1[i] /= v2[i];
		}
		return v1;
	}

	template <typename T1, typename T2, std::size_t N, typename = std::enable_if_t < std::is_same < T1, decltype(T1{} / T2{}) > ::value >>
	inline constexpr Vector<T1, N> operator/=(Vector<T1, N>& v, const T2 s) noexcept
	{
		for (size_t i = 0; i < N; ++i) 
		{
			v[i] /= s;
		}
		return v;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator+(const Vector<T, N>& v1, const Vector<T, N>& v2) noexcept
	{
		auto result{ v1 };
		return result += v2;
	}

	template <typename T, std::size_t N>
	inline constexpr Vector<T, N> operator-(const Vector<T, N>& v1, const Vector<T, N>& v2) noexcept
	{
		auto result{ v1 };
		return result -= v2;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} *T2{}), std::size_t N >
	inline constexpr Vector<T3, N> operator*(const Vector<T1, N>& v, const T2 s) noexcept
	{
		Vector<T3, N> result;
		for (size_t i = 0; i < N; ++i) 
		{
			result[i] = v[i] * s;
		}
		return result;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} *T2{}), std::size_t N >
	inline constexpr Vector<T3, N> operator*(const T1 s, const Vector<T2, N>& v2) noexcept
	{
		return v2 * s;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} / T2{}), std::size_t N>
	inline constexpr Vector<T3, N> operator/(const Vector<T1, N>& v, const T2 s) noexcept
	{
		Vector<T3, N> result;
		for (size_t i = 0; i < N; ++i) 
		{
			result[i] = v[i] / s;
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
	inline bool isFinite(const Vector<T, N>& v)
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (!isFinite(v[i])) return false;
		}
		return true;
	}

	template <typename T, std::size_t N>
	inline bool isZero(const Vector<T, N>& v)
	{
		return (v == Vector<T, N>::Zero());
	}

	template <typename T, std::size_t N>
	inline bool nearlyEqual(const Vector<T, N>& v1, const Vector<T, N>& v2, Real tolerance = Real{ 1e-15 }) noexcept
	{
		for (size_t i = 0; i < N; ++i)
		{
			if (!nearlyEqual(v1[i], v2[i], tolerance))
			{
				return false;
			}
		}
		return true;
	}

	template <typename T1, typename T2, typename T3 = decltype(T1{} * T2{}), std::size_t N>
	inline constexpr T3 dot(const Vector<T1, N>& v1, const Vector<T2, N>& v2) noexcept
	{
		auto result = T3{};
		for (size_t i = 0; i < N; ++i)
		{
			result += v1[i] * v2[i];
		}
		return result;
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