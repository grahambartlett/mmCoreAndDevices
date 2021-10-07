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


int PureFocus850AutoFocus::OnConfigInProgress(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0L);
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
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);

			/* Unit can continue running whilst we get updated configuration */
			configInProgress = true;
		}
		else if (value == 0)
		{
			long objectiveSelected = 1;
			long slot;

			// We have no guarantee of the order in which the preset name and individual values
			// are updated.  We must set the preset names here to guarantee that values for
			// presets are picked up correctly.  The custom preset name will leave individual
			// values unchanged.
			for (slot = 1; slot <= 6; slot++)
			{
				std::string objectiveName = objective[slot - 1].preset;
				objective[slot - 1].setPreset(objectiveName);
				UpdateObjectiveSlotProperties(slot);
			};

			// After this, properties can only be changed for current objective
			configInProgress = false;

			// Save initial operating state for unit
			if (ret == DEVICE_OK)
			{
				ret = GetObjective(objectiveSelected);
			}

			// Stop the system servoing, so that changing objective slots should have no effect
			if (ret == DEVICE_OK)
			{
				ret = SetServoOn(false);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetServoInhibit(false);
			}

			// Stepper/piezo mode must be set first, because it stomps over output limits
			if (ret == DEVICE_OK)
			{
				ret = SetPiezoMode(isPiezoMotor);
			}			

			// Configure all objective slots
			for (slot = 1; (slot <= 6) && (ret == DEVICE_OK); slot++)
			{
				if (ret == DEVICE_OK)
				{
					ret = SetObjective(slot);
				}

				if (ret == DEVICE_OK)
				{
					ret = SendObjectiveSlotProperties(slot);
				}
			}

			// Configure global settings
			if (ret == DEVICE_OK)
			{
				ret = SetFocusServoInterruptOn(focusInterruptOn);
			}		

			if (ret == DEVICE_OK)
			{
				ret = SetInterfaceInhibit(interfaceInhibit, interfaceInhibitCount);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetDigipotControlsOffset(digipotControlsOffset);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetServoDirectionPositive(isServoDirectionPositive);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetFocusDriveDirectionPositive(isFocusDriveDirectionPositive);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetExposureTimeUs(exposureTimeUs);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetDigipotOffsetSpeedPercent(digipotOffsetSpeedPercent);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetFocusDriveRange(focusDriveRangeMicrons);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetInFocusRecoveryTime(inFocusRecoveryTimeMs);
			}

			// Return to initial operating state
			if (ret == DEVICE_OK)
			{
				ret = SetObjective(objectiveSelected);
			}

			// Start servoing if set by configuration
			if (ret == DEVICE_OK)
			{
				ret = SetServoInhibit(servoInhibit);
			}

			if (ret == DEVICE_OK)
			{
				ret = SetServoOn(servoOn);
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
		// Ignore request and set dummy default
		pProp->Set(0L);
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
			// Lock so that keypad cannot change settings during this
			ret = SetKeypadLock(true);

			// Allow changes to settings to be made
			singleChangeInProgress = true;
		}
		else if (value == 0)
		{
			// Unlock keypad
			ret = SetKeypadLock(false);

			// Disallow changes to settings
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


int PureFocus850AutoFocus::OnObjectiveSelect(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(1L);
	}
	else if (eAct == MM::BeforeGet)
	{
		ret = GetObjective(objectiveSelect);
		if (ret == DEVICE_OK)
		{
			pProp->Set(objectiveSelect);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if (configInProgress || (!singleChangeInProgress))
		{
			// Revert displayed value during starting or not enabled
			pProp->Set(objectiveSelect);
		}
		else
		{
			long value;
			pProp->Get(value);

			if ((value < 1) || (value > 6))
			{
				ret = ERR_INVALID_VALUE;
			}
			else
			{
				ret = SetObjective(value);
				if (ret == DEVICE_OK)
				{
					objectiveSelect = value;
				}
			}

			if (ret != DEVICE_OK)
			{
				// Restore
				pProp->Set(objectiveSelect);
			}
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

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		ret = GetOffsetPositionUm(offsetPositionUm);
		if (ret == DEVICE_OK)
		{
			pProp->Set(offsetPositionUm);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if (configInProgress || (!singleChangeInProgress))
		{
			// Revert displayed value during starting or not enabled
			pProp->Set(objectiveSelect);
		}
		else
		{
			double value;
			pProp->Get(value);

			ret = SetOffsetPositionUm(value);
			if (ret == DEVICE_OK)
			{
				offsetPositionUm = value;
			}

			if (ret != DEVICE_OK)
			{
				// Restore
				pProp->Set(offsetPositionUm);
			}
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

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		ret = GetFocusPositionUm(focusPositionUm);
		if (ret == DEVICE_OK)
		{
			pProp->Set(focusPositionUm);
		}
	}
	else if (eAct == MM::AfterSet)
	{
		if (configInProgress || (!singleChangeInProgress))
		{
			// Revert displayed value during starting or not enabled
			pProp->Set(objectiveSelect);
		}
		else
		{
			
			double value;
			pProp->Get(value);

			ret = SetFocusPositionUm(value);
			if (ret == DEVICE_OK)
			{
				focusPositionUm = value;
			}

			if (ret != DEVICE_OK)
			{
				// Restore
				pProp->Set(focusPositionUm);
			}
		}
	}
	else
	{
		// No action
	}

	return ret;
}



int PureFocus850AutoFocus::OnLiftToLoadDistanceUm(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(liftToLoadDistanceUm);
	}
	else if (eAct == MM::AfterSet)
	{
		if ((!configInProgress) && (!singleChangeInProgress))
		{
			// Block this if not allowed
			pProp->Set(liftToLoadDistanceUm);
		}
		else
		{
			pProp->Get(liftToLoadDistanceUm);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnFocusPositionStepUm(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(focusPositionStepUm);
	}
	else if (eAct == MM::AfterSet)
	{
		if ((!configInProgress) && (!singleChangeInProgress))
		{
			// Block this if not allowed
			pProp->Set(focusPositionStepUm);
		}
		else
		{
			pProp->Get(focusPositionStepUm);
		}
	}
	else
	{
		// No action
	}

	return ret;
}


int PureFocus850AutoFocus::OnOffsetPositionStepUm(MM::PropertyBase* pProp, MM::ActionType eAct)
{
	int ret = DEVICE_OK;

	if (!initialized)
	{
		// Ignore request and set dummy default
		pProp->Set(0.0);
	}
	else if (eAct == MM::BeforeGet)
	{
		pProp->Set(offsetPositionStepUm);
	}
	else if (eAct == MM::AfterSet)
	{
		if ((!configInProgress) && (!singleChangeInProgress))
		{
			// Block this if not allowed
			pProp->Set(offsetPositionStepUm);
		}
		else
		{
			pProp->Get(offsetPositionStepUm);
		}
	}
	else
	{
		// No action
	}

	return ret;
}
