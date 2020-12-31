#subdir.mk

OBJ +=	./FileTran/FileTranServerCarry.o64 \
		./FileTran/FileTranServerData.o64 \
		./FileTran/FileTranServerImpl.o64
		
DEP +=	./FileTran/FileTranServerCarry.d \
		./FileTran/FileTranServerData.d \
		./FileTran/FileTranServerImpl.d

./FileTran/%.o64 : ../../FileTran/%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
