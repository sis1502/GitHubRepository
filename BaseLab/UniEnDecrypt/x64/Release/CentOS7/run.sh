export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../OpenSSL/CentOS7/x64/lib:.

rm -rf core.*

ulimit -c unlimited

./UniEnDecrypt_0.0.0.1
