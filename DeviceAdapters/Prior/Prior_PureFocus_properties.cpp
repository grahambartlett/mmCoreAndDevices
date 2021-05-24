///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_properties.cpp
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus adapter property actions
// COPYRIGHT:     Prior Scientific Instruments Ltd., 2021
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
// CVS:           $Id: Prior.cpp 17410 2020-12-23 21:39:43Z nico $
//

#include "prior_PureFocus.h"


int PureFocus850AutoFocus::OnPort(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		pProp->Set(port.c_str());
	}
	else if (eAct == MM::AfterSet)
	{
		if (initialized)
		{
			// revert
			pProp->Set(port.c_str());
			ret = ERR_PORT_CHANGE_FORBIDDEN;
		}

		pProp->Get(port);
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnSerialNumber(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		long value;
		ret = GetSerialNumber(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set(value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnBuildVersion(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		std::string version, dateTime;
		ret = GetBuildInfo(version, dateTime);
		if (ret == DEVICE_OK)
		{
			pProp->Set(version.c_str());
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnBuildDateTime(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		std::string version, dateTime;
		ret = GetBuildInfo(version, dateTime);
		if (ret == DEVICE_OK)
		{
			pProp->Set(dateTime.c_str());
		}
	}

	return ret;
}
