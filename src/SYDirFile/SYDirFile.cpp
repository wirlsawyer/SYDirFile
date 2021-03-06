// SYDirFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SYDirFileManger.h"

SYDirFileManger *g_syDirFileMgr = SYDirFileManger::Instance();

int _tmain(int argc, _TCHAR* argv[])
{


	int a = 56;
	int *b = &a; 
	int c = *b;

	std::vector<SYDirInfo*> *vecDirInfo = g_syDirFileMgr->GetDrives();

	WCHAR wszPath[80];
	for (unsigned int i=0; i<vecDirInfo->size(); i++)
	{
		SYDirInfo *info = vecDirInfo->at(i);
		info->Print();
	}

	wsprintf(wszPath, L"%suninstall.txt", vecDirInfo->at(vecDirInfo->size()-1));

	bool bResult = g_syDirFileMgr->IsExistWithFileName(wszPath);

	if (bResult)
	{
		OutputDebugString(L"Exist\n");
	}else{
		OutputDebugString(L"No Exist\n");
	}
	


	//WCHAR Root[10]= "C:\\";
	WCHAR Volumelabel[20];
	DWORD SerialNumber;
	DWORD MaxCLength;
	DWORD FileSysFlag;
	WCHAR FileSysName[10];
	GetVolumeInformation( L"F:\\",Volumelabel,255,&SerialNumber,&MaxCLength,&FileSysFlag,FileSysName,255);
	printf("標籤名稱(Volumelabel) = %s\n",Volumelabel);
	printf("標籤序號(SerialNumber) = 0x%x\n",*(&SerialNumber));
	printf("系統允許最大檔案名長度(MaxCLength) = 0x%x\n",*(&MaxCLength));
	printf("檔案系統標識(FileSysFlag) = 0x%x\n",*(&FileSysFlag));
	printf("檔案系統名稱(FileSysName) = %s\n",FileSysName);


	FindFirstVolume(Volumelabel, sizeof(Volumelabel));



	std::vector<std::wstring>* pVecEnum = g_syDirFileMgr->EnumDirWithDirPath(L"E:\\Sample\\SYHttpServer\\src\\all\\debug\\*.*");
	for (unsigned int i=0; i<pVecEnum->size(); i++)
	{
		OutputDebugString(pVecEnum->at(i).c_str());
		OutputDebugString(L"\n");
	}


	std::vector<SYDirFileInfo*>* pVecPlusEnum = g_syDirFileMgr->EnumDirPlusWithDirPath(L"E:\\Sample\\SYHttpServer\\src\\all\\debug\\*.*");
	for (unsigned int i=0; i<pVecPlusEnum->size(); i++)
	{
		SYDirFileInfo *pFileInfo = pVecPlusEnum->at(i);
		if (pFileInfo->IsDirectory)
		{
			OutputDebugString(L"[Directory] ");
		}else{
			OutputDebugString(L"[file] ");
		}
		OutputDebugString(pFileInfo->strName.c_str());
		OutputDebugString(L"\n");
	}


	system("PAUSE");
	return 0;
}

