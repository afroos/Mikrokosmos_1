add_executable(UnitTests UnitTests.cpp)

target_sources(UnitTests PRIVATE 
	BoxTest.cpp
	CircleTest.cpp
	ColliderTest.cpp
	ComplexTest.cpp
	MaterialTest.cpp
	RealTest.cpp
	RigidBodyTest.cpp
	SIUnitsTest.cpp
	VectorTest.cpp
	WorldTest.cpp
)

target_link_libraries(UnitTests Mikrokosmos)