#subdir.mk

OBJ +=	./Client/GRPCChannel.o64 \
		./Client/GRPCClient.o64 \
		./Client/main.o64
		
DEP +=	./Client/GRPCChannel.d \
		./Client/GRPCClient.d \
		./Client/main.d

./Client/%.o64 : ../../%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
