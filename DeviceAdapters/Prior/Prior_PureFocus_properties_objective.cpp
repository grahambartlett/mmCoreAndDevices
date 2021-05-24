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


void PureFocus850AutoFocus::UpdateObjectiveSlotProperties(const long slot)
{
	std::string propertyName;
	std::string baseName = "Objective";
	baseName.append(1, (char)('0' + slot));
	baseName.append("-");

	propertyName = baseName;
	propertyName.append("Preset");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("PinholeCentre");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("PinholeWidth");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("LaserPower");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("BackgroundA");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("BackgroundB");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("BackgroundC");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("BackgroundD");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("KP");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("KI");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("KD");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("IsServoDirectionPositive");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("OutputLimitMinimum");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("OutputLimitMaximum");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("SampleLowThreshold");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("FocusLowThreshold");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("FocusHighThreshold");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("FocusRangeThreshold");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("InFocusRecoveryTimeMs");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("InterfaceHighThreshold");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("InterfaceLowThreshold");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("IsFocusServoInterruptOn");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("IsServoLimitOn");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("ServoLimitMaximumPositive");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("ServoLimitMaximumNegative");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("IsPiezoMotor");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("FocusDriveRangeMicrons");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("MaxFocusSpeedMicronsPerS");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("MaxFocusAccelMicronsPerS2");
	UpdateProperty(propertyName.c_str());

	propertyName = baseName;
	propertyName.append("IsFocusDriveDirectionPositive");
	UpdateProperty(propertyName.c_str());
}


int PureFocus850AutoFocus::SendObjectiveSlotProperties(const long slot)
{
	int ret = DEVICE_OK;
	int index = slot - 1;

	if (ret == DEVICE_OK)
	{
		ret = SetPinhole(objective[index].pinholeCentre, objective[index].pinholeWidth);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetLaserPower(objective[index].laserPower);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetBackgrounds(objective[index].backgroundA,
			objective[index].backgroundB,
			objective[index].backgroundC,
			objective[index].backgroundD);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetKP(objective[index].kP);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetKI(objective[index].kI);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetKD(objective[index].kD);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetServoDirectionPositive(objective[index].servoDirectionSignIsPositive);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetOutputLimits(objective[index].outputLimitMin, objective[index].outputLimitMax);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetSampleLowThreshold(objective[index].sampleLowThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetFocusLowThreshold(objective[index].focusLowThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetFocusHighThreshold(objective[index].focusHighThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetFocusRangeThreshold(objective[index].focusRangeThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetInFocusRecoveryTime(objective[index].inFocusRecoveryTimeMs);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetInterfaceHighThreshold(objective[index].interfaceHighThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetInterfaceLowThreshold(objective[index].interfaceLowThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetFocusServoInterruptOn(objective[index].focusServoInterruptOn);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetServoLimit(objective[index].servoLimitOn, objective[index].servoLimitMaxPositive, objective[index].servoLimitMaxNegative);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetPiezoMode(objective[index].isPiezoMotor);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetFocusDriveRange(objective[index].focusDriveRangeMicrons);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetMaxFocusSpeedMicronsPerS(objective[index].maxFocusSpeedMicronsPerS);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetMaxFocusAccelMicronsPerS2(objective[index].maxFocusAccelMicronsPerS2);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetFocusDriveDirectionPositive(objective[index].focusDriveDirectionSignIsPositive);
	}

	return ret;
}


int PureFocus850AutoFocus::OnPreset(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].preset.c_str());
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			// Load property state from configuration on startup
			std::string value;
			pProp->Get(value);
			objective[slot - 1].setPreset(value);
			UpdateObjectiveSlotProperties(slot);
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot - 1].preset.c_str());
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						std::string value;
						pProp->Get(value);
						objective[slot - 1].setPreset(value);
						UpdateObjectiveSlotProperties(slot);

						ret = SendObjectiveSlotProperties(slot);
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].preset.c_str());
			}
		}
	}

	return ret;
}



int PureFocus850AutoFocus::OnPinholeCentre(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double centre, width;
			ret = GetPinhole(centre, width);
			if (ret == DEVICE_OK)
			{
				pProp->Set(centre);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot-1].pinholeCentre);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].pinholeCentre);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].pinholeCentre = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].pinholeCentre);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetPinhole(value, objective[slot - 1].pinholeWidth);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].pinholeCentre = value;							
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].pinholeCentre);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnPinholeWidth(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double centre, width;
			ret = GetPinhole(centre, width);
			if (ret == DEVICE_OK)
			{
				pProp->Set(width);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].pinholeWidth);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].pinholeWidth);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].pinholeWidth = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].pinholeWidth);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetPinhole(objective[slot - 1].pinholeCentre, value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].pinholeWidth = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].pinholeWidth);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnLaserPower(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetLaserPower(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].laserPower);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].laserPower);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].laserPower = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].laserPower);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetLaserPower(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].laserPower = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].laserPower);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnBackgroundA(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double a, b, c, d;
			ret = GetBackgrounds(a, b, c, d);
			if (ret == DEVICE_OK)
			{
				pProp->Set(a);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].backgroundA);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].backgroundA);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].backgroundA = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].backgroundA);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetBackgrounds(value,
								objective[slot - 1].backgroundB,
								objective[slot - 1].backgroundC,
								objective[slot - 1].backgroundD);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].backgroundA = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].backgroundA);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnBackgroundB(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double a, b, c, d;
			ret = GetBackgrounds(a, b, c, d);
			if (ret == DEVICE_OK)
			{
				pProp->Set(b);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].backgroundB);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].backgroundB);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].backgroundB = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].backgroundB);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetBackgrounds(objective[slot - 1].backgroundA,
								value,
								objective[slot - 1].backgroundC,
								objective[slot - 1].backgroundD);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].backgroundB = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].backgroundB);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnBackgroundC(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double a, b, c, d;
			ret = GetBackgrounds(a, b, c, d);
			if (ret == DEVICE_OK)
			{
				pProp->Set(c);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].backgroundC);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].backgroundC);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].backgroundC = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].backgroundC);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetBackgrounds(objective[slot - 1].backgroundA,
								objective[slot - 1].backgroundB,
								value,
								objective[slot - 1].backgroundD);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].backgroundC = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].backgroundC);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnBackgroundD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double a, b, c, d;
			ret = GetBackgrounds(a, b, c, d);
			if (ret == DEVICE_OK)
			{
				pProp->Set(d);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].backgroundD);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].backgroundD);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].backgroundD = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].backgroundD);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetBackgrounds(objective[slot - 1].backgroundA,
								objective[slot - 1].backgroundB,
								objective[slot - 1].backgroundC,
								value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].backgroundD = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].backgroundD);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnKP(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetKP(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].kP);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].kP);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].kP = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].kP);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetKP(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].kP = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].kP);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnKI(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetKI(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].kI);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].kI);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].kI = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].kI);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetKI(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].kI = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].kI);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnKD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetKD(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].kD);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].kD);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].kD = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].kD);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetKD(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].kD = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].kD);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnServoDirectionSignIsPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool value;
			ret = GetServoDirectionPositive(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set((long)value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set((long)objective[slot - 1].servoDirectionSignIsPositive);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set((long)objective[slot-1].servoDirectionSignIsPositive);
			}
			else
			{
				// Load property state from configuration
				long value;
				pProp->Get(value);
				objective[slot - 1].servoDirectionSignIsPositive = (value != 0);
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)objective[slot-1].servoDirectionSignIsPositive);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						long value;
						pProp->Get(value);
						if ((value < 0) || (value > 1))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							bool boolValue = (value != 0);
							ret = SetServoDirectionPositive(boolValue);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoDirectionSignIsPositive = boolValue;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)objective[slot - 1].servoDirectionSignIsPositive);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnOutputLimitMin(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double minLimit, maxLimit;
			ret = GetOutputLimits(minLimit, maxLimit);
			if (ret == DEVICE_OK)
			{
				pProp->Set(minLimit);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].outputLimitMin);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].outputLimitMin);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].outputLimitMin = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].outputLimitMin);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetOutputLimits(value, objective[slot - 1].outputLimitMax);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].outputLimitMin = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].outputLimitMin);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnOutputLimitMax(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double minLimit, maxLimit;
			ret = GetOutputLimits(minLimit, maxLimit);
			if (ret == DEVICE_OK)
			{
				pProp->Set(maxLimit);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].outputLimitMax);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].outputLimitMax);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].outputLimitMax = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].outputLimitMax);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetOutputLimits(objective[slot - 1].outputLimitMin, value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].outputLimitMax = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].outputLimitMax);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnSampleLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetSampleLowThreshold(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].sampleLowThreshold);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].sampleLowThreshold);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].sampleLowThreshold = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].sampleLowThreshold);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetSampleLowThreshold(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].sampleLowThreshold = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].sampleLowThreshold);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetFocusLowThreshold(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].focusLowThreshold);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].focusLowThreshold);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].focusLowThreshold = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].focusLowThreshold);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetFocusLowThreshold(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].focusLowThreshold = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].focusLowThreshold);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetFocusHighThreshold(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].focusHighThreshold);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].focusHighThreshold);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].focusHighThreshold = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].focusHighThreshold);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetFocusHighThreshold(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].focusHighThreshold = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].focusHighThreshold);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusRangeThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetFocusRangeThreshold(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].focusRangeThreshold);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].focusRangeThreshold);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].focusRangeThreshold = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].focusRangeThreshold);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetFocusRangeThreshold(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].focusRangeThreshold = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].focusRangeThreshold);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInFocusRecoveryTimeMs(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetInFocusRecoveryTime(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].inFocusRecoveryTimeMs);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].inFocusRecoveryTimeMs);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].inFocusRecoveryTimeMs = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].inFocusRecoveryTimeMs);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetInFocusRecoveryTime(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].inFocusRecoveryTimeMs = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].inFocusRecoveryTimeMs);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInterfaceHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetInterfaceHighThreshold(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].interfaceHighThreshold);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].interfaceHighThreshold);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].interfaceHighThreshold = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].interfaceHighThreshold);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetInterfaceHighThreshold(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].interfaceHighThreshold = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].interfaceHighThreshold);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnInterfaceLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetInterfaceLowThreshold(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].interfaceLowThreshold);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].interfaceLowThreshold);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].interfaceLowThreshold = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].interfaceLowThreshold);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetInterfaceLowThreshold(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].interfaceLowThreshold = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].interfaceLowThreshold);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusServoInterruptOn(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool value;
			ret = GetFocusServoInterruptOn(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set((long)value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set((long)objective[slot - 1].focusServoInterruptOn);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set((long)objective[slot-1].focusServoInterruptOn);
			}
			else
			{
				// Load property state from configuration
				long value;
				pProp->Get(value);
				objective[slot - 1].focusServoInterruptOn = (value != 0);
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)objective[slot-1].focusServoInterruptOn);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						long value;
						pProp->Get(value);
						if ((value < 0) || (value > 1))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							bool boolValue = (value != 0);
							ret = SetFocusServoInterruptOn(boolValue);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].focusServoInterruptOn = boolValue;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)objective[slot - 1].focusServoInterruptOn);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnServoLimitOn(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool limitOn;
			double maxPositive, maxNegative;
			ret = GetServoLimit(limitOn, maxPositive, maxNegative);
			if (ret == DEVICE_OK)
			{
				pProp->Set((long)limitOn);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set((long)objective[slot - 1].servoLimitOn);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set((long)objective[slot-1].servoLimitOn);
			}
			else
			{
				// Load property state from configuration
				long value;
				pProp->Get(value);
				objective[slot - 1].servoLimitOn = (value != 0);
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)objective[slot-1].servoLimitOn);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						long value;
						pProp->Get(value);
						if ((value < 0) || (value > 1))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							bool boolValue = (value != 0);
							ret = SetServoLimit(boolValue, objective[slot - 1].servoLimitMaxPositive, objective[slot - 1].servoLimitMaxNegative);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoLimitOn = boolValue;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)objective[slot - 1].servoLimitOn);
			}
		}
	}

	return ret;
}



int PureFocus850AutoFocus::OnServoLimitMaxPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool limitOn;
			double maxPositive, maxNegative;
			ret = GetServoLimit(limitOn, maxPositive, maxNegative);
			if (ret == DEVICE_OK)
			{
				pProp->Set(maxPositive);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].servoLimitMaxPositive);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].servoLimitMaxPositive);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].servoLimitMaxPositive = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].servoLimitMaxPositive);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetServoLimit(objective[slot - 1].servoLimitOn, value, objective[slot - 1].servoLimitMaxNegative);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoLimitMaxPositive = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].servoLimitMaxPositive);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnServoLimitMaxNegative(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool limitOn;
			double maxPositive, maxNegative;
			ret = GetServoLimit(limitOn, maxPositive, maxNegative);
			if (ret == DEVICE_OK)
			{
				pProp->Set(maxNegative);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].servoLimitMaxNegative);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].servoLimitMaxNegative);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].servoLimitMaxNegative = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].servoLimitMaxNegative);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetServoLimit(objective[slot - 1].servoLimitOn, objective[slot - 1].servoLimitMaxPositive, value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoLimitMaxNegative = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].servoLimitMaxNegative);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnIsPiezoMotor(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool value;
			ret = GetPiezoMode(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set((long)value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set((long)objective[slot - 1].isPiezoMotor);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set((long)objective[slot-1].isPiezoMotor);
			}
			else
			{
				// Load property state from configuration
				long value;
				pProp->Get(value);
				objective[slot - 1].isPiezoMotor = (value != 0);
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)objective[slot-1].isPiezoMotor);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						long value;
						pProp->Get(value);
						if ((value < 0) || (value > 1))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							bool boolValue = (value != 0);
							ret = SetPiezoMode(boolValue);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].isPiezoMotor = boolValue;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)objective[slot - 1].isPiezoMotor);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusDriveRangeMicrons(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetFocusDriveRange(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].focusDriveRangeMicrons);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].focusDriveRangeMicrons);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].focusDriveRangeMicrons = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].focusDriveRangeMicrons);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetFocusDriveRange(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].focusDriveRangeMicrons = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].focusDriveRangeMicrons);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnMaxFocusSpeedMicronsPerS(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetMaxFocusSpeedMicronsPerS(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].maxFocusSpeedMicronsPerS);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].maxFocusSpeedMicronsPerS);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].maxFocusSpeedMicronsPerS = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].maxFocusSpeedMicronsPerS);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetMaxFocusSpeedMicronsPerS(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].maxFocusSpeedMicronsPerS = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].maxFocusSpeedMicronsPerS);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnMaxFocusAccelMicronsPerS2(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double value;
			ret = GetMaxFocusAccelMicronsPerS2(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set(value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].maxFocusAccelMicronsPerS2);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set(objective[slot-1].maxFocusAccelMicronsPerS2);
			}
			else
			{
				// Load property state from configuration
				double value;
				pProp->Get(value);
				objective[slot - 1].maxFocusAccelMicronsPerS2 = value;
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].maxFocusAccelMicronsPerS2);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						double value;
						pProp->Get(value);
						if ((value < pProp->GetLowerLimit()) || (value > pProp->GetUpperLimit()))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							ret = SetMaxFocusAccelMicronsPerS2(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].maxFocusAccelMicronsPerS2 = value;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set(objective[slot - 1].maxFocusAccelMicronsPerS2);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusDriveDirectionSignIsPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			bool value;
			ret = GetFocusDriveDirectionPositive(value);
			if (ret == DEVICE_OK)
			{
				pProp->Set((long)value);
			}
		}
		else if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set((long)objective[slot - 1].focusDriveDirectionSignIsPositive);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			if (objective[slot - 1].preset.compare("Custom") != 0)
			{
				// Preserve value from preset
				pProp->Set((long)objective[slot-1].focusDriveDirectionSignIsPositive);
			}
			else
			{
				// Load property state from configuration
				long value;
				pProp->Get(value);
				objective[slot - 1].focusDriveDirectionSignIsPositive = (value != 0);
			}
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set((long)objective[slot-1].focusDriveDirectionSignIsPositive);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty("Objective");
				if (ret == DEVICE_OK)
				{
					if (slot != objectiveSelect)
					{
						// Can only set values for current objective
						ret = ERR_INVALID_OBJECTIVE;
					}
					else
					{
						long value;
						pProp->Get(value);
						if ((value < 0) || (value > 1))
						{
							// Out of range
							ret = ERR_INVALID_VALUE;
						}
						else
						{
							// Valid, so set value on controller
							bool boolValue = (value != 0);
							ret = SetFocusDriveDirectionPositive(boolValue);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].focusDriveDirectionSignIsPositive = boolValue;
								if (objective[slot - 1].preset.compare("Custom") != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign("Custom");
									std::string propertyName("Objective");
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-Preset");
									UpdateProperty(propertyName.c_str());
								}
							}
						}
					}
				}

				// If we locked the keypad, always unlock even if there was an error
				(void)SetKeypadLock(false);
			}

			if (ret != DEVICE_OK)
			{
				// Revert displayed value on failure
				pProp->Set((long)objective[slot - 1].focusDriveDirectionSignIsPositive);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnConfigInProgress(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)configInProgress);
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (value == 1)
		{
			/* Unit can continue running whilst we get updated configuration */
			configInProgress = true;
		}
		else if (value == 0)
		{
			bool isServoing = false;
			long objectiveSelected = 1;
			long slot;

			// After this, properties can only be changed for current objective
			configInProgress = false;
			
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);

			// Save initial operating state for unit
			if (ret == DEVICE_OK)
			{
				ret = GetServoOn(isServoing);
			}

			if (ret == DEVICE_OK)
			{
				ret = GetObjective(objectiveSelected);
			}

			// Configure all objective slots
			for (slot = 1; (slot <= 6) && (ret == DEVICE_OK); slot++)
			{
				if (ret == DEVICE_OK)
				{
					ret = SetObjective(slot);
				}

				ret = SendObjectiveSlotProperties(slot);
			}

			// Return to initial operating state
			if (ret == DEVICE_OK)
			{
				ret = SetObjective(objectiveSelected);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetServoOn(isServoing);
			}

			// Unlock keypad when complete
			ret = SetKeypadLock(false);
		}
		else
		{
			// Restore value if invalid.  Do not report an error though.
			pProp->Set((long)configInProgress);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnSingleChangeInProgress(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)singleChangeInProgress);
	}
	else if (eAct == MM::AfterSet)
	{
		long value;
		pProp->Get(value);

		if (value == 1)
		{
			/* Unit can continue running whilst we get updated configuration */
			singleChangeInProgress = true;
		}
		else if (value == 0)
		{
			singleChangeInProgress = false;
		}
		else
		{
			// Restore value if invalid.  Do not report an error though.
			pProp->Set((long)singleChangeInProgress);
		}
	}
	else
	{
		// No action
	}

	return ret;
}
