## TODOCHECKER

ToDoChecker is a console application that checks through your directory for any TODOs indicated. 
It will then return you the files indicated in the directory.

## Requirements

For Ubuntu
- Do note that you will need g++-8 for this.
- Before building, do run g++ -v to check your version.

For Mac
- This is tested on clang11
- Please replace CC to CC=g++
- and remove $(CXXFLAGS_BEHIND)

## Build Instructions

- Just run "make" on the directory
- This will build both the unit tests and the application itself into the folder called stage.

## Run Instructions

- run ./stage/todochecker for simple check
- run ./stage/todochecker -h for the options to run the todochecker with
