#include "EnDe.h"

using namespace Sis_;

int main(int agrc, char *argv[])
{
	CEnDe ed;

	unsigned char enc[] = { 0x85,0x4d,0x5e,0xdf,0x8c,0x5e,0x53,0x23,
		0xca,0xed,0xac,0x97,0xaa,0x78,0x29,0x45 };
	unsigned char dec[] = { 0x85,0x4d,0x5e,0xdf,0x8c,0x5e,0x53,0x23,
		0xca,0xed,0xac,0x97,0xaa,0x78,0x29,0x45 };

	cout << "InitAES:" << ed.InitAES(enc, 16) << endl;

	string clear;
	clear = "张建华马建龙夏宜安";
	cout << "clear:" << clear << ":" << clear.size() << endl;
	
	string cipher;

	cout << "rsa.Encrypt:" << ed.Encrypt(clear, cipher, 0) << endl;
	cout << "cipher:" << cipher << ":" << cipher.size() << endl;

	string clear_;
	cout << "rsa.Decrypt:" << ed.Decrypt(cipher, clear_, 0) << endl;
	cout << "clear_:" << clear_ << ":" << clear_.size() << endl;

	while (!getchar())
	{
		//...
	}

	return 0;
}
