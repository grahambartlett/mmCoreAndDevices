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


int PureFocus850AutoFocus::UpdateObjectiveSlotProperties(const long slot)
{
	int j;
	std::string propertyName;
	std::string baseName;
	int retVal = DEVICE_OK;
	
	if (slot == 0)
	{
		baseName = propCurrentPrefix;
	}
	else
	{
		baseName = propObjectivePrefix;
		baseName.append(1, (char)('0' + slot));
		baseName.append("-");

		propertyName = baseName;
		propertyName.append(propPreset);
		if (retVal == DEVICE_OK)
		{
			retVal = UpdateProperty(propertyName.c_str());
		}

		for (j = 0; (j < 5) && (retVal == DEVICE_OK); j ++)
		{
			propertyName = baseName;
			propertyName.append(propLensOffset);
			baseName.append(1, (char)('0' + j));
			retVal = UpdateProperty(propertyName.c_str());
		}
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propKP);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propKI);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propKD);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propOutputLimitMinimum);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propOutputLimitMaximum);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propSampleLowThreshold);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propFocusLowThreshold);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propFocusHighThreshold);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propFocusRangeThreshold);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propInterfaceHighThreshold);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propInterfaceLowThreshold);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propLaserPower);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propBackgroundA);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propBackgroundB);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propBackgroundC);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propBackgroundD);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propRegionStartD);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propRegionEndD);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propPinholeCentre);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propPinholeWidth);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propIsServoLimitOn);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propServoLimitMaxPositiveMicrons);
		retVal = UpdateProperty(propertyName.c_str());
	}

	if (retVal == DEVICE_OK)
	{
		propertyName = baseName;
		propertyName.append(propServoLimitMaxNegativeMicrons);
		retVal = UpdateProperty(propertyName.c_str());
	}

	return retVal;
}


int PureFocus850AutoFocus::SendObjectiveSlotProperties(const long slot)
{
	int ret = DEVICE_OK;
	int index = slot - 1;
	int j;

	for (j = 0; j < 5; j ++)
	{
		if (ret == DEVICE_OK)
		{
			ret = SetStoredOffsetUm(j, objective[index].lensOffsets[j]);
		}
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
		ret = SetInterfaceHighThreshold(objective[index].interfaceHighThreshold);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetInterfaceLowThreshold(objective[index].interfaceLowThreshold);
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
		ret = SetRegionD(objective[index].regionStartD,
			objective[index].regionEndD);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetPinhole(objective[index].pinholeCentre, objective[index].pinholeWidth);
	}

	if (ret == DEVICE_OK)
	{
		ret = SetServoLimit(objective[index].servoLimitOn, objective[index].servoLimitMaxPositiveMicrons, objective[index].servoLimitMaxNegativeMicrons);
	}

	return ret;
}


int PureFocus850AutoFocus::OnPreset(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set("");
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
			// Do not use setPreset() here, because we must not
			// change other settings on startup.  Any differences
			// will be reconciled when configInProgress is cleared
			// and the mass update is started.
			std::string value;
			pProp->Get(value);
			objective[slot - 1].preset = value;
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
				ret = UpdateProperty(propObjective);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].pinholeCentre = value;
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
				ret = UpdateProperty(propObjective);
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
								// Changing one value can change the other, so read both back
								double centre, width;
								ret = GetPinhole(centre, width);
								if (ret == DEVICE_OK)
								{
									// Store new values locally
									objective[slot - 1].pinholeCentre = centre;		
									objective[slot - 1].pinholeWidth = width;	
									if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
									{
										// This is now a custom setting
										objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
										std::string propertyName(propObjectivePrefix);
										propertyName.append(1, (char)('0' + slot));
										propertyName.append("-");
										propertyName.append(propPreset);
										UpdateProperty(propertyName.c_str());
									}
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].pinholeWidth = value;
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
				ret = UpdateProperty(propObjective);
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
								// Changing one value can change the other, so read both back
								double centre, width;
								ret = GetPinhole(centre, width);
								if (ret == DEVICE_OK)
								{
									// Store new values locally
									objective[slot - 1].pinholeCentre = centre;		
									objective[slot - 1].pinholeWidth = width;	
									if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
									{
										// This is now a custom setting
										objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
										std::string propertyName(propObjectivePrefix);
										propertyName.append(1, (char)('0' + slot));
										propertyName.append("-");
										propertyName.append(propPreset);
										UpdateProperty(propertyName.c_str());
									}
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].laserPower = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundA = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundB = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundC = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundD = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].kP = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].kI = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].kD = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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


int PureFocus850AutoFocus::OnOutputLimitMin(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].outputLimitMin = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].outputLimitMax = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].sampleLowThreshold = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusLowThreshold = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusHighThreshold = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusRangeThreshold = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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


int PureFocus850AutoFocus::OnInterfaceHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].interfaceHighThreshold = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].interfaceLowThreshold = value;
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
				ret = UpdateProperty(propObjective);
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
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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


int PureFocus850AutoFocus::OnServoLimitOn(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
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
			// Load property state from configuration
			long value;
			pProp->Get(value);
			objective[slot - 1].servoLimitOn = (value != 0);
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
				ret = UpdateProperty(propObjective);
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
							ret = SetServoLimit(boolValue, objective[slot - 1].servoLimitMaxPositiveMicrons, objective[slot - 1].servoLimitMaxNegativeMicrons);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoLimitOn = boolValue;
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			pProp->Set(objective[slot - 1].servoLimitMaxPositiveMicrons);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].servoLimitMaxPositiveMicrons = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].servoLimitMaxPositiveMicrons);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty(propObjective);
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
							ret = SetServoLimit(objective[slot - 1].servoLimitOn, value, objective[slot - 1].servoLimitMaxNegativeMicrons);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoLimitMaxPositiveMicrons = value;
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
				pProp->Set(objective[slot - 1].servoLimitMaxPositiveMicrons);
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
		// Ignore request and set dummy default
		pProp->Set(0.0);
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
			pProp->Set(objective[slot - 1].servoLimitMaxNegativeMicrons);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].servoLimitMaxNegativeMicrons = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].servoLimitMaxNegativeMicrons);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty(propObjective);
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
							ret = SetServoLimit(objective[slot - 1].servoLimitOn, objective[slot - 1].servoLimitMaxPositiveMicrons, value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].servoLimitMaxNegativeMicrons = value;
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
				pProp->Set(objective[slot - 1].servoLimitMaxNegativeMicrons);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnLensOffset(MM::PropertyBase* pProp, MM::ActionType eAct, long slotAndLens)
{
	int ret = DEVICE_OK;
	long slot = slotAndLens & 0xFF;
	long lens = (slotAndLens >> 8) & 0xFF;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		// Note that lens offset settings do not have a "current" value
		if ((slot < 1) || (slot > 6) || (lens < 0) || (lens > 4))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else
		{
			// Objective slot
			pProp->Set(objective[slot - 1].lensOffsets[lens]);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if ((slot < 1) || (slot > 6) || (lens < 0) || (lens > 4))
		{
			// Invalid objective; should never happen
			ret = DEVICE_INVALID_PROPERTY;
		}
		else if (configInProgress)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].lensOffsets[lens] = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].lensOffsets[lens]);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty(propObjective);
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
							ret = SetStoredOffsetUm(lens, value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].lensOffsets[lens] = value;
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
				pProp->Set(objective[slot - 1].servoLimitMaxNegativeMicrons);
			}
		}
	}

	return ret;
}

int PureFocus850AutoFocus::OnRegionStartD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double start, end;
			ret = GetRegionD(start, end);
			if (ret == DEVICE_OK)
			{
				pProp->Set(start);
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
			pProp->Set(objective[slot - 1].regionStartD);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].regionStartD = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].regionStartD);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty(propObjective);
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
							ret = SetRegionD(value, objective[slot - 1].regionEndD);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].regionStartD = value;
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
				pProp->Set(objective[slot - 1].regionStartD);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnRegionEndD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		if (slot == 0)
		{
			// Current value
			double start, end;
			ret = GetRegionD(start, end);
			if (ret == DEVICE_OK)
			{
				pProp->Set(end);
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
			pProp->Set(objective[slot - 1].regionEndD);
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
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].regionEndD = value;
		}
		else if (!singleChangeInProgress)
		{
			// Revert displayed value
			pProp->Set(objective[slot-1].regionEndD);
		}
		else
		{
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);
			if (ret == DEVICE_OK)
			{
				// Need to know which objective setting is currently active
				ret = UpdateProperty(propObjective);
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
							ret = SetRegionD(objective[slot - 1].regionStartD, value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].regionEndD = value;
								if (objective[slot - 1].preset.compare(PureFocus850ObjectiveSlot::customPresetName) != 0)
								{
									// This is now a custom setting
									objective[slot - 1].preset.assign(PureFocus850ObjectiveSlot::customPresetName);
									std::string propertyName(propObjectivePrefix);
									propertyName.append(1, (char)('0' + slot));
									propertyName.append("-");
									propertyName.append(propPreset);
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
				pProp->Set(objective[slot - 1].regionEndD);
			}
		}
	}

	return ret;
}
