add_executable(UnitTests UnitTests.cpp)

target_sources(UnitTests PRIVATE 
	BoxTest.cpp
	CircleTest.cpp
	ColliderTest.cpp
	Rotation2Test.cpp
	MaterialTest.cpp
	RealTest.cpp
	RigidBodyTest.cpp
	SIUnitsTest.cpp
	PoseTest.cpp
	VectorTest.cpp
	WorldTest.cpp
)

target_link_libraries(UnitTests Mikrokosmos)