#include "ScriptMgr.h"
#include "Player.h"
#include "TalentMgr.h"
#include "Chat.h"
#include "Config.h"

class TalentExpansionLock : public PlayerScript
{
public:
    TalentExpansionLock() : PlayerScript("TalentExpansionLock") { }

    bool OnPlayerCanLearnTalent(Player* player, TalentEntry const* talent, uint32 /*rank*/) override
    {
        if (!sConfigMgr->GetOption<bool>("TalentExpansionLock.Enable", true))
            return true;

        if (!player || !talent)
            return true;

        uint32 level = player->GetLevel();
        uint32 talentDepth = talent->Row * 5;

        uint32 maxDepth60 = sConfigMgr->GetOption<uint32>("TalentExpansionLock.Level60MaxDepth", 30);
        uint32 maxDepth70 = sConfigMgr->GetOption<uint32>("TalentExpansionLock.Level70MaxDepth", 40);

        uint32 maxDepthAllowed = 0;

        if (level <= 60)
            maxDepthAllowed = maxDepth60;
        else if (level <= 70)
            maxDepthAllowed = maxDepth70;
        else
            return true;

        if (talentDepth > maxDepthAllowed)
        {
            ChatHandler(player->GetSession()).PSendSysMessage(
                "|cffFF0000[TalentExpansionLock]|r Your level (%u) allows talents only up to %u talent depth.",
                level,
                maxDepthAllowed
            );

            return false;
        }

        return true;
    }
};

class TalentExpansionLock_WorldScript : public WorldScript
{
public:
    TalentExpansionLock_WorldScript() : WorldScript("TalentExpansionLock_WorldScript") { }

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        sConfigMgr->LoadModuleConfigs();
    }
};

void Addmod_talent_expansion_lockScripts()
{
    new TalentExpansionLock_WorldScript();
    new TalentExpansionLock();
}