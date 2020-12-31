#subdir.mk

OBJ +=	./NetConfig/NetConfigServerCarry.o64 \
		./NetConfig/NetConfigServerData.o64 \
		./NetConfig/NetConfigServerImpl.o64
		
DEP +=	./NetConfig/NetConfigServerCarry.d \
		./NetConfig/NetConfigServerData.d \
		./NetConfig/NetConfigServerImpl.d

./NetConfig/%.o64 : ../../NetConfig/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
