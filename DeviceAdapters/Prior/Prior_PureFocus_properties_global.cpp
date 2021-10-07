///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_properties_objective.cpp
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus adapter objective slot property actions
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

#include <sstream>

#include "prior_PureFocus.h"

#include <windows.h>
#include <stdio.h>


int PureFocus850AutoFocus::OnIsPiezoMotor(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)isPiezoMotor);
		}
		else
		{
			// Read state
			bool value;
			ret = GetPiezoMode(value);
			if (ret == DEVICE_OK)
			{
				isPiezoMotor = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			isPiezoMotor = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)isPiezoMotor);
		}
		else if (value == (long)isPiezoMotor)
		{
			// Do not set this again if there has been no change,
			// otherwise other settings also get changed
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetPiezoMode(boolValue);
			if (ret == DEVICE_OK)
			{
				double min, max;
				std::string baseName, propertyName;

				// Store new value locally
				isPiezoMotor = boolValue;

				// Read back new output limits, which change when this is changed
				ret = GetOutputLimits(min, max);
				if (ret == DEVICE_OK)
				{
					int i;
					for (i = 0; i < 6; i ++)
					{
						if ((objective[i].outputLimitMin != min) || (objective[i].outputLimitMax != max))
						{
							objective[i].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
							objective[i].outputLimitMin = min;
							objective[i].outputLimitMax = max;

							baseName.assign(propObjectivePrefix);
							baseName.append(1, (char)('1' + i));
							baseName.append("-");

							propertyName.assign(baseName);
							propertyName.append(propOutputLimitMinimum);
							UpdateProperty(propertyName.c_str());

							propertyName.assign(baseName);
							propertyName.append(propOutputLimitMaximum);
							UpdateProperty(propertyName.c_str());
						}
					}

					propertyName.assign(propCurrentPrefix);
					propertyName.append(propOutputLimitMinimum);
					UpdateProperty(propertyName.c_str());

					propertyName.assign(propCurrentPrefix);
					propertyName.append(propOutputLimitMaximum);
					UpdateProperty(propertyName.c_str());
				}
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)isPiezoMotor);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnServoOn(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)servoOn);
		}
		else
		{
			// Read state
			bool value;
			ret = GetServoOn(value);
			if (ret == DEVICE_OK)
			{
				servoOn = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			servoOn = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)servoOn);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetServoOn(boolValue);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				servoOn = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)servoOn);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnServoInhibit(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)servoInhibit);
		}
		else
		{
			// Read state
			bool value;
			ret = GetServoInhibit(value);
			if (ret == DEVICE_OK)
			{
				servoInhibit = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			servoInhibit = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)servoInhibit);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetServoInhibit(boolValue);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				servoInhibit = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)servoInhibit);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusInterruptOn(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)focusInterruptOn);
		}
		else
		{
			// Read state
			bool value;
			ret = GetFocusServoInterruptOn(value);
			if (ret == DEVICE_OK)
			{
				focusInterruptOn = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			focusInterruptOn = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)focusInterruptOn);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetFocusServoInterruptOn(boolValue);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				focusInterruptOn = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)focusInterruptOn);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInterfaceInhibit(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)interfaceInhibit);
		}
		else
		{
			// Read state
			bool inhibit;
			double count;
			ret = GetInterfaceInhibit(inhibit, count);
			if (ret == DEVICE_OK)
			{
				interfaceInhibit = inhibit;
				pProp->Set((long)inhibit);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			interfaceInhibit = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)interfaceInhibit);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetInterfaceInhibit(boolValue, interfaceInhibitCount);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				interfaceInhibit = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)interfaceInhibit);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInterfaceInhibitCount(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set(interfaceInhibitCount);
		}
		else
		{
			// Read state
			bool inhibit;
			double count;
			ret = GetInterfaceInhibit(inhibit, count);
			if (ret == DEVICE_OK)
			{
				interfaceInhibitCount = count;
				pProp->Set(interfaceInhibitCount);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			interfaceInhibitCount = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(interfaceInhibitCount);
		}
		else
		{
			ret = SetInterfaceInhibit(interfaceInhibit, value);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				interfaceInhibitCount = value;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(interfaceInhibitCount);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnDigipotControlsOffset(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)digipotControlsOffset);
		}
		else
		{
			// Read state
			bool value;
			ret = GetDigipotControlsOffset(value);
			if (ret == DEVICE_OK)
			{
				digipotControlsOffset = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			digipotControlsOffset = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)digipotControlsOffset);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetDigipotControlsOffset(boolValue);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				digipotControlsOffset = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)digipotControlsOffset);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnIsServoDirectionPositive(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)isServoDirectionPositive);
		}
		else
		{
			// Read state
			bool value;
			ret = GetServoDirectionPositive(value);
			if (ret == DEVICE_OK)
			{
				isServoDirectionPositive = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			isServoDirectionPositive = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)isServoDirectionPositive);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetServoDirectionPositive(boolValue);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				isServoDirectionPositive = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)isServoDirectionPositive);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnIsFocusDriveDirectionPositive(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set((long)isFocusDriveDirectionPositive);
		}
		else
		{
			// Read state
			bool value;
			ret = GetFocusDriveDirectionPositive(value);
			if (ret == DEVICE_OK)
			{
				isFocusDriveDirectionPositive = value;
				pProp->Set((long)value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			isFocusDriveDirectionPositive = (value != 0);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)isFocusDriveDirectionPositive);
		}
		else if ((value < 0) || (value > 1))
		{
			// Out of range
			ret = ERR_INVALID_VALUE;
		}
		else
		{
			bool boolValue = (value != 0);
			ret = SetFocusDriveDirectionPositive(boolValue);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				isFocusDriveDirectionPositive = boolValue;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)isFocusDriveDirectionPositive);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnExposureTimeUs(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set(exposureTimeUs);
		}
		else
		{
			// Read state
			double value;
			ret = GetExposureTimeUs(value);
			if (ret == DEVICE_OK)
			{
				exposureTimeUs = value;
				pProp->Set(value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			exposureTimeUs = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(exposureTimeUs);
		}
		else
		{
			ret = SetExposureTimeUs(value);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				exposureTimeUs = value;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(exposureTimeUs);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnDigipotOffsetSpeedPercent(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set(digipotOffsetSpeedPercent);
		}
		else
		{
			// Read state
			double value;
			ret = GetDigipotOffsetSpeedPercent(value);
			if (ret == DEVICE_OK)
			{
				digipotOffsetSpeedPercent = value;
				pProp->Set(value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			digipotOffsetSpeedPercent = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(digipotOffsetSpeedPercent);
		}
		else
		{
			ret = SetDigipotOffsetSpeedPercent(value);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				digipotOffsetSpeedPercent = value;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(digipotOffsetSpeedPercent);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusDriveRangeMicrons(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set(focusDriveRangeMicrons);
		}
		else
		{
			// Read state
			double value;
			ret = GetFocusDriveRange(value);
			if (ret == DEVICE_OK)
			{
				focusDriveRangeMicrons = value;
				pProp->Set(value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			focusDriveRangeMicrons = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(focusDriveRangeMicrons);
		}
		else
		{
			ret = SetFocusDriveRange(value);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				focusDriveRangeMicrons = value;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(focusDriveRangeMicrons);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInFocusRecoveryTimeMs(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (configInProgress)
		{
			// Report stored state from configuration
			pProp->Set(inFocusRecoveryTimeMs);
		}
		else
		{
			// Read state
			double value;
			ret = GetInFocusRecoveryTime(value);
			if (ret == DEVICE_OK)
			{
				inFocusRecoveryTimeMs = value;
				pProp->Set(value);
			}
		}
	}
	else if (eAct == MM::AfterSet)
	{
		double value;
		pProp->Get(value);

		if (configInProgress)
		{
			// Load property state from configuration
			inFocusRecoveryTimeMs = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(inFocusRecoveryTimeMs);
		}
		else
		{
			ret = SetInFocusRecoveryTime(value);
			if (ret == DEVICE_OK)
			{
				// Store new value locally
				inFocusRecoveryTimeMs = value;
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(inFocusRecoveryTimeMs);
			}
		}
	}

	return ret;
}
