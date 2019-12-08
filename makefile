CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -I$(BOOST_HOME)

maze: maze.o
	$(CXX) $(CXXFLAGS) -o maze maze.o

clean:
	rm	main
