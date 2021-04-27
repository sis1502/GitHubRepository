#resource.mk

Version = 0.0.0.1

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD
LIB = -L../../../OpenSSL/CentOS7
LIB_FLAG = -lcrypto -lssl -ldl -lpthread
INC =	-I../../../../PubUtil \
		-I../../../src/RSA \
		-I../../../src \
		-I../../../OpenSSL/CentOS7
OBJ = 
DEP = 
TARGET = RSAWithOpenSSL_$(Version)
