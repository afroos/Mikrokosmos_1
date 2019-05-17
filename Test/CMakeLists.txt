add_executable(UnitTests UnitTests.cpp 
	BodyTest.cpp
	SIUnitsTest.cpp
	VectorTest.cpp
)

target_link_libraries(UnitTests Mikrokosmos)