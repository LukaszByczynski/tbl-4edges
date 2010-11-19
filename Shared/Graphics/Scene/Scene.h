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

#ifndef zenic_Scene_h
#define zenic_Scene_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Base/Serialize/SerializableFactory.h>

#include "AnimationController.h"
#include "BoneArray.h"
#include "BoneMap.h"
#include "Model.h"
#include "Node.h"
#include "Camera.h"
#include "SceneInfo.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

ZENIC_REFERENCE_SERIALIZABLE_FACTORY(BoneArray);
ZENIC_REFERENCE_SERIALIZABLE_FACTORY(BoneMap);
ZENIC_REFERENCE_SERIALIZABLE_FACTORY(Model);
ZENIC_REFERENCE_SERIALIZABLE_FACTORY(Node);
ZENIC_REFERENCE_SERIALIZABLE_FACTORY(Camera);
ZENIC_REFERENCE_SERIALIZABLE_FACTORY(SceneInfo);
ZENIC_REFERENCE_SERIALIZABLE_FACTORY(AnimationController);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
