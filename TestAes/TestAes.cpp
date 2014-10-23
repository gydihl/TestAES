// TestAes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AES.h"
#include "string.h"

void testEncodeDecode()
{
	unsigned char key[17] = "1234567980abcdef";
	AES aes(key);

	FILE *fp = fopen("D:\\gameloading.json", "rb");
	fpos_t pos = 0;
	fgetpos(fp, &pos);
	fseek(fp, 0L, SEEK_END);
	long lFilelength = ftell(fp);
	fsetpos(fp, &pos);

	long bufSize = lFilelength;
	if (lFilelength % 16 > 0)
	{
		bufSize = 16 * (lFilelength / 16 + 1);
	}
	unsigned char *buf = new unsigned char[bufSize];
	memset(buf, 0, lFilelength);
	fread(buf, sizeof(char), lFilelength, fp);
	fclose(fp);
	memset(buf+lFilelength, 0, bufSize-lFilelength);
	printf("%s\n", buf);

	aes.encode((void*)buf, bufSize);
	FILE *fpSave = fopen("D:\\gameloading_cpp_1.json", "wb");
	fwrite(buf, sizeof(char), bufSize, fpSave);
	fclose(fpSave);

	aes.decode((void*)buf, bufSize);
	FILE *fpInv = fopen("D:\\gameloading_cpp.json", "wb");
	fwrite(buf, sizeof(char), lFilelength, fpInv);
	fclose(fpInv);
}

void testDecode()
{
	unsigned char key[17] = "1234567980abcdef";
	AES aes(key);

	FILE *fpEncode = fopen("D:\\gameloading_1.json", "rb");
	
	fpos_t pos = 0;
	fgetpos(fpEncode, &pos);
	fseek(fpEncode, 0L, SEEK_END);
	long lFilelength = ftell(fpEncode);
	fsetpos(fpEncode, &pos);

	unsigned char *buf = new unsigned char[lFilelength];
	memset(buf, 0, lFilelength);

	fread(buf, sizeof(unsigned char), lFilelength, fpEncode);
	fclose(fpEncode);

	aes.decode(buf, lFilelength);

	while (0 == buf[lFilelength-1])
	{
		--lFilelength;
	}

	FILE *fpDecode = fopen("D:\\gameloading_cpp_py.json", "wb");
	fwrite(buf, sizeof(unsigned char), lFilelength, fpDecode);
	fclose(fpDecode);
}

int _tmain(int argc, _TCHAR* argv[])
{
//	testEncodeDecode();
	testDecode();


// 	char str[32] = "¹þà¶£¬AESËã·¨À´ÁË";
// 	printf("%s\n", str);
// 	aes.Cipher((void*)str);
// 	printf("%s\n", str);
// 	aes.InvCipher((void*)str, 32);
// 	printf(str);
	return 0;
}

