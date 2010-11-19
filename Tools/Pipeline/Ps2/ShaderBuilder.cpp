
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

#include "ShaderBuilder.h"
#include "ExporterBackend.h"
#include <XSIMaterial.h>
#include <XSIShader.h>
#include <XSIImageLibrary.h>
#include <VariantParameter.h> 
#include <ConnectionPoint.h>
#include <ShaderConnectionPoint.h>
#include <Scene.h>
#include <Shared/Base/Io/Log.h>
#include <Shared/Base/Storage/String.h>
#include <Shared/Graphics/Renderer/Ps2/Material.h>
#include <Shared/Geometry/Ps2/TempTexture.h>
#include <Shared/Base/Math/Color32.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ShaderBuilder::build(Material* material, ExporterBackend& backend, CSLXSIMaterial* xsiMaterial)
{
	int shaderCount = xsiMaterial->GetShaderCount();
	CSLXSIShader** shaders = xsiMaterial->GetShaderList();

	ZENIC_INFO("Material name " << xsiMaterial->Name().GetText()); 

	for (int i = shaderCount-1; i >= 0; --i)
	{
		CSLXSIShader* xsiShader = shaders[i];

		String shaderId(xsiShader->GetProgID());

		u32 hash = shaderId.quickHash();

		switch (hash)
		{
			case SoftImageTxt2d : textureShader(material, backend, xsiShader); break;
			case SoftImageConstant : constantShader(material, backend, xsiShader); break;
			//case SoftImagePtBillboard : billboardShader(material, backend, xsiShader); break;
			default:
			{
				ZENIC_WARNING("Unable to build Shader of type: " << shaders[i]->GetProgID());
			}
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderBuilder::textureShader(Material* material, ExporterBackend& backend, CSLXSIShader* xsiShader)
{
	// Setup constant values for the shader

	constantShader(material, backend, xsiShader);

	// Find image pointer

	uint subCount = xsiShader->GetConnectionPointCount();
	CSLShaderConnectionPoint** shaderConnectionPoints = xsiShader->GetConnectionPointList();

	CSLVariantParameter** variantParameterList = xsiShader->GetParameterList();
	uint variantParameterListCount = xsiShader->GetParameterCount();

	for (uint k = 0; k < subCount; ++k)
	{
		CSLShaderConnectionPoint* shaderConnectionPoint = shaderConnectionPoints[k];
		CSLShaderConnectionPoint::EConnectionType shaderType = shaderConnectionPoint->GetConnectionType();

		if (shaderType == CSLShaderConnectionPoint::SI_IMAGE)
		{
			CSLImage* image = xsiShader->Scene()->GetImageLibrary ()->FindImage(shaderConnectionPoint->GetImage());

			Texture* texture = reinterpret_cast<Texture*>(backend.findTexture(image));

			if (texture)
				material->setBaseTexture(*texture);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ShaderBuilder::constantShader(Material* material, ExporterBackend& backend, CSLXSIShader* xsiShader)
{
	CSLVariantParameter** variantParameterList = xsiShader->GetParameterList();
	uint variantParameterListCount = xsiShader->GetParameterCount();

	Color32 color(0, 0, 0, 0);
	float transparency = 0.0f;

	for (uint i = 0; i < variantParameterListCount; ++i)
	{
		CSLVariantParameter* parameter = variantParameterList[i];
		SI_Char* name = parameter->GetName();
		
		if (!strcmp("Name", name))
		{
			SI_TinyVariant* variantValue = parameter->GetValue(); 
			const char* variantName = variantValue->p_cVal;
			if (variantName)
			{
				if (strstr(variantName, "Glow"))
					material->setGlow(true);
				else if (strstr(variantName, "Additive"))
				{
					material->setAdditive(true);
					material->setTransValue(0x40);
				}
			}
		}
		else if (!strcmp("color.red", name))
			color.r = u8(parameter->GetFloatValue() * 255.0f);
		else if (!strcmp("color.green", name))
			color.g = u8(parameter->GetFloatValue() * 255.0f);
		else if (!strcmp("color.blue", name))
			color.b = u8(parameter->GetFloatValue() * 255.0f);
		else if (!strcmp("transparency.red", name))
			transparency += parameter->GetFloatValue();
		else if (!strcmp("transparency.green", name))
			transparency += parameter->GetFloatValue();
		else if (!strcmp("transparency.blue", name))
			transparency += parameter->GetFloatValue();
	}

	material->setColor(color);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void ShaderBuilder::BillboardShader(Material* material, ExporterBackend& backend, CSLXSIShader* xsiShader)
{
	material->setSprite(true);
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}


