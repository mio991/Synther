CXX = clang++

INC = -I./include
LIB = -L./lib

LINKS = -lfmsynth

OFILE = ./bin/synther

dep:
	# libfmsynth
	$(MAKE) -C ./modules/libfmsynth
	mkdir ./lib
	cp ./modules/libfmsynth/libfmsynth.a ./lib/libfmsynth.a
	cp -a ./modules/libfmsynth/include ./

.PHONY: all

all: $(dep) ./src/Main.cpp
	$(CXX) -Weverything $(INC) ./src/Main.cpp $(LIB) $(LINKS) -o ./bin/snther
