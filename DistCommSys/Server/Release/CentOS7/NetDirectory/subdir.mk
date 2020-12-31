#subdir.mk

OBJ +=	./NetDirectory/NetDirectoryServerCarry.o64 \
		./NetDirectory/NetDirectoryServerData.o64 \
		./NetDirectory/NetDirectoryServerImpl.o64
		
DEP +=	./NetDirectory/NetDirectoryServerCarry.d \
		./NetDirectory/NetDirectoryServerData.d \
		./NetDirectory/NetDirectoryServerImpl.d

./NetDirectory/%.o64 : ../../NetDirectory/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
