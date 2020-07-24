#include "stdafx.h"
#include "bypass.h"

Bypass::Bypass() {}

Bypass::~Bypass() {
	if (m_hProcess != NULL) CloseHandle(m_hProcess);
}

bool Bypass::Attach(DWORD dwPid) {
	m_hProcess = OpenProcess(PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_VM_OPERATION, TRUE, dwPid);
	if (m_hProcess != NULL) return true; return false;
}

bool Bypass::Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
	if (ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead)) return true; return false;
}

bool Bypass::Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
	if (WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten)) return true; return false;
}

HANDLE Bypass::GetProcessHandle(){
	return Bypass::m_hProcess;
}

bool Bypass::Close() {
	if (CloseHandle(m_hProcess))return true; return false;
}