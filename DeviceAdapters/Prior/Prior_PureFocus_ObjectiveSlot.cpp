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


PureFocus850ObjectiveSlot::PureFocus850ObjectiveSlot() : 
preset("Custom"),
pinholeCentre(10),
pinholeWidth(20),
laserPower(0),
backgroundA(0),
backgroundB(0),
backgroundC(0),
backgroundD(0),
kP(0),
kI(0),
kD(0),
servoDirectionSignIsPositive(false),
outputLimitMin(0),
outputLimitMax(0),
sampleLowThreshold(0),
focusLowThreshold(0),
focusHighThreshold(0),
focusRangeThreshold(0),
inFocusRecoveryTimeMs(0),
interfaceHighThreshold(0),
interfaceLowThreshold(0),
focusServoInterruptOn(false),
servoLimitOn(false),
servoLimitMaxPositive(0),
servoLimitMaxNegative(0),
isPiezoMotor(false),
focusDriveRangeMicrons(0),
maxFocusSpeedPercent(0),
maxFocusSpeedMicronsPerS(0),
maxFocusAccelPercent(0),
maxFocusAccelMicronsPerS2(0),
focusDriveDirectionSignIsPositive(true)
{
}
