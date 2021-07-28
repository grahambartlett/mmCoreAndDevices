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


/** Structure holding data for one objective slot.
@todo Ultimately values should have "set" functions which provide validations.
*/
struct PureFocus850ObjectiveSlot
{
public:
	std::string preset;
	double lensOffsets[5];
	double kP;
	double kI;
	double kD;
	double outputLimitMin;
	double outputLimitMax;
	double sampleLowThreshold;
	double focusLowThreshold;
	double focusHighThreshold;
	double focusRangeThreshold;
	double interfaceHighThreshold;
	double interfaceLowThreshold;
	double laserPower;
	double backgroundA;
	double backgroundB;
	double backgroundC;
	double backgroundD;
	double regionStartD;
	double regionEndD;
	bool servoLimitOn;
	double servoLimitMaxPositiveMicrons;
	double servoLimitMaxNegativeMicrons;
	double pinholeCentre;
	double pinholeWidth;

	PureFocus850ObjectiveSlot();

	/** Set settings to values for preset, if preset name is valid and not "Custom".
	@param presetName Preset name
	@returns True if preset name is valid, false if not.
	*/
	bool setPreset(const std::string& presetName);

	/** Get valid preset name by index.  Start from index 0 and work up until function returns false.
	@param presetName Valid preset name at index
	@param index Index for name
	@returns True if we have a name with this index, false if not
	*/
	static bool getValidPresetName(std::string& presetName, unsigned long index);

	/** Default preset name */
	static const char *const defaultPresetName;

	/** Custom preset name */
	static const char *const customPresetName;

	/** Stepper type prefix */
	static const char *const stepperPrefix;

	/** Piezo type prefix */
	static const char *const piezoPrefix;
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

	// Actions for setting comms port
	int OnPort(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Actions for properties stored in configuration per objective slot
	int OnPreset(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnLensOffset(MM::PropertyBase* pProp, MM::ActionType eAct, long slotAndLens);
	int OnKP(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnKI(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnKD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnOutputLimitMin(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnOutputLimitMax(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnSampleLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnFocusRangeThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnInterfaceHighThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnInterfaceLowThreshold(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnLaserPower(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundA(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundB(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundC(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnBackgroundD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnRegionStartD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnRegionEndD(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnPinholeCentre(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnPinholeWidth(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoLimitOn(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoLimitMaxPositive(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);
	int OnServoLimitMaxNegative(MM::PropertyBase* pProp, MM::ActionType eAct, long slot);

	// Actions for global properties stored in configuration
	int OnIsPiezoMotor(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnServoOn(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnServoInhibit(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusInterruptOn(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnInterfaceInhibit(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnInterfaceInhibitCount(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnDigipotControlsOffset(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnIsServoDirectionPositive(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnIsFocusDriveDirectionPositive(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnExposureTimeUs(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnDigipotOffsetSpeedPercent(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusDriveRangeMicrons(MM::PropertyBase* pProp, MM::ActionType eActy);
	int OnInFocusRecoveryTimeMs(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Actions for properties used to sequence setting configuration values
	int OnConfigInProgress(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnSingleChangeInProgress(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Actions for system control read/write properties not stored in configuration
	int OnObjectiveSelect(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnOffsetPositionUm(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPositionUm(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnLiftToLoadDistanceUm(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnFocusPositionStepUm(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnOffsetPositionStepUm(MM::PropertyBase* pProp, MM::ActionType eAct);

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
	int OnServoInLimit(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnIsSamplePresent(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnIsInterfaceCorrect(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnLineData(MM::PropertyBase* pProp, MM::ActionType eAct, long section);

	// Actions for other properties
	int OnSerialNumber(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnBuildVersion(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnBuildDateTime(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnArrayReadIndex(MM::PropertyBase* pProp, MM::ActionType eAct);
	int OnObjectivePresetNames(MM::PropertyBase* pProp, MM::ActionType eAct);

	// Action for one-shot commands
	int OnExecuteCommand(MM::PropertyBase* pProp, MM::ActionType eAct);
	
	// Comms with PF850
	int SetKeypadLock(const bool value);
	int SetObjective(const long value);
	int GetObjective(long& value);
	int SetPinhole(const double centre, const double width);
	int GetPinhole(double& centre, double& width);
	int SetLaserPower(const double value);
	int GetLaserPower(double& value);
	int SetBackgrounds(const double a, const double b, const double c, const double d);
	int GetBackgrounds(double& a, double& b, double& c, double& d);
	int GetABCD(double &a, double &b, double &c, double &d);
	int GetFocusPidPosition(double& value);
	int GetFocusPidError(double& value);
	int GetFocusPidOutput(double& value);
	int SetServoOn(const bool value);
	int GetServoOn(bool& value);
	int SetKP(const double value);
	int GetKP(double& value);
	int SetKI(const double value);
	int GetKI(double& value);
	int SetKD(const double value);
	int GetKD(double& value);
	int SetFocusPidTarget();
	int GetFocusPidTarget(double& value);
	int SetServoDirectionPositive(const bool value);
	int GetServoDirectionPositive(bool& value);
	int SetOutputLimits(const double min, const double max);
	int GetOutputLimits(double& min, double& max);
	int GetSampleState(bool& value);
	int SetSampleLowThreshold(const double value);
	int GetSampleLowThreshold(double& value);
	int GetFocusState(bool& value);
	int SetFocusLowThreshold(const double value);
	int GetFocusLowThreshold(double& value);
	int SetFocusHighThreshold(const double value);
	int GetFocusHighThreshold(double& value);
	int SetFocusRangeThreshold(const double value);
	int GetFocusRangeThreshold(double& value);
	int SetInFocusRecoveryTime(const double value);
	int GetInFocusRecoveryTime(double& value);
	int GetTimeToInFocus(double& value);
	int SetInterfaceHighThreshold(const double value);
	int GetInterfaceHighThreshold(double& value);
	int SetInterfaceLowThreshold(const double value);
	int GetInterfaceLowThreshold(double& value);
	int GetInterfaceCorrect(bool& value);
	int SetServoInhibit(const bool value);
	int GetServoInhibit(bool& value);
	int SetFocusServoInterruptOn(const bool value);
	int GetFocusServoInterruptOn(bool& value);
	int SetServoLimit(const bool isActive, const double maxPositive, const double maxNegative);
	int GetServoLimit(bool& isActive, double& maxPositive, double& maxNegative);
	int SetDigipotControlsOffset(const bool value);
	int GetDigipotControlsOffset(bool& value);
	int SetDigipotFocusSpeedPercent(const double value);
	int GetDigipotFocusSpeedPercent(double& value);
	int SetDigipotOffsetSpeedPercent(const double value);
	int GetDigipotOffsetSpeedPercent(double& value);
	int SetOffsetToHome();
	int SetOffsetVelocityMoveUmPerS(const double value);
	int GetOffsetPositionUm(double& value);
	int GetIsOffsetMoving(bool& value);
	int SetOffsetPositionUm(const double value);
	int SetOffsetToStoredOffset(const long index);
	int SetStoredOffsetToCurrentPosition(const long index);
	int SetStoredOffsetUm(const long index, const double value);
	int SetFocusDriveRange(const double value);
	int GetFocusDriveRange(double& value);
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
	int GetFocusDriveDirectionPositive(bool& value);
	int GetLimitSwitches(bool& positiveLimitActive, bool& negativeLimitActive);
	int GetBuildInfo(std::string& version, std::string& dateTime);
	int GetSerialNumber(long& value);
	int Restart();
	int SaveConfigurationToFlash();
	int SetPiezoMode(const bool value);
	int GetPiezoMode(bool& value);
	int SetRegionD(const double start, const double end);
	int GetRegionD(double& start, double& end);
	int SetInterfaceInhibit(const bool inhibit, const double count);
	int GetInterfaceInhibit(bool& inhibit, double& count);
	int SetExposureTimeUs(const double value);
	int GetExposureTimeUs(double& value);
	int GetServoInLimit(bool &value);
	int SetZPositionAbsoluteUm(const double value);
	int SetFocusPositionUpUm(const double value);
	int SetFocusPositionDownUm(const double value);
	int GetLineData(std::string& values);
	int RefreshLineData();

private:
	bool initialized;
	const std::string name;

	/** Serial port for comms */
	std::string port;

	/** Ensure each comms message is handled atomically */
	MMThreadLock commsMutex;

	/** Configuration preset group is being loaded */
	bool configInProgress;

	/** Single parameter is being updated */
	bool singleChangeInProgress;

	/** Stored settings for each objective slot */
	PureFocus850ObjectiveSlot objective[6];

	/* Stored global settings */
	bool isPiezoMotor;
	bool servoOn;
	bool servoInhibit;
	bool focusInterruptOn;
	bool interfaceInhibit;
	double interfaceInhibitCount;
	bool digipotControlsOffset;
	bool isServoDirectionPositive;
	bool isFocusDriveDirectionPositive;
	double exposureTimeUs;
	double digipotOffsetSpeedPercent;
	double focusDriveRangeMicrons;
	double inFocusRecoveryTimeMs;

	/* Volatile control values */
	long objectiveSelect;
	double offsetPositionUm;
	double focusPositionUm;
	double liftToLoadDistanceUm;
	double focusPositionStepUm;
	double offsetPositionStepUm;

	/** Index for reading back array data */
	long arrayReadIndex;

	/** Last captured data for line pixels */
	std::string lineData;

	/* Lock out default copy operations */
	PureFocus850AutoFocus(PureFocus850AutoFocus&);
	PureFocus850AutoFocus& operator=(PureFocus850AutoFocus&);

	/** Update properties in GUI for an objective slot
	@param slot Objective slot (0-6)
	@returns DEVICE_OK if succeeded
	*/
	int UpdateObjectiveSlotProperties(const long slot);

	/** Send properties to PF850 for an objective slot
	@param slot Objective slot (1-6)
	@returns DEVICE_OK if succeeded
	*/
	int SendObjectiveSlotProperties(const long slot);

	/* Names of objective properties */
	static char* propObjectivePrefix;
	static char* propCurrentPrefix;
	static char* propPreset;
	static char* propLensOffset;
	static char* propKP;
	static char* propKI;
	static char* propKD;
	static char* propOutputLimitMinimum;
	static char* propOutputLimitMaximum;
	static char* propSampleLowThreshold;
	static char* propFocusLowThreshold;
	static char* propFocusHighThreshold;
	static char* propFocusRangeThreshold;
	static char* propInterfaceLowThreshold;
	static char* propInterfaceHighThreshold;
	static char* propLaserPower;
	static char* propBackgroundA;
	static char* propBackgroundB;
	static char* propBackgroundC;
	static char* propBackgroundD;
	static char* propRegionStartD;
	static char* propRegionEndD;
	static char* propPinholeCentre;
	static char* propPinholeWidth;
	static char* propIsServoLimitOn;
	static char* propServoLimitMaxPositiveMicrons;
	static char* propServoLimitMaxNegativeMicrons;

	/* Names of global properties */
	static char* propIsPiezoMotor;
	static char* propServoOn;
	static char* propServoInhibit;
	static char* propFocusInterruptOn;
	static char* propInterfaceInhibit;
	static char* propInterfaceInhibitCount;
	static char* propDigipotControlsOffset;
	static char* propIsServoDirectionPositive;
	static char* propIsFocusDriveDirectionPositive;
	static char* propExposureTimeUs;
	static char* propDigipotOffsetSpeedPercent;
	static char* propFocusDriveRangeMicrons;
	static char* propInFocusRecoveryTimeMs;

	/* Names of control flag properties */
	static char* propConfigInProgress;
	static char* propSingleChangeInProgress;

	/* Names of volatile settings not saved */
	static char* propObjective;
	static char* propOffsetPositionMicrons;
	static char* propFocusPositionMicrons;
	static char* propLiftToLoadDistanceMicrons;
	static char* propFocusPositionStepMicrons;
	static char* propOffsetPositionStepMicrons;

	/* Names of status values read back */
	static char* propCalculationABCD;
	static char* propFocusPidTarget;
	static char* propFocusPidPosition;
	static char* propFocusPidError;
	static char* propFocusPidOutput;
	static char* propFocusState;
	static char* propTimeToInFocus;
	static char* propIsOffsetMoving;
	static char* propIsFocusDriveMoving;
	static char* propPositiveLimitSwitch;
	static char* propNegativeLimitSwitch;
	static char* propServoInLimit;
	static char* propIsSamplePresent;
	static char* propIsInterfaceCorrect;
	static char* propLineData1;
	static char* propLineData2;
	static char* propLineData3;
	static char* propLineData4;
	static char* propLineData5;
	static char* propLineData6;

	/* Other general properties */
	static char* propSerialNumber;
	static char* propFirmwareBuildVersion;
	static char* propFirmwareBuildDateTime;
	static char* propArrayReadIndex;
	static char* propObjectivePresetNames;
	static char* propExecuteCommand;

	/** State enumerations for executing command.

	MicroManager does not have the concept of making function calls down the stack,
	so it is necessary to use a "command" property which triggers actions based on
	values passed.

	To ensure entering random values cannot easily trigger commands, each command
	value contains an inverted copy of the same "key" value.  We can then easily
	validate the value without needing further checks.  This is only a simple
	interlock to protect against accidental changes, not a security measure.

	So that this fits in signed or unsigned long integers without producing
	warnings, we will stick to 12-bit "key" values, giving 24-bit enumerated values
	with the inverted copy of the "key" value.  This allows for up to 4095 commands
	which should be more than enough.
	*/
	enum ExecuteCommandState
	{
		NONE = 0,

		SAVE_TO_UNIT			= 0x001FFE,

		OFFSET_STEP_UP			= 0x010FEF,
		OFFSET_STEP_DOWN		= 0x011FED,

		Z_STEP_UP				= 0x020FDF,
		Z_STEP_DOWN				= 0x021FDE,
		Z_EMERGENCY_STOP		= 0x022FDD,
		Z_SOFT_STOP				= 0x023FDC,
		Z_GO_HOME				= 0x025FDA,
		Z_LIFT_TO_LOAD			= 0x026FD9
	};

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
