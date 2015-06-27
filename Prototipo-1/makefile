CC = g++
CFLAGS = -c -Wall 
COPENGL = -lglut -lGLU -lm -lGL 
CFLAGSEXTRA = `wx-config --libs --cxxflags --gl-libs` 

CPPSOURCES = $(wildcard DOT_CPP/* .cpp)
HSOURCES = -I DOT_H/

all: programa


programa: $(CPPSOURCES:cpp=o)

	g++ -Ofast -O2 -o $@ $^  $(CFLAGSEXTRA) $(COPENGL)
	mv $^ DOT_O

%.o: %.cpp 

	g++ -c $< $(HSOURCES) -o $@ $(COPENGL) $(CFLAGSEXTRA) $(CFLAGS)
	
