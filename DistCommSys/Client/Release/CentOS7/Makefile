#Makefile

include resource.mk

include grpc_Generated/subdir.mk
include FileTran/subdir.mk
include MsgTran/subdir.mk
include NetConfig/subdir.mk
include NetDirectory/subdir.mk
include NetWaterMark/subdir.mk
include Client/subdir.mk

all : $(OBJ)
	$(CXX) $(OBJ) $(LIB) $(LIB_FLAG) -o $(TARGET)
	
clean :
	rm -rf $(TARGET) $(OBJ) $(DEP) 
