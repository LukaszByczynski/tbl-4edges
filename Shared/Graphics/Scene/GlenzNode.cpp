///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2006 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GlenzNode.h"

#include <Shared/Base/Serialize/SerializableVersion.h>
#include <Shared/Base/Serialize/Serializer.h>

#include <Shared/Base/Io/Log.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ZENIC_CREATE_SERIALIZABLE_FACTORY(GlenzNode, SERIALIZABLE_ID('Z','N','I','C'), SERIALIZABLE_ID('G','L','N','Z'))

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint m_seed = 93186752;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float floatRandom()  
{
	static uint a = 1588635695, m = 4294967291U, q = 2, r = 1117695901;
	m_seed = a*(m_seed % q) - r*(m_seed / q);
	return ((float)m_seed / (float)m);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint GlenzNode::s_collectedCount = 0;
GlenzNode* GlenzNode::s_collectedNodes[MaxCollectedNodes];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GlenzNode::GlenzNode()
{
	m_angles.x = floatRandom();
	m_angles.y = floatRandom();
	m_angles.z = floatRandom();

	m_anglesSpeed.x = floatRandom();
	m_anglesSpeed.y = floatRandom();
	m_anglesSpeed.z = floatRandom();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GlenzNode::~GlenzNode()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GlenzNode::update(float /*time*//*, float deltaTime*/)
{
	float deltaTime = 1.0f / 60.0f;	// TODO: Fix me badly
	Vector3 pos = transform().position();

	Matrix4 mx;
	Matrix4 my;
	Matrix4 mz;

	mx.makeXrotation(m_angles.x);
	my.makeYrotation(m_angles.y);
	mz.makeZrotation(m_angles.z);

	m_angles.x += m_anglesSpeed.x * deltaTime;
	m_angles.y += m_anglesSpeed.y * deltaTime;
	m_angles.z += m_anglesSpeed.z * deltaTime;

	Matrix4 matrix = mx * my * mz;
	matrix.setPosition(pos);

	setTransform(matrix);

	ZENIC_ASSERT_DESC(s_collectedCount < MaxCollectedNodes, "Maximum of 300 GlenzNodes supported for now");
	s_collectedNodes[s_collectedCount++] = this;

	// No need to update node here as we rotate these nodes ourself
	//Node::update(time);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GlenzNode::serialize(Serializer& s)
{
	SerializableVersion version(1, factory());

	s << version;

	Node::serialize(s);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}



