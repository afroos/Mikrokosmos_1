#ifndef MIKROKOSMOS_MATH_GEOMETRY_TRANSFORM_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_TRANSFORM_HPP

#include <Mikrokosmos/Math/Algebra/Vector2.hpp>
#include <Mikrokosmos/Math/Geometry/Rotation2.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	using Translation2 = Length2;

	class Transform
	{
	public:

		Transform() noexcept = default;
		Transform(const Translation2& t, const Rotation2& r) noexcept;
		Transform(Length tx, Length ty, Angle theta) noexcept;

		static Transform Identity() noexcept;

		Translation2 translation() const noexcept;
		Rotation2 rotation() const noexcept;

		void setTranslation(const Translation2& t) noexcept;
		void setTranslation(Length tx, Length ty) noexcept;
		void setRotation(const Rotation2& r) noexcept;
		void setRotation(Angle theta) noexcept;

		Transform& translate(const Translation2& t) noexcept;
		Transform& translate(Length tx, Length ty) noexcept;
		Transform& rotate(const Rotation2& r) noexcept;
		Transform& rotate(Angle theta) noexcept;

		Transform& operator*=(const Transform& m2) noexcept;

	private:

		Translation2 translation_{ Translation2::Zero() };
		Rotation2 rotation_{ Rotation2::Identity() };
	};

	Transform Translation(const Translation2& t) noexcept;
	Transform Translation(Length tx, Length ty) noexcept;
	Transform Rotation(const Rotation2& r) noexcept;
	Transform Rotation(Angle theta) noexcept;

	bool operator==(const Transform& m1, const Transform& m2) noexcept;
	bool operator!=(const Transform& m1, const Transform& m2) noexcept;

	Transform operator*(const Transform& m1, const Transform& m2) noexcept;
	Length2 operator*(const Transform& m, const Length2& v) noexcept;

	std::ostream& operator<<(std::ostream& os, const Transform& m);

	Transform inverse(const Transform& m) noexcept;

	bool nearlyEqual(const Transform& m1, const Transform& m2, Real margin = 1e-15) noexcept;
}

#endif