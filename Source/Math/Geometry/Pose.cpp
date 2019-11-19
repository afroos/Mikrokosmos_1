#include <Mikrokosmos/Math/Geometry/Pose.hpp>

namespace Mikrokosmos
{
	Pose::Pose(const Length2& t, const Rotation2& r) noexcept
	{
		setPosition(t);
		setOrientation(r);
	}

	Pose::Pose(Length tx, Length ty, Angle theta) noexcept
		: Pose{ Length2{tx, ty}, Rotation2{theta} }
	{
	}

	Pose Pose::Identity() noexcept
	{
		return Pose{};
	}

	Length2 Pose::position() const noexcept
	{
		return position_;
	}

	Rotation2 Pose::orientation() const noexcept
	{
		return orientation_;
	}

	void Pose::setPosition(const Length2& p) noexcept
	{
		assert(isFinite(p));
		position_ = p;
	}

	void Pose::setPosition(Length px, Length py) noexcept
	{
		setPosition(Length2{ px, py });
	}

	void Pose::setOrientation(const Rotation2& r) noexcept
	{
		assert(isFinite(r.angle()));
		orientation_ = r;
	}

	void Pose::setOrientation(Angle theta) noexcept
	{
		setOrientation(Rotation2{ theta });
	}

	Pose& Pose::translate(const Length2& t) noexcept
	{
		*this *= Translation(t);
		return *this;
	}

	Pose& Pose::translate(Length tx, Length ty) noexcept
	{
		translate(Length2{ tx, ty });
		return *this;
	}

	Pose& Pose::rotate(const Rotation2 & r) noexcept
	{
		*this *= Rotation(r);
		return *this;
	}

	Pose& Pose::rotate(Angle theta) noexcept
	{
		rotate(Rotation2{ theta });
		return *this;
	}

	Pose& Pose::operator*=(const Pose & m2) noexcept
	{
		setPosition(orientation_ * m2.position() + position_);
		setOrientation(orientation_ * m2.orientation());
		return *this;
	}

	Pose Translation(const Length2& t) noexcept
	{
		return Pose{ t, Rotation2{ 0.0_rad } };
	}

	Pose Translation(Length tx, Length ty) noexcept
	{
		return Translation(Length2{ tx, ty });
	}

	Pose Rotation(const Rotation2& r) noexcept
	{
		return Pose{ Length2::Zero(), r };
	}

	Pose Rotation(Angle theta) noexcept
	{
		return Rotation(Rotation2{ theta });
	}

	bool operator==(const Pose & m1, const Pose & m2) noexcept
	{
		return (m1.position() == m2.position() && m1.orientation() == m2.orientation());
	}

	bool operator!=(const Pose & m1, const Pose & m2) noexcept
	{
		return !(m1 == m2);
	}

	Pose operator*(const Pose & m1, const Pose & m2) noexcept
	{
		auto result = m1;
		result *= m2;
		return result;
	}

	Length2 operator*(const Pose & m, const Length2 & v) noexcept
	{
		return m.orientation()* v + m.position();
	}

	std::ostream& operator<<(std::ostream& os, const Pose& m)
	{
		os << m.position() << ", " << m.orientation();
		return os;
	}

	Pose inverse(const Pose& m) noexcept
	{
		auto invR = inverse(m.orientation());
		return Pose{ -(invR * m.position()), invR };
	}

	bool nearlyEqual(const Pose& m1, const Pose& m2, Real margin) noexcept
	{
		return ( nearlyEqual(m1.position(), m2.position(), margin) && 
			     nearlyEqual(m1.orientation(), m2.orientation(), margin) );
	}

	bool isFinite(const Pose& m) noexcept
	{
		return(isFinite(m.position()) && isFinite(m.orientation().angle()));
	}
}
