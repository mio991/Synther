CXX = clang++

INC = -I./include
LIB = -L./lib

LINKS = -lfmsynth

OFILE = ./bin/synther

OBJ = Main.o

all: $(OBJ)

%.o: %.cpp
	$(CXX) -Weverything -std=c++11 -c $(INC) -o ./obj/$@ $<

$(OBJ) : dep obj

dep: lib
	# libfmsynth
	$(MAKE) -C ./modules/libfmsynth
	cp ./modules/libfmsynth/libfmsynth.a ./lib/libfmsynth.a
	cp -a ./modules/libfmsynth/include ./

lib:
	mkdir ./lib


obj:
	mkdir ./obj

.PHONY: all $(OBJ)
