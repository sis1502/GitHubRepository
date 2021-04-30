#Makefile

include resource.mk

include subdir.mk

all : $(OBJ)
	$(CXX) $(OBJ) $(LIB) $(LIB_FLAG) -o $(TARGET)
	
clean :
	rm -rf $(TARGET) $(OBJ) $(DEP) 
