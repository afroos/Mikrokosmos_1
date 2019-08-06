#include <Mikrokosmos/Math/Geometry/Transform.hpp>

namespace Mikrokosmos
{
	/*
	constexpr Transform::Transform(Length2 translation, Angle rotation) noexcept
	{
		setTranslation(translation);
		//setRotation(rotation);
	}

	constexpr Transform Transform::Identity() noexcept
	{
		return Transform{};
	}

	constexpr Transform Transform::Translation(Length2 t) noexcept
	{
		return Transform{t, 0.0_rad};
	}

	constexpr Transform Transform::Translation(Length x, Length y) noexcept
	{
		return Translation(Length2{x, y});
	}

	constexpr Transform Transform::Rotation(Angle a) noexcept
	{
		return Transform{ Length2{}, a };
	}

	constexpr Length2 Transform::translation() const noexcept
	{
		return translation_;
	}

	constexpr Angle Transform::rotation() const noexcept
	{
		// ???
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

	void Transform::setRotation(Angle a) noexcept
	{
		// ???
	}

	constexpr Transform& Transform::translate(Length2 t) noexcept
	{
		setTranslation(translation_ + t);
	}

	constexpr Transform& Transform::translate(Length x, Length y) noexcept
	{
		translate(Length2{ x, y });
	}

	constexpr Transform& Transform::rotate(Angle a) noexcept
	{
		// ???
	}

	constexpr Transform Transform::inverse() const noexcept
	{
		// ???
	}

	constexpr bool operator==(const Transform & t1, const Transform & t2) noexcept
	{
		return (t1.translation() == t2.translation() && t1.rotation() == t2.rotation());
	}

	constexpr bool operator!=(const Transform & t1, const Transform & t2) noexcept
	{
		return !(t1 == t2);
	}

	constexpr Transform operator*=(Transform & t1, const Transform & t2) noexcept
	{
		// ???
	}

	constexpr Transform operator*(const Transform & t1, const Transform & t2) noexcept
	{
		auto result{ t1 };
		result *= t2;
		return result;
	}

	constexpr Length2 operator*(const Transform & t, const Length2 v) noexcept
	{
		// ???
	}

	constexpr bool isFinite(const Transform & t)
	{
		return (isFinite(t.translation()) && isFinite(t.rotation()));
	}
	*/
}