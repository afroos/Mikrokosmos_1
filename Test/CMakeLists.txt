add_executable(UnitTests UnitTests.cpp 
	BodyTest.cpp
	CircleTest.cpp
	ColliderTest.cpp
	MaterialTest.cpp
	SIUnitsTest.cpp
	VectorTest.cpp
	WorldTest.cpp
)

target_link_libraries(UnitTests Mikrokosmos)