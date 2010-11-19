///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2003-2006 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Notice: this code needs to be improved to handle things like
// -iImage.tga (argument directly after parameter)
// -i "my image here" (get string inside " ")

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Base/Io/Log.h>
#include "Arguments.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arguments::Arguments()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arguments::~Arguments()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Arguments::init(int argc,char* argv[])
{
	if (argc == 1)
	{
		showHelp();
		return false;
	}

	for (uint i = 1; i < (uint)argc; ++i)
	{
		std::map<std::string,const char*>::iterator p = m_arguments.find(argv[i]);

		if (p != m_arguments.end())
			return false;

		m_arguments.insert(std::pair<std::string,const char*>(std::string(argv[i]), argv[i+1]));
		++i; // nice
	}
		
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* Arguments::getArg(const char* arg)
{
	std::map<std::string,const char*>::iterator i = m_arguments.find(arg);

	if (i != m_arguments.end())
		return i->second;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Arguments::showHelp()
{
	logOut << "Builder Parameters" << endl;
	logOut << "Notice: this code needs to be improved to handle things like" << endl;
	logOut << "-iImage.tga (argument directly after parameter)" << endl;
	logOut << "-i \"my image here\" (get string inside \" \")" << endl << endl;

	logOut << "-h Show this help" << endl;
	logOut << "-p [Platform] (ps2, opengl)" << endl;
	logOut << "-f texture format (4, 8, 32)" << endl;
	logOut << "-s Input Scene" << endl;
	logOut << "-i Input Image" << endl;
	logOut << "-o Output file" << endl;

	logOut << "Example: Builder -i myImage.jpg -o myImage.zei" << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}