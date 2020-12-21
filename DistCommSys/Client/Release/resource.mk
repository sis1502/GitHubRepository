#resource.mk

Version = 1.0.0.2

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD -D_CONSOLE -D_UNITTEST
LIB = -lprotobuf -lupb -lgrpc -lgrpc++ -lgpr -laddress_sorting -lgrpc++_reflection -lpthread -ldl
LIB_FLAG = -L../../grpc/lib -L../../grpc/lib64
INC =	-I../../PubUtil \
		-I../../grpc/include \
		-I../../ \
		-I../ \
		-I../FileTran \
		-I../MsgTran \
		-I../NetConfig \
		-I../NetDirectory \
		-I../NetWaterMark
OBJ = 
DEP = 
TARGET = Client_$(Version)


