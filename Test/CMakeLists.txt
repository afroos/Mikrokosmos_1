add_executable(UnitTests UnitTests.cpp 
	SIUnitsTest.cpp
	VectorTest.cpp
)

target_link_libraries(UnitTests Mikrokosmos)