///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_comms_ServoSettings.cpp
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


int PureFocus850AutoFocus::SetServoOn(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SERVO," << (long)value;

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


int PureFocus850AutoFocus::GetServoOn(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SERVO";

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
					value = false;
				}
				else if ((answer.length() >= 1) && (answer[0] == '1'))
				{
					value = true;
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


int PureFocus850AutoFocus::SetKP(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KP," << value;

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


int PureFocus850AutoFocus::GetKP(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KP";
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


int PureFocus850AutoFocus::SetKI(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KI," << value;

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


int PureFocus850AutoFocus::GetKI(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KI";
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


int PureFocus850AutoFocus::SetKD(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KD," << value;

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


int PureFocus850AutoFocus::GetKD(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KD";
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


int PureFocus850AutoFocus::SetFocusPidTarget()
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "TARGET";

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


int PureFocus850AutoFocus::GetFocusPidTarget(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "TARGET,?";

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


int PureFocus850AutoFocus::SetServoDirectionPositive(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SERVODIR,";
		if (value)
		{
			command << "1";
		}
		else
		{
			command << "-1";
		}

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


int PureFocus850AutoFocus::GetServoDirectionPositive(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SERVODIR";

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if ((answer.length() >= 2) && (answer[0] == '-') && (answer[1] == '1'))
				{
					value = false;
				}
				else if ((answer.length() >= 1) && (answer[0] == '1'))
				{
					value = true;
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


int PureFocus850AutoFocus::SetOutputLimits(const double min, const double max)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OUTLIM," << (long)min << "," << (long)max;

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

int PureFocus850AutoFocus::GetOutputLimits(double& min, double& max)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OUTLIM";

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
					size_t endC = 0;

					endC = answer.find(',');
					if ((endC == std::string::npos) || (endC == 0) || (endC >= (answer.length() - 1)))
					{
						ret = ERR_UNRECOGNIZED_ANSWER;
					}

					if (ret == DEVICE_OK)
					{
						min = atof(answer.substr(0, endC).c_str());
						max = atof(answer.substr(endC + 1).c_str());
					}
				}
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}
