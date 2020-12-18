#resource.mk

Version = 0.0.0.1

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD -D_DEBUG -D_TIMECOUNT
LIB = 
LIB_FLAG = 
INC =	-I../../PubUtil \
		-I../src/Conversion \
		-I../src
OBJ = 
DEP = 
TARGET = Conversion_$(Version)
