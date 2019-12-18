#include "Hooks.hpp"
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include <json.hpp>

#define _H4_STD_CONVERSIONS_
#define _H4API_PLUGINS_
#define _H4API_LIBRARY_
#include "H4API.hpp"

using json = nlohmann::json;
using StringVector = std::vector<std::string>;
using IntVector = std::vector<int>;
using namespace h4;

constexpr LPCSTR ABILITIES_JSON = ".\\NewCreatureAbilities.json";
constexpr INT CREATURE_NUMBER = 74;
constexpr INT ABILITIES_NUMBER = 86;

// * Global Patcher
Patcher *_P;
// * Global Patcher Instance
PatcherInstance *_PI;

const std::string CREATURE_NAMES[CREATURE_NUMBER] =
{
	"Air Elemental",
	"Angel",
	"Ballista",
	"Bandit",
	"Behemoth",
	"Beholder",
	"Black Dragon",
	"Bone Dragon",
	"Centaur",
	"Cerberus",
	"Champion",
	"Crossbowman",
	"Crusader",
	"Cyclops",
	"Venom Spawn",
	"Devil",
	"Dragon Golem",
	"Dwarf",
	"Earth Elemental",
	"Efreet",
	"Elf",
	"Faerie Dragon",
	"Fire Elemental",
	"Gargoyle",
	"Genies",
	"Ghost",
	"Berserker",
	"Gold Golem",
	"Griffin",
	"Hafling",
	"Harpy",
	"Hydra",
	"Ice Demon",
	"Imp",
	"Leprecon",
	"Mage",
	"Mantis",
	"Medusa",
	"Mermaid",
	"Minotaur",
	"Monk",
	"Mummy",
	"Naga",
	"Nightmare",
	"Nomad",
	"Ogre Mage",
	"Orc",
	"Peasant",
	"Phoenix",
	"Pikeman",
	"Pirate",
	"Satyr",
	"Sea Monster",
	"Skeleton",
	"Squire",
	"Sprite",
	"Thunder Bird",
	"Titan",
	"Troglodyte",
	"Troll",
	"Unicorn",
	"Vampire",
	"Water Elemental",
	"White Tiger",
	"Wolves",
	"Zombie",
	"Waspwort",
	"Goblin Knight",
	"Evil Sorceress",
	"Gargantuan",
	"Dark Champion",
	"Catapult",
	"Frenzied Gnasher",
	"Mega Dragon",
};

const std::string CREATURE_ABILITIES[ABILITIES_NUMBER] =
{
	"Triple Headed Attack",
	"Aging",
	"Area Attack",
	"Berserker",
	"Binding",
	"Blind Immunity",
	"Blinding",
	"Block",
	"Bloodlust",
	"Breath Attack",
	"Chaos Ward",
	"Charging",
	"Cold Attack",
	"Cold Resistance",
	"Curse",
	"Devouring",
	"Death Ward",
	"Elementals",
	"Extra Melee",
	"Extra Ranged",
	"Fire Attack",
	"Fire Resistance",
	"Fire Shield",
	"First Strike",
	"Negate first Strike",
	"Flying",
	"Fortune",
	"Freezing Attack",
	"Giant Slayer",
	"Multiple Attack",
	"Hypnotize",
	"Ignore Wards",
	"Ignore Zones of Control",
	"Insubstantial",
	"Life Ward",
	"Lighting Attack",
	"Long Range",
	"Long Weapon",
	"Magic Immunity",
	"Magic Mirror",
	"Magic Resistence",
	"Mana Leech",
	"Mechanical",
	"Melee Giant Slayer",
	"Mirth",
	"Negate Mind Immunity",
	"No Retaliation",
	"Normal Melee",
	"Fear",
	"Poison",
	"Random Harmful Spells",
	"Ranged",
	"Ranged First Strike",
	"Ranged Giant Slayer",
	"Ranged Stun",
	"Rebirth",
	"Regeneration",
	"Resurrection",
	"Bonuses At Sea",
	"Shoots Twice",
	"Short Range",
	"No Obstacle Penalty",
	"Skeletal",
	"Spell Vulnerability",
	"Spellcaster",
	"Stealth",
	"Stone Gaze",
	"Stone Skin",
	"Strength",
	"Strike And Return",
	"Strikes Twice",
	"Stunning",
	"Summon Demons",
	"Taxpayer",
	"Teleport",
	"Terror",
	"Tougness",
	"Undead",
	"Unlimited Retaliation",
	"Unlimited Shots",
	"Life Draining",
	"Weakness",
	"Unused Ability",
	"Greek Fire",
	"Arc Breath Attack",
	"Siege Capable",
};

struct CaseInsensitiveComparator
{
	struct NoCaseCompare
	{
		bool operator() (const unsigned char& c1, const unsigned char& c2) const
		{
			return std::tolower(c1) < std::tolower(c2);
		}
	};
	bool operator() (const std::string& s1, const std::string& s2) const
	{
		return std::lexicographical_compare(s1.begin(), s1.end(),   // source range
			s2.begin(), s2.end(),   // dest range
			NoCaseCompare());  // comparison
	}
};

BOOL ReadJson()
{
	std::ifstream in(ABILITIES_JSON);

	if (!in.is_open())
	{
		H4Error::ShowError("Unable to open CreatureAbilities.json.");
		return FALSE;
	}

	json j;
	in >> j;

	std::map < std::string, int, CaseInsensitiveComparator> abilitiesMap;
	for (int i = 0; i < ABILITIES_NUMBER; ++i)
		abilitiesMap[CREATURE_ABILITIES[i]] = i;

	IntVector creatureAbilities[CREATURE_NUMBER];

	int id = 0;
	char error[512];

	for (auto& name : CREATURE_NAMES)
	{
		if (!j.contains(name))
		{
			sprintf_s(error, "All creatures must be present.\nCreature [%s]", name.c_str());
			H4Error::ShowError(error);
			return FALSE;
		}
		auto& abilities = j[name];
		if (!abilities.is_array())
		{
			sprintf_s(error, "Invalid creature format.\nCreature [%s]", name.c_str());
			H4Error::ShowError(error);
			return FALSE;
		}
		auto& vec = creatureAbilities[id];
		for (auto& a : abilities)
		{
			if (!a.is_string())
			{
				sprintf_s(error, "Invalid ability format.\nCreature [%s]\nNot a string!", name.c_str());
				H4Error::ShowError(error);
				return FALSE;
			}
			auto ability = a.get<std::string>();
			const auto& it = abilitiesMap.find(ability);
			if (it == abilitiesMap.end())
			{
				sprintf_s(error, "Ability could not be found.\nCreature [%s]\nAbility [%s]", name.c_str(), ability.c_str());
				H4Error::ShowError(error);
				return FALSE;
			}
			vec.push_back(it->second);
		} // loop abilities
		++id;
	} // loop creatures

	if (id < CREATURE_NUMBER)
	{
		sprintf_s(error, "Some creatures were not found.\nExpected [%d]\nFound: [%d]", id, CREATURE_NUMBER);
		H4Error::ShowError(error);
		return FALSE;
	}

	for (int i = 0; i < CREATURE_NUMBER; ++i)
	{
		auto& creature = P_CreatureAbilities(i);
		creature.id = i;
		creature.abilities = creatureAbilities[i];
	}

	return TRUE;
}

void hooks_init(PatcherInstance * pi)
{
	if (ReadJson())
		pi->WriteByte(0xA477F8, 5); // Skip call 0x654820 @ 0x654800
}
