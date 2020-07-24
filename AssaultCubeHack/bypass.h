#ifndef BYPASS_H_
#define BYPASS_H_




#include <Windows.h>

class Bypass {
public:
	// Constructor & destructor
	Bypass();
	~Bypass();

	// Public methods
	bool Attach(DWORD dwPid);
	bool Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead = NULL);
	bool Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten = NULL);
	HANDLE GetProcessHandle();
	bool Close();

private:
	HANDLE m_hProcess = NULL;
};


#endif // BYPASS_H_





