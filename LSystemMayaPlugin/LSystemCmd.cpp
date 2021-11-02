#include "LSystemCmd.h"


#include <maya/MGlobal.h>
#include <list>


#include <iostream>
#include <string.h>
#include <maya/MArgList.h>



LSystemCmd::LSystemCmd() : MPxCommand()
{
}

LSystemCmd::~LSystemCmd() 
{
}

MStatus LSystemCmd::doIt( const MArgList& args )
{
	// message in Maya output window
    cout<<"doIt"<<endl;
	std::cout.flush();

	// message in scriptor editor
	MGlobal::displayInfo("doIt");



	MStatus status;


	// Command Line Arguments
	MString stepSize = "";
	MString degreeAngle = "";
	MString grammar = "";
	MString numIterations = "";

	for (int i = 0; i < args.length(); i++)
	{
		if (args.asString(i) == MString("-stepSize"))
		{
			stepSize = args.asString(++i);
		}
		else if (args.asString(i) == MString("-degreeAngle"))
		{
			degreeAngle = args.asDouble(++i);
		}
		else if (args.asString(i) == MString("-grammar"))
		{
			grammar = args.asString(++i);
		}
		else if (args.asString(i) == MString("-numIterations"))
		{
			numIterations = args.asInt(++i);
		}
	}


	MString melCommands = "print \"stepSize: " + stepSize + "  \"";
	status = MGlobal::executeCommand(melCommands);

	melCommands = "print \"degreeAngle: " + degreeAngle + "  \"";
	status = MGlobal::executeCommand(melCommands);

	melCommands = "print \"grammar: " + grammar + "  \"";
	status = MGlobal::executeCommand(melCommands);

	melCommands = "print \"numIterations: " + stepSize + "  \"";
	status = MGlobal::executeCommand(melCommands);


	melCommands = "circle -c 0 0 0 -nr 0 1 0 -sw 360 -r 2 -d 3 -ut 0 -tol 0.01 -s 16 -ch 1 -name nurbsCircle1;";
	MGlobal::executeCommand(melCommands);


	melCommands = "curve -d 1 -p 5 0 0 -p 10 0 0 -k 0 -k 1 -name curve1;";
	MGlobal::executeCommand(melCommands);

	melCommands = "select -r nurbsCircle1 curve1;";
	MGlobal::executeCommand(melCommands);

	melCommands = "extrude -ch true -rn false -po 1 -et 2 -ucp 1 -fpt 1 -upn 1 -rotation 0 -scale 1 -rsp 1 \"nurbsCircle1\" \"curve1\";";
	MGlobal::executeCommand(melCommands);


    return status;
}

