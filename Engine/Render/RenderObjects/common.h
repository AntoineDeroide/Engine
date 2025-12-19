#pragma once

#include <direct.h>
#include <WindowsX.h>
#include "d3dx12.h"

#define PRINT_COM_ERROR(msg, result) { _com_error err(result); LPCTSTR errMsg = err.ErrorMessage(); PRINT_DEBUG(msg); PRINT_DEBUG(errMsg);}