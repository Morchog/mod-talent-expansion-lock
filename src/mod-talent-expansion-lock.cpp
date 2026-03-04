#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "Config.h"

class TalentExpansionLock : public PlayerScript
{
public:
    TalentExpansionLock() : PlayerScript("TalentExpansionLock") { }

    // =========================================================
    // Talent Depth Lock
    // =========================================================
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
            ChatHandler(player->GetSession()).PSendSysMessage("This talent is not available for your level!");

            return false;
        }

        return true;
    }

    // =========================================================
    // Glyph Lock System
    // =========================================================
    void UpdateGlyphSlots(Player* player)
    {
        if (!sConfigMgr->GetOption<bool>("TalentExpansionLock.Enable", true))
            return;

        if (!player)
            return;

        uint8 level = player->GetLevel();

        for (uint8 slot = 0; slot < 6; ++slot)
        {
            uint32 unlockLevel = sConfigMgr->GetOption<uint32>(
                Acore::StringFormat("TalentExpansionLock.GlyphSlot{}", slot),
                80
            );

            bool unlocked = level >= unlockLevel;

            if (!unlocked)
            {
                // Remove glyph if exists
                if (player->GetGlyph(slot))
                    player->SetGlyph(slot, 0);
            }

            player->SetGlyphSlot(slot, unlocked);
        }

        // Refresh talent/glyph UI
        player->SendTalentsInfoData(false);
    }

    void OnLogin(Player* player) override
    {
        UpdateGlyphSlots(player);
    }

    void OnLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        UpdateGlyphSlots(player);
    }
};

class TalentExpansionLock_WorldScript : public WorldScript
{
public:
    TalentExpansionLock_WorldScript() : WorldScript("TalentExpansionLock_WorldScript") { }

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        sConfigMgr->LoadModulesConfigs();
    }
};

void Addmod_talent_expansion_lockScripts()
{
    new TalentExpansionLock_WorldScript();
    new TalentExpansionLock();
}