#subdir.mk

OBJ +=	./RSAProc.o64 
		
DEP +=	./RSAProc.d 

./%.o64 : ../../../src/RSA/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
