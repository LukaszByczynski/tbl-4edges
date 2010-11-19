 #include "FadeToGray.h"
#include "PostEffectBuilder.h"
#include "PostEffectHelper.h"

#include <Shared/Hardware/Ps2/Gs.h>
#include <Shared/Hardware/Ps2/Gif.h>
#include <Shared/Hardware/Ps2/Dma.h>
#include <Shared/Graphics/Renderer/Ps2/Renderer.h>
#include <Shared/Base/Io/Log.h>

#define LINE ZENIC_INFO(__LINE__);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FadeToGray::FadeToGray(const RenderSettings& renderSettings) :
	m_settings(renderSettings)
{
	u32 tempPal[256];

	m_ztessel1 = zenic_new u8[64 * 1024];
	m_ztessel2 = zenic_new u8[64 * 1024];
	m_zpal = zenic_new u8[4 * 1024];

	m_gtessel1 = zenic_new u8[64 * 1024];
	m_gtessel2 = zenic_new u8[64 * 1024];
	m_gpal = zenic_new u8[4 * 1024];

	for (uint i = 0; i < 256; ++i)
		tempPal[i] = (i / 2) * 0x1010101;

	PostEffectBuilder::buildPaletteUploadChain(m_zpal, 510, tempPal);

	ZENIC_INFO(m_settings.zbuffer());
	ZENIC_INFO(m_settings.buffer0());
	ZENIC_INFO(m_settings.buffer1());
	ZENIC_INFO(m_settings.screenWidth());
	ZENIC_INFO(m_settings.screenHeight());

	PostEffectBuilder::buildIndexChain(m_ztessel2, 140, 0, 
												   140, 510, 0, 0, 
												   640, 224);

	PostEffectBuilder::buildIndexChain(m_ztessel1, 140, 70, 
												   140, 510, 0, 0, 
												   640, 224);
/*
	PostEffectBuilder::buildIndexChain(m_ztessel1, m_settings.zbuffer(), m_settings.buffer1(), 
												   m_settings.zbuffer(), 510, 0, 0, 
												   m_settings.screenWidth(), m_settings.screenHeight());
*/
	for (uint i = 0; i < 256; ++i)
		tempPal[i] = i * 0x1010101;


	PostEffectBuilder::buildPaletteUploadChain(m_gpal, 510, tempPal);

	PostEffectBuilder::buildIndexChain(m_gtessel1, 0, 0, 
												   140, 510, 0, 0, 
												   640, 224);

	PostEffectBuilder::buildIndexChain(m_gtessel2, 70, 70, 
												   140, 510, 0, 0, 
												   640, 224);
/*
	PostEffectBuilder::buildIndexChain(m_gtessel2, m_settings.buffer0(), m_settings.buffer0(), 
												   m_settings.zbuffer(), 510, 0, 0, 
												   m_settings.screenWidth(), m_settings.screenHeight());

	PostEffectBuilder::buildIndexChain(m_gtessel1, m_settings.buffer1(), m_settings.buffer1(), 
												   m_settings.zbuffer(), 510, 0, 0, 
												   m_settings.screenWidth(), m_settings.screenHeight());
*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FadeToGray::~FadeToGray()
{
	zenic_delete [] m_ztessel1;
	zenic_delete [] m_ztessel2;
	zenic_delete [] m_zpal;

	zenic_delete [] m_gtessel1;
	zenic_delete [] m_gtessel2;
	zenic_delete [] m_gpal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FadeToGray::render(uint currentScreen, Dma& dmaChain)
{
/*
	{
		// clear alpha channel to 0x80
		PostEffectHelper hlp;
		hlp.setFrame(currentScreen, 640 / 64, 0, 0x00ffffff);
		hlp.setRgba(0, 0, 0, 0x80); 
		hlp.blit(0, 0, 640, 224);
	}
	///uoetuhoes
*/
	dmaChain.addSrcCntTag();
	dmaChain.add32(VIF_FLUSH());
	dmaChain.add32(VIF_NOP());
	dmaChain.add32(VIF_NOP());
	dmaChain.add32(VIF_DIRECT(3));

	// set ztest
	dmaChain.add128(GIFTAG(2, gif::Eop, 0, 0, gif::Packed, 1),gif::A_D);
	dmaChain.add128(GS_TEST(0, 0, 0, 0, 0, 0, 1, 2), GS_REG(TEST_2));
	dmaChain.add128(GS_RGBAQ(0x80, 0x80, 0x80, 0x80, 1.0),  GS_REG(RGBAQ));
	dmaChain.endPacket();

	PostEffectBuilder::uploadIndexChain(dmaChain, currentScreen ? m_ztessel1 : m_ztessel2, 1, 0x00ffff, 
										true, 0x00ffffff, false, m_zpal);

	// disable ztest, set alpha blend
	dmaChain.addSrcCntTag(0, VIF_DIRECT(2));
	dmaChain.add128(GIFTAG(1, gif::Eop, 0, 0, gif::Packed, 1), gif::A_D);
	dmaChain.add128(GS_ALPHA(1, 0, 1, 0, 0), GS_REG(ALPHA_2));
	dmaChain.endPacket();

	PostEffectBuilder::uploadIndexChain(dmaChain, currentScreen ? m_gtessel1 : m_gtessel2, 1, 
										0x00000000, false, 0xffffff, true, m_gpal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}

