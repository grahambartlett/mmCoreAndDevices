///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_ZStage.cpp
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus Z-stage adapter
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
#include "FixSnprintf.h"

#include "prior_PureFocus.h"

#include <cstdio>
#include <string>
#include <math.h>
#include "../../MMDevice/ModuleInterface.h"
#include <sstream>


PureFocus850ZStage::PureFocus850ZStage() :
CStageBase <PureFocus850ZStage>(),
name(g_PureFocus850ZStageName),
initialized(false)
{
	// Pre-initialization properties
	CreateProperty(MM::g_Keyword_Name, name.c_str(), MM::String, true);
	CreateProperty(MM::g_Keyword_Description, "Prior PureFocus 850 Z stage drive", MM::String, true);
}


PureFocus850ZStage::PureFocus850ZStage(PureFocus850ZStage&) :
CStageBase <PureFocus850ZStage>(),
name(g_PureFocus850ZStageName),
initialized(false)
{
	// Should never be called
	assert(false);
}


PureFocus850ZStage& PureFocus850ZStage::operator=(PureFocus850ZStage&)
{
	// Should never be called
	assert(false);
	return *this;
}


bool PureFocus850ZStage::Busy()
{
	return false;
}


void PureFocus850ZStage::GetName(char* pszName) const
{
	CDeviceUtils::CopyLimitedString(pszName, name.c_str());
}


int PureFocus850ZStage::Initialize()
{
	int ret = DEVICE_OK;

	initialized = true;

	//ret = UpdateStatus();
	if (ret != DEVICE_OK)
	{
		return ret;
	}

	return DEVICE_OK;
}


int PureFocus850ZStage::Shutdown()
{
	if (initialized)
	{
		initialized = false;
	}

	return DEVICE_OK;
}


PureFocus850ZStage::~PureFocus850ZStage()
{
	Shutdown();
}


int PureFocus850ZStage::SetPositionUm(double pos)
{
	return DEVICE_OK;
}


int PureFocus850ZStage::SetRelativePositionUm(double pos)
{
	return DEVICE_OK;
}


int PureFocus850ZStage::GetPositionUm(double& pos)
{
	pos = 0.0;
	return DEVICE_OK;
}


int PureFocus850ZStage::SetPositionSteps(long steps)
{
	return DEVICE_OK;
}


int PureFocus850ZStage::GetPositionSteps(long& steps)
{
	steps = 1;
	return DEVICE_OK;
}


int PureFocus850ZStage::SetOrigin()
{
	return DEVICE_OK;
}


int PureFocus850ZStage::GetLimits(double& min, double& max)
{
	min = 0.0;
	max = 1.0;
	return DEVICE_OK;
}


int PureFocus850ZStage::IsStageSequenceable(bool& isSequenceable) const
{
	isSequenceable = false;
	return DEVICE_OK;
}


bool PureFocus850ZStage::IsContinuousFocusDrive() const
{
	return false;
}
