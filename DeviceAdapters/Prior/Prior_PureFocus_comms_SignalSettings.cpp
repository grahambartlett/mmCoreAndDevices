///////////////////////////////////////////////////////////////////////////////
// FILE:          Prior_PureFocus_comms_SignalSettings.cpp
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
		long centreRounded = (long)(centre + 0.5);
		long widthRounded = (long)(width + 0.5);
		command << "PINHOLE," << centreRounded << "," << widthRounded;

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


int PureFocus850AutoFocus::GetPinhole(double& centre, double& width)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "PINHOLE";

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
						centre = atof(answer.substr(0, endC).c_str());
						width = atof(answer.substr(endC + 1).c_str());
					}
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
		long valueRounded = (long)(value + 0.5);
		command << "LASER," << valueRounded;

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


int PureFocus850AutoFocus::GetLaserPower(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "LASER";

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
					value = atof(answer.c_str());
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
		long aRounded = (long)(a + 0.5);
		long bRounded = (long)(b + 0.5);
		long cRounded = (long)(c + 0.5);
		long dRounded = (long)(d + 0.5);
		command << "BACKGROUND," << aRounded << "," << bRounded << "," << cRounded << "," << dRounded;

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


int PureFocus850AutoFocus::GetBackgrounds(double& a, double& b, double& c, double& d)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "BACKGROUND";

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
					size_t startA = 0;
					size_t endA = 0;
					size_t endB = 0;
					size_t endC = 0;

					startA = answer.find("BACKGROUND,");
					if ((startA == std::string::npos) || (startA >= (answer.length() - 1)))
					{
						ret = ERR_UNRECOGNIZED_ANSWER;
					}
					else
					{
						startA += 11;
						endA = answer.find(',', startA);
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
					}

					if (ret == DEVICE_OK)
					{
						a = atof(answer.substr(startA, endA).c_str());
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


int PureFocus850AutoFocus::SetRegionD(const double start, const double end)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		long startRounded = (long)(start + 0.5);
		long endRounded = (long)(end + 0.5);
		command << "REGION,D," << startRounded << "," << endRounded;

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			if (hasHead)
			{
				// Block/wait for acknowledge, or until we time out
				std::string answer;
				ret = GetSerialAnswer(port.c_str(), "\r", answer);

				if (ret == DEVICE_OK)
				{
					// Parse response
					if (answer.find("REGION,D,") != std::string::npos)
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
				else if (allowNoHead)
				{
					/* Deal with head not present */
					hasHead = false;
				}
				else
				{			
					/* Comms error and answer expected */
				}
			}

			if (!hasHead)
			{
				/* Simulate valid response if head is not present during development */
				ret = DEVICE_OK;
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}


int PureFocus850AutoFocus::GetRegionD(double& start, double& end)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "REGION,D";

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			if (hasHead)
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

						endA = answer.find(',');
						if ((endA == std::string::npos) || (endA == 0) || (endA >= (answer.length() - 1)))
						{
							ret = ERR_UNRECOGNIZED_ANSWER;
						}

						if (ret == DEVICE_OK)
						{
							start = atof(answer.substr(0, endA).c_str());
							end = atof(answer.substr(endA + 1).c_str());
						}
					}
				}
				else if (allowNoHead)
				{
					/* Deal with head not present */
					hasHead = false;
				}
				else
				{			
					/* Comms error and answer expected */
				}
			}

			if (!hasHead)
			{
				/* Simulate valid response if head is not present during development */
				start = 0.0;
				end = 0.0;
				ret = DEVICE_OK;
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}


int PureFocus850AutoFocus::SetExposureTimeUs(const double value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		long valueRounded = (long)(value + 0.5);
		command << "EXPOSURE," << valueRounded;

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


int PureFocus850AutoFocus::GetExposureTimeUs(double& value)
{
	int ret = DEVICE_OK;

	commsMutex.Lock();

	// First clear serial port from previous stuff
	ret = Prior::ClearPort(*this, *GetCoreCallback(), port);

	if (ret == DEVICE_OK)
	{
		// Send command
		std::ostringstream command;
		command << "EXPOSURE";

		ret = SendSerialCommand(port.c_str(), command.str().c_str(), "\r");

		if (ret == DEVICE_OK)
		{
			// Block/wait for acknowledge, or until we time out
			std::string answer;
			ret = GetSerialAnswer(port.c_str(), "\r", answer);

			if (ret == DEVICE_OK)
			{
				// Parse response
				value = atof(answer.c_str());
			}
		}
	}

	commsMutex.Unlock();

	return ret;
}
