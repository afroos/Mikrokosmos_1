#ifndef MIKROKOSMOS_MATH_GEOMETRY_SHAPE_HPP
#define MIKROKOSMOS_MATH_GEOMETRY_SHAPE_HPP

namespace Mikrokosmos
{
	class Shape
	{
	public:

		Shape(const Shape&) = delete;
		Shape& operator=(const Shape&) = delete;

		virtual ~Shape() = 0;

	protected:

		Shape();

	private:

	};
}

#endif
