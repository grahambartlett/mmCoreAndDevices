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


PureFocus850AutoFocus::PureFocus850AutoFocus() :
CAutoFocusBase <PureFocus850AutoFocus>(),
name(g_PureFocus850AutoFocusName),
initialized(false),
port(""),
objectiveSelect(1),
servoInhibit(false),
digipotControlsOffset(false),
offsetPositionUm(0.0),
focusPositionUm(0.0)
{
	CPropertyAction* action;
	CPropertyActionEx* actionEx;

	InitializeDefaultErrorMessages();
	SetErrorText(ERR_UNRECOGNIZED_ANSWER, "Unrecognized answer received from the device");
	SetErrorText(ERR_INVALID_VALUE, "Value out of range");
	SetErrorText(ERR_INVALID_MESSAGE, "Device received a corrupt or invalid message");
	SetErrorText(ERR_INVALID_OBJECTIVE, "Objective is not active");

	// Pre-initialization properties
	CreateProperty(MM::g_Keyword_Name, name.c_str(), MM::String, true);
	CreateProperty(MM::g_Keyword_Description, "Prior PureFocus 850 autofocus", MM::String, true);

	// Port
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnPort);
	CreateProperty(MM::g_Keyword_Port, "Undefined", MM::String, false, action, true);

	// Device details
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnSerialNumber);
	CreateProperty("SerialNumber", "0", MM::String, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnBuildVersion);
	CreateProperty("FirmwareBuildVersion", "Undefined", MM::String, true, action);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnBuildDateTime);
	CreateProperty("FirmwareBuildDateTime", "Undefined", MM::String, true, action);

	// Objective settings, stored in configuration
	for (int i = 1; i <= 6; i++)
	{
		std::string propertyName;
		std::string baseName("Objective");
		baseName.append(1, (char)('0' + i));
		baseName.append("-");
		
		propertyName = baseName;
		propertyName.append("Preset");
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPresetInit, i);
		CreateProperty(propertyName.c_str(), "", MM::String, false, actionEx, true);

		propertyName = baseName;
		propertyName.append("PresetSettable");
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPreset, i);
		CreateProperty(propertyName.c_str(), "", MM::String, false, actionEx, false);

		propertyName = baseName;
		propertyName.append("PinholeCentre");
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPinholeCentre, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		propertyName = baseName;
		propertyName.append("PinholeWidth");
		actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnPinholeWidth, i);
		CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		//propertyName = baseName;
		//propertyName.append("LaserPower");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnLaserPower, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		//propertyName = baseName;
		//propertyName.append("BackgroundA");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundA, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		//propertyName = baseName;
		//propertyName.append("BackgroundB");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundB, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		//propertyName = baseName;
		//propertyName.append("BackgroundC");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundC, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		//propertyName = baseName;
		//propertyName.append("BackgroundD");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnBackgroundD, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 4095.0);

		//propertyName = baseName;
		//propertyName.append("KP");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKP, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		//propertyName = baseName;
		//propertyName.append("KI");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKI, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		//propertyName = baseName;
		//propertyName.append("KD");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnKD, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1.0e10);

		//propertyName = baseName;
		//propertyName.append("IsServoDirectionPositive");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoDirectionSignIsPositive, i);
		//CreateProperty(propertyName.c_str(), "1", MM::Integer, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0, 1);

		//propertyName = baseName;
		//propertyName.append("OutputLimitMinimum");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnOutputLimitMin, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), -1e10, 0.0);

		//propertyName = baseName;
		//propertyName.append("OutputLimitMaximum");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnOutputLimitMax, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("SampleLowThreshold");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnSampleLowThreshold, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("FocusLowThreshold");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusLowThreshold, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("FocusHighThreshold");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusHighThreshold, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("FocusRangeThreshold");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusRangeThreshold, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("InFocusRecoveryTimeMs");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInFocusRecoveryTimeMs, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e6);

		//propertyName = baseName;
		//propertyName.append("InterfaceHighThreshold");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInterfaceHighThreshold, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("InterfaceLowThreshold");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnInterfaceLowThreshold, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("IsFocusServoInterruptOn");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusServoInterruptOn, i);
		//CreateProperty(propertyName.c_str(), "0", MM::Integer, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0, 1);

		//propertyName = baseName;
		//propertyName.append("IsServoLimitOn");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitOn, i);
		//CreateProperty(propertyName.c_str(), "0", MM::Integer, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0, 1);

		//propertyName = baseName;
		//propertyName.append("ServoLimitMaximumPositive");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitMaxPositive, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("ServoLimitMaximumNegative");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnServoLimitMaxNegative, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), -1e10, 0.0);

		//propertyName = baseName;
		//propertyName.append("IsPiezoMotor");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnIsPiezoMotor, i);
		//CreateProperty(propertyName.c_str(), "0", MM::Integer, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0, 1);

		//propertyName = baseName;
		//propertyName.append("FocusDriveRangeMicrons");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusDriveRangeMicrons, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("MaxFocusSpeedPercent");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnMaxFocusSpeedPercent, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 100.0);

		//propertyName = baseName;
		//propertyName.append("MaxFocusSpeedMicronsPerS");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnMaxFocusSpeedMicronsPerS, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("MaxFocusAccelPercent");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnMaxFocusAccelPercent, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 100.0);

		//propertyName = baseName;
		//propertyName.append("MaxFocusAccelMicronsPerS2");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnMaxFocusAccelMicronsPerS2, i);
		//CreateProperty(propertyName.c_str(), "0.0", MM::Float, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0.0, 1e10);

		//propertyName = baseName;
		//propertyName.append("IsFocusDriveDirectionPositive");
		//actionEx = new CPropertyActionEx(this, &PureFocus850AutoFocus::OnFocusDriveDirectionSignIsPositive, i);
		//CreateProperty(propertyName.c_str(), "1", MM::Integer, false, actionEx, true);
		//SetPropertyLimits(propertyName.c_str(), 0, 1);
	}

	// Volatile settings read back from unit, not stored in configuration
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnObjectiveSelect);
	CreateProperty("Objective", "1", MM::Integer, false, action, false);
	SetPropertyLimits("Objective", 1, 6);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnServoInhibit);
	CreateProperty("ServoInhibit", "1", MM::Integer, false, action, false);
	SetPropertyLimits("ServoInhibit", 0, 1);
	
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnDigipotControlsOffset);
	CreateProperty("DigipotControlsOffset", "1", MM::Integer, false, action, false);
	SetPropertyLimits("DigipotControlsOffset", 0, 1);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnOffsetPositionUm);
	CreateProperty("OffsetPositionUm", "1", MM::Float, false, action, false);
	
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPositionUm);
	CreateProperty("FocusPositionUm", "1", MM::Float, false, action, false);

	// Status values read back from unit
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnCalculationABCD);
	CreateProperty("CalculationABCD", "0,0,0,0", MM::String, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidTarget);
	CreateProperty("FocusPidTarget", "0", MM::Float, true, action, false);
	
	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidPosition);
	CreateProperty("FocusPidPosition", "0", MM::Float, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidError);
	CreateProperty("FocusPidError", "0", MM::Float, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusPidOutput);
	CreateProperty("FocusPidOutput", "0", MM::Float, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnFocusState);
	CreateProperty("FocusState", "0", MM::Integer, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnTimeToInFocus);
	CreateProperty("TimeToInFocus", "0", MM::Float, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsOffsetMoving);
	CreateProperty("IsOffsetMoving", "0", MM::Integer, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnIsFocusDriveMoving);
	CreateProperty("IsFocusDriveMoving", "0", MM::Integer, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnPositiveLimitSwitch);
	CreateProperty("PositiveLimitSwitch", "0", MM::Integer, true, action, false);

	action = new CPropertyAction(this, &PureFocus850AutoFocus::OnNegativeLimitSwitch);
	CreateProperty("NegativeLimitSwitch", "0", MM::Integer, true, action, false);
}


PureFocus850AutoFocus::PureFocus850AutoFocus(PureFocus850AutoFocus&) :
CAutoFocusBase <PureFocus850AutoFocus>(),
name(g_PureFocus850AutoFocusName),
initialized(false)
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

	// Get latest settings from the controller
	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("Objective");
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("ServoInhibit");
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("DigipotControlsOffset");
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("OffsetPositionUm");
	}

	if (ret == DEVICE_OK)
	{
		ret = UpdateProperty("FocusPositionUm");
	}

	return ret;
}


int PureFocus850AutoFocus::Shutdown()
{
	if (initialized)
	{
		initialized = false;
	}

	return DEVICE_OK;
}


PureFocus850AutoFocus::~PureFocus850AutoFocus()
{
	Shutdown();
}


int PureFocus850AutoFocus::SetContinuousFocusing(bool state)
{
	return 0;
}


int PureFocus850AutoFocus::GetContinuousFocusing(bool& state)
{
	return 0;
}


bool PureFocus850AutoFocus::IsContinuousFocusLocked()
{
	return false;
}


int PureFocus850AutoFocus::FullFocus()
{
	return 0;
}


int PureFocus850AutoFocus::IncrementalFocus()
{
	return 0;
}


int PureFocus850AutoFocus::GetLastFocusScore(double& score)
{
	return 0;
}


int PureFocus850AutoFocus::GetCurrentFocusScore(double& score)
{
	return 0;
}


int PureFocus850AutoFocus::GetOffset(double& offset)
{
	return 0;
}


int PureFocus850AutoFocus::SetOffset(double offset)
{
	return 0;
}
