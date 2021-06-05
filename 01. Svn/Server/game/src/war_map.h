//Search:

	void	SetBeginEvent(LPEVENT pkEv);

//Add below:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	void	SetBeginEventCit(LPEVENT pkEv);
	DWORD	GetStartTimeCit() const { return m_dwStartTimeCit; }
#endif

//Search:

LPEVENT m_pkBeginEvent;

//Add below:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	LPEVENT m_pkBeginEventCit;
#endif

//Search:

	DWORD		m_dwStartTime;

//Add below:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	DWORD		m_dwStartTimeCit;
#endif
