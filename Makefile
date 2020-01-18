GCC=g++
CXXFLAGS=--std=c++17
SRC=src/main.cpp src/engine.cpp
TODOCHECKER=stage/todochecker
UNIT_SRC=unit_tests/unit.cpp src/engine.cpp
UNIT_STAGE=stage/unit
STAGE=stage


all: unit todochecker

todochecker: 
	mkdir -p $(STAGE)
	$(GCC) $(CXXFLAGS) $(SRC) -o $(TODOCHECKER)

unit:
	mkdir -p $(STAGE)
	$(GCC) $(CXXFLAGS) $(UNIT_SRC) -o $(UNIT_STAGE)

clean:
	 rm stage/*