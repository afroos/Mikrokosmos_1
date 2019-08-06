#include <Mikrokosmos/Math/Algebra/Complex.hpp>

#include <cmath>

namespace Mikrokosmos
{

	Complex::Complex(Real a, Real b) noexcept 
	: a_{a},
	  b_{b}
	{
		//assert(isFinite(a) && isFinite(b));
	}

	Complex::Complex(Real r, Angle theta) noexcept
	{
		assert(isFinite(r) && isFinite(theta));
		a_ = r * cos(theta.magnitude);
		b_ = r * sin(theta.magnitude);
	}

	Complex Complex::Identity() noexcept
	{
		return Complex{ 1.0, 0.0 };
	}

	Real Complex::a() const noexcept
	{
		return a_;
	}

	Real Complex::b() const noexcept
	{
		return b_;
	}

	Complex& Complex::operator*=(const Complex& z2) noexcept
	{
		auto real = a() * z2.a() - b() * z2.b();
		auto imag = a() * z2.b() + b() * z2.a();

		a_ = real;
		b_ = imag;
		
		return *this;
	}

	bool operator==(const Complex& z1, const Complex& z2) noexcept
	{
		return ( z1.a() == z2.a() && z1.b() == z2.b() );
	}

	bool operator!=(const Complex& z1, const Complex& z2) noexcept
	{
		return !(z1 == z2);
	}

	Complex operator*(const Complex& z1, const Complex& z2) noexcept
	{
		auto result{ z1 };
		result *= z2;
		return result;
	}

	Length2 operator*(const Complex& z, const Length2 v) noexcept
	{
		auto zv = z * Complex{ v.x().magnitude, v.y().magnitude };
		return Length2{ zv.a(), zv.b() };
	}

	std::ostream& operator<<(std::ostream& os, const Complex& z)
	{
		os << '(';
		os << z.a() << ", " << z.b();
		os << ')';
		return os;
	}

	Angle arg(const Complex& z) noexcept
	{
		return Angle{ atan2(z.b(), z.a()) };
	}

	Complex conjugate(Complex z) noexcept
	{
		return Complex{ z.a(), -z.b() };
	}

}