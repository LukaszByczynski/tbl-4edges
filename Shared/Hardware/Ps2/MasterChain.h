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

#ifndef zenic_MasterChain_h
#define zenic_MasterChain_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Base/Storage/Singleton.h>
#include <Shared/Base/Types.h>
#include "Dma.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MasterChain : public Singleton<MasterChain>
{
public:

	MasterChain(uint size = 200 * 1024);	// default 200KB of mem.
	~MasterChain();

	Dma& chain();

	void wait();
	void kick();
	void flip();

private:

	u8* m_dmaBuffer1;
	u8* m_dmaBuffer2;

	u32	m_size;
	bool m_flip;

	Dma m_vif1Chain;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void MasterChain::wait()
{
	Dma::waitVif1();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline Dma& MasterChain::chain()
{
	return m_vif1Chain;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}

#endif 
