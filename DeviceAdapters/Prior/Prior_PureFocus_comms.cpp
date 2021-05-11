///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_comms.cpp
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


int PureFocus850AutoFocus::SetKeypadLock(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "KBDLOCK," << (long)value;

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
					if (answer.compare("E,5") == 0)
					{
						// Older firmware may not support this command, in which case we ignore the error
						ret = DEVICE_OK;
					}
					else
					{
						int errNo = atoi(answer.substr(2).c_str());
						ret = ERR_OFFSET + errNo;
					}
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


int PureFocus850AutoFocus::SetPinhole(const double centre, const double width)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "PINHOLE," << (long)centre << "," << (long)width;

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


int PureFocus850AutoFocus::SetLaserPower(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LASER," << (long)value;

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


int PureFocus850AutoFocus::SetBackgrounds(const double a, const double b, const double c, const double d)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "BACKGROUND," << (long)a << "," << (long)b << "," << (long)c << "," << (long)d;

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				if (answer.find("BACKGROUND", 0, 10) != std::string::npos)
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


int PureFocus850AutoFocus::GetSampleState(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAMPLE";

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


int PureFocus850AutoFocus::SetSampleLowThreshold(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAMPLEL," << (long)value;

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


int PureFocus850AutoFocus::GetFocusState(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAMPLE";

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


int PureFocus850AutoFocus::SetFocusLowThreshold(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "FOCUSL," << (long)value;

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


int PureFocus850AutoFocus::SetFocusHighThreshold(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "FOCUSH," << (long)value;

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


int PureFocus850AutoFocus::SetFocusRangeThreshold(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "FOCUSR," << value;

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


int PureFocus850AutoFocus::SetInFocusRecoveryTime(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "IFP," << (long)value;

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


int PureFocus850AutoFocus::GetTimeToInFocus(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "TTIF";

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


int PureFocus850AutoFocus::SetInterfaceHighThreshold(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "INTERFACEH," << (long)value;

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


int PureFocus850AutoFocus::SetInterfaceLowThreshold(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "INTERFACEL," << (long)value;

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


int PureFocus850AutoFocus::GetInterfaceCorrect(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "INTERFACE";

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


int PureFocus850AutoFocus::SetServoInhibit(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "INHIBIT," << (long)value;

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


int PureFocus850AutoFocus::GetServoInhibit(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "INHIBIT";

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


int PureFocus850AutoFocus::SetFocusServoInterruptOn(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "FOCUSI," << (long)value;

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


int PureFocus850AutoFocus::SetServoLimit(const bool isActive, const double maxPositive, const double maxNegative)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SERVOLIMIT," << (long)isActive << "," << (long)maxPositive << "," << (long)maxNegative;

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


int PureFocus850AutoFocus::SetDigipotControlsOffset(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENS," << value;

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


int PureFocus850AutoFocus::GetDigipotControlsOffset(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENS";

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


int PureFocus850AutoFocus::SetDigipotFocusSpeedPercent(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OF," << value;

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


int PureFocus850AutoFocus::SetDigipotOffsetSpeedPercent(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "OFL," << value;

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


int PureFocus850AutoFocus::SetOffsetToHome()
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENSH";

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


int PureFocus850AutoFocus::SetOffsetVelocityMoveUmPerS(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Convert value from um/s to steps/s, where 25600 steps = 1mm
		const double scaledValue = value * (25600.0 / 1000.0);

		// Send command
		std::ostringstream command;
		command << "LENSV," << scaledValue;

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



int PureFocus850AutoFocus::GetOffsetPositionUm(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENSP";

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
					// Convert value from steps to um, where 25600 steps = 1mm
					value = atof(answer.c_str());
					value *= (1000.0 / 25600.0);
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


int PureFocus850AutoFocus::GetIsOffsetMoving(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENS$";

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


int PureFocus850AutoFocus::SetOffsetPositionUm(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Convert value from um/s to steps/s, where 25600 steps = 1mm
		const double scaledValue = value * (25600.0 / 1000.0);

		// Send command
		std::ostringstream command;
		command << "LENSG," << (long)scaledValue;

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


int PureFocus850AutoFocus::SetOffsetToStoredOffset(const long index)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENSGO," << (index + 1);

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


int PureFocus850AutoFocus::SetStoredOffsetToCurrentPosition(const long index)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENSSO," << (index + 1);

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


int PureFocus850AutoFocus::SetStoredOffsetUm(const long index, const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Convert value from um/s to steps/s, where 25600 steps = 1mm
		const double scaledValue = value * (25600.0 / 1000.0);

		// Send command
		std::ostringstream command;
		command << "LENSSO," << (index + 1) << "," << (long)scaledValue;

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


int PureFocus850AutoFocus::SetFocusDriveRange(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "UPR," << value;

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


int PureFocus850AutoFocus::GetIsFocusDriveMoving(bool& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "$";

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
				else if ((answer.length() >= 1) && (answer[0] == '4'))
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

int PureFocus850AutoFocus::SetFocusPositionUm(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Convert value from 100nm steps to um
		const double scaledValue = value * 10.0;

		// Send command
		std::ostringstream command;
		command << "PZ," << (long)scaledValue;

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


int PureFocus850AutoFocus::GetFocusPositionUm(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LENSP";

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
					// Convert value from 100nm steps to um
					value = atof(answer.c_str());
					value *= 0.1;
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



int PureFocus850AutoFocus::SetFocusPositionVelocityMoveUmPerS(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "VZ," << value;

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


int PureFocus850AutoFocus::SetFocusPositionZeroToCurrentPosition()
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "Z";

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


int PureFocus850AutoFocus::SetMaxFocusSpeedPercent(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SMZ," << value;

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


int PureFocus850AutoFocus::GetMaxFocusSpeedPercent(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SMZ";

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


int PureFocus850AutoFocus::SetMaxFocusSpeedMicronsPerS(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SMZ," << value << ",U";

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


int PureFocus850AutoFocus::GetMaxFocusSpeedMicronsPerS(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SMZ,U";

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


int PureFocus850AutoFocus::SetMaxFocusAccelPercent(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAZ," << value;

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


int PureFocus850AutoFocus::GetMaxFocusAccelPercent(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAZ";

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


int PureFocus850AutoFocus::SetMaxFocusAccelMicronsPerS2(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAZ," << value << ",U";

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


int PureFocus850AutoFocus::GetMaxFocusAccelMicronsPerS2(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAZ,U";

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


int PureFocus850AutoFocus::SetFocusDriveDirectionPositive(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "ZD,";
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


int PureFocus850AutoFocus::GetLimitSwitches(bool& positiveLimitActive, bool& negativeLimitActive)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LMT";

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
					if (answer[0] == '0')
					{
						positiveLimitActive = false;
						negativeLimitActive = false;
					}
					else if (answer[0] == '1')
					{
						positiveLimitActive = true;
						negativeLimitActive = false;
					}
					else if (answer[0] == '2')
					{
						positiveLimitActive = false;
						negativeLimitActive = true;
					}
					else if (answer[0] == '3')
					{
						positiveLimitActive = true;
						negativeLimitActive = true;
					}
					else
					{
						ret = ERR_UNRECOGNIZED_ANSWER;
					}
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


int PureFocus850AutoFocus::GetBuildInfo(std::string& version, std::string& dateTime)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "DATE";

		// Read and ignore the first line
		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");
		if (ret == DEVICE_OK)
		{
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);
		}

		if (ret == DEVICE_OK)
		{
			// Read the second line, which contains the date and time
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				/* The response includes a line with the format
				"Version 1.09 compiled Apr 28 2021 13:16:31"
				We don't care about the rest of the response, so we
				just look for this line and ignore everything else.
				*/
				if ((answer.length() > 2) && (answer[0] == 'E'))
				{
					int errNo = atoi(answer.substr(2).c_str());
					ret = ERR_OFFSET + errNo;
				}
				else if (answer.length() >= 1)
				{
					size_t start, end;

					start = answer.find("Version ");
					if (start == std::string::npos)
					{
						ret = ERR_UNRECOGNIZED_ANSWER;
					}
					else
					{
						start += 8;
						end = answer.find(" ", start);
						if ((end == std::string::npos) || (end <= start))
						{
							ret = ERR_UNRECOGNIZED_ANSWER;
						}
						else
						{
							version = answer.substr(start, (end - start));
							start = end + 1;
						}
					}

					if (ret == DEVICE_OK)
					{
						end = answer.find("compiled ", start);
						if (end == std::string::npos)
						{
							ret = ERR_UNRECOGNIZED_ANSWER;
						}
						else
						{
							start = end + 9;
							end = answer.find("\n", start);
							if (end == std::string::npos)
							{
								// Read entire rest of string
								dateTime = answer.substr(start);
							}
							else
							{
								// Read rest of line
								dateTime = answer.substr(start, (end - start));
							}
						}
					}
				}
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}


int PureFocus850AutoFocus::GetSerialNumber(long& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SERIAL";

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
					value = atoi(answer.c_str());
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


int PureFocus850AutoFocus::Restart()
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "RESTART";

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


int PureFocus850AutoFocus::SaveConfigurationToFlash()
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "SAVE";

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


int PureFocus850AutoFocus::SetPiezoMode(const bool value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "CONFIG,";
		if (value)
		{
			command << "P";
		}
		else
		{
			command << "S";
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
