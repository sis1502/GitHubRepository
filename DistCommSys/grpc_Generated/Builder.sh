#Builder.sh

rm -rf *.h *.cc

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../grpc/lib:../grpc/lib64

../grpc/bin/protoc-3.12.2.0 -I./ --cpp_out=./ Metadata.proto
../grpc/bin/protoc-3.12.2.0 -I./ --grpc_out=./ --plugin=protoc-gen-grpc=../grpc/bin/grpc_cpp_plugin Metadata.proto
../grpc/bin/protoc-3.12.2.0 -I./ --cpp_out=./ FileTran.proto
../grpc/bin/protoc-3.12.2.0 -I./ --grpc_out=./ --plugin=protoc-gen-grpc=../grpc/bin/grpc_cpp_plugin FileTran.proto
../grpc/bin/protoc-3.12.2.0 -I./ --cpp_out=./ MsgTran.proto
../grpc/bin/protoc-3.12.2.0 -I./ --grpc_out=./ --plugin=protoc-gen-grpc=../grpc/bin/grpc_cpp_plugin MsgTran.proto
../grpc/bin/protoc-3.12.2.0 -I./ --cpp_out=./ NetConfig.proto
../grpc/bin/protoc-3.12.2.0 -I./ --grpc_out=./ --plugin=protoc-gen-grpc=../grpc/bin/grpc_cpp_plugin NetConfig.proto
../grpc/bin/protoc-3.12.2.0 -I./ --cpp_out=./ NetDirectory.proto
../grpc/bin/protoc-3.12.2.0 -I./ --grpc_out=./ --plugin=protoc-gen-grpc=../grpc/bin/grpc_cpp_plugin NetDirectory.proto
../grpc/bin/protoc-3.12.2.0 -I./ --cpp_out=./ NetWaterMark.proto
../grpc/bin/protoc-3.12.2.0 -I./ --grpc_out=./ --plugin=protoc-gen-grpc=../grpc/bin/grpc_cpp_plugin NetWaterMark.proto
