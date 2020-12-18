#subdir.mk

OBJ +=	./Conv.o64 
		
DEP +=	./Conv.d 

./%.o64 : ../src/Conversion/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
