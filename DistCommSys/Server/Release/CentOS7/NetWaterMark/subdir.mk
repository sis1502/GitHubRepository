#subdir.mk

OBJ +=	./NetWaterMark/NetWaterMarkServerCarry.o64 \
		./NetWaterMark/NetWaterMarkServerData.o64 \
		./NetWaterMark/NetWaterMarkServerImpl.o64
		
DEP +=	./NetWaterMark/NetWaterMarkServerCarry.d \
		./NetWaterMark/NetWaterMarkServerData.d \
		./NetWaterMark/NetWaterMarkServerImpl.d

./NetWaterMark/%.o64 : ../../NetWaterMark/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
