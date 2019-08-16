#include <Mikrokosmos/Math/Algebra/Transform.hpp>

namespace Mikrokosmos
{
	
	Transform::Transform(Length2 translation, Angle rotation) noexcept
	{
		setTranslation(translation);
		setRotation(rotation);
	}

	Transform Transform::Identity() noexcept
	{
		return Transform{};
	}

	Transform Transform::Translation(Length2 t) noexcept
	{
		return Transform{t, 0.0_rad};
	}

	Transform Transform::Translation(Length x, Length y) noexcept
	{
		return Translation(Length2{x, y});
	}

	Transform Transform::Rotation(Angle theta) noexcept
	{
		return Transform{ Length2{}, theta };
	}

	Length2 Transform::translation() const noexcept
	{
		return translation_;
	}

	Angle Transform::rotation() const noexcept
	{
		return rotation_.angle();
	}

	void Transform::setTranslation(Length2 t) noexcept
	{
		assert(isFinite(t));
		translation_ = t;
	}

	void Transform::setTranslation(Length x, Length y) noexcept
	{
		setTranslation(Length2{ x, y });
	}

	void Transform::setRotation(Angle theta) noexcept
	{
		assert(isFinite(theta));
		//rotation_.setAngle(theta);
	}

	Transform& Transform::translate(Length2 t) noexcept
	{
		setTranslation(translation_ + t);
		return *this;
	}

	Transform& Transform::translate(Length x, Length y) noexcept
	{
		translate(Length2{ x, y });
		return *this;
	}

	Transform& Transform::rotate(Angle theta) noexcept
	{
		auto totalRotation = rotation_ * Rotation2(theta);
		setRotation(totalRotation.angle());
		return *this;
	}

	bool operator==(const Transform & t1, const Transform & t2) noexcept
	{
		return (t1.translation() == t2.translation() && t1.rotation() == t2.rotation());
	}

	bool operator!=(const Transform & t1, const Transform & t2) noexcept
	{
		return !(t1 == t2);
	}

	Transform operator*=(Transform & t1, const Transform & t2) noexcept
	{
		// ???
		return Transform{};
	}

	Transform operator*(const Transform & t1, const Transform & t2) noexcept
	{
		auto result{ t1 };
		result *= t2;
		return result;
	}

	Length2 operator*(const Transform & t, const Length2& v) noexcept
	{
		// ???
		return Length2{};
	}

	Transform inverse(const Transform& t) noexcept
	{
		// ???
		return Transform{};
	}

	bool isFinite(const Transform & t)
	{
		return (isFinite(t.translation()) && isFinite(t.rotation()));
	}
	
}