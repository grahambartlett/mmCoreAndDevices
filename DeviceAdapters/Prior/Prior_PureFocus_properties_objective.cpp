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


int PureFocus850AutoFocus::OnPreset(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].preset.c_str());
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Do not honour this; instead pick up the pre-init setting already set
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
						/** @todo Update all objective settings for this preset */
						std::string value;
						pProp->Get(value);
						objective[slot - 1].preset = value;
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


int PureFocus850AutoFocus::OnPresetInit(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].preset.c_str());
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration on startup
			std::string value;
			pProp->Get(value);
			objective[slot - 1].preset = value;
		}
		else
		{
			// This property does not let us change the setting after initialisation
			pProp->Set(objective[slot - 1].preset.c_str());
		}
	}

	return ret;
}



int PureFocus850AutoFocus::OnPinholeCentre(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot-1].pinholeCentre);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].pinholeCentre = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].pinholeWidth);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].pinholeWidth = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].laserPower);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].laserPower = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].backgroundA);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundA = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].backgroundB);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundB = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].backgroundC);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundC = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].backgroundD);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].backgroundD = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].kP);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].kP = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].kI);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].kI = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].kD);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].kD = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)objective[slot - 1].servoDirectionSignIsPositive);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			long value;
			pProp->Get(value);
			objective[slot - 1].servoDirectionSignIsPositive = (value != 0);
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].outputLimitMin);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].outputLimitMin = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].outputLimitMax);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].outputLimitMax = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].sampleLowThreshold);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].sampleLowThreshold = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].focusLowThreshold);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusLowThreshold = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].focusHighThreshold);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusHighThreshold = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].focusRangeThreshold);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusRangeThreshold = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].inFocusRecoveryTimeMs);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].inFocusRecoveryTimeMs = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].interfaceHighThreshold);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].interfaceHighThreshold = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].interfaceLowThreshold);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].interfaceLowThreshold = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)objective[slot - 1].focusServoInterruptOn);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			long value;
			pProp->Get(value);
			objective[slot - 1].focusServoInterruptOn = (value != 0);
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)objective[slot - 1].servoLimitOn);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			long value;
			pProp->Get(value);
			objective[slot - 1].servoLimitOn = (value != 0);
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].servoLimitMaxPositive);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].servoLimitMaxPositive = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].servoLimitMaxNegative);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].servoLimitMaxNegative = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)objective[slot - 1].isPiezoMotor);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			long value;
			pProp->Get(value);
			objective[slot - 1].isPiezoMotor = (value != 0);
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].focusDriveRangeMicrons);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].focusDriveRangeMicrons = value;
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


int PureFocus850AutoFocus::OnMaxFocusSpeedPercent(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].maxFocusSpeedPercent);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].maxFocusSpeedPercent = value;
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
							ret = SetMaxFocusSpeedPercent(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].maxFocusSpeedPercent = value;
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
				pProp->Set(objective[slot - 1].maxFocusSpeedPercent);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnMaxFocusSpeedMicronsPerS(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].maxFocusSpeedMicronsPerS);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].maxFocusSpeedMicronsPerS = value;
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


int PureFocus850AutoFocus::OnMaxFocusAccelPercent(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].maxFocusAccelPercent);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].maxFocusAccelPercent = value;
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
							ret = SetMaxFocusAccelPercent(value);
							if (ret == DEVICE_OK)
							{
								// Store new value locally
								objective[slot - 1].maxFocusAccelPercent = value;
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
				pProp->Set(objective[slot - 1].maxFocusAccelPercent);
			}
		}
	}

	return ret;
}


int PureFocus850AutoFocus::OnMaxFocusAccelMicronsPerS2(MM::PropertyBase* pProp, MM::ActionType eAct, long slot)
{
	int ret = DEVICE_OK;

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(objective[slot - 1].maxFocusAccelMicronsPerS2);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			double value;
			pProp->Get(value);
			objective[slot - 1].maxFocusAccelMicronsPerS2 = value;
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

	if ((slot < 1) || (slot > 6))
	{
		// Invalid objective; should never happen
		ret = DEVICE_INVALID_PROPERTY;
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set((long)objective[slot - 1].focusDriveDirectionSignIsPositive);
	}
	else if (eAct == MM::AfterSet)
	{
		if (!initialized)
		{
			// Load property state from configuration
			long value;
			pProp->Get(value);
			objective[slot - 1].focusDriveDirectionSignIsPositive = (value != 0);
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
