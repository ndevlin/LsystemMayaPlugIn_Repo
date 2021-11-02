
#pragma once

#include <maya\MTypeId.h>
#include <maya\MFnMesh.h>
#include <maya\MPointArray.h>
#include <maya\MPoint.h>

#include "LSystemNode.h"

#include "LSystem.h"
#include "LSystemCmd.h"

#include "cylinder.h"

MObject LSystemNode::time;
MObject LSystemNode::outputMesh;
MTypeId LSystemNode::id(0x80000);


MObject LSystemNode::defaultAngle;
MObject LSystemNode::stepSize;
MObject LSystemNode::grammar;
MObject LSystemNode::inputTime;
MObject LSystemNode::outputGeometry;


LSystemNode::LSystemNode()
{}

LSystemNode::~LSystemNode()
{}


void* LSystemNode::creator()
{
	return new LSystemNode();
}

MStatus LSystemNode::initialize()
{
	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;
	MFnNumericAttribute numAttr;

	MStatus returnStatus;
	

	std::cout << "Initializing Node" << std::endl;

	LSystemNode::time = unitAttr.create("time", "tm",
		MFnUnitAttribute::kTime,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystem time attribute\n");


	LSystemNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating output attribute\n");

	LSystemNode::defaultAngle = numAttr.create("angle", "angle", MFnNumericData::kDouble, 30.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystem angle attribute\n");

	LSystemNode::stepSize = numAttr.create("step", "step", MFnNumericData::kDouble, 1.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystem stepSize attribute\n");

	LSystemNode::grammar = typedAttr.create("grammar", "grammar",
		MFnData::kString,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystem grammar attribute\n");


	typedAttr.setStorable(false);

	returnStatus = addAttribute(LSystemNode::time);
	McheckErr(returnStatus, "ERROR adding time attribute\n");

	returnStatus = addAttribute(LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR adding outputMesh attribute\n");

	returnStatus = addAttribute(LSystemNode::defaultAngle);
	McheckErr(returnStatus, "ERROR adding angle attribute\n");

	returnStatus = addAttribute(LSystemNode::stepSize);
	McheckErr(returnStatus, "ERROR adding stepSize attribute\n");

	returnStatus = addAttribute(LSystemNode::grammar);
	McheckErr(returnStatus, "ERROR adding grammar attribute\n");


	/*
	returnStatus = attributeAffects(LSystemNode::time,
		LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	*/
	
	returnStatus = attributeAffects(LSystemNode::defaultAngle,
		LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");

	returnStatus = attributeAffects(LSystemNode::stepSize,
		LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");

	returnStatus = attributeAffects(LSystemNode::grammar,
		LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	

	return MS::kSuccess;
}


MStatus LSystemNode::compute(const MPlug& plug, MDataBlock& data)

{
	MStatus status;

	LSystem lsystem = LSystem();

	if (plug == outputMesh) {
		/* Get time */
		MDataHandle timeData = data.inputValue(time, &status);
		McheckErr(status, "Error getting time data handle\n");
		MTime time = timeData.asTime();

		/* Get output object */
		MDataHandle outputHandle = data.outputValue(outputMesh, &status);
		McheckErr(status, "ERROR getting output data handle\n");


		MDataHandle angleHandle = data.inputValue(defaultAngle, &status);
		McheckErr(status, "ERROR getting angle data handle\n");
		double angleDouble = angleHandle.asDouble();

		MDataHandle stepHandle = data.inputValue(stepSize, &status);
		McheckErr(status, "ERROR getting stepSize data handle\n");
		double stepDouble = stepHandle.asDouble();

		MDataHandle grammarHandle = data.inputValue(grammar, &status);
		McheckErr(status, "ERROR getting grammar data handle\n");
		MString grammarString = grammarHandle.asString();



		lsystem.loadProgramFromString(grammarString.asChar());
		lsystem.setDefaultAngle(angleDouble);
		lsystem.setDefaultStep(stepDouble);


		std::vector<LSystem::Branch> branches;

		lsystem.process(time.as(MTime::kFilm), branches);


		MPointArray points;
		MIntArray facesCount;
		MIntArray faceConnects;

		MFnMesh meshFS;


		for (int i = 0; i < branches.size(); i++)
		{
			LSystem::Branch currentBranch = branches.at(i);
			vec3 one = currentBranch.first;
			vec3 two = currentBranch.second;

			// Switch order to make tree grow vertically
			MPoint point1 = MPoint(one[0], one[2], one[1]);
			MPoint point2 = MPoint(two[0], two[2], two[1]);

			CylinderMesh mesh = CylinderMesh(point1, point2);

			mesh.appendToMesh(points, facesCount, faceConnects);
		}
		
		int numVerts = points.length();
		int numFaces = facesCount.length();


		MFnMeshData dataCreator;
		MObject newOutputData = dataCreator.create(&status);
		McheckErr(status, "ERROR creating outputData");

		MObject newOutputMesh = meshFS.create(numVerts, numFaces, points, facesCount, faceConnects, newOutputData, &status);
		McheckErr(status, "ERROR creating output Mesh \n");

		outputHandle.set(newOutputData);
		data.setClean(plug);
	}
	else
		return MS::kUnknownParameter;

	return MS::kSuccess;
}


MStatus LSystemNode::doIt(const MArgList &args)
{
	MStatus status = MStatus::kSuccess;

	MGlobal::displayInfo("Creating an LSystemNode. ");

	return status;
}





