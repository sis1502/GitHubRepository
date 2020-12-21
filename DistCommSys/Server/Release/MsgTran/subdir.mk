#subdir.mk

OBJ +=	./MsgTran/MsgTranServerCarry.o64 \
		./MsgTran/MsgTranServerData.o64 \
		./MsgTran/MsgTranServerImpl.o64
		
DEP +=	./MsgTran/MsgTranServerCarry.d \
		./MsgTran/MsgTranServerData.d \
		./MsgTran/MsgTranServerImpl.d

./MsgTran/%.o64 : ../MsgTran/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
