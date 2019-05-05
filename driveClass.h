#include <windows.h>
#include <string>

#pragma pack(push, 1)

typedef struct {
  BYTE Offset_OEM[3];           // �������� �� ����� �������� �������
  BYTE OEM_Name[8];             // ��� �������� �������
  BYTE BytesPerSector[2];       // ���������� ���� � �������
  BYTE SectorsPerCluster;       // ���������� �������� � ��������
  BYTE Offset_TotalSectors[26]; // �������� �� �������� ���������� �������� � ��
  ULONGLONG TotalSectors;       // ���������� �������� � �������� �������
} ntfsBootRecord;

#pragma pack(pop)

class driveClass {
protected:
	HANDLE fileHandle;				// ���������� ��������� ���������� (������� �����)
	BYTE *fsName;					// �������� �������� �������
	DWORD bytesPerSector;
	DWORD sectorsPerCluster;
	DWORD totalClusters;
	ntfsBootRecord *currentRecord;	// ������� ����������� ������

	HANDLE open(const WCHAR *fileName);     // �������� �����
	void setFsAttributes();                 // ������ ��������� � ��������
	void printHexBuffer(BYTE * buffer);     // ����������� ������� � HEX ����
	void close();                           // �������� �����

public:
	driveClass();                           		// �����������

	DWORD numOfClustersToRead;
	DWORD firstClusterToRead;

	BYTE *getFsName();
	DWORD getBytesPerSector();
	DWORD getSectorsPerCluster();
	DWORD getBytesPerCluster();
	DWORD getTotalClusters();
	bool checkBootRecord(const WCHAR *fileName);    // �������� �� ������������ �� � NTFS
	void readClusters();                            // ����� ������������ ���������

	~driveClass();                                  // ����������
};


