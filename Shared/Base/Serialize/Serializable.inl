inline Serializable::Serializable() : m_manager(0), m_nextManaged(0)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void* Serializable::operator new(size_t s)
{
	return HeapAllocator::allocator().allocate(s);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void* Serializable::operator new(size_t /*s*/, void* ptr)
{
	return ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void Serializable::operator delete(void* ptr)
{
	Serializable* object = static_cast<Serializable*>(ptr);

	if (object->m_manager)
		object->m_manager->remove(object);
	else
		HeapAllocator::allocator().free(ptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void Serializable::operator delete(void*, void*)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline SerializableManager* Serializable::manager() const
{
	return m_manager;
}
