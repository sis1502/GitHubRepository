#subdir.mk

OBJ +=	./FileTran/FileTranClientCarry.o64 \
		./FileTran/FileTranClientData.o64 \
		./FileTran/FileTranClientImpl.o64
		
DEP +=	./FileTran/FileTranClientCarry.d \
		./FileTran/FileTranClientData.d \
		./FileTran/FileTranClientImpl.d

./FileTran/%.o64 : ../FileTran/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
