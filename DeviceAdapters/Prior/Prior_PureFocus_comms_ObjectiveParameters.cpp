///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_comms_ObjectiveParameters.cpp
// PROJECT:       Micro-Manager
// SUBSYSTEM:     DeviceAdapters
//-----------------------------------------------------------------------------
// DESCRIPTION:   Prior PureFocus comms handling
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
#include <cstdlib>
#include <sstream>

#include "prior_PureFocus.h"

#include "../../MMDevice/ModuleInterface.h"


int PureFocus850AutoFocus::SetObjective(const long value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OBJ," << value;

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() >= 1) && (answer[0] == '0'))
				{
					// Success
				}
				else if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else
				{
					ret = ERR_UNRECOGNIZED_ANSWER;
				}
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}


int PureFocus850AutoFocus::GetObjective(long& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OBJ";
		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() >= 1) && (answer[0] >= '1') && (answer[0] <= '6'))
				{
					// Valid response
					value = (long)(answer[0] - '0');
				}
				else if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else
				{
					ret = ERR_UNRECOGNIZED_ANSWER;
				}
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}
