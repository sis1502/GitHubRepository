export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../grpc/lib:.

rm -rf core.*

ulimit -c unlimited

./Client_1.0.0.2
