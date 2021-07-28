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


int PureFocus850AutoFocus::GetLineData(std::string& values)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "@,0,1500";

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		// 3 hex characters per pixel, 1500 pixels
		values.resize(4500);

		int index;
		for (index = 0; (ret == DEVICE_OK) && (index < 23); index ++)
		{
			// 23 full lines at 64 pixels per line
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);
			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() >= 198) && (answer.compare(0, 6, "@,064,") == 0))
				{
					values.replace((index * 192), 192, answer, 6, 192);
				}
				else if ((answer.length() >= 4) && (answer.compare(0, 3, "@,E") == 0))
				{
					int errNo = atoi(answer.substr(3).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else
				{
					ret = ERR_UNRECOGNIZED_ANSWER;
				}
			}
		}

		if (ret == DEVICE_OK)
		{
			// 1 partial line left of 28 pixels
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);
			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() >= 90) && (answer.compare(0, 6, "@,028,") == 0))
				{
					values.replace((23 * 192), 84, answer, 6, 84);
				}
				else if ((answer.length() >= 4) && (answer.compare(0, 3, "@,E") == 0))
				{
					int errNo = atoi(answer.substr(3).c_str());
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


int PureFocus850AutoFocus::RefreshLineData()
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "REFRESH";

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		std::string answer;
		ret = GetSerialAnswer(port.c_str(), "\r", answer);
		if (ret == DEVICE_OK)
		{
			// Parse response
			if (answer.compare("REFRESH,0") == 0)
			{
				// Response is OK
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

	commsMutex.Unlock();

	return ret;
}
