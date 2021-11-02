
#pragma once

//#include <maya/MPxCommand.h>
//#include <maya/MFnPlugin.h> //
//#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MArgList.h>
//#include <maya/MGlobal.h>
#include <maya/MSimple.h>
//#include <maya/MDoubleArray.h> //
//#include <maya/MPoint.h> //
#include <maya/MPointArray.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MDGModifier.h>
#include <maya/MPlugArray.h>
#include <maya/MVector.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MStringArray.h>
#include <list>

#include "LSystemCmd.h"


#include "LSystemNode.h"


MStatus initializePlugin(MObject obj)
{
	MStatus   status = MStatus::kSuccess;
	MFnPlugin plugin(obj, "Nathan Devlin", "1.0", "Any");

	status = plugin.registerCommand("LSystemCmd", LSystemCmd::creator);
	if (!status) {
		status.perror("registerCommand");
		return status;
	}

	status = plugin.registerNode("LSystemNode", LSystemNode::id,
		LSystemNode::creator, LSystemNode::initialize);
	if (!status) {
		status.perror("registerNode");
		return status;
	}


	std::string pluginPath = plugin.loadPath().asChar();
	std::string filePath = "source \"" + pluginPath + "/MyPluginDialog.mel\";";
	
	MGlobal::executeCommand(filePath.c_str(), true);


	return status;
}


MStatus uninitializePlugin(MObject obj)
{
	MStatus   status = MStatus::kSuccess;
	MFnPlugin plugin(obj);

	status = plugin.deregisterCommand("LSystemCmd");
	if (!status) {
		status.perror("deregisterCommand");
		return status;
	}

	status = plugin.deregisterNode(LSystemNode::id);
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}


	return status;
}

