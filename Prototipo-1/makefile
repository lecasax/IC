CC = g++
CFLAGS = -c -Wall
COPENGL = -lglut -lGLU -lm -lGL
CFLAGSEXTRA = `wx-config --libs core, base, aui --cxxflags --gl-libs`
COPTIMIZATION = -Ofast -O2 -std=c++11

CPPSOURCES = $(wildcard DOT_CPP/* .cpp)
HSOURCES = -I DOT_H/

all: programa


programa: $(CPPSOURCES:cpp=o)

	g++ $(COPTIMIZATION) -o $@ $^  $(CFLAGSEXTRA) $(COPENGL)
	mv $^ DOT_O

%.o: %.cpp

	g++ -c $< $(HSOURCES) -o $@ $(COPENGL) $(CFLAGSEXTRA) $(CFLAGS)

