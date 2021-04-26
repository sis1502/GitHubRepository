#include "RSAProc.h"

using namespace Sis_;

int main(int agrc, char *argv[])
{
	CRSAProc rsa;

	//cout << "GenerateRSAKey:" << rsa.GenerateRSAKey() << endl;

	rsa.Init(2048, GetRunningDirectory() + "private_key.pem", GetRunningDirectory() + "public_key.pem");

	string clear;
	clear.assign(300, 'a');
	cout << "clear:" << clear << endl;

	string strEncrypt;
	//cout << "string max_size:" << strEncrypt.max_size() << endl;
	rsa.EncryptWithPrivate(clear, strEncrypt);
	cout << strEncrypt << ":" << strEncrypt.size() << endl;

	string strDecrypt;
	rsa.DecryptWithPublic(strEncrypt, strDecrypt);
	cout << strDecrypt << ":" << strDecrypt.size() << endl;

	while (!getchar())
	{
		//...
	}

	return 0;
}
