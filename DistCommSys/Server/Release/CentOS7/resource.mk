#resource.mk

Version = 1.0.0.1

CXX = g++
CXX_FLAG = -c -fpermissive -fPIC -std=c++11 -MMD
LIB = -lprotobuf -lupb -lgrpc -lgrpc++ -lgpr -laddress_sorting -lgrpc++_reflection -lpthread -ldl
LIB_FLAG = -L../../../grpc/CentOS7/lib -L../../../grpc/CentOS7/lib64
INC =	-I../../../ \
		-I../../../grpc/CentOS7 \
		-I../../../grpc_Generated/CentOS7
OBJ = 
DEP = 
TARGET = Server_$(Version)


