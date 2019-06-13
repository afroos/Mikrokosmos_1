add_executable(UnitTests UnitTests.cpp)

target_sources(UnitTests PRIVATE 
	BodyTest.cpp
	CircleTest.cpp
	ColliderTest.cpp
	MaterialTest.cpp
	SIUnitsTest.cpp
	VectorTest.cpp
	WorldTest.cpp
)

target_link_libraries(UnitTests Mikrokosmos)