#resource.mk

Version = 1.0.0.1
SolutionDir = /home/sis/WorkingStation/DistCommSys
GrpcDir = $(SolutionDir)/grpc
ProtoDir = $(SolutionDir)/grpc_Generated
ProjectDir = $(SolutionDir)/Server

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD
LIB = -lprotobuf -lupb -lgrpc -lgrpc++ -lgpr -laddress_sorting -lgrpc++_reflection -lpthread -ldl
LIB_FLAG = -L$(GrpcDir)/lib -L$(GrpcDir)/lib64
INC =	-I$(SolutionDir)/PubUtil \
		-I$(GrpcDir)/include \
		-I$(ProtoDir) \
		-I$(ProjectDir) \
		-I$(ProjectDir)/FileTran \
		-I$(ProjectDir)/MsgTran \
		-I$(ProjectDir)/NetConfig \
		-I$(ProjectDir)/NetDirectory \
		-I$(ProjectDir)/NetWaterMark
OBJ = 
DEP = 
TARGET = Server_$(Version)


