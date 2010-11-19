#include "FileStream.h"

#include "../Debug/Assert.h"

#include <string.h>
#include <Shared/Base/Io/Log.h>

namespace zenic
{

FileStream::FileStream()
{
	m_offset = m_size = 0;
	m_mode = Read;
}

FileStream::~FileStream()
{
	close();
}

bool FileStream::open(const char* filename, Mode mode)
{
	close();

	m_mode = mode;

	File::Mode internalMode;
	switch (mode)
	{
		case Read: internalMode = File::Read; break;
		case Write: internalMode = File::Write; break;
		default: return false;
	}

	ZENIC_INFO("Opened file " << filename);

	return m_file.open(filename, internalMode);
}

void FileStream::close()
{
	flush();
	m_file.close();

	m_offset = m_size = 0;
	m_mode = Read;
}

int FileStream::read(void* buffer, int size)
{
	ZENIC_ASSERT_DESC(m_mode == Read, "FileStream::read - not in read mode");

	while (size)
	{
		if ((m_offset == m_size))
		{
			if (size >= BufferSize)
			{
				if (size != m_file.read(buffer, static_cast<File::Size>(size)))
					return false;
				return true;
			}

			s32 buffer_size = m_file.read(m_buffer, BufferSize);

			if (File::InvalidOffset == buffer_size)
				return false;

			m_offset = 0;
			m_size = static_cast<uint>(buffer_size);
		}

		int packet_size = size > (m_size-m_offset) ? (m_size-m_offset) : size;

		::memcpy(buffer, m_buffer + m_offset, static_cast<size_t>(packet_size));
		size -= packet_size;
		buffer = static_cast<void*>(static_cast<u8*>(buffer) + packet_size);
		m_offset += uint(packet_size);
	}

	return true;
}

int FileStream::write(const void* buffer, int size)
{
	ZENIC_ASSERT_DESC(m_mode == Write, "FileStream::write - not in write mode");

	while (size)
	{
		if (m_offset == BufferSize)
		{
			if (File::InvalidSize == m_file.write(m_buffer, m_offset))
				return false;
			m_offset = 0;
		}

		int packet_size = size > (BufferSize-m_offset) ? (BufferSize-m_offset) : size;

		::memcpy(m_buffer + m_offset, buffer, static_cast<size_t>(packet_size));
		size -= packet_size;
		buffer = static_cast<const void*>(static_cast<const u8*>(buffer) + packet_size);
		m_offset += uint(packet_size);
	}

	return true;
}

int FileStream::seek(SeekMode mode, int offset)
{
	if (!flush())
		return false;

	m_size = m_offset = 0;

	File::Location location;
	switch (mode)
	{
		case Start: location = File::Start; break;
		case Current: location = File::Current; break;
		case End: location = File::End; break;
		default: return false;
	}

	File::Offset output = m_file.seek(location, static_cast<File::Offset>(offset));

	return (File::InvalidOffset != output);
}

bool FileStream::flush()
{
	if ((Write == m_mode) && (m_offset > 0))
	{
		if (File::InvalidSize == m_file.write(m_buffer, m_offset))
			return false;
		m_offset = 0;
	}

	return true;
}

int FileStream::tell() const
{
	File::Offset offset = m_file.tell();

	if (offset == File::InvalidOffset)
		return 0;

	return static_cast<int>(offset);
}

}
