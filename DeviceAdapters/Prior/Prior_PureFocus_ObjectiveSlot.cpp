///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_ObjectiveSlot.cpp
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus values for objective slot
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


PureFocus850ObjectiveSlot::PureFocus850ObjectiveSlot()
{
	setPreset("Stepper - Default");
}


bool PureFocus850ObjectiveSlot::setPreset(const std::string& presetName)
{
	if (presetName.compare("Custom") == 0)
	{
		// Set name but leave everything else unchanged
		preset.assign("Custom");
	}
	else
	{
		// Fall back to stepper default for an invalid name
		preset.assign("Stepper - Default");
		pinholeCentre = 750;
		pinholeWidth = 750;
		laserPower = 0;
		backgroundA = 0;
		backgroundB = 0;
		backgroundC = 0;
		backgroundD = 0;
		kP = 100000.00;
		kI = 0;
		kD = 0;
		servoDirectionSignIsPositive = true;
		outputLimitMin = -500000;
		outputLimitMax = 500000;
		sampleLowThreshold = 50000;
		focusLowThreshold = 500;
		focusHighThreshold = 4095;
		focusRangeThreshold = 0.05;
		inFocusRecoveryTimeMs = 1;
		interfaceHighThreshold = 4095;
		interfaceLowThreshold = 0;
		focusServoInterruptOn = false,
		servoLimitOn = false,
		servoLimitMaxPositive = 0;
		servoLimitMaxNegative = 0;
		isPiezoMotor = false;
		focusDriveRangeMicrons = 100;
		maxFocusSpeedMicronsPerS = 400;
		maxFocusAccelMicronsPerS2 = 12000;
		focusDriveDirectionSignIsPositive = true;

		if (presetName.compare("Stepper - Default") != 0)
		{
			return false;
		}
	}

	return true;
}


bool PureFocus850ObjectiveSlot::getValidPresetName(std::string& presetName, unsigned long index)
{
	char* presetNameList[] =
	{
		"Stepper - Default",
		"Stepper - 100x M achro 0.90 materials",
		"Stepper - 10x 0.17 apo 0.40 fixed slide",
		"Stepper - 10x M achro 0.25 materials",
		"Stepper - 20x 0.17 apo 0.75 fixed slide",
		"Stepper - 20x M achro 0.40 materials",
		"Stepper - 40x 0.17 apo 0.90 fixed slide",
		"Stepper - 4x 0.17 apo 0.16 fixed slide",
		"Stepper - 50x M achro 0.75 materials",
		"Stepper - 5x M achro 0.10 materials",
		"Stepper - 60x 0.17 apo 0.90 fixed slide",
		"Piezo - Default",
		"Piezo - 100x M achro 0.90 materials - NZ100",
		"Piezo - 100x M achro 0.90 materials - OP400",
		"Piezo - 10x 0.17 apo 0.40 fixed slide - NZ100",
		"Piezo - 10x 0.17 apo 0.40 fixed slide - OP400",
		"Piezo - 10x M achro 0.25 materials - NZ100",
		"Piezo - 10x M achro 0.25 materials - OP400",
		"Piezo - 20x 0.17 apo 0.75 fixed slide - NZ100",
		"Piezo - 20x 0.17 apo 0.75 fixed slide - OP400",
		"Piezo - 20x M achro 0.40 materials - NZ100",
		"Piezo - 20x M achro 0.40 materials - OP400",
		"Piezo - 40x 0.17 apo 0.90 fixed slide - NZ100",
		"Piezo - 40x 0.17 apo 0.90 fixed slide - OP400",
		"Piezo - 4x 0.17 apo 0.16 fixed slide - NZ100",
		"Piezo - 4x 0.17 apo 0.16 fixed slide - OP400",
		"Piezo - 50x M achro 0.75 materials - NZ100",
		"Piezo - 50x M achro 0.75 materials - OP400",
		"Piezo - 5x M achro 0.10 materials - NZ100",
		"Piezo - 5x M achro 0.10 materials - OP400",
		"Piezo - 60x 0.17 apo 0.90 fixed slide - NZ100",
		"Piezo - 60x 0.17 apo 0.90 fixed slide - OP400"
	};

	if ((index < 0) || (index >= (sizeof(presetNameList) / sizeof(presetNameList[0]))))
	{
		return false;
	}
	else
	{
		presetName.assign(presetNameList[index]);
		return true;
	}
}


void PureFocus850ObjectiveSlot::getDefaultPresetName(std::string& presetName)
{
	presetName.assign("Stepper - Default");
}
