///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BoneArray::Bone::setBound(const Bound& bound)
{
	m_bound = bound;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline const Bound& BoneArray::Bone::bound() const
{
	return m_bound;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BoneArray::Bone::setTransform(const Matrix4& transform)
{
	m_transform = transform;	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline const Matrix4& BoneArray::Bone::transform() const
{
	return m_transform;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BoneArray::Bone::setTarget(Node* target)
{
	m_target = target;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline Node* BoneArray::Bone::target() const
{
	return m_target;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline BoneArray::BoneArray()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BoneArray::setBones( uint bones )
{
	m_bones.resize(bones);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline uint BoneArray::bones() const
{
	return m_bones.count();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline BoneArray::Bone& BoneArray::bone(uint index)
{
	ZENIC_ASSERT(index < m_bones.count());
	return m_bones[index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline const String& BoneArray::Bone::name() const
{
	return m_name;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void BoneArray::Bone::setName(const char* name)
{
	m_name = name;
}
