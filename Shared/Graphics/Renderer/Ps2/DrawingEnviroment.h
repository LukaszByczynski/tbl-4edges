///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2003-2004 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef zenic_ps2_DrawingEnviroment_h
#define zenic_ps2_DrawingEnviroment_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Hardware/Ps2/Gs.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// forwards
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DrawingEnviroment
{
public:

	DrawingEnviroment();
	DrawingEnviroment(bool setDefault);

	void setAddress(u32 address, u32 pitch, gs::Psm pixelFormat);
	void setZbuffer(u32 address, gs::Psm pixelFormat,u32);
	void setScissor(u32 x0, u32 y0, u32 x1, u32 y1);
	void setXyOffset(u32 xoffset, u32 yoffset);

	void colorClampEnable(bool enable);
	void setZtest(u32 mode);
	void setPrmodeCont(bool prim);

	u64* normal();
	u32 size();
	u64* chain();

	void initHeader();
	void setDefault();

private:

	u64 m_dmaData[12*2] ALIGN(16);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline DrawingEnviroment::DrawingEnviroment()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline DrawingEnviroment::DrawingEnviroment(bool initDefault)
{
	initHeader();

	if(initDefault)
		setDefault();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DrawingEnviroment::setPrmodeCont(bool prim)
{
	m_dmaData[(2*2)+0] = GS_PRMODECONT(prim);  
	m_dmaData[(2*2)+1] = GS_REG(PRMODECONT);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DrawingEnviroment::setAddress(u32 address, u32 pitch, gs::Psm pixelFormat)
{
	m_dmaData[(3*2)+0] = GS_FRAME(address, pitch, pixelFormat, 0);  
	m_dmaData[(3*2)+1] = GS_REG(FRAME_1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DrawingEnviroment::setZbuffer(u32 address, gs::Psm /*pixelFormat*/,u32)
{
	m_dmaData[(4*2)+0] = GS_ZBUF(address, gs::Z24, 0);  
	m_dmaData[(4*2)+1] = GS_REG(ZBUF_1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DrawingEnviroment::setScissor(u32 x0, u32 y0, u32 x1, u32 y1)
{
	m_dmaData[(5*2)+0] = GS_SCISSOR(x0,y0, x1, y1);  
	m_dmaData[(5*2)+1] = GS_REG(SCISSOR_1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DrawingEnviroment::setXyOffset(u32 x, u32 y)
{
	m_dmaData[(6*2)+0] = GS_XYOFFSET(x, y);  
	m_dmaData[(6*2)+1] = GS_REG(XYOFFSET_1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void DrawingEnviroment::setZtest(u32 mode)
{
	m_dmaData[(7*2)+0] = GS_TEST(0, gs::alpha::Always, 0xff, gs::alpha::Keep, 0, 0, 0, mode); 
	m_dmaData[(7*2)+1] = GS_REG(TEST_1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline u64* DrawingEnviroment::normal()
{
	return static_cast<u64*>(&m_dmaData[2]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline u64* DrawingEnviroment::chain()
{
	return static_cast<u64*>(&m_dmaData[0]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline u32 DrawingEnviroment::size()
{
	return 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //zenic_ps2_DrawingEnviroment_h


