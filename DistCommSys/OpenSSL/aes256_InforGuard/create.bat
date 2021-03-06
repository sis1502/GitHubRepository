openssl genrsa -passout pass:1111 -aes256 -out ca.key 2048

openssl req -passin pass:1111 -new -x509 -days 3650 -key ca.key -out ca.crt -subj "/C=CN/ST=HuNan/L=ChangSha/O=CVICSE/OU=gRPC/CN=InforGuard"

openssl genrsa -passout pass:1111 -aes256 -out server_privatekey.pem 2048

openssl req -passin pass:1111 -new -key server_privatekey.pem -out server_csr.pem -subj "/C=CN/ST=HuNan/L=ChangSha/O=CVICSE/OU=gRPC/CN=InforGuard"

openssl x509 -req -passin pass:1111 -days 3650 -in server_csr.pem -CA ca.crt -CAkey ca.key -CAcreateserial -out server_self_signed_crt.pem

openssl rsa -passin pass:1111 -in server_privatekey.pem -out server_privatekey.pem

openssl genrsa -passout pass:1111 -aes256 -out client_privatekey.pem 2048

openssl req -passin pass:1111 -new -key client_privatekey.pem -out client_csr.pem -subj "/C=CN/ST=HuNan/L=ChangSha/O=CVICSE/OU=gRPC/CN=InforGuard"

openssl x509 -passin pass:1111 -req -days 3650 -in client_csr.pem -CA ca.crt -CAkey ca.key -CAcreateserial -out client_self_signed_crt.pem

openssl rsa -passin pass:1111 -in client_privatekey.pem -out client_privatekey.pem