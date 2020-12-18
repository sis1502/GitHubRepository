#subdir.mk

OBJ +=	./Convertor.o64 
		
DEP +=	./Convertor.d 

./%.o64 : ../../src/Convertor/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
