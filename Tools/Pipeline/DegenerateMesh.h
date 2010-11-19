///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2005 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef zenic_DegenerateMesh_h
#define zenic_DegenerateMesh_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSLXSIMesh;
class CSLXSIShape;
class CSLXSITriangleList;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Base/Math/Vector3.h>
#include <Shared/Base/Math/Vector2.h>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DegenerateMesh
{
public:

	DegenerateMesh();
	~DegenerateMesh();

	struct Vertex
	{
		inline Vertex() : 
			position(0.0f, 0.0f, 0.0f), 
			normal(0.0f, 0.0f, 0.0f), 
			uv(0.0f, 0.0f), 
			nextIndex(0), 
			initialized(false)
		{
		}

		Vector3	position;
		Vector3 normal;
		Vector2 uv;
		u32 nextIndex;
		bool initialized;

		bool operator==(const Vertex& v) const;
	};

	void process(CSLXSIMesh* mesh, bool useNormals = false);
	const std::vector<u32>& indexList() const { return m_indices; }
	const std::vector<Vertex>& vertexList() const { return m_uniqueVertexList; }

private:

	u32 createOrRetrieveUniqueVertex(u32 originalPositionIndex, const Vertex& vertex);

	std::vector<Vertex> m_uniqueVertexList;
	std::vector<u32> m_indices;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif
