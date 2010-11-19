///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2003-2005 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef zenic_win32_Texture_h
#define zenic_win32_Texture_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Base/Types.h>
#include <Shared/Base/Serialize/Serializable.h>
#include <Shared/Base/Serialize/SerializableFactory.h>
#include <Shared/Base/Serialize/SerializableStructure.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// forwards
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

namespace win32
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Texture : public Serializable
{
	ZENIC_SERIALIZABLE_FACTORY;
public:

	class Surface
	{
		ZENIC_SERIALIZABLE_STRUCTURE;
	public:

		Surface();

		void setPitch( u32 pitch );
		u32 pitch() const;

		void setData( DataPtr<u8> data );
		DataPtr<u8> data() const;

	private:
		u32 m_pitch;
		DataPtr<u8> m_data;
	};

	enum // Properties
	{
		Compressed		= 0x00000001,
		Float			= 0x00000002,

		Cubemap			= 0x00000010,
		Volume			= 0x00000020,
		Mipmaps			= 0x00000040,

		PositiveX		= 0x04000000,
		NegativeX		= 0x08000000,
		PositiveY		= 0x10000000,
		NegativeY		= 0x20000000,
		PositiveZ		= 0x40000000,
		NegativeZ		= 0x80000000
	};

	Texture();
	virtual ~Texture();

	void setWidth( u32 width );
	u32 width() const;

	void setHeight( u32 height );
	u32 height() const;

	void setDepth( u32 depth );
	u32 depth() const;

	void setFormat( u32 format );
	u32 format() const;

	void setProperties( u32 properties );
	u32 properties() const;

	void setSurfaces( u32 surfaces );
	u32 surfaces() const;

	Surface& surface( u32 index );

	virtual void serialize( Serializer& s );

private:

	u32 m_width;
	u32 m_height;
	u32 m_depth;
	u32 m_format;
	u32 m_properties;

	DataPtr<Surface> m_surfaces;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Texture.inl"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

}

#endif
