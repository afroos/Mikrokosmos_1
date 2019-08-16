#include <Mikrokosmos/Math/Algebra/Rotation2.hpp>

#include <cmath>

namespace Mikrokosmos
{
	Rotation2::Rotation2(Angle theta) noexcept
	{
		assert(isFinite(theta));
		z_ = std::polar<Real>(Real{ 1 }, theta.magnitude);
	}

	Rotation2 Rotation2::Identity() noexcept
	{
		return Rotation2{ 0.0_rad };
	}

	Angle Rotation2::angle() const noexcept
	{
		return Angle{ std::arg(z_) };
	}

	Rotation2 Rotation2::inverse() noexcept
	{
		Rotation2 r;
		r.z_ = std::conj(z_);
		return r;
	}

	Rotation2& Rotation2::operator*=(const Rotation2& r2) noexcept
	{
		z_ *= r2.z_;
		return *this;
	}

	bool operator==(const Rotation2& r1, const Rotation2& r2) noexcept
	{
		return ( r1.z_ == r2.z_ );
	}

	Length2 operator*(const Rotation2& r, const Length2 v) noexcept
	{
		auto rv = r.z_ * std::complex<Real>{ v.x().magnitude, v.y().magnitude };
		return Length2{ rv.real(), rv.imag() };
	}

	bool operator!=(const Rotation2& r1, const Rotation2& r2) noexcept
	{
		return !(r1 == r2);
	}

	Rotation2 operator*(const Rotation2& r1, const Rotation2& r2) noexcept
	{
		auto result = r1;
		result *= r2;
		return result;
	}

	std::ostream& operator<<(std::ostream& os, const Rotation2& r)
	{
		os << r.angle();
		return os;
	}

}