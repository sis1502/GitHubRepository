export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../grpc/CentOS7/lib:.

rm -rf core.*

ulimit -c unlimited

./Server_1.0.0.1
