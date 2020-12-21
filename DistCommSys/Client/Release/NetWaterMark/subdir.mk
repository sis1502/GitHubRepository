#subdir.mk

OBJ +=	./NetWaterMark/NetWaterMarkClientCarry.o64 \
		./NetWaterMark/NetWaterMarkClientData.o64 \
		./NetWaterMark/NetWaterMarkClientImpl.o64
		
DEP +=	./NetWaterMark/NetWaterMarkClientCarry.d \
		./NetWaterMark/NetWaterMarkClientData.d \
		./NetWaterMark/NetWaterMarkClientImpl.d

./NetWaterMark/%.o64 : ../NetWaterMark/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
