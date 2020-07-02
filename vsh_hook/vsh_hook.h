#pragma once
#pragma comment(lib, "libhttp_stub.a")
#pragma comment(lib, "libhttp_util_stub.a")
#pragma comment(lib, "libnet_stub.a")
#pragma comment(lib, "netctl_stub")
#pragma comment(lib, "libsysutil_stub.a")
#pragma comment(lib, "libc.a")
#pragma comment(lib, "libstdc++.a")
#pragma comment(lib, "libstdc++_stub.a")
#pragma comment(lib, "libsn.a")
#pragma comment(lib, "libm.a")
#pragma comment(lib, "libio_stub.a")
#pragma comment(lib, "liblv2_stub.a")
#pragma comment(lib, "libfs_stub.a")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cellstatus.h>
#include <sys/prx.h>
#include <cell/sysmodule.h>
#include <sys/process.h>
#include <sys/ppu_thread.h>
#include <sys/syscall.h>
#include <sys/tty.h>
#include <ppu_intrinsics.h>
#include <ctype.h>
#include <sys/timer.h>
#include <fastmath.h>
#include <cell/pad.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sys\sys_time.h>
#include <time.h>
#include <cell/cell_fs.h>
#include <cell/http.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sys\socket.h>
#include <netinet\in.h>
#include <arpa\inet.h>
#include <sys/sys_time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/net.h>
#include <netex/errno.h>
#include <inttypes.h>  
#include <sys/memory.h>
#include <stdarg.h>
#include <cstdlib>
#include <sys/time_util.h>
#include <assert.h>
#include <sys/return_code.h>
#include <stddef.h>
#include <math.h>
#include <typeinfo>
#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <net\if_dl.h>
#include <cell/fs/cell_fs_errno.h>
#include <cell/fs/cell_fs_file_api.h>
#include <sys/fs.h>
#include <sys/ss_get_open_psid.h>
#include <netex\libnetctl.h>

#define CDECL extern "C"
CDECL void* _sys_malloc(size_t size);
#define malloc _sys_malloc
CDECL void _sys_free(void* ptr);
#define free _sys_free
CDECL void* _sys_memalign(size_t boundary, size_t size);
#define memalign _sys_memalign
CDECL void* _sys_memchr(const void* s, int c, size_t n);
#define memchr _sys_memchr
CDECL int _sys_memcmp(const void* s1, const void* s2, size_t n);
#define memcmp _sys_memcmp
CDECL void* _sys_memcpy(void* dest, const void* src, size_t n);
#define memcpy _sys_memcpy
CDECL void* _sys_memset(void* m, int c, size_t n);
#define memset _sys_memset
CDECL void* _sys_memmove(void* str1, const void* str2, size_t n);
#define memmove _sys_memmove
CDECL int _sys_printf(const char* fmt, ...);
#define printf _sys_printf
CDECL int _sys_snprintf(char* buffer, size_t len, const char* fmt, ...);
#define snprintf _sys_snprintf
CDECL int _sys_sprintf(char* buffer, const char* fmt, ...);
#define sprintf _sys_sprintf
CDECL char* _sys_strcat(char* dest, const char* src);
#define strcat _sys_strcat
CDECL char* _sys_strchr(const char* s, int c);
#define strchr _sys_strchr
CDECL int _sys_strcmp(const char* s1, const char* s2);
#define strcmp _sys_strcmp
CDECL char* _sys_strcpy(char* dest, const char* src);
#define strcpy _sys_strcpy
CDECL size_t _sys_strlen(const char* str);
#define strlen _sys_strlen
CDECL int _sys_strncasecmp(const char* s1, const char* s2, size_t n);
#define strncasecmp _sys_strncasecmp
CDECL char* _sys_strncat(char* dest, const char* src, size_t n);
#define strncat _sys_strncat
CDECL int _sys_strncmp(const char* s1, const char* s2, size_t n);
#define strncmp _sys_strncmp
CDECL char* _sys_strncpy(char* dest, const char* src, size_t n);
#define strncpy _sys_strncpy
CDECL char* _sys_strrchr(const char* s, int c);
#define strrchr _sys_strrchr
CDECL int _sys_tolower(int c);
#define tolower _sys_tolower
CDECL int _sys_toupper(int c);
#define toupper _sys_toupper
CDECL int _sys_vprintf(const char* format, va_list arg);
#define vprintf _sys_vprintf
CDECL int _sys_vsnprintf(char* buffer, std::size_t buf_size, const char* format, va_list arg);
#define vsnprintf _sys_vsnprintf
CDECL int _sys_vsprintf(char* s, const char* format, va_list arg);
#define vsprintf _sys_vsprintf

#include "vsh_addresses.h"

#define TOC 0x00705648 //update for other ps3 updates


struct CellPadData_t {
	uint64_t unknown;
	uint32_t cellPads;
};

enum CellPadButtons {
	BUTTON_LTRIG = 0x1,
	BUTTON_RTRIG = 0x2,

	BUTTON_LSHLDR = 0x4,
	BUTTON_RSHLDR = 0x8,

	BUTTON_LSTICK = 0x20000,
	BUTTON_RSTICK = 0x40000,

	DPAD_UP = 0x100000,
	DPAD_DOWN = 0x400000,
	DPAD_LEFT = 0x800000,
	DPAD_RIGHT = 0x200000,

	BUTTON_A = 0x40,
	BUTTON_B = 0x20,
	BUTTON_X = 0x80,
	BUTTON_Y = 0x10,
};

int32_t sys_dbg_read_process_memory(uint64_t address, void *data, size_t size);
int32_t sys_dbg_write_process_memory(uint64_t address, const void *data, size_t size);
int sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size);
int sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size);
void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub);
void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub);
bool bCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask);
unsigned long FindPattern(unsigned long dwAddress, unsigned long dwLen, unsigned char* bMask, char* szMask);
