# mod-talent-expansion-lock
This mod disables going below a certain talent depth at levels 60 and 70
- Level 60 is capped at the 30-point talent level (including all talents on that row)
- Level 70 is capped at the 40-point talent level (including all talents on that row)

Glyph slots unlocking level requirements are also increased to compensate for the talents depth limit. **This change is not reflected in the UI - players will still see the original values in game, but functionaly they will unlock at the specified levels!** (Can be disabled in config)
- 🌟 Major Glyph 1 = 50
- Minor Glyph 1 = 30
- 🌟Major Glyph 2 = 70
- Minor Glyph 2 = 65
- 🌟Major Glyph 3 = 80
- Minor Glyph 3 = 75

Mods like Individual Progression (https://github.com/ZhengPeiRu21/mod-individual-progression) can benefit of such behaviour to stay true to the content progress (Vanilla -> TBC -> Wotlk)

#⚠ Requires using the [https://github.com/Morchog/azerothcore-wotlk.git](https://github.com/Morchog/azerothcore-wotlk/tree/master) fork of the azerothcore-wotlk repo
There is a PR open to merge the hook used in this mod, until it is merged - use the fork above.
- Or if you use Playerbots mod -> use this fork: https://github.com/kekegaroll/azerothcore-wotlk.git
