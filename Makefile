CXX=g++
CXXFLAGS= -std=c++11 -W -I /usr/local/include -L /usr/local/lib -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs
BIN=vidglitch

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	#$(CXX) $(CXXFLAGS) -o $(BIN) $^
	$(CXX) vidglitch.cpp -std=c++11 -g -o $(BIN) -I /usr/local/include -L /usr/local/lib -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs


%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)
