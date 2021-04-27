export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../OpenSSL/CentOS7/lib:.

rm -rf core.*

ulimit -c unlimited

./RSAWithOpenSSL_0.0.0.1
