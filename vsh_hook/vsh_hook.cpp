#include "vsh_hook.h"

SYS_MODULE_INFO( vsh_hook, 0, 1, 1);
SYS_MODULE_START( _vsh_hook_prx_entry );
SYS_MODULE_STOP( _vsh_hook_prx_exit );

float colorR = 255, colorG = 0, colorB = 0;
void DoColors() {
	if (colorR > 0 && colorB == 0)
	{
		colorR -= 1;
		colorG += 1;
	}
	if (colorG > 0 && colorR == 0)
	{
		colorG -= 1;
		colorB += 1;
	}
	if (colorB > 0 && colorG == 0)
	{
		colorR += 1;
		colorB -= 1;
	}
}
uint32_t colorDo;
void colorHook_Stub(uint32_t r3, uint32_t r4) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
void colorHook_Hook(uint32_t r3, uint32_t r4) {
	const char * itemName = (char*)(r4 + 0x8);
	colorDo += 1;
	if (colorDo == 60) {
		DoColors();
		colorDo = 0;
	}
	*(float*)(r4 + 0x120) = colorR / 255.0f;
	*(float*)(r4 + 0x124) = colorG / 255.0f;
	*(float*)(r4 + 0x128) = colorB / 255.0f;
	colorHook_Stub(r3, r4);
}


void prx_start(uint64_t r3) {
	printf("thread started\n");
	addresses.colorHook_addr = FindPattern(0x00010200, 0x0063F7EC, (unsigned char*)"\x3D\x20\x00\x00\x7C\x08\x02\xA6\xF8\x21\x00\x00\x39\x29\x00\x00\xF8\x01\x00\xA0\x7D\x25\x4B\x78", (char*)"xx??xxxxxx??xx??xxxxxxxx"); printf("pattern for colorHook_addr found at address 0x%X\n", addresses.colorHook_addr);
	sys_timer_usleep(3000 * 1000);
	if (addresses.colorHook_addr) {
		printf("hooking address %p\n", addresses.colorHook_addr);
		HookFunctionStart(addresses.colorHook_addr, *(uint32_t*)(colorHook_Hook), *(uint32_t*)(colorHook_Stub));
	}

	system_call_1(0x29, 0);
}
sys_ppu_thread_t prx_start_thread_id;
extern "C" int _vsh_hook_prx_entry(void) {
	printf("vsh_hook loaded\n");

	sys_ppu_thread_create(&prx_start_thread_id, prx_start, 0, 0, 0, 0, "prx start");
	printf("prx start thread ran\n");
	return SYS_PRX_RESIDENT;
}

extern "C" int _vsh_hook_prx_exit(void) {
	UnHookFunctionStart(addresses.colorHook_addr, *(uint32_t*)(colorHook_Stub));
	return SYS_PRX_RESIDENT;
}

int32_t sys_dbg_read_process_memory(uint64_t address, void *data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}

int32_t sys_dbg_write_process_memory(uint64_t address, const void *data, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}

int sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}

int sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}

void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub)
{
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
	sys_dbg_read_process_memory(functionStartAddress, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((functionStartAddress + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (functionStartAddress + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x20);
	sys_dbg_write_process_memory(functionStub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((newFunction >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (newFunction & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, hookFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, hookFunctionStub, 0x10);
}

void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub) {
	uint32_t normalFunctionStub[4];
	sys_dbg_read_process_memory(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, normalFunctionStub, 0x10);

	sys_dbg_read_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
}

bool bCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)
		return false;

	return (*szMask) == NULL;
}
unsigned long FindPattern(unsigned long dwAddress, unsigned long dwLen, unsigned char* bMask, char* szMask)
{
	for (unsigned long i = 0; i < dwLen; i++)
	if (bCompare((unsigned char*)(dwAddress + i), bMask, szMask))
		return (unsigned long)(dwAddress + i);

	return 0;
}

