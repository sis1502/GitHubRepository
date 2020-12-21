#subdir.mk

OBJ +=	./NetConfig/NetConfigClientCarry.o64 \
		./NetConfig/NetConfigClientData.o64 \
		./NetConfig/NetConfigClientImpl.o64
		
DEP +=	./NetConfig/NetConfigClientCarry.d \
		./NetConfig/NetConfigClientData.d \
		./NetConfig/NetConfigClientImpl.d

./NetConfig/%.o64 : ../NetConfig/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
