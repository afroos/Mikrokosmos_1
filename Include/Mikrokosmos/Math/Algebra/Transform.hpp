#ifndef MIKROKOSMOS_MATH_GEOMETRY_TRANSFORM_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_TRANSFORM_HPP

#include <Mikrokosmos/Math/Algebra/Rotation2.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Transform
	{
	public:

		Transform() noexcept = default;
		Transform(Length2 translation, Angle rotation) noexcept;

		static Transform Identity() noexcept;
		static Transform Translation(Length2 t) noexcept;
		static Transform Translation(Length x, Length y) noexcept;
		static Transform Rotation(Angle theta) noexcept;

		Length2 translation() const noexcept;
		Angle rotation() const noexcept;

		void setTranslation(Length2 t) noexcept;
		void setTranslation(Length x, Length y) noexcept;
		void setRotation(Angle theta) noexcept;
		Transform& translate(Length2 t) noexcept;
		Transform& translate(Length x, Length y) noexcept;
		Transform& rotate(Angle theta) noexcept;
		Transform inverse() const noexcept;

	private:

		Length2 translation_{ 0.0_m, 0.0_m };
		Rotation2 rotation_{ Rotation2::Identity() };
	};

	bool operator==(const Transform& t1, const Transform& t2) noexcept;
	bool operator!=(const Transform& t1, const Transform& t2) noexcept;
	Transform operator*=(Transform& t1, const Transform& t2) noexcept;
	Transform operator*(const Transform& t1, const Transform& t2) noexcept;
	Length2 operator*(const Transform& t, const Length2& v) noexcept;
	
	Transform inverse(const Transform& t) noexcept;
	bool isFinite(const Transform& t);

}

#endif
