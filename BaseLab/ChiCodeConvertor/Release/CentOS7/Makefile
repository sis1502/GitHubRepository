#Makefile

include resource.mk

include subdir_Conversion.mk
#include subdir_PubUtil.mk
include subdir_src.mk

all : $(OBJ)
	$(CXX) $(OBJ) $(LIB) $(LIB_FLAG) -o $(TARGET)
	
clean :
	rm -rf $(TARGET) $(OBJ) $(DEP) 
