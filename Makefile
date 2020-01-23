GCC=
CXXFLAGS=--std=c++17
CXXFLAGS_BEHIND=
SRC=src/main.cpp src/engine.cpp
TODOCHECKER=stage/todochecker
UNIT_SRC=unit_tests/unit.cpp src/engine.cpp
UNIT_STAGE=stage/unit
STAGE=stage
UNAME_S := $(shell uname)
ifeq ($(UNAME_S), Darwin)
	GCC=g++
endif
ifeq ($(UNAME_S), Linux)
	GCC += g++8
	CXXFLAGS_BEHIND += -lstdc++fs
endif

all: unit todochecker

todochecker: 
	mkdir -p $(STAGE)
	$(GCC) $(CXXFLAGS) $(SRC) $(CXXFLAGS_BEHIND) -o $(TODOCHECKER)

unit:
	mkdir -p $(STAGE)
	$(GCC) $(CXXFLAGS) $(UNIT_SRC) $(CXXFLAGS_BEHIND) -o $(UNIT_STAGE)

clean:
	 rm stage/*
