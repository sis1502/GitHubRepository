#Builder.sh

rm -rf *.h *.cc

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../grpc/CentOS7/lib:../../grpc/CentOS7/lib64

../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --cpp_out=./ ../Metadata.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --grpc_out=./ --plugin=protoc-gen-grpc=../../grpc/CentOS7/bin/grpc_cpp_plugin ../Metadata.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --cpp_out=./ ../FileTran.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --grpc_out=./ --plugin=protoc-gen-grpc=../../grpc/CentOS7/bin/grpc_cpp_plugin ../FileTran.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --cpp_out=./ ../MsgTran.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --grpc_out=./ --plugin=protoc-gen-grpc=../../grpc/CentOS7/bin/grpc_cpp_plugin ../MsgTran.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --cpp_out=./ ../NetConfig.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --grpc_out=./ --plugin=protoc-gen-grpc=../../grpc/CentOS7/bin/grpc_cpp_plugin ../NetConfig.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --cpp_out=./ ../NetDirectory.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --grpc_out=./ --plugin=protoc-gen-grpc=../../grpc/CentOS7/bin/grpc_cpp_plugin ../NetDirectory.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --cpp_out=./ ../NetWaterMark.proto
../../grpc/CentOS7/bin/protoc-3.12.2.0 -I../ --grpc_out=./ --plugin=protoc-gen-grpc=../../grpc/CentOS7/bin/grpc_cpp_plugin ../NetWaterMark.proto
