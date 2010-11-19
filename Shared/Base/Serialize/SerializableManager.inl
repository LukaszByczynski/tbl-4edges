inline SerializableManager::SerializableManager() : m_first(0), m_firstOwned(0)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void SerializableManager::setPools(DataPtr< DataPtr<u8> > pools)
{
	m_pools = pools;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline DataPtr< DataPtr<u8> > SerializableManager::pools() const
{
	return m_pools;
}
