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


int PureFocus850AutoFocus::OnObjectiveSelect(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		if (initialized)
		{
			ret = GetObjective(objectiveSelect);
		}

		if (ret == DEVICE_OK)
		{
			pProp->Set(objectiveSelect);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if ((value < 1) || (value > 6))
		{
			ret = ERR_INVALID_VALUE;
		}
		else if (initialized)
		{
			ret = SetObjective(value);
			if (ret == DEVICE_OK)
			{
				objectiveSelect = value;
			}
			else
			{
				// Restore
				pProp->Set(objectiveSelect);
			}
		}
		else
		{
			// Restore
			pProp->Set(objectiveSelect);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnServoInhibit(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		if (initialized)
		{
			ret = GetServoInhibit(servoInhibit);
		}

		if (ret == DEVICE_OK)
		{
			pProp->Set((long)servoInhibit);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if ((value < 0) || (value > 1))
		{
			ret = ERR_INVALID_VALUE;
		}
		else if (initialized)
		{
			bool boolValue = (value != 0);
			ret = SetServoInhibit(boolValue);
			if (ret == DEVICE_OK)
			{
				servoInhibit = boolValue;
			}
			else
			{
				// Restore
				pProp->Set((long)servoInhibit);
			}
		}
		else
		{
			// Restore
			pProp->Set((long)servoInhibit);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnDigipotControlsOffset(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		if (initialized)
		{
			ret = GetDigipotControlsOffset(digipotControlsOffset);
		}

		if (ret == DEVICE_OK)
		{
			pProp->Set((long)digipotControlsOffset);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if ((value < 0) || (value > 1))
		{
			ret = ERR_INVALID_VALUE;
		}
		else if (initialized)
		{
			bool boolValue = (value != 0);
			ret = SetDigipotControlsOffset(boolValue);
			if (ret == DEVICE_OK)
			{
				digipotControlsOffset = boolValue;
			}
			else
			{
				// Restore
				pProp->Set((long)digipotControlsOffset);
			}
		}
		else
		{
			// Restore
			pProp->Set((long)digipotControlsOffset);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnOffsetPositionUm(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		if (initialized)
		{
			ret = GetOffsetPositionUm(offsetPositionUm);
		}

		if (ret == DEVICE_OK)
		{
			pProp->Set(offsetPositionUm);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (initialized)
		{
			ret = SetOffsetPositionUm(value);
			if (ret == DEVICE_OK)
			{
				offsetPositionUm = value;
			}
			else
			{
				// Restore
				pProp->Set(offsetPositionUm);
			}
		}
		else
		{
			// Restore
			pProp->Set(offsetPositionUm);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusPositionUm(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		if (initialized)
		{
			ret = GetFocusPositionUm(focusPositionUm);
		}

		if (ret == DEVICE_OK)
		{
			pProp->Set(focusPositionUm);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (initialized)
		{
			ret = SetFocusPositionUm(value);
			if (ret == DEVICE_OK)
			{
				focusPositionUm = value;
			}
			else
			{
				// Restore
				pProp->Set(focusPositionUm);
			}
		}
		else
		{
			// Restore
			pProp->Set(focusPositionUm);
		}
	}
	else
	{
		// No action
	}

	return ret;
}
