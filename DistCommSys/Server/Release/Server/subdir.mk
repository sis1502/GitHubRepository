#subdir.mk

OBJ +=	./Server/GRPCServer.o64 \
		./Server/main.o64
		
DEP +=	./Server/GRPCServer.d \
		./Server/main.d

./Server/%.o64 : ../%.cpp
	$(CXX) $(INC) $(CXX_FLAG) -o $@ $< 
