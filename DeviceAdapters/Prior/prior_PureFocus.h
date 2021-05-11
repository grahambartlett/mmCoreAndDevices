///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus.h
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus controller adapter
// COPYRIGHT:     University of California, San Francisco, 2006
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
// CVS:           $Id: prior.h 17231 2020-01-07 18:05:26Z nico $
//

#ifndef _PRIOR_PUREFOCUS_H_
#define _PRIOR_PUREFOCUS_H_

#include "prior_shared.h"

#include "../../MMDevice/MMDevice.h"
#include "../../MMDevice/DeviceBase.h"
#include <string>
#include <map>


struct PureFocus850ObjectiveSlot
{
public:
	std::string preset;
	double pinholeCentre;
	double pinholeWidth;
	double laserPower;
	double backgroundA;
	double backgroundB;
	double backgroundC;
	double backgroundD;
	double kP;
	double kI;
	double kD;
	bool servoDirectionSignIsPositive;
	double outputLimitMin;
	double outputLimitMax;
	double sampleLowThreshold;
	double focusLowThreshold;
	double focusHighThreshold;
	double focusRangeThreshold;
	double inFocusRecoveryTimeMs;
	double interfaceHighThreshold;
	double interfaceLowThreshold;
	bool focusServoInterruptOn;
	bool servoLimitOn;
	double servoLimitMaxPositive;
	double servoLimitMaxNegative;
	bool isPiezoMotor;
	double focusDriveRangeMicrons;
	double maxFocusSpeedPercent;
	double maxFocusSpeedMicronsPerS;
	double maxFocusAccelPercent;
	double maxFocusAccelMicronsPerS2;
	bool focusDriveDirectionSignIsPositive;

	PureFocus850ObjectiveSlot();
};


class PureFocus850AutoFocus : public CAutoFocusBase <PureFocus850AutoFocus>
{
public:
	PureFocus850AutoFocus();
	~PureFocus850AutoFocus();

	virtual bool Busy();
	virtual void GetName(char* pszName) const;
	virtual int Initialize();
	virtual int Shutdown();

	// AutoFocus API
	virtual int SetContinuousFocusing(bool state);
	virtual int GetContinuousFocusing(bool& state);
	virtual bool IsContinuousFocusLocked();
	virtual int FullFocus();
	virtual int IncrementalFocus();
	virtual int GetLastFocusScore(double& score);
	virtual int GetCurrentFocusScore(double& score);
	virtual int GetOffset(double& offset);
	virtual int SetOffset(double offset);

	// Actions for properties stored in configuration
	int OnPort(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Actions for properties stored in configuration per objective slot
	int OnPresetInit(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnPreset(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnPinholeCentre(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnPinholeWidth(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnLaserPower(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundA(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundB(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundC(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnKP(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnKI(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnKD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoDirectionSignIsPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnOutputLimitMin(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnOutputLimitMax(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnSampleLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusRangeThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnInFocusRecoveryTimeMs(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnInterfaceHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnInterfaceLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusServoInterruptOn(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoLimitOn(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoLimitMaxPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoLimitMaxNegative(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnIsPiezoMotor(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusDriveRangeMicrons(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnMaxFocusSpeedPercent(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnMaxFocusSpeedMicronsPerS(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnMaxFocusAccelPercent(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnMaxFocusAccelMicronsPerS2(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusDriveDirectionSignIsPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);

	// Actions for read/write settings properties not stored in configuration
	int OnObjectiveSelect(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnServoInhibit(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnDigipotControlsOffset(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnOffsetPositionUm(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPositionUm(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Actions for read-only status properties
	int OnCalculationABCD(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPidTarget(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPidPosition(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPidError(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPidOutput(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusState(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnTimeToInFocus(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnInterfaceCorrect(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnIsOffsetMoving(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnIsFocusDriveMoving(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnPositiveLimitSwitch(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnNegativeLimitSwitch(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Actions for unit build properties
	int OnSerialNumber(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnBuildVersion(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnBuildDateTime(MM::PropertyBase* pProp, MM::ActionType eAct);
	
	// Comms with PF850
	int SetKeypadLock(const bool value);
	int SetObjective(const long value);
	int GetObjective(long& value);
	int SetPinhole(const double centre, const double width);
	int SetLaserPower(const double value);
	int SetBackgrounds(const double a, const double b, const double c, const double d);
	int GetABCD(double &a, double &b, double &c, double &d);
	int GetFocusPidPosition(double& value);
	int GetFocusPidError(double& value);
	int GetFocusPidOutput(double& value);
	int SetServoOn(const bool value);
	int SetKP(const double value);
	int SetKI(const double value);
	int SetKD(const double value);
	int SetFocusPidTarget();
	int GetFocusPidTarget(double& value);
	int SetServoDirectionPositive(const bool value);
	int SetOutputLimits(const double min, const double max);
	int GetSampleState(bool& value);
	int SetSampleLowThreshold(const double value);
	int GetFocusState(bool& value);
	int SetFocusLowThreshold(const double value);
	int SetFocusHighThreshold(const double value);
	int SetFocusRangeThreshold(const double value);
	int SetInFocusRecoveryTime(const double value);
	int SetInterfaceHighThreshold(const double value);
	int SetInterfaceLowThreshold(const double value);
	int GetTimeToInFocus(double& value);
	int GetInterfaceCorrect(bool& value);
	int SetServoInhibit(const bool value);
	int GetServoInhibit(bool& value);
	int SetFocusServoInterruptOn(const bool value);
	int SetServoLimit(const bool isActive, const double maxPositive, const double maxNegative);
	int SetDigipotControlsOffset(const bool value);
	int GetDigipotControlsOffset(bool& value);
	int SetDigipotFocusSpeedPercent(const double value);
	int SetDigipotOffsetSpeedPercent(const double value);
	int SetOffsetToHome();
	int SetOffsetVelocityMoveUmPerS(const double value);
	int GetOffsetPositionUm(double& value);
	int GetIsOffsetMoving(bool& value);
	int SetOffsetPositionUm(const double value);
	int SetOffsetToStoredOffset(const long index);
	int SetStoredOffsetToCurrentPosition(const long index);
	int SetStoredOffsetUm(const long index, const double value);
	int SetFocusDriveRange(const double value);
	int GetIsFocusDriveMoving(bool& value);
	int SetFocusPositionUm(const double value);
	int GetFocusPositionUm(double& value);
	int SetFocusPositionVelocityMoveUmPerS(const double value);
	int SetFocusPositionZeroToCurrentPosition();
	int SetMaxFocusSpeedPercent(const double value);
	int GetMaxFocusSpeedPercent(double& value);
	int SetMaxFocusAccelPercent(const double value);
	int GetMaxFocusAccelPercent(double& value);
	int SetMaxFocusSpeedMicronsPerS(const double value);
	int GetMaxFocusSpeedMicronsPerS(double& value);
	int SetMaxFocusAccelMicronsPerS2(const double value);
	int GetMaxFocusAccelMicronsPerS2(double& value);
	int SetFocusDriveDirectionPositive(const bool value);
	int GetLimitSwitches(bool& positiveLimitActive, bool& negativeLimitActive);
	int GetBuildInfo(std::string& version, std::string& dateTime);
	int GetSerialNumber(long& value);
	int Restart();
	int SaveConfigurationToFlash();
	int SetPiezoMode(const bool value);

private:
	bool initialized;
	const std::string name;

	/** Serial port for comms */
	std::string port;

	/** Ensure each comms message is handled atomically */
	MMThreadLock commsMutex;

	/** Objective currently selected */
	long objectiveSelect;
	bool servoInhibit;
	bool digipotControlsOffset;
	double offsetPositionUm;
	double focusPositionUm;

	/** Stored settings for each objective slot */
	PureFocus850ObjectiveSlot objective[6];

	/* Lock out default copy operations */
	PureFocus850AutoFocus(PureFocus850AutoFocus&);
	PureFocus850AutoFocus& operator=(PureFocus850AutoFocus&);
};


class PureFocus850ZStage : public CStageBase<PureFocus850ZStage>
{
public:
	PureFocus850ZStage();
	~PureFocus850ZStage();

	virtual int Initialize();
	virtual int Shutdown();
	virtual void GetName(char* pszName) const;
	virtual bool Busy();

	// Stage API
	virtual int SetPositionUm(double pos);
	virtual int SetRelativePositionUm(double pos);
	virtual int GetPositionUm(double& pos);
	virtual int SetPositionSteps(long steps);
	virtual int GetPositionSteps(long& steps);
	virtual int SetOrigin();
	virtual int GetLimits(double& min, double& max);
	virtual int IsStageSequenceable(bool& isSequenceable) const;
	virtual bool IsContinuousFocusDrive() const;

private:
	bool initialized;
	const std::string name;

	/* Lock out default copy operations */
	PureFocus850ZStage(PureFocus850ZStage&);
	PureFocus850ZStage& operator=(PureFocus850ZStage&);
};


#endif
