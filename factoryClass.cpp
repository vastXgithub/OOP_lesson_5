#include <iostream>
#include "factoryClass.h"
#include "ntfsClass.h"
#include "exfatClass.h"
#include "string.h"
#include <functional>

using namespace std;

typedef struct
{
	BYTE Offset_OEM[3];           // �������� �� ����� �������� �������
	char OEM_Name[8];             // ��� �������� �������
} fsOEMname;

factoryClass::factoryClass() { }

fsClass* factoryClass::objCreator(driveClass* driveObj)
{
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0;
	fsOEMname *currentOEM = (fsOEMname*)driveObj->readRecords(sectorOffset, 1024);

	hash<string> hash_fn;
	switch ((unsigned int) hash_fn(currentOEM->OEM_Name)) {

	case 3418147480:
		return new ntfsClass(driveObj);
		break;
	case 968235445:
		return new exfatClass(driveObj);
	default:
        cout << "This file system doesn`t support!" << endl;   // ��������� ��������������
		system("pause");
		return 0;
		break;
	}
}

factoryClass::~factoryClass() { }
