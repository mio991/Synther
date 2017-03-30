CXX = clang++

INC = -I./include
LIB = -L./lib

LINKS = -lfmsynth

OFILE = ./bin/synther

OBJ = Main.o

#VPATH = src/

all: $(addprefix obj/, $(OBJ)) bin dep
	$(CXX) $(LIB) $(LINKS) -o $(OFILE) $(addprefix obj/, $(OBJ))

obj/%.o: src/%.cpp
	echo compiled $@
	$(CXX) -Weverything -std=c++11 -c $(INC) -o $@ $<

$(OBJ) : dep obj

dep: lib
	# libfmsynth
	$(MAKE) -C ./modules/libfmsynth
	cp ./modules/libfmsynth/libfmsynth.a ./lib/libfmsynth.a
	cp -a ./modules/libfmsynth/include ./

# Dirs
bin:
	mkdir ./bin

lib:
	mkdir ./lib

obj:
	mkdir ./obj

.PHONY: all $(OBJ)

#all: $(dep) ./src/Main.cpp
	#$(CXX) -Weverything $(INC) ./src/Main.cpp $(LIB) $(LINKS) -o ./bin/snther
