#subdir.mk

OBJ +=	./NetDirectory/NetDirectoryClientCarry.o64 \
		./NetDirectory/NetDirectoryClientData.o64 \
		./NetDirectory/NetDirectoryClientImpl.o64
		
DEP +=	./NetDirectory/NetDirectoryClientCarry.d \
		./NetDirectory/NetDirectoryClientData.d \
		./NetDirectory/NetDirectoryClientImpl.d

./NetDirectory/%.o64 : ../NetDirectory/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
