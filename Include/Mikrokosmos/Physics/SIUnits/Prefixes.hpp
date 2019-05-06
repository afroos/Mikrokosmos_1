#ifndef MIKROKOSMOS_PHYSICS_SIUNITS_PREFIXES_HPP
#define MIKROKOSMOS_PHYSICS_SIUNITS_PREFIXES_HPP

#include <Mikrokosmos/Common/Real.hpp>

namespace Mikrokosmos
{
	constexpr auto yocto = Real{ 1e-24 };
	constexpr auto zepto = Real{ 1e-21 };
	constexpr auto atto  = Real{ 1e-18 };
	constexpr auto femto = Real{ 1e-15 };
	constexpr auto pico  = Real{ 1e-12 };
	constexpr auto nano  = Real{ 1e-09 };
	constexpr auto micro = Real{ 1e-06 };
	constexpr auto milli = Real{ 1e-03 };
	constexpr auto centi = Real{ 1e-02 };
	constexpr auto deci  = Real{ 1e-01 };
	constexpr auto deka  = Real{ 1e+01 };
	constexpr auto hecto = Real{ 1e+02 };
	constexpr auto kilo  = Real{ 1e+03 };
	constexpr auto mega  = Real{ 1e+06 };
	constexpr auto giga  = Real{ 1e+09 };
	constexpr auto tera  = Real{ 1e+12 };
	constexpr auto peta  = Real{ 1e+15 };
	constexpr auto exa   = Real{ 1e+18 };
	constexpr auto zetta = Real{ 1e+21 };
	constexpr auto yotta = Real{ 1e+24 };
}

#endif