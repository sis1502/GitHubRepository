#resource.mk

Version = 0.0.0.1

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD
LIB = 
LIB_FLAG = 
INC =	-I../../../PubUtil \
		-I../../src/Convertor \
		-I../../src
OBJ = 
DEP = 
TARGET = Conversion_$(Version)
