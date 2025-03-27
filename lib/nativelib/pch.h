#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>
#include <CommCtrl.h>
#include <wchar.h>
#include <string>
#include <sstream>
#include <strsafe.h>
#include <vector>
#include <map>
#include <functional>

#include "include/natlib/utils/macros.h"
#include "include/natlib/utils/utils.h"

#include "include/natlib/events/event.h"
#include "include/natlib/events/event_observer.h"
#include "include/natlib/events/event_dispatcher.h"

#include "include/natlib/base/ihandle.h"

#include "include/natlib/color.h"
#include "include/natlib/gdi.h"
#include "include/natlib/rect.h"
#include "include/natlib/size.h"
#include "include/natlib/icon.h"
#include "include/natlib/image.h"
#include "include/natlib/image_list.h"

#include "include/natlib/base/events.h"
#include "include/natlib/base/base_control.h"
#include "include/natlib/base/base_window.h"
#include "include/natlib/base/control.h"

