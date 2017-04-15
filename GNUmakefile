CXX = clang++

INC = -I./include
LIB = -L./lib

LINKS = -lfmsynth -lasound

OFILE = ./bin/synther

LYROBJF = Sine.o

OBJ = Main.o ISnd.o Rndr.o Lyr.o Drctr.o $(addprefix Lyr/, $(LYROBJF))

OBJF = $(addprefix obj/, $(OBJ))

all: $(OBJF) bin
	$(CXX) -g -pthread -o $(OFILE) $(OBJF) $(LIB) $(LINKS)

$(OBJF) : dirs #dep

obj/%.o: src/%.cpp
	$(CXX) -g -Weverything -Wno-padded -Wno-c++98-compat -std=c++11 -pthread -c $(INC) -o $@ $<

dep: dirs
	# libfmsynth
	$(MAKE) -C ./modules/libfmsynth
	cp ./modules/libfmsynth/libfmsynth.a ./lib/libfmsynth.a
	cp -a ./modules/libfmsynth/include ./

dirs:
	mkdir -p ./bin
	mkdir  -p ./lib
	mkdir -p ./obj
	mkdir -p ./obj/Lyr
	mkdir -p ./obj/Lyr

clean: obj
	rm -R ./obj
