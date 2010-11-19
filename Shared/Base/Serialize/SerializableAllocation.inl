inline SerializableAllocation::SerializableAllocation(Allocator& allocator, uint alignment) : m_allocator(&allocator), m_alignment(alignment)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline SerializableAllocation& SerializableAllocation::operator = (const SerializableAllocation& allocation)
{
	m_allocator = allocation.m_allocator;
	m_alignment = allocation.m_alignment;

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline Allocator& SerializableAllocation::allocator() const
{
	return *m_allocator;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline uint SerializableAllocation::alignment() const
{
	return m_alignment;
}
