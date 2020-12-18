export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../grpc/lib:.

rm -rf core.*

ulimit -c unlimited

./Conversion_0.0.0.1
