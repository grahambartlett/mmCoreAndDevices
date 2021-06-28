///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus.cpp
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus adapter
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

#ifdef WIN32
   #include <windows.h>
#endif
#include <sstream>

#include "prior_PureFocus.h"

#include "../../MMDevice/ModuleInterface.h"


/* Names of objective properties */
char* PureFocus850AutoFocus::propObjectivePrefix = "Objective";
char* PureFocus850AutoFocus::propCurrentPrefix = "Current-";
char* PureFocus850AutoFocus::propPreset = "Preset";
char* PureFocus850AutoFocus::propLensOffset = "LensOffset";
char* PureFocus850AutoFocus::propKP = "KP";
char* PureFocus850AutoFocus::propKI = "KI";
char* PureFocus850AutoFocus::propKD = "KD";
char* PureFocus850AutoFocus::propOutputLimitMinimum = "OutputLimitMinimum";
char* PureFocus850AutoFocus::propOutputLimitMaximum = "OutputLimitMaximum";
char* PureFocus850AutoFocus::propSampleLowThreshold = "SampleLowThreshold";
char* PureFocus850AutoFocus::propFocusLowThreshold = "FocusLowThreshold";
char* PureFocus850AutoFocus::propFocusHighThreshold = "FocusHighThreshold";
char* PureFocus850AutoFocus::propFocusRangeThreshold = "FocusRangeThreshold";
char* PureFocus850AutoFocus::propInterfaceLowThreshold = "InterfaceLowThreshold";
char* PureFocus850AutoFocus::propInterfaceHighThreshold = "InterfaceHighThreshold";
char* PureFocus850AutoFocus::propLaserPower = "LaserPower";
char* PureFocus850AutoFocus::propBackgroundA = "BackgroundA";
char* PureFocus850AutoFocus::propBackgroundB = "BackgroundB";
char* PureFocus850AutoFocus::propBackgroundC = "BackgroundC";
char* PureFocus850AutoFocus::propBackgroundD = "BackgroundD";
char* PureFocus850AutoFocus::propRegionStartD = "RegionStartD";
char* PureFocus850AutoFocus::propRegionEndD = "RegionEndD";
char* PureFocus850AutoFocus::propPinholeCentre = "PinholeCentre";
char* PureFocus850AutoFocus::propPinholeWidth = "PinholeWidth";
char* PureFocus850AutoFocus::propIsServoLimitOn = "IsServoLimitOn";
char* PureFocus850AutoFocus::propServoLimitMaxPositiveMicrons = "ServoLimitMaxPositiveMicrons";
char* PureFocus850AutoFocus::propServoLimitMaxNegativeMicrons = "ServoLimitMaxNegativeMicrons";

/* Names of global properties */
char* PureFocus850AutoFocus::propIsPiezoMotor = "Global-IsPiezoMotor";
char* PureFocus850AutoFocus::propServoOn = "Global-ServoOn";
char* PureFocus850AutoFocus::propServoInhibit = "Global-ServoInhibit";
char* PureFocus850AutoFocus::propFocusInterruptOn = "Global-FocusInterruptOn";
char* PureFocus850AutoFocus::propInterfaceInhibit = "Global-InterfaceInhibit";
char* PureFocus850AutoFocus::propInterfaceInhibitCount = "Global-InterfaceInhibitCount";
char* PureFocus850AutoFocus::propDigipotControlsOffset = "Global-DigipotControlsOffset";
char* PureFocus850AutoFocus::propIsServoDirectionPositive = "Global-IsServoDirectionPositive";
char* PureFocus850AutoFocus::propIsFocusDriveDirectionPositive = "Global-IsFocusDriveDirectionPositive";
char* PureFocus850AutoFocus::propExposureTimeUs = "Global-ExposureTimeUs";
char* PureFocus850AutoFocus::propDigipotOffsetSpeedPercent = "Global-DigipotOffsetSpeedPercent";
char* PureFocus850AutoFocus::propFocusDriveRangeMicrons = "Global-FocusDriveRangeMicrons";
char* PureFocus850AutoFocus::propInFocusRecoveryTimeMs = "Global-InFocusRecoveryTimeMs";

/* Names of control properties */
char* PureFocus850AutoFocus::propConfigInProgress = "ConfigInProgress";
char* PureFocus850AutoFocus::propSingleChangeInProgress = "SingleChangeInProgress";

/* Names of volatile settings not saved */
char* PureFocus850AutoFocus::propObjective = "Setting-Objective";
char* PureFocus850AutoFocus::propOffsetPositionMicrons = "Setting-OffsetPositionMicrons";
char* PureFocus850AutoFocus::propFocusPositionMicrons = "Setting-FocusPositionMicrons";
char* PureFocus850AutoFocus::propLiftToLoadDistanceMicrons = "Setting-LiftToLoadDistanceMicrons";
char* PureFocus850AutoFocus::propFocusPositionStepMicrons = "Setting-FocusPositionStepMicrons";
char* PureFocus850AutoFocus::propOffsetPositionStepMicrons = "Setting-OffsetPositionStepMicrons";

/* Names of status values read back */
char* PureFocus850AutoFocus::propCalculationABCD = "Status-CalculationABCD";
char* PureFocus850AutoFocus::propFocusPidTarget = "Status-FocusPidTarget";
char* PureFocus850AutoFocus::propFocusPidPosition = "Status-FocusPidPosition";
char* PureFocus850AutoFocus::propFocusPidError = "Status-FocusPidError";
char* PureFocus850AutoFocus::propFocusPidOutput = "Status-FocusPidOutput";
char* PureFocus850AutoFocus::propFocusState = "Status-FocusState";
char* PureFocus850AutoFocus::propTimeToInFocus = "Status-TimeToInFocus";
char* PureFocus850AutoFocus::propIsOffsetMoving = "Status-IsOffsetMoving";
char* PureFocus850AutoFocus::propIsFocusDriveMoving = "Status-IsFocusDriveMoving";
char* PureFocus850AutoFocus::propPositiveLimitSwitch = "Status-PositiveLimitSwitch";
char* PureFocus850AutoFocus::propNegativeLimitSwitch = "Status-NegativeLimitSwitch";
char* PureFocus850AutoFocus::propServoInLimit = "Status-ServoInLimit";
char* PureFocus850AutoFocus::propIsSamplePresent = "Status-IsSamplePresent";
char* PureFocus850AutoFocus::propIsInterfaceCorrect = "Status-IsInterfaceCorrect";

/* Other general properties */
char* PureFocus850AutoFocus::propSerialNumber = "SerialNumber";
char* PureFocus850AutoFocus::propFirmwareBuildVersion = "FirmwareBuildVersion";
char* PureFocus850AutoFocus::propFirmwareBuildDateTime = "FirmwareBuildDateTime";
char* PureFocus850AutoFocus::propArrayReadIndex = "ArrayReadIndex";
char* PureFocus850AutoFocus::propObjectivePresetNames = "ObjectivePresetNames";
char* PureFocus850AutoFocus::propExecuteCommand = "ExecuteCommand";


PureFocus850AutoFocus::PureFocus850AutoFocus() :

// General MM stuff
CAutoFocusBase <PureFocus850AutoFocus>(),
name(g_PureFocus850AutoFocusName),
initialized(false),
port(""),

// Global settings
isPiezoMotor(false),
servoOn(false),
servoInhibit(false),
focusInterruptOn(false),
interfaceInhibit(false),
interfaceInhibitCount(false),
digipotControlsOffset(false),
isServoDirectionPositive(false),
isFocusDriveDirectionPositive(false),
exposureTimeUs(0.0),
digipotOffsetSpeedPercent(0.0),
focusDriveRangeMicrons(0.0),
inFocusRecoveryTimeMs(0.0),

// Volatile settings
objectiveSelect(1),
offsetPositionUm(0.0),
focusPositionUm(0.0),
liftToLoadDistanceUm(100.0),
focusPositionStepUm(1.0),
offsetPositionStepUm(1.0),

// Config/setting updates
configInProgress(false),
singleChangeInProgress(false),
arrayReadIndex(0)
{
	CPropertyAction* action;
	CPropertyActionEx* actionEx;

	InitializeDefaultErrorMessages();
	SetErrorText(ERR_UNRECOGNIZED_ANSWER, "Unrecognized answer received from the device");
	SetErrorText(ERR_INVALID_VALUE, "Value out of range");
	SetErrorText(ERR_INVALID_MESSAGE, "Device received a corrupt or invalid message");
	SetErrorText(ERR_INVALID_OBJECTIVE, "Objective is not active");

	// Pre-initialization read-only properties
	CreateProperty(MM::g_Keyword_Name, name.c_str(), MM::String, true);
	CreateProperty(MM::g_Keyword_Description, "Prior PureFocus PF-850 autofocus", MM::String, true);

	// Port - also pre-initialization but can be set
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnPort);
	CreateProperty(MM::g_Keyword_Port, "Undefined", MM::String, false, action, true);

	// Device details and other propertires
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnSerialNumber);
	CreateProperty(propSerialNumber, "0", MM::String, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnBuildVersion);
	CreateProperty(propFirmwareBuildVersion, "", MM::String, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnBuildDateTime);
	CreateProperty(propFirmwareBuildDateTime, "", MM::String, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnArrayReadIndex);
	CreateProperty(propArrayReadIndex, "0", MM::Integer, false, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnObjectivePresetNames);
	CreateProperty(propObjectivePresetNames, "", MM::String, true, action);

	// Objective settings, stored in configuration
	for (int i = 1; i <= 6; i++)
	{
		int j;
		std::string propertyName;
		std::string baseName(propObjectivePrefix);
		baseName.append(1, (char)('0' + i));
		baseName.append("-");
		
		propertyName = baseName;
		propertyName.append(propPreset);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPreset, i);
		CreateProperty(propertyName.c_str(), "", MM::String, false, actionEx);

		for (j = 0; j < 5; j ++)
		{
			propertyName = baseName;
			propertyName.append(propLensOffset);
			propertyName.append(1, (char)('0' + j));
			actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnLensOffset, (j << 8) + i);
			CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
			SetPropertyLimits(propertyName.c_str(), -1.0e10, 1.0e10);
		}

		propertyName = baseName;
		propertyName.append(propKP);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKP, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		propertyName = baseName;
		propertyName.append(propKI);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKI, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		propertyName = baseName;
		propertyName.append(propKD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		propertyName = baseName;
		propertyName.append(propOutputLimitMinimum);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnOutputLimitMin, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), -1e10, 0.0);

		propertyName = baseName;
		propertyName.append(propOutputLimitMaximum);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnOutputLimitMax, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propSampleLowThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnSampleLowThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propFocusLowThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusLowThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propFocusHighThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusHighThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propFocusRangeThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusRangeThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propInterfaceHighThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInterfaceHighThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propInterfaceLowThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInterfaceLowThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propLaserPower);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnLaserPower, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundA);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundA, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundB);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundB, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundC);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundC, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propRegionStartD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnRegionStartD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propRegionEndD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnRegionEndD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propPinholeCentre);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPinholeCentre, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propPinholeWidth);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPinholeWidth, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propIsServoLimitOn);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitOn, i);
		CreateProperty(propertyName.c_str(), "0", MM::Integer, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0, 1);

		propertyName = baseName;
		propertyName.append(propServoLimitMaxPositiveMicrons);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitMaxPositive, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propServoLimitMaxNegativeMicrons);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitMaxNegative, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx);
		SetPropertyLimits(propertyName.c_str(), -1e10, 0.0);
	}

	// Current objective settings, read back
	{
		int i = 0;
		std::string propertyName;
		std::string baseName(propCurrentPrefix);
		
		// Note that we cannot read back the current array of lens offsets;
		// and of course there is no preset.

		propertyName = baseName;
		propertyName.append(propKP);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKP, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		propertyName = baseName;
		propertyName.append(propKI);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKI, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		propertyName = baseName;
		propertyName.append(propKD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		propertyName = baseName;
		propertyName.append(propOutputLimitMinimum);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnOutputLimitMin, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), -1e10, 0.0);

		propertyName = baseName;
		propertyName.append(propOutputLimitMaximum);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnOutputLimitMax, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propSampleLowThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnSampleLowThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propFocusLowThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusLowThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propFocusHighThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusHighThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propFocusRangeThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusRangeThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propInterfaceHighThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInterfaceHighThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propInterfaceLowThreshold);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInterfaceLowThreshold, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propLaserPower);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnLaserPower, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundA);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundA, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundB);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundB, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundC);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundC, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propBackgroundD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propRegionStartD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnRegionStartD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propRegionEndD);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnRegionEndD, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propPinholeCentre);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPinholeCentre, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propPinholeWidth);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPinholeWidth, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append(propIsServoLimitOn);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitOn, i);
		CreateProperty(propertyName.c_str(), "0", MM::Integer, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0, 1);

		propertyName = baseName;
		propertyName.append(propServoLimitMaxPositiveMicrons);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitMaxPositive, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		propertyName = baseName;
		propertyName.append(propServoLimitMaxNegativeMicrons);
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitMaxNegative, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, true, actionEx);
		SetPropertyLimits(propertyName.c_str(), -1e10, 0.0);
	}

	// Global settings, stored in configuration
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsPiezoMotor);
	CreateProperty(propIsPiezoMotor, "1", MM::Integer, false, action);
	SetPropertyLimits(propIsPiezoMotor, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnServoOn);
	CreateProperty(propServoOn, "0", MM::Integer, false, action);
	SetPropertyLimits(propServoOn, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnServoInhibit);
	CreateProperty(propServoInhibit, "0", MM::Integer, false, action);
	SetPropertyLimits(propServoInhibit, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusInterruptOn);
	CreateProperty(propFocusInterruptOn, "0", MM::Integer, false, action);
	SetPropertyLimits(propFocusInterruptOn, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnInterfaceInhibit);
	CreateProperty(propInterfaceInhibit, "0", MM::Integer, false, action);
	SetPropertyLimits(propInterfaceInhibit, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnInterfaceInhibitCount);
	CreateProperty(propInterfaceInhibitCount, "0", MM::Float, false, action);
	SetPropertyLimits(propInterfaceInhibitCount, 0, 255);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnDigipotControlsOffset);
	CreateProperty(propDigipotControlsOffset, "0", MM::Integer, false, action);
	SetPropertyLimits(propDigipotControlsOffset, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsServoDirectionPositive);
	CreateProperty(propIsServoDirectionPositive, "0", MM::Integer, false, action);
	SetPropertyLimits(propIsServoDirectionPositive, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsFocusDriveDirectionPositive);
	CreateProperty(propIsFocusDriveDirectionPositive, "0", MM::Integer, false, action);
	SetPropertyLimits(propIsFocusDriveDirectionPositive, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnExposureTimeUs);
	CreateProperty(propExposureTimeUs, "0", MM::Float, false, action);
	SetPropertyLimits(propExposureTimeUs, 0, 1e10);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnDigipotOffsetSpeedPercent);
	CreateProperty(propDigipotOffsetSpeedPercent, "0", MM::Float, false, action);
	SetPropertyLimits(propDigipotOffsetSpeedPercent, 0, 100);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusDriveRangeMicrons);
	CreateProperty(propFocusDriveRangeMicrons, "0", MM::Float, false, action);
	SetPropertyLimits(propFocusDriveRangeMicrons, 0, 1e10);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnInFocusRecoveryTimeMs);
	CreateProperty(propInFocusRecoveryTimeMs, "0", MM::Float, false, action);
	SetPropertyLimits(propInFocusRecoveryTimeMs, 0, 1e10);

	// Volatile settings read back from unit, not stored in configuration.
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnConfigInProgress);
	CreateProperty(propConfigInProgress, "1", MM::Integer, false, action);
	SetPropertyLimits(propConfigInProgress, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnSingleChangeInProgress);
	CreateProperty(propSingleChangeInProgress, "0", MM::Integer, false, action);
	SetPropertyLimits(propSingleChangeInProgress, 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnObjectiveSelect);
	CreateProperty(propObjective, "1", MM::Integer, false, action);
	SetPropertyLimits(propObjective, 1, 6);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnOffsetPositionUm);
	CreateProperty(propOffsetPositionMicrons, "1", MM::Float, false, action);
	
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPositionUm);
	CreateProperty(propFocusPositionMicrons, "1", MM::Float, false, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnLiftToLoadDistanceUm);
	CreateProperty(propLiftToLoadDistanceMicrons, "100", MM::Float, false, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPositionStepUm);
	CreateProperty(propFocusPositionStepMicrons, "1", MM::Float, false, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnOffsetPositionStepUm);
	CreateProperty(propOffsetPositionStepMicrons, "1", MM::Float, false, action);

	// Status values read back from unit
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnCalculationABCD);
	CreateProperty(propCalculationABCD, "0:0:0:0", MM::String, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidTarget);
	CreateProperty(propFocusPidTarget, "0", MM::Float, true, action);
	
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidPosition);
	CreateProperty(propFocusPidPosition, "0", MM::Float, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidError);
	CreateProperty(propFocusPidError, "0", MM::Float, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidOutput);
	CreateProperty(propFocusPidOutput, "0", MM::Float, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusState);
	CreateProperty(propFocusState, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnTimeToInFocus);
	CreateProperty(propTimeToInFocus, "0", MM::Float, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsOffsetMoving);
	CreateProperty(propIsOffsetMoving, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsFocusDriveMoving);
	CreateProperty(propIsFocusDriveMoving, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnPositiveLimitSwitch);
	CreateProperty(propPositiveLimitSwitch, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnNegativeLimitSwitch);
	CreateProperty(propNegativeLimitSwitch, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnServoInLimit);
	CreateProperty(propServoInLimit, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsSamplePresent);
	CreateProperty(propIsSamplePresent, "0", MM::Integer, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsInterfaceCorrect);
	CreateProperty(propIsInterfaceCorrect, "0", MM::Integer, true, action);

	// Execute one-shot commands
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnExecuteCommand);
	CreateProperty(propExecuteCommand, "0", MM::Integer, false, action);
}


PureFocus850AutoFocus::PureFocus850AutoFocus(PureFocus850AutoFocus&) :
CAutoFocusBase <PureFocus850AutoFocus>(),
name(g_PureFocus850AutoFocusName),
initialized(false),
configInProgress(false),
singleChangeInProgress(false)
{
	// Should never be called
	assert(false);
}


PureFocus850AutoFocus& PureFocus850AutoFocus::operator=(PureFocus850AutoFocus&)
{
	// Should never be called
	assert(false);
	return *this;
}


bool PureFocus850AutoFocus::Busy()
{
	return false;
}


void PureFocus850AutoFocus::GetName(char* pszName) const
{
	CDeviceUtils::CopyLimitedString(pszName, name.c_str());
}


int PureFocus850AutoFocus::Initialize()
{
	int ret = DEVICE_OK;
	int i;
	
	/** @todo Add any initialisation here */

	if (ret == DEVICE_OK)
	{
		initialized = true;
	}

	// Get device details
	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("SerialNumber");
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("FirmwareBuildVersion");
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("FirmwareBuildDateTime");
	}

	// Get initial values for objective slots
	for (i = 0; i <= 6; i ++)
	{
		UpdateObjectiveSlotProperties(i);
	}

	// Get initial values for globals
	UpdateProperty(propIsPiezoMotor);
	UpdateProperty(propServoOn);
	UpdateProperty(propServoInhibit);
	UpdateProperty(propFocusInterruptOn);
	UpdateProperty(propInterfaceInhibit);
	UpdateProperty(propInterfaceInhibitCount);
	UpdateProperty(propDigipotControlsOffset);
	UpdateProperty(propIsServoDirectionPositive);
	UpdateProperty(propIsFocusDriveDirectionPositive);
	UpdateProperty(propExposureTimeUs);
	UpdateProperty(propDigipotOffsetSpeedPercent);
	UpdateProperty(propFocusDriveRangeMicrons);
	UpdateProperty(propInFocusRecoveryTimeMs);

	// Update control flags
	UpdateProperty(propConfigInProgress);
	UpdateProperty(propSingleChangeInProgress);

	// Get latest settings from the controller
	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty(propObjective);
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty(propOffsetPositionMicrons);
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty(propFocusPositionMicrons);
	}

	this->GetCoreCallback()->LogMessage(this, "Completed PureFocus Initialize()", false);

	return ret;
}


int PureFocus850AutoFocus::Shutdown()
{
	if (initialized)
	{
		initialized = false;

		SetProperty(MM::g_Keyword_Port, "Undefined");
	}

	return DEVICE_OK;
}


PureFocus850AutoFocus::~PureFocus850AutoFocus()
{
	Shutdown();
}


int PureFocus850AutoFocus::SetContinuousFocusing(bool state)
{
	int ret = DEVICE_OK;

	// This is the same as reading/writing the ServoOn property
	ret = SetServoOn(state);
	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty(propServoOn);
	}
	
	return ret;
}


int PureFocus850AutoFocus::GetContinuousFocusing(bool& state)
{
	int ret = DEVICE_OK;

	// This is the same as reading/writing the ServoOn property
	ret = UpdateProperty(propServoOn);
	if (ret == DEVICE_OK)
	{
		state = servoOn;
	}
	
	return ret;
}


bool PureFocus850AutoFocus::IsContinuousFocusLocked()
{
	bool result = false;
	int ret = DEVICE_OK;
	long status;

	// This is the same as reading/writing the FocusState property
	ret = GetProperty(propFocusState, status);
	if (ret == DEVICE_OK)
	{
		result = (status != 0);
	}
	
	return result;
}


int PureFocus850AutoFocus::FullFocus()
{
	// This runs one-shot focussing.  Stub this, since it is not relevant for us.
	return DEVICE_OK;
}


int PureFocus850AutoFocus::IncrementalFocus()
{
	// This runs one-shot focussing.  Stub this, since it is not relevant for us.
	return DEVICE_OK;
}


int PureFocus850AutoFocus::GetLastFocusScore(double& score)
{
	(void)score;
	// Since this runs autofocus continuously, there is no concept of a "last" focus score.
	return DEVICE_UNSUPPORTED_COMMAND;
}


int PureFocus850AutoFocus::GetCurrentFocusScore(double& score)
{
	// This is the same as reading/writing the FocusPidError property
	return GetProperty(propFocusPidError, score);
}


int PureFocus850AutoFocus::GetOffset(double& offset)
{
	/// @todo Does this correspond directly to our offset, or something else?
	offset = 0.0;
	return DEVICE_OK;
}


int PureFocus850AutoFocus::SetOffset(double offset)
{
	(void)offset;
	/// @todo Does this correspond directly to our offset, or something else?
	return DEVICE_OK;
}
