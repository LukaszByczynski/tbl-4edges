///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool File::isGood() const
{
	return m_good;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool File::isBad() const
{
	return !m_good;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline bool File::isEof() const
{
	return m_eof;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void File::reset()
{
	setGood(false);
	setEof(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void File::setGood(bool good)
{
	m_good = good;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void File::setEof(bool eof)
{
	m_eof = eof;
}
