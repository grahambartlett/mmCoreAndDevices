///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_comms_FocusSignal.cpp
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


int PureFocus850AutoFocus::GetABCD(double &a, double &b, double &c, double &d)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "ABCD";

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else
				{
					// Check and tokenise response
					size_t endA = 0;
					size_t endB = 0;
					size_t endC = 0;

					endA = answer.find(',');
					if ((endA == std::string::npos) || (endA == 0) || (endA >= (answer.length() - 1)))
					{
						ret = ERR_UNRECOGNIZED_ANSWER;
					}
					else
					{
						endB = answer.find(',', endA + 1);
						if ((endB == std::string::npos) || ((endB - endA) < 2) || (endB >= (answer.length() - 1)))
						{
							ret = ERR_UNRECOGNIZED_ANSWER;
						}
						else
						{
							endC = answer.find(',', endB + 1);
							if ((endC == std::string::npos) || ((endC - endB) < 2) || (endC >= (answer.length() - 1)))
							{
								ret = ERR_UNRECOGNIZED_ANSWER;
							}
						}
					}

					if (ret == DEVICE_OK)
					{
						a = atof(answer.substr(0, endA).c_str());
						b = atof(answer.substr(endA + 1, endB).c_str());
						c = atof(answer.substr(endB + 1, endC).c_str());
						d = atof(answer.substr(endC + 1).c_str());
					}
				}
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}


int PureFocus850AutoFocus::GetFocusPidPosition(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "POS";
		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else if (answer.length() >= 1)
				{
					value = atof(answer.c_str());
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


int PureFocus850AutoFocus::GetFocusPidOutput(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OUTPUT";
		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else if (answer.length() >= 1)
				{
					value = atof(answer.c_str());
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


int PureFocus850AutoFocus::GetFocusPidError(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "ERROR";
		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else if (answer.length() >= 1)
				{
					value = atof(answer.c_str());
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
