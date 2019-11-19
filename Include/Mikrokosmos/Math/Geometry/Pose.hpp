#ifndef MIKROKOSMOS_MATH_GEOMETRY_POSE_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_POSE_HPP

#include <Mikrokosmos/Math/Algebra/Vector2.hpp>
#include <Mikrokosmos/Math/Geometry/Rotation2.hpp>
#include <Mikrokosmos/Physics/SIUnits.hpp>

namespace Mikrokosmos
{
	class Pose
	{
	public:

		Pose() noexcept = default;
		Pose(const Length2& p, const Rotation2& r) noexcept;
		Pose(Length px, Length py, Angle theta) noexcept;

		static Pose Identity() noexcept;

		Length2 position() const noexcept;
		Rotation2 orientation() const noexcept;

		void setPosition(const Length2& p) noexcept;
		void setPosition(Length px, Length py) noexcept;
		void setOrientation(const Rotation2& r) noexcept;
		void setOrientation(Angle theta) noexcept;

		Pose& translate(const Length2& t) noexcept;
		Pose& translate(Length tx, Length ty) noexcept;
		Pose& rotate(const Rotation2& r) noexcept;
		Pose& rotate(Angle theta) noexcept;

		Pose& operator*=(const Pose& m2) noexcept;

	private:

		Length2 position_{ Length2::Zero() };
		Rotation2 orientation_{ Rotation2::Identity() };
	};

	Pose Translation(const Length2& t) noexcept;
	Pose Translation(Length tx, Length ty) noexcept;
	Pose Rotation(const Rotation2& r) noexcept;
	Pose Rotation(Angle theta) noexcept;

	bool operator==(const Pose& m1, const Pose& m2) noexcept;
	bool operator!=(const Pose& m1, const Pose& m2) noexcept;

	Pose operator*(const Pose& m1, const Pose& m2) noexcept;
	Length2 operator*(const Pose& m, const Length2& v) noexcept;

	std::ostream& operator<<(std::ostream& os, const Pose& m);

	Pose inverse(const Pose& m) noexcept;

	bool nearlyEqual(const Pose& m1, const Pose& m2, Real margin = 1e-15) noexcept;

	bool isFinite(const Pose& m) noexcept;
}

#endif