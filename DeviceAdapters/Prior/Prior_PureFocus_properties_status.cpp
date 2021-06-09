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

#include <sstream>


int PureFocus850AutoFocus::OnCalculationABCD(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set("0,0,0,0");
	}
	else if (eAct == MM::BeforeGet)
	{
		double a = 0.0, b = 0.0, c = 0.0, d = 0.0;
		ret = GetABCD(a, b, c, d);
		if (ret == DEVICE_OK)
		{
			std::ostringstream stringValue;
			stringValue << a << "," << b << "," << c << "," << d;
			pProp->Set(stringValue.str().c_str());
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusPidPosition(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		double value = 0.0;
		ret = GetFocusPidPosition(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set(value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusPidError(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		double value = 0.0;
		ret = GetFocusPidError(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set(value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusPidOutput(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		double value = 0.0;
		ret = GetFocusPidOutput(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set(value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusPidTarget(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		double value = 0.0;
		ret = GetFocusPidTarget(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set(value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusState(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		bool value = false;
		ret = GetFocusState(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set((long)value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnTimeToInFocus(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		double value = 0.0;
		ret = GetTimeToInFocus(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set(value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInterfaceCorrect(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		bool value = false;
		ret = GetInterfaceCorrect(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set((long)value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnIsOffsetMoving(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		bool value = false;
		ret = GetIsOffsetMoving(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set((long)value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnIsFocusDriveMoving(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		bool value = false;
		ret = GetIsFocusDriveMoving(value);
		if (ret == DEVICE_OK)
		{
			pProp->Set((long)value);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnPositiveLimitSwitch(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		bool positive = false, negative = false;
		ret = GetLimitSwitches(positive, negative);
		if (ret == DEVICE_OK)
		{
			pProp->Set((long)positive);
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnNegativeLimitSwitch(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		bool positive = false, negative = false;
		ret = GetLimitSwitches(positive, negative);
		if (ret == DEVICE_OK)
		{
			pProp->Set((long)negative);
		}
	}

	return ret;
}
