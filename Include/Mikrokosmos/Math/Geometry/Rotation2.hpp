#ifndef MIKROKOSMOS_MATH_GEOMETRY_ROTATION2_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_ROTATION2_HPP

#include <Mikrokosmos/Physics/SIUnits.hpp>

#include <complex>

namespace Mikrokosmos
{
	class Rotation2
	{
	public:

		Rotation2() noexcept = default;
		explicit Rotation2(Angle theta) noexcept;

		static Rotation2 Identity() noexcept;

		Angle angle() const noexcept;

		Rotation2& operator*=(const Rotation2& r2) noexcept;

		friend bool operator==(const Rotation2& r1, const Rotation2& r2) noexcept;
		friend Length2 operator*(const Rotation2& r, const Length2 v) noexcept;
		friend Rotation2 inverse(const Rotation2& r) noexcept;

	private:

		std::complex<Real> z_{ Real{1}, Real{0} };
	};

	bool operator!=(const Rotation2& r1, const Rotation2& r2) noexcept;
	Rotation2 operator*(const Rotation2& r1, const Rotation2& r2) noexcept;	
	std::ostream& operator<<(std::ostream& os, const Rotation2& r);

	bool nearlyEqual(const Rotation2& r1, const Rotation2& r2, Real margin = 1e-15) noexcept;
}

#endif