cmake_minimum_required(VERSION 3.13)

project(Mikrokosmos VERSION 0.0.1 LANGUAGES CXX)

option(MIKROKOSMOS_BUILD_STATIC_LIBS "Build Mikrokosmos static libraries." ON)
option(MIKROKOSMOS_BUILD_SHARED_LIBS "Build Mikrokosmos shared libraries." OFF)
option(MIKROKOSMOS_BUILD_EXAMPLE "Build Mikrokosmos example applications." OFF)
option(MIKROKOSMOS_BUILD_TESTBED "Build Mikrokosmos testbed application." OFF)
option(MIKROKOSMOS_BUILD_TEST "Build Mikrokosmos unit test application." ON)
option(MIKROKOSMOS_BUILD_BENCHMARK "Build Mikrokosmos benchmark application." OFF)
option(MIKROKOSMOS_INSTALL "Install Mikrokosmos libraries, includes, and CMake scripts." OFF)
option(MIKROKOSMOS_INSTALL_DOC "Install Mikrokosmos documentation." OFF)
option(MIKROKOSMOS_ENABLE_COVERAGE "Enable Mikrokosmos code coverage generation." OFF)

if(MIKROKOSMOS_BUILD_STATIC_LIBS)
	add_library(Mikrokosmos STATIC)
	target_include_directories(Mikrokosmos PUBLIC Include)
	target_compile_features(Mikrokosmos INTERFACE cxx_std_17)
	add_subdirectory(Source)
endif(MIKROKOSMOS_BUILD_STATIC_LIBS)

if(MIKROKOSMOS_BUILD_EXAMPLE)
	add_subdirectory(Example)
endif(MIKROKOSMOS_BUILD_EXAMPLE)

if(MIKROKOSMOS_BUILD_TESTBED)
	add_subdirectory(Testbed)
endif(MIKROKOSMOS_BUILD_TESTBED)

if(MIKROKOSMOS_BUILD_TEST)
	enable_testing()
	add_subdirectory(Test)
endif(MIKROKOSMOS_BUILD_TEST)

if(MIKROKOSMOS_BUILD_BENCHMARK)
	add_subdirectory(Benchmark)
endif(MIKROKOSMOS_BUILD_BENCHMARK)