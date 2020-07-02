#pragma once
#include "vsh_hook.h"

struct addresses_t {
	uint32_t colorHook_addr;
	uint32_t setTextHook_addr;
};

extern addresses_t addresses;
