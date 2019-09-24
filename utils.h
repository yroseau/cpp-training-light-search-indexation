#pragma once

#include "types.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if (nullptr != x) { delete x; x = nullptr; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) if (nullptr != x) { delete[] x; x = nullptr; }
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(x) if (nullptr != x) { free(x); x = nullptr; }
#endif
