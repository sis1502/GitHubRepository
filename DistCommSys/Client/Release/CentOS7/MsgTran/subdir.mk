#subdir.mk

OBJ +=	./MsgTran/MsgTranClientCarry.o64 \
		./MsgTran/MsgTranClientData.o64 \
		./MsgTran/MsgTranClientImpl.o64
		
DEP +=	./MsgTran/MsgTranClientCarry.d \
		./MsgTran/MsgTranClientData.d \
		./MsgTran/MsgTranClientImpl.d

./MsgTran/%.o64 : ../../MsgTran/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
