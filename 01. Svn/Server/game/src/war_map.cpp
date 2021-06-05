//Add in includes:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
#include "utils.h"
#include "regen.h"
#endif

//Search:

EVENTFUNC(war_begin_event)

//Add below function:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
EVENTFUNC(war_begin_cit_event)
{
	war_map_info* info = dynamic_cast<war_map_info*>(event->info);

	if (info == NULL)
	{
		sys_err("war_begin_cit_event> <Factor> Null pointer");
		return 0;
	}

	CWarMap* pMap = info->pWarMap;

	if (get_global_time() > pMap->GetStartTimeCit())
	{
		pMap->Notice("Savaþ baþladý!");
		SECTREE_MANAGER::instance().PurgeNPCsInMap(pMap->GetMapIndex());
		pMap->SetBeginEventCit(NULL);
	}
	else
	{
		char szNoticeText[512];
		if (pMap->GetStartTimeCit() - get_global_time() == 120)
		{
			snprintf(szNoticeText, sizeof(szNoticeText), "Savaþ 2 dakika içinde baþlayacak.");
			pMap->Notice(szNoticeText);
		}
		else if (pMap->GetStartTimeCit() - get_global_time() == 90)
		{
			snprintf(szNoticeText, sizeof(szNoticeText), "Savaþ 1.5 dakika içinde baþlayacak.");
			pMap->Notice(szNoticeText);
		}
		else if (pMap->GetStartTimeCit() - get_global_time() == 60)
		{
			snprintf(szNoticeText, sizeof(szNoticeText), "Savaþ 1 dakika içinde baþlayacak.");
			pMap->Notice(szNoticeText);
		}
		else if (pMap->GetStartTimeCit() - get_global_time() <= 30)
		{
			snprintf(szNoticeText, sizeof(szNoticeText), "Savaþ %d saniye içinde baþlayacak.", pMap->GetStartTimeCit() - get_global_time());
			pMap->Notice(szNoticeText);
		}
	}

	return PASSES_PER_SEC(1);
}
#endif

//Search:

SetBeginEvent(event_create(war_begin_event, info, PASSES_PER_SEC(60)));

//Add below:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	war_map_info* info2 = AllocEventInfo<war_map_info>();
	info2->pWarMap = this;
	SetBeginEventCit(event_create(war_begin_cit_event, info2, PASSES_PER_SEC(1)));
#endif

//Search:

	m_dwStartTime = get_dword_time();

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	m_dwStartTimeCit = get_global_time() + 150;
#endif

//Search:

		AddFlag(1);
	}

//Add below:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	const std::string& szFilename = "locale/turkey/map/metin2_map_t3/cit.txt";

	LPSECTREE_MAP pkMap = SECTREE_MANAGER::instance().GetMap(lMapIndex);

	if (pkMap)
		regen_load_in_file(szFilename.c_str(), lMapIndex, pkMap->m_setting.iBaseX, pkMap->m_setting.iBaseY);
#endif

//Search:

CWarMap::~CWarMap()
{
	event_cancel(&m_pkBeginEvent);

//Add below:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
	event_cancel(&m_pkBeginEventCit);
#endif

//Search:

void CWarMap::SetBeginEvent(LPEVENT pkEv)

//Add below function:

#ifdef ENABLE_AUTO_GUILD_WAR_SYSTEM
void CWarMap::SetBeginEventCit(LPEVENT pkEv)
{
	if (m_pkBeginEventCit != NULL)
		event_cancel(&m_pkBeginEventCit);

	if (pkEv != NULL)
		m_pkBeginEventCit = pkEv;
}
#endif