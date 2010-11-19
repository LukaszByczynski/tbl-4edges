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

#ifndef zenic_ps2_CityScapePart_h
#define zenic_ps2_CityScapePart_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Part.h"
#include <Shared/Base/Types.h>
#include <Shared/Graphics/Renderer/Ps2/Shaders/PostEffect/FadeToFog.h>
#include <Shared/Graphics/Renderer/Ps2/RenderSettings.h>
#include <Shared/Graphics/Renderer/Ps2/Branch/BranchSettings.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	class SceneInfo;

	namespace ps2
	{
		class Texture;
		class Dma;
		class Renderer;
		class Branch;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CityScapePart : public Part
{

public:

	CityScapePart(Renderer& renderer, Dma& dmaChain);
	virtual ~CityScapePart() {}

	bool create();
	void update(float time, float deltaTime, SyncPoints::Part* syncPoints = 0);
	void reset();

private:

	enum
	{
		MaxCount = 40
	};


	BranchSettings m_branchSettings;
	FadeToFog m_fadeToFogPostEffect;
	Renderer& m_renderer;
	Dma& m_dmaChain;
	SceneInfo* m_scene;
	Texture* m_alphaMask;
	Branch*	m_branches[MaxCount];

	float m_splitTimer;
	float m_divideTimer;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline CityScapePart::CityScapePart(Renderer& renderer, Dma& dmaChain) :
	m_fadeToFogPostEffect(RenderSettings()),
	m_renderer(renderer),
	m_dmaChain(dmaChain),
	m_scene(0),
	m_alphaMask(0),
	m_splitTimer(0.0f),
	m_divideTimer(0.0f)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif



