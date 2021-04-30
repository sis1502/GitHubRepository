#resource.mk

Version = 0.0.0.1

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD
LIB = -L../../../OpenSSL/CentOS7/x64/lib
LIB_FLAG = -lcrypto -lssl -ldl -lpthread
INC =	-I../../../../PubUtil \
		-I../../../OpenSSL/CentOS7/x64/include \
		-I../../../src/AES \
		-I../../../src/RSA \
		-I../../../src
OBJ = 
DEP = 
TARGET = UniEnDecrypt_$(Version)
