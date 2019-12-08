CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -I$(BOOST_HOME)

main: maze.o
	$(CXX) $(CXXFLAGS) -o main maze.o

clean:
	rm	main
