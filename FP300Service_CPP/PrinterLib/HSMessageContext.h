#pragma once

#ifdef WIN32
#include <Windows.h>
#else
typedef unsigned char byte;
#endif


#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "DevInfo.h"
#include "openssl/dh.h"
#include "openssl/x509v3.h"
 #include <openssl/hmac.h>


using namespace std;


namespace ExDevice
{
	enum PaddingMode
	{
		None = 1,
		PKCS7 = 2,
		Zeros = 3,
		ANSIX923 = 4,
		ISO10126 = 5,
	};
	enum CipherMode
	{
		CBC = 1,
		ECB = 2,
		OFB = 3,
		CFB = 4,
		CTS = 5,
	};

	class ICryptoTransform
	{
	public :
		EVP_CIPHER_CTX *ctx;
		const EVP_CIPHER *	chiper;

		vector<byte> IV;
		vector<byte> Key;
		CipherMode Mode;
		PaddingMode Padding;

		bool fEncrypt;

		ICryptoTransform();
		virtual ~ICryptoTransform();
		
		virtual vector<byte> TransformFinalBlock(vector<byte>inputBuffer, int inputOffset, int inputCount);
	};
	class SymmetricAlgorithm
	{

	public :
		virtual ICryptoTransform *CreateEncryptor() = 0;
		virtual ICryptoTransform *CreateDecryptor() = 0;

		
	};

	class Rijndael : public SymmetricAlgorithm
	{
	public:
		virtual ICryptoTransform *CreateEncryptor();
		virtual ICryptoTransform *CreateDecryptor();
	};

	class HashAlgorithm
	{
	//EVP_MD * evp_md;
	protected:
		HMAC_CTX ctx;
		EVP_MD_CTX *evpMdCtx;
		EVP_MD *evpMd;
	
	public:
		virtual ~HashAlgorithm();
		vector<byte>  ComputeHash(vector<byte> buffer);
		virtual vector<byte>  ComputeHash(vector<byte> buffer, int offset, int count);
		virtual void Initialize() = 0;
		virtual vector<byte> TransformFinalBlock(vector<byte> inputBuffer, int inputOffset, int inputCount);

		vector<byte>  Hash;
		unsigned int HashSize;
	};
	class KeyedHashAlgorithm : public HashAlgorithm
	{
	public :
		vector<byte> Key;
	};
	class HMAC : public KeyedHashAlgorithm
	{
	public:
		virtual vector<byte> TransformFinalBlock(vector<byte> inputBuffer, int inputOffset, int inputCount);
	};
	
	class HMACSHA256 : public HMAC
	{
		bool fInit;
	public :
		HMACSHA256(vector<byte> &key);
		virtual ~HMACSHA256();
		virtual void Initialize();
		virtual vector<byte>  ComputeHash(vector<byte> buffer, int offset, int count);
	};
	class SHA256 : public HashAlgorithm
	{
	public:
		SHA256();
		virtual ~SHA256();
		void Initialize();
	};

	class DiffieHellman
	{
	public:
		DiffieHellman();
		DiffieHellman(int bits);
		~DiffieHellman();
		bool GeneratePubKey();
		static vector<byte> Bignum2Vector(const BIGNUM *big_num);
		

		
		int bits;
		BIGNUM *GivenPubKey;
		vector<byte> secretKey;
		int secretKeyLength;
		DH *dh1;
	};

	class X509Certificate2
	{
		X509 *x;
	public:
		X509Certificate2(const vector<byte> &data);
		EVP_PKEY* PublicKey();
	};

	class RSA
	{
		::RSA *r;
	public:
		RSA(const vector<byte> &publicKey);
		RSA(EVP_PKEY *pKey);
		virtual ~RSA();
		bool Verify(vector<byte> signedBytes, vector<byte> sign);
	};

    class HSMessageContext
    {
	public:
        static const int MASTER_SECRET_LEN = 32;
        static const int IV_LEN = 16;
        static const int HMAC_LEN = 32;
        static const int HMAC_CHECK_VALUE_LEN = 32;
        static const int KEY_LEN_AES256 = 32;

        DeviceInfo ExDevInfo;
        DeviceInfo EcrDevInfo;
        DiffieHellman ExDH;
        DiffieHellman EcrDH;
        vector<byte> ExRandom;
        vector<byte> EcrRandom;
        vector<byte> keyEnc;
        vector<byte> keyIV;
        vector<byte> keyHMAC;

        X509Certificate2 *EcrCertificate;
        int ErrorCode;
        int PosIndex;

	private:
        KeyedHashAlgorithm *keyHMACAlg;
        SymmetricAlgorithm *symAlg;
        ICryptoTransform *encryptor;
        ICryptoTransform *decryptor;

	public :
		HSMessageContext ();
		virtual ~HSMessageContext(void);

        vector<byte> TransformData(vector<byte> buffer, int offset, int len);
        vector<byte> ComputeRecordMAC(vector<byte> buffer, int len);
        vector<byte> EncryptRecord(vector<byte> fragment, int fragmentLen, vector<byte> mac);
        void DecryptRecord(vector<byte> fragment, vector<byte>& dcrFragment, vector<byte>& dcrMAC);
        void CreateCryptoTransformer();
        static vector<byte> PRFForTLS1_2(vector<byte> secret, string label, vector<byte> data, int length);

		private:
			static vector<byte> Expand(int HashSize, HMAC* hmac, vector<byte> seed, int length);
    };

	bool CreateSecretKeys(DiffieHellman &DH);
}
