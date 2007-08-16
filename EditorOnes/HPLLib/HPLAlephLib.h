#ifndef _HPL_ALEPH_LIB_
#define _HPL_ALEPH_LIB_

//just for AlephOne
#include "HPLMapTool.h"
#include "HPLSelectData.h"
#include "HPLDoneHistory.h"
#include "HPLViewGridManager.h"
#include "HPLEventManager.h"
#include "HPLStockManager.h"
#include "HPLShapesManager.h"
#include "HPLVisualModeManager.h"
#include "HPLCopyPasteManager.h"

//ˆê”ÊŒü‚¯
#include "HPLMath.h"
#include "HPLStringModifier.h"
#include "HPLQuickSort.h"
#include "HPLSurfaceModifier.h"
#include "HPLError.h"

#ifdef WX
#include "wx/wx.h"

//wxWidgetsê—pŠÖ”
//char->wx
namespace wx{
	namespace string{
		wxString getString(const char* format, ...)
		{
			char message[BUF_MAX];
			va_list maker;
			va_start(maker, format);
			vsprintf(message, format, maker);
			wxString str = wxConvertMB2WX(message);
			return str;
		}
	};
};
#endif

#endif
