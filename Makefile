EXENAME = final
OBJS = PNG.o HSLAPixel.o lodepng.o image.o main.o Graph.o airport.o datReader.o 
TEST = test

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
endif
endif

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)



airport.o: airport.cpp
	$(CXX) $(CXXFLAGS) airport.cpp

PNG.o: cs225/PNG.cpp cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

HSLAPixel.o: cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

lodepng.o: cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

datReader.o: datReader.cpp
	$(CXX) $(CXXFLAGS) datReader.cpp

image.o: image.cpp
	$(CXX) $(CXXFLAGS) image.cpp

Graph.o: Graph.cpp
	$(CXX) $(CXXFLAGS) Graph.cpp

test: output_msg PNG.o HSLAPixel.o lodepng.o cs225/catch/catchmain.cpp tests.cpp airport.cpp datReader.cpp Graph.cpp
	$(LD)  PNG.o HSLAPixel.o lodepng.o cs225/catch/catchmain.cpp tests.cpp airport.cpp datReader.cpp Graph.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) final



