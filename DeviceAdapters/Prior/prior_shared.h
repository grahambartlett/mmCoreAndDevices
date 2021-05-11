///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_shared.h
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior ProScan controller adapter
// COPYRIGHT:     University of California, San Francisco, 2006
// LICENSE:       This file is distributed under the BSD license.
//                License text is included with the source distribution.
//
//                This file is distributed in the hope that it will be useful,
//                but WITHOUT ANY WARRANTY; without even the implied warranty
//                of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//                IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//                CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//                INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES.
//
// AUTHOR:        Graham Bartlett, gbartlett@prior.com
//
// CVS:           $Id: prior.h 17231 2020-01-07 18:05:26Z nico $
//

#ifndef _PRIOR_SHARED_H_
#define _PRIOR_SHARED_H_

#include "../../MMDevice/MMDevice.h"
#include <string>


//////////////////////////////////////////////////////////////////////////////
// Error codes
//
#define ERR_UNKNOWN_POSITION         10002
#define ERR_PORT_CHANGE_FORBIDDEN    10004
#define ERR_SET_POSITION_FAILED      10005
#define ERR_INVALID_STEP_SIZE        10006
#define ERR_INVALID_MODE             10008
#define ERR_UNRECOGNIZED_ANSWER      10009
#define ERR_UNSPECIFIED_ERROR        10010

#define ERR_OFFSET 10100

#define ERR_INVALID_MESSAGE			(ERR_OFFSET + 4)
#define ERR_INVALID_VALUE			(ERR_OFFSET + 8)
#define ERR_INVALID_OBJECTIVE		(ERR_OFFSET + 12)

// Names of devices, which must be consistent between classes and the factory functions
extern const char* g_XYStageDeviceName;
extern const char* g_ZStageDeviceName;
extern const char* g_NanoStageDeviceName;
extern const char* g_BasicControllerName;
extern const char* g_Shutter1Name;
extern const char* g_Shutter2Name;
extern const char* g_Shutter3Name;
extern const char* g_LumenName;
extern const char* g_Wheel1Name;
extern const char* g_Wheel2Name;
extern const char* g_Wheel3Name;
extern const char* g_TTL0Name;
extern const char* g_TTL1Name;
extern const char* g_TTL2Name;
extern const char* g_TTL3Name;
extern const char* g_PureFocus850Name;
extern const char* g_PureFocus850AutoFocusName;
extern const char* g_PureFocus850ZStageName;
extern const char* g_PureFocus850ObjectiveSelectName;
extern const char* g_PureFocus850Objective1Name;
extern const char* g_PureFocus850Objective2Name;
extern const char* g_PureFocus850Objective3Name;
extern const char* g_PureFocus850Objective4Name;
extern const char* g_PureFocus850Objective5Name;
extern const char* g_PureFocus850Objective6Name;

namespace Prior
{
	// Flush all data currently in Rx queue for port.
	// @param device Device for which we are running this
	// @param core MM core instance
	// @param port Port name string
	// @returns DEVICE_OK if OK, other error value if port is inaccessible
	// @note Ideally there should be a global utility function available for this, but sadly there isn't.
	int ClearPort(MM::Device& device, MM::Core& core, std::string port);
};


#endif

