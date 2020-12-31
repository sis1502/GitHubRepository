#subdir.mk

OBJ +=	./grpc_Generated/Metadata.grpc.pb.o64 \
		./grpc_Generated/Metadata.pb.o64 \
		./grpc_Generated/FileTran.grpc.pb.o64 \
		./grpc_Generated/FileTran.pb.o64 \
		./grpc_Generated/MsgTran.grpc.pb.o64 \
		./grpc_Generated/MsgTran.pb.o64 \
		./grpc_Generated/NetConfig.grpc.pb.o64 \
		./grpc_Generated/NetConfig.pb.o64 \
		./grpc_Generated/NetDirectory.grpc.pb.o64 \
		./grpc_Generated/NetDirectory.pb.o64 \
		./grpc_Generated/NetWaterMark.grpc.pb.o64 \
		./grpc_Generated/NetWaterMark.pb.o64 
		
DEP +=	./grpc_Generated/Metadata.grpc.pb.d \
		./grpc_Generated/Metadata.pb.d \
		./grpc_Generated/FileTran.grpc.pb.d \
		./grpc_Generated/FileTran.pb.d \
		./grpc_Generated/MsgTran.grpc.pb.d \
		./grpc_Generated/MsgTran.pb.d \
		./grpc_Generated/NetConfig.grpc.pb.d \
		./grpc_Generated/NetConfig.pb.d \
		./grpc_Generated/NetDirectory.grpc.pb.d \
		./grpc_Generated/NetDirectory.pb.d \
		./grpc_Generated/NetWaterMark.grpc.pb.d \
		./grpc_Generated/NetWaterMark.pb.d 
		
./grpc_Generated/%.o64 : ../../../grpc_Generated/CentOS7/%.cc
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
