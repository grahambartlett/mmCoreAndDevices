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
		// Ignore request and set dummy default
		pProp->Set(0L);
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
		// Ignore request and set dummy default
		pProp->Set("");
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
		// Ignore request and set dummy default
		pProp->Set("");
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


int PureFocus850AutoFocus::OnArrayReadIndex(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		pProp->Set(arrayReadIndex);
	}
	else if (eAct == MM::AfterSet)
	{
		if ((!configInProgress) && singleChangeInProgress)
		{
			long value;
			pProp->Get(value);
			arrayReadIndex = value;
		}
	}
	else
	{
		// Ignore
	}

	return ret;
}


int PureFocus850AutoFocus::OnObjectivePresetNames(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (eAct == MM::BeforeGet)
	{
		// Get name at index
		std::string presetName;
		bool isOk = PureFocus850ObjectiveSlot::getValidPresetName(presetName, arrayReadIndex);

		if (isOk)
		{
			pProp->Set(presetName.c_str());
		}
		else
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnExecuteCommand(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set((long)NONE);
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)NONE);
	}
	else if (eAct == MM::AfterSet)
	{
		if ((!configInProgress) && singleChangeInProgress)
		{
			long value;
			pProp->Get(value);

			switch((ExecuteCommandState)value)
			{
			case SAVE_TO_UNIT:
				ret = SaveConfigurationToFlash();
				break;

			case OFFSET_STEP_UP:
				{
					double position;
					ret = PureFocus850AutoFocus::GetOffsetPositionUm(position);
					if (ret == DEVICE_OK)
					{
						std::ostringstream positionValue;
						positionValue << (position + offsetPositionStepUm);
						ret = SetProperty(propOffsetPositionStepMicrons, positionValue.str().c_str());
					}
				}
				break;

			case OFFSET_STEP_DOWN:
				{
					double position;
					ret = PureFocus850AutoFocus::GetOffsetPositionUm(position);
					if (ret == DEVICE_OK)
					{
						std::ostringstream positionValue;
						positionValue << (position - offsetPositionStepUm);
						ret = SetProperty(propOffsetPositionStepMicrons, positionValue.str().c_str());
					}
				}
				break;

			case Z_STEP_UP:
				ret = SetFocusPositionUpUm(focusPositionStepUm);
				break;

			case Z_STEP_DOWN:
				ret = SetFocusPositionDownUm(focusPositionStepUm);
				break;

			case Z_EMERGENCY_STOP:
				/** @todo */
				break;

			case Z_SOFT_STOP:
				/** @todo */
				break;

			case Z_GO_HOME:
				if (isPiezoMotor)
				{
					// For a piezo, home is half travel range
					ret = SetZPositionAbsoluteUm(focusDriveRangeMicrons * 0.5);
				}
				else
				{
					// For a stepper motor, home is zero
					ret = SetZPositionAbsoluteUm(0.0);
				}
				break;

			case Z_LIFT_TO_LOAD:
				ret = SetZPositionAbsoluteUm(liftToLoadDistanceUm);
				break;

			default:
				// Silently ignore this
				break;
			}
		}

		// Return property to idle state
		pProp->Set((long)NONE);
	}

	return ret;
}
