
#pragma once

#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MPoint.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>

#include <maya/MFnNumericAttribute.h>

#include <maya/MFnPlugin.h>

#include <maya/MPxNode.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMeshData.h>

#include <maya/MIOStream.h>

#include <maya/MPxCommand.h>
#include <maya/MGlobal.h>


#include "Lsystem.h"



MStatus returnStatus;

#define McheckErr(stat,msg)			\
	if ( MS::kSuccess != stat ) {	\
		cerr << msg;				\
		return MS::kFailure;		\
	}

class LSystemNode : public MPxNode
{
public:
	LSystemNode();
	virtual ~LSystemNode();

	MStatus compute(const MPlug& plug, MDataBlock& data);

	static  void*	creator();
	static  MStatus initialize();

	virtual MStatus doIt(const MArgList &args);

	static MObject	time;
	static MObject	outputMesh;
	static MTypeId	id;


	static MObject defaultAngle;
	static MObject stepSize;
	static MObject grammar;
	static MObject inputTime;
	static MObject outputGeometry;



	};

