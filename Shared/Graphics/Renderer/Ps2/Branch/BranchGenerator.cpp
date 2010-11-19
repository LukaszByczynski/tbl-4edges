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

#include "BranchGenerator.h"
#include "Branch.h"
#include <Shared/Base/Io/Log.h>
#include <Shared/Base/Debug/Assert.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Branch BranchGenerator::m_branches[100];
Vector3 BranchGenerator::m_strips[(5*100) * 100];
int BranchGenerator::m_branchIndex = 0;
int BranchGenerator::m_stripIndex = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Branch* BranchGenerator::generate(Branch* clone)
{
	if (m_branchIndex > 1000) 
		return 0;

	Branch* branch = &m_branches[m_branchIndex];
	branch->clone(clone);

	m_branchIndex++;

	return branch;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3* BranchGenerator::allocStrips()
{
	if (m_stripIndex > 2000)
		return 0;

	Vector3* strips = &m_strips[m_stripIndex * (5 * 100)];
	m_stripIndex++;

	return strips;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}
