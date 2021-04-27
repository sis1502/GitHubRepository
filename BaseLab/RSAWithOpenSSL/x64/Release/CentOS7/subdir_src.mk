#subdir.mk

OBJ +=	./main.o64 
		
DEP +=	./main.d 

./%.o64 : ../../../src/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
