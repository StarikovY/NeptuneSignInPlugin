#define CRYPT_OID_INFO_HAS_EXTRA_FIELDS 1


#include <collection.h>
#include "wincrypt.h"
#include <stdexcept>

#include "SignFileComponent.h"

// in the implementation file .cpp
using namespace SignFileComponent;
using namespace Concurrency;
using namespace Platform;
using namespace Windows;
using namespace Windows::Foundation;
#ifndef NEED1
using namespace Windows::Security::Cryptography;
using namespace Windows::Security::Cryptography::Certificates;
using namespace Windows::Security::Cryptography::Core;
#endif
using namespace System::Diagnostics;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Streams;

static int fFound = 0;

unsigned int HrFindCertificateBySubjectName(wchar_t* wszStore, wchar_t* wszSubject, PCCERT_CONTEXT* ppcCert);

IBuffer^ ReadFileToBuffer(Platform::String^ fName)
{
	auto storageFolder = ApplicationData::Current->LocalFolder;

	StorageFile^ file;

	try
	{
		auto openFileTask = storageFolder->GetFileAsync(fName);

		while (openFileTask->Status == Windows::Foundation::AsyncStatus::Started)
			;

		file = openFileTask->GetResults();
	}
	catch (Exception^ ex)
	{
	}

	if (file == nullptr)
	{
			return nullptr;
	}

	auto ReadBuf = FileIO::ReadBufferAsync(file);

	while (ReadBuf->Status == Windows::Foundation::AsyncStatus::Started)
		;

	return(ReadBuf->GetResults());
}

void SaveBufferToFile(Platform::String^ fName, IBuffer^ buffer)
{
	auto storageFolder = ApplicationData::Current->LocalFolder;
	
	StorageFile^ file;

	try
	{
		auto openFileTask = storageFolder->GetFileAsync(fName);

		while (openFileTask->Status == Windows::Foundation::AsyncStatus::Started)
		;

		file = openFileTask->GetResults();
	}
	catch (Exception^ ex)
	{
	}

		if (file == nullptr)
		{
			auto createFileTask = storageFolder->CreateFileAsync(fName);

			while (createFileTask->Status == Windows::Foundation::AsyncStatus::Started)
				;

			file = createFileTask->GetResults();
		}

		auto writeDataTask = FileIO::WriteBufferAsync(file, buffer);

		while (writeDataTask->Status == Windows::Foundation::AsyncStatus::Started)
			;
}

void SaveTextToFile(Platform::String^ fName, Platform::String^ buffer)
{
	auto storageFolder = ApplicationData::Current->LocalFolder;
	
	StorageFile^ file;
	
	try
	{
		auto openFileTask = storageFolder->GetFileAsync(fName);

		while (openFileTask->Status == Windows::Foundation::AsyncStatus::Started)
			;

		file = openFileTask->GetResults();
	}
	catch (Exception^ ex)
	{
	}

	if (file == nullptr)
	{
		auto createFileTask = storageFolder->CreateFileAsync(fName);

		while (createFileTask->Status == Windows::Foundation::AsyncStatus::Started)
			;

		file = createFileTask->GetResults();
	}

	auto writeDataTask = FileIO::WriteTextAsync(file, buffer);

	while (writeDataTask->Status == Windows::Foundation::AsyncStatus::Started)
		;
}

unsigned int SHA256(Platform::String^ data, BYTE* pbHash, DWORD* cbHashSize)
{
	DWORD Res = 0;
	BYTE HashBuf[1024];

	BCRYPT_ALG_HANDLE       hAlg = NULL;
	BCRYPT_HASH_HANDLE      hHash = NULL;
	DWORD cbData = 0;
	DWORD cbHash = 0;
	DWORD cbHashObject = sizeof(HashBuf);

	// Prepare hashing
	 //open an algorithm handle
	Res = BCryptOpenAlgorithmProvider(
		&hAlg,
		BCRYPT_SHA256_ALGORITHM,
		NULL,
		0);
	if (Res != 0)
	{
		return Res;
	}

	//calculate the size of the buffer to hold the hash object
	Res = BCryptGetProperty(
		hAlg,
		BCRYPT_HASH_LENGTH,
		(PBYTE)&cbHash,
		sizeof(DWORD),
		&cbData,
		0);

	if (Res != 0)
	{
		return Res;
	}

	if (cbHash > *cbHashSize)
	{
		Res = (DWORD)E_OUTOFMEMORY;
		return(Res);
	}
	else
		*cbHashSize = cbHash;

	Res = BCryptCreateHash(
		hAlg,
		&hHash,
		HashBuf,
		cbHashObject,
		NULL,
		0,
		0);

	int sizeHashied = 0;

	auto dataArr = data->Data();

	auto cbDataSize = data->Length()*sizeof(WCHAR);  //UNICODE!!!!

	while (sizeHashied < cbDataSize)
	{ 
		if ((cbDataSize - sizeHashied) > 2048)
		{
			Res = BCryptHashData(hHash, (PBYTE)dataArr + sizeHashied, 2048, 0);
			sizeHashied += 2048;
		}
		else
		{
			Res = BCryptHashData(hHash, (PBYTE)dataArr + sizeHashied, (cbDataSize - sizeHashied), 0);
			sizeHashied = cbDataSize;
		}
		if (Res != 0)
			return(Res);
	}
	
	Res = BCryptFinishHash(hHash, pbHash, cbHash, 0);


	if (hAlg)
	{
		BCryptCloseAlgorithmProvider(hAlg, 0);
	}

	if (hHash)
	{
		BCryptDestroyHash(hHash);
	}

	return(Res);
}

IAsyncOperation<Platform::String^>^ SigningFile::HrSignData(Platform::String^ Subject, Platform::String^ Data, Platform::String^ 
	SaveToFile, Platform::Boolean saveResults)
{
	auto certsTask = CertificateStores::FindAllAsync();

	while (certsTask->Status == AsyncStatus::Started)
		;

	auto certs = certsTask->GetResults();

	CryptographicKey^ privateKey = nullptr;

	for (Certificate^ cert : certs)
	{
		auto certName = cert->Subject;

		//skip others
		if (certName != Subject)
			continue;

		auto privateKeyTask = PersistedKeyProvider::OpenKeyPairFromCertificateAsync(cert,
			HashAlgorithmNames::Sha256, CryptographicPadding::RsaPkcs1V15);

		while (privateKeyTask->Status == AsyncStatus::Started)
			;

		privateKey = privateKeyTask->GetResults();

		//NO KEY finded
		if (privateKey != nullptr)
			break;
	}

	//NO KEY finded
	if (privateKey == nullptr)
		throw "Error NO KEY finded";

	BYTE pbHash[128];
	DWORD cbHash = sizeof(pbHash);

	auto res = SHA256(Data, pbHash, &cbHash);
	if (res != 0)
		throw "Get string hash error";

	DataWriter^ writer = ref new DataWriter();

	writer->WriteBytes(Platform::ArrayReference<BYTE>(pbHash, cbHash));

	IBuffer^ buffer = writer->DetachBuffer();

	if(saveResults)
		SaveBufferToFile("hash.hs", buffer);

	return concurrency::create_async([this, privateKey, buffer, SaveToFile, saveResults]
	{
		return create_task(CryptographicEngine::SignHashedDataAsync(privateKey, buffer)).then([SaveToFile, saveResults](task<IBuffer^> signTask)
		{
			IBuffer^ signedData;

			signedData = signTask.get();

			auto encoded = CryptographicBuffer::EncodeToBase64String(signedData);

			SaveTextToFile(SaveToFile, encoded);
			
			if (saveResults)
				SaveBufferToFile("signedbuf.snb", signedData);

			return encoded;
		});
	});
}

IAsyncOperation<Platform::Boolean>^ SigningFile::HrVerifySign(Platform::String^ Subject, Platform::String^ Data, Platform::String^ Signature)
{
	auto certsTask = CertificateStores::FindAllAsync();

	while (certsTask->Status == AsyncStatus::Started)
		;

	auto certs = certsTask->GetResults();

	CryptographicKey^ publicKey = nullptr;

	for (Certificate^ cert : certs)
	{
		auto certName = cert->Subject;

		//skip others
		if (certName != Subject)
			continue;

		publicKey = PersistedKeyProvider::OpenPublicKeyFromCertificate(cert,
			HashAlgorithmNames::Sha256, CryptographicPadding::RsaPkcs1V15);

		//NO KEY finded */
		if (publicKey != nullptr)
			break;
	}

	//NO KEY finded
	if (publicKey == nullptr)
		throw "Error NO KEY finded";

	BYTE pbHash[128];
	DWORD cbHash = sizeof(pbHash);

	auto res = SHA256(Data, pbHash, &cbHash);
	if (res != 0)
		throw "Get string hash error";

	DataWriter^ writer = ref new DataWriter();

	writer->WriteBytes(Platform::ArrayReference<BYTE>(pbHash, cbHash));

	IBuffer^ bufferData = writer->DetachBuffer();

	IBuffer^ bufferSign = CryptographicBuffer::DecodeFromBase64String(Signature); 

	bool result = CryptographicEngine::VerifySignatureWithHashInput(publicKey, bufferData, bufferSign);

	if (result)
	{
		SaveTextToFile("result.vrf", "true");
	}
	else
	{
		SaveTextToFile("result.vrf", "false");
	}
	

	return concurrency::create_async([this, result]
	{
		return result;
	});
}


