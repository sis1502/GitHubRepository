#subdir.mk


### src

OBJ +=	./main.o64 \
		./EnDe.o64
		
DEP +=	./main.d \
		./Ende.d

./%.o64 : ../../../src/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
	
	
### AES

OBJ +=	./AESProc.o64

DEP +=	./AESProc.d

./%.o64 : ../../../src/AES/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
	

### RSA

#OBJ +=	./RSAProc.o64

#DEP +=	./RSAProc.d

#./%.o64 : ../../../src/RSA/%.cpp
#	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
