#pragma once
#include "tv_types.h"

class EXPORTCLASS CTVPackage
{
private:
	
public:
	int iPackageIndex;
	//CTVPackage(void);
	//~CTVPackage(void);
	int CreatePackage(const char* sPackageName);
	int OpenPackage(const char* sPackageName);
	void ClosePackage(int iPackageID);
	void CloseAllPackages();
	char* GetFile(const char* sSourceFilename, int iPackageID = -1);
	char* GetFileBuffer(const char* sSourceFilename, int iPackageID = -1);
	int GetFileIndex(const char* sSourceFilename, int iPackageID = -1);
	bool ExtractFile(const char* sSourceFilename, const char* sDestinationFile, int iPackageID = -1);
	bool FileExists(const char* sFilename, int iPackageID = -1);
	void SetCheckCRC32(bool bCheckCRC32);
	bool AddFile(const char* sSourceFilename, const char* sPackFilename, int iPackageID);
	void SetArchivePassword(const char* cPassword, int iPackageID = -1);
	void CleanUp(int iPackageID = -1);
	int GetFileCount(int iPackageID = -1);
	char* GetFileName(int iPackageID, int iFileIndex);
	int GetFileSize(int iPackageID, int iFileIndex);
	bool GetFileProtected(int iPackageID, int iFileIndex);
	bool DeleteFile(const char* sFilename, int iPackageID = -1);
	bool CompactPackage(int iPackageID = -1);
};
