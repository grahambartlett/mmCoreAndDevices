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


const char *const PureFocus850ObjectiveSlot::defaultPresetName = "Stepper - Default";
const char *const PureFocus850ObjectiveSlot::customPresetName = "Custom";
const char *const PureFocus850ObjectiveSlot::stepperPrefix = "Stepper - ";
const char *const PureFocus850ObjectiveSlot::piezoPrefix = "Piezo - ";


PureFocus850ObjectiveSlot::PureFocus850ObjectiveSlot()
{
	setPreset(defaultPresetName);
}


bool PureFocus850ObjectiveSlot::setPreset(const std::string& presetName)
{
	int i;
	bool found = true;

	if (presetName.compare(customPresetName) == 0)
	{
		// Set name but leave everything else unchanged
	}
	else if (presetName.find(piezoPrefix) == 0)
	{
		// Piezo types
		size_t start = strlen(piezoPrefix);
		size_t size = presetName.size();

		if (presetName.compare(start, size, "100x M achro 0.90 materials - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 100000.00;
			kI = 10000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 2500;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "100x M achro 0.90 materials - OP400") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 5000.00;
			kI = 500000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 2500;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "10x 0.17 apo 0.40 fixed slide - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 1000000.00;
			kI = 100000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 70000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 50000;
			interfaceLowThreshold = 10000;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 300;
			regionEndD = 400;
			pinholeCentre = 750;
			pinholeWidth = 100;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "10x 0.17 apo 0.40 fixed slide - OP400") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 5000.00;
			kI = 500000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 2500;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "10x M achro 0.25 materials - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 1000000.00;
			kI = 100000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 50000;
			interfaceLowThreshold = 10000;
			laserPower = 650;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "10x M achro 0.25 materials - OP400") == 0)
		{
			lensOffsets[0] = -76272;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 400000.00;
			kI = 40000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 650;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "20x 0.17 apo 0.75 fixed slide - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 700000.00;
			kI = 70000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 30000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 200;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "20x 0.17 apo 0.75 fixed slide - OP400") == 0)
		{
			lensOffsets[0] = -18179;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 100000.00;
			kI = 10000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 30000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 200;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "20x M achro 0.40 materials - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 1000000.00;
			kI = 100000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 800;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "20x M achro 0.40 materials - OP400") == 0)
		{
			lensOffsets[0] = -50694;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 200000.00;
			kI = 20000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 800;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "40x 0.17 apo 0.90 fixed slide - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 400000.00;
			kI = 40000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 400;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "40x 0.17 apo 0.90 fixed slide - OP400") == 0)
		{
			lensOffsets[0] = 82487;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 200000.00;
			kI = 20000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 400;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "4x 0.17 apo 0.16 fixed slide - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 2000000.00;
			kI = 200000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 13000;
			focusLowThreshold = 2500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 200000;
			interfaceLowThreshold = 20000;
			laserPower = 1200;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 600;
			regionEndD = 650;
			pinholeCentre = 750;
			pinholeWidth = 6;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "4x 0.17 apo 0.16 fixed slide - OP400") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 500000.00;
			kI = 50000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 13000;
			focusLowThreshold = 2500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 200000;
			interfaceLowThreshold = 20000;
			laserPower = 1200;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 600;
			regionEndD = 650;
			pinholeCentre = 750;
			pinholeWidth = 6;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "50x M achro 0.75 materials - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 100000.00;
			kI = 10000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 650;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "50x M achro 0.75 materials - OP400") == 0)
		{
			lensOffsets[0] = -49044;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 10000.00;
			kI = 1000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 650;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "5x M achro 0.10 materials - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 10000000.00;
			kI = 1000000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 750;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "5x M achro 0.10 materials - OP400") == 0)
		{
			lensOffsets[0] = -76192;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 2000000.00;
			kI = 200000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 750;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "60x 0.17 apo 0.90 fixed slide - NZ100") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 500000.00;
			kI = 50000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 30000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 400;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "60x 0.17 apo 0.90 fixed slide - OP400") == 0)
		{
			lensOffsets[0] = 178335;

			for (i = 1; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 300000.00;
			kI = 30000000.00;
			kD = 0;
			outputLimitMin = -4193280;
			outputLimitMax = 4193280;
			sampleLowThreshold = 30000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 400;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "default") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 100000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 0;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else
		{
			found = false;
		}
	}
	else if (presetName.find(stepperPrefix) == 0)
	{
		// Stepper types
		size_t start = strlen(stepperPrefix);
		size_t size = presetName.size() - start;

		if (presetName.compare(start, size, "100x M achro 0.90 materials") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 100000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 2500;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "10x 0.17 apo 0.40 fixed slide") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 1000000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 70000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 50000;
			interfaceLowThreshold = 10000;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 300;
			regionEndD = 400;
			pinholeCentre = 750;
			pinholeWidth = 100;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "10x M achro 0.25 materials") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 1000000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 650;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "20x 0.17 apo 0.75 fixed slide") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 700000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 30000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 200;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "20x M achro 0.40 materials") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 1000000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 800;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "40x 0.17 apo 0.90 fixed slide") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 400000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 400;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "4x 0.17 apo 0.16 fixed slide") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 2000000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 13000;
			focusLowThreshold = 2500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 200000;
			interfaceLowThreshold = 20000;
			laserPower = 1200;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 600;
			regionEndD = 650;
			pinholeCentre = 750;
			pinholeWidth = 6;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "50x M achro 0.75 materials") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 300000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 50000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 650;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "5x M achro 0.10 materials") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 3000000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 100000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 750;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 750;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "60x 0.17 apo 0.90 fixed slide") == 0)
		{
			for (i = 0; i < 5; i ++)
			{
				lensOffsets[i] = 0;
			}

			kP = 500000.00;
			kI = 0;
			kD = 0;
			outputLimitMin = -500000;
			outputLimitMax = 500000;
			sampleLowThreshold = 30000;
			focusLowThreshold = 500;
			focusHighThreshold = 4095;
			focusRangeThreshold = 0.05;
			interfaceHighThreshold = 4095;
			interfaceLowThreshold = 0;
			laserPower = 4000;
			backgroundA = 0;
			backgroundB = 0;
			backgroundC = 0;
			backgroundD = 0;
			regionStartD = 0;
			regionEndD = 0;
			pinholeCentre = 750;
			pinholeWidth = 400;
			servoLimitOn = false,
			servoLimitMaxPositiveMicrons = 0;
			servoLimitMaxNegativeMicrons = 0;
		}
		else if (presetName.compare(start, size, "default") == 0)
		{
		}
		else
		{
			found = false;
		}
	}
	else
	{
		found = false;
	}

	if (found)
	{
		// Common actions
		preset.assign(presetName);
	}
	else
	{
		// Fall back to stepper default for an invalid name
		preset.assign(defaultPresetName);

		for (i = 0; i < 5; i ++)
		{
			lensOffsets[i] = 0;
		}

		kP = 100000.00;
		kI = 0;
		kD = 0;
		outputLimitMin = -500000;
		outputLimitMax = 500000;
		sampleLowThreshold = 50000;
		focusLowThreshold = 500;
		focusHighThreshold = 4095;
		focusRangeThreshold = 0.05;
		interfaceHighThreshold = 4095;
		interfaceLowThreshold = 0;
		laserPower = 0;
		backgroundA = 0;
		backgroundB = 0;
		backgroundC = 0;
		backgroundD = 0;
		regionStartD = 0;
		regionEndD = 0;
		pinholeCentre = 750;
		pinholeWidth = 750;
		servoLimitOn = false,
		servoLimitMaxPositiveMicrons = 0;
		servoLimitMaxNegativeMicrons = 0;
	}

	return found;
}


bool PureFocus850ObjectiveSlot::getValidPresetName(std::string& presetName, unsigned long index)
{
	const char* presetNameList[] =
	{
		"Stepper - Default",
		"Stepper - 4x 0.17 apo 0.16 fixed slide",
		"Stepper - 5x M achro 0.10 materials",
		"Stepper - 10x 0.17 apo 0.40 fixed slide",
		"Stepper - 10x M achro 0.25 materials",
		"Stepper - 20x 0.17 apo 0.75 fixed slide",
		"Stepper - 20x M achro 0.40 materials",
		"Stepper - 40x 0.17 apo 0.90 fixed slide",
		"Stepper - 50x M achro 0.75 materials",
		"Stepper - 60x 0.17 apo 0.90 fixed slide",
		"Stepper - 100x M achro 0.90 materials",
		"Piezo - Default",
		"Piezo - 4x 0.17 apo 0.16 fixed slide - NZ100",
		"Piezo - 4x 0.17 apo 0.16 fixed slide - OP400",
		"Piezo - 5x M achro 0.10 materials - NZ100",
		"Piezo - 5x M achro 0.10 materials - OP400",
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
		"Piezo - 50x M achro 0.75 materials - NZ100",
		"Piezo - 50x M achro 0.75 materials - OP400",
		"Piezo - 60x 0.17 apo 0.90 fixed slide - NZ100",
		"Piezo - 60x 0.17 apo 0.90 fixed slide - OP400",
		"Piezo - 100x M achro 0.90 materials - NZ100",
		"Piezo - 100x M achro 0.90 materials - OP400",
		"Custom"
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
