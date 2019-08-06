#ifndef MIKROKOSMOS_MATH_ALGEBRA_COMPLEX_HPP
#define MIKROKOSMOS_MATH_ALGEBRA_COMPLEX_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Complex
	{
	public:

		Complex() noexcept = default;
		Complex(Real a, Real b) noexcept;
		Complex(Real r, Angle theta) noexcept;

		static Complex Identity() noexcept;

		Real a() const noexcept;
		Real b() const noexcept;

		Complex& operator*=(const Complex& z2) noexcept;

	private:

		Real a_{ 1.0 };
		Real b_{ 0.0 };
	};

	bool operator==(const Complex& z1, const Complex& z2) noexcept;
	bool operator!=(const Complex& z1, const Complex& z2) noexcept;
	Complex operator*(const Complex& z1, const Complex& z2) noexcept;
	Length2 operator*(const Complex& z, const Length2 v) noexcept;
	std::ostream& operator<<(std::ostream& os, const Complex& z);

	Angle arg(const Complex& z) noexcept;
	Complex conjugate(Complex z) noexcept;

}

#endif