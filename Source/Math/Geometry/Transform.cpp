#include <Mikrokosmos/Math/Geometry/Transform.hpp>

#include <Mikrokosmos/Math/Geometry/Transform.hpp>

namespace Mikrokosmos
{
	Transform::Transform(const Translation2& t, const Rotation2& r) noexcept
	{
		setTranslation(t);
		setRotation(r);
	}

	Transform::Transform(Length tx, Length ty, Angle theta) noexcept
		: Transform{ Translation2{tx, ty}, Rotation2{theta} }
	{
	}

	Transform Transform::Identity() noexcept
	{
		return Transform{};
	}

	Length2 Transform::translation() const noexcept
	{
		return translation_;
	}

	Rotation2 Transform::rotation() const noexcept
	{
		return rotation_;
	}

	void Transform::setTranslation(const Translation2& t) noexcept
	{
		assert(isFinite(t));
		translation_ = t;
	}

	void Transform::setTranslation(Length tx, Length ty) noexcept
	{
		setTranslation(Translation2{ tx, ty });
	}

	void Transform::setRotation(const Rotation2& r) noexcept
	{
		assert(isFinite(r.angle()));
		rotation_ = r;
	}

	void Transform::setRotation(Angle theta) noexcept
	{
		setRotation(Rotation2{ theta });
	}

	Transform& Transform::translate(const Translation2& t) noexcept
	{
		*this *= Translation(t);
		return *this;
	}

	Transform& Transform::translate(Length tx, Length ty) noexcept
	{
		translate(Translation2{ tx, ty });
		return *this;
	}

	Transform& Transform::rotate(const Rotation2 & r) noexcept
	{
		*this *= Rotation(r);
		return *this;
	}

	Transform& Transform::rotate(Angle theta) noexcept
	{
		rotate(Rotation2{ theta });
		return *this;
	}

	Transform& Transform::operator*=(const Transform & m2) noexcept
	{
		setTranslation(rotation_ * m2.translation() + translation_);
		setRotation(rotation_ * m2.rotation());
		return *this;
	}

	Transform Translation(const Translation2& t) noexcept
	{
		return Transform{ t, Rotation2{ 0.0_rad } };
	}

	Transform Translation(Length tx, Length ty) noexcept
	{
		return Translation(Translation2{ tx, ty });
	}

	Transform Rotation(const Rotation2& r) noexcept
	{
		return Transform{ Translation2::Zero(), r };
	}

	Transform Rotation(Angle theta) noexcept
	{
		return Rotation(Rotation2{ theta });
	}

	bool operator==(const Transform & m1, const Transform & m2) noexcept
	{
		return (m1.translation() == m2.translation() && m1.rotation() == m2.rotation());
	}

	bool operator!=(const Transform & m1, const Transform & m2) noexcept
	{
		return !(m1 == m2);
	}

	Transform operator*(const Transform & m1, const Transform & m2) noexcept
	{
		auto result = m1;
		result *= m2;
		return result;
	}

	Length2 operator*(const Transform & m, const Length2 & v) noexcept
	{
		return m.rotation()* v + m.translation();
	}

	std::ostream& operator<<(std::ostream& os, const Transform& m)
	{
		os << m.translation() << ", " << m.rotation();
		return os;
	}

	Transform inverse(const Transform& m) noexcept
	{
		auto invR = inverse(m.rotation());
		return Transform{ -(invR * m.translation()), invR };
	}

	bool nearlyEqual(const Transform& m1, const Transform& m2, Real margin) noexcept
	{
		return ( nearlyEqual(m1.translation(), m2.translation(), margin) && 
			     nearlyEqual(m1.rotation(), m2.rotation(), margin) );
	}
}
