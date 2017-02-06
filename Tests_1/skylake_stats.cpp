#include "skylake_stats.h"
#include "config.h"
#include "stringUtils.h"
#include "Stream.h"
#include "opcodeEnum.h"
#include "player.h"
#include "connexion.h"

#include <fstream>


uint32 p_stats::get_attack() const {
	return base_power + bonus_power + base_attack + attack_modifier + enchant_attack + bonus_attack; // buffs
}

uint32 p_stats::get_defense() const {
	return base_endurance + bonus_endurance + base_defense + defense_modifier + enchant_defense + bonus_defense; // buffs
}

uint32 p_stats::get_balance() const {
	return base_balance_factor + bonus_balance_factor + base_balance + balance_modifier + enchant_balance + bonus_balance; // buffs
}

uint32 p_stats::get_impact() const {
	return base_impact_factor + bonus_impact_factor + base_impact + impact_modifier + enchant_impact + bonus_impact; // buffs
}

uint32 p_stats::get_max_hp() const {
	return base_max_hp + bonus_hp; //+buffs
}

uint32 p_stats::get_max_mp() const {
	return base_max_mp + bonus_mp; //+buffs
}

uint32 p_stats::get_five_hp_regen() const {
	return base_five_hp_regen + bonus_five_hp_regen;//+buffs
}

uint32 p_stats::get_three_hp_regen() const {
	return base_three_hp_regen + bonus_three_hp_regen;//+buffs
}

uint32 p_stats::get_five_mp_regen() const {
	return base_five_mp_regen + bonus_five_mp_regen;//+buffs
}

uint32 p_stats::get_three_mp_regen() const {
	return base_three_mp_regen + bonus_three_mp_regen;//+buffs
}

uint32 p_stats::get_power() const {
	return base_power + bonus_power; //+buffs
}

uint32 p_stats::get_endurance() const {
	return base_endurance + bonus_endurance; //+buffs
}

uint32 p_stats::get_balance_factor() const {
	return base_balance_factor + bonus_balance_factor; //+buffs
}

uint32 p_stats::get_impact_factor() const {
	return base_balance_factor + bonus_balance_factor; //+buffs
}

uint32 p_stats::get_attack_speed() const {
	return base_attack_speed + bonus_attack_speed; //+buffs
}

uint32 p_stats::get_movement_speed(uint32 status) const {
	return status > 0 ?  (base_movement_speed + bonus_movement_speed) : (base_run_speed + bonus_run_speed);
}

uint32 p_stats::get_pvp_attack() const {
	return base_pvp_attack + bonus_pvp_attack; //+buffs
}

uint32 p_stats::get_pvp_defense() const {
	return base_pvp_defense + bonus_pvp_defense; //+buffs
}

uint32 p_stats::get_special() const {
	return base_special + bonus_special;
}

uint32 p_stats::get_special_regen() const {
	return base_special_regen + bonus_special_regen;
}

uint32 p_stats::get_special_regen_rate() const
{
	return base_special_regen_rate + bonus_special_regen_rate;
}

float p_stats::get_crit_rate() const {
	return base_crit_rate + bonus_crit_rate; //+buffs
}

float p_stats::get_crit_resist() const {
	return base_crit_resist + bonus_crit_resist; //+buffs
}

float p_stats::get_crit_power() const {
	return base_crit_power + bonus_crit_power; //+buffs
}

float p_stats::get_weakening_resist() const {
	return base_weakening_resist + bonus_weakening_resist; //+buffs
}

float p_stats::get_poison_resist() const {
	return base_poison_resist + bonus_poison_resist; //+buffs
}

float p_stats::get_stun_resist() const {
	return base_stun_resist + bonus_stun_resist; //+buffs
}

float p_stats::get_weakening_rate() const {
	return base_weakening_rate + bonus_weakening_rate; //+buffs
}

float p_stats::get_poison_rate() const {
	return base_poison_rate + bonus_poison_rate; //+buffs
}

float p_stats::get_stun_rate() const {
	return base_stun_rate + bonus_stun_rate; //+buffs
}





void p_stats::clear_enchat() {
	enchant_attack = enchant_balance = enchant_defense = enchant_impact = 0;
}

void p_stats::claer_modifiers() {
	attack_modifier = defense_modifier = balance_modifier = impact_modifier = 0;
}

void p_stats::clear_base()
{
	base_special = base_special_regen = base_special_regen_rate = 0;
	base_attack = base_defense = base_impact = base_balance = 0;
	base_pvp_attack = base_pvp_defense = 0;
	base_five_hp_regen = base_five_mp_regen = base_three_hp_regen = base_three_mp_regen = 0;
	base_max_hp = base_max_mp = 0;
	base_power = base_endurance = 0;
	base_impact_factor = base_balance_factor = 0;
	base_attack_speed = base_run_speed = base_movement_speed = 0;
	base_gather_speed = base_mine_speed = base_harvest_speed = base_craft_speed = 0;
	base_crit_power = base_crit_rate = base_crit_resist = 0.0f;
	base_stun_rate = base_poison_rate = base_weakening_rate = 0.0f;
	base_weakening_resist = base_poison_resist = base_stun_resist = 0.0f;
}

void p_stats::clear_bonus()
{
	bonus_special = bonus_special_regen = bonus_special_regen_rate = 0;
	bonus_attack = bonus_defense = bonus_impact = bonus_balance = 0;
	bonus_pvp_attack = bonus_pvp_defense = 0;
	bonus_five_hp_regen = bonus_five_mp_regen = bonus_three_hp_regen = bonus_three_mp_regen = 0;
	bonus_hp = bonus_mp = 0;
	bonus_power = bonus_endurance = 0;
	bonus_impact_factor = bonus_balance_factor = 0;
	bonus_attack_speed = bonus_run_speed = bonus_movement_speed = 0;
	//bonus_gather_speed = bonus_mine_speed = bonus_harvest_speed = bonus_craft_speed = 0;
	bonus_crit_power = bonus_crit_rate = bonus_crit_resist = 0.0f;
	bonus_stun_rate = bonus_poison_rate = bonus_weakening_rate = 0.0f;
	bonus_weakening_resist = bonus_poison_resist = bonus_stun_resist = 0.0f;
}

bool p_stats::has_special() const {
	return get_special() > 0 ? true : false;
}





char* WINAPI get_line(char* file, std::string& line)
{
	std::string out;
	while (file[0] != EOF)
	{
		if (file[0] == '\n')
		{
			line += file[0];
			file++;
			break;
		}

		line += file[0];
		file++;
	}

	if (file[0] == EOF) return NULL;

	return file;
}

char* WINAPI parse_stats(char* file, s_stats::stats& stats) {
	std::string line;
	char* currsor = get_line(file, line);
	while (currsor)
	{
		if (line[0] == '}')
		{
			break;
		}

		if (stringStartsWith(line, "hp"))
		{
			stats.hp = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "mp"))
		{
			stats.mp = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "power"))
		{
			stats.power = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "endurance"))
		{
			stats.endurance = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "impact"))
		{
			stats.impact = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "balance"))
		{
			stats.balance = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "attackSpeed"))
		{
			stats.attack_speed = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "attack"))
		{
			stats.attack = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "defense"))
		{
			stats.defense = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "pvpAttack"))
		{
			stats.pvp_attack = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "pvpDefense"))
		{
			stats.pvp_defense = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "fiveHpRegen"))
		{
			stats.five_hp_regen = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "threeHpRegen"))
		{
			stats.three_hp_regen = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "fiveMpRegen"))
		{
			stats.five_mp_regen = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "threeMpRegen"))
		{
			stats.three_mp_regen = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "runSpeed"))
		{
			stats.run_speed = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "specialRegenRate"))
		{
			stats.special_regen_rate = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "specialRegen"))
		{
			stats.special_regen = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "special"))
		{
			stats.special = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "movementSpeed"))
		{
			stats.movement_speed = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "critRate"))
		{
			stats.crit_rate = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "critResist"))
		{
			stats.crit_resist = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "critPower"))
		{
			stats.crit_power = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "stunResist"))
		{
			stats.stun_resist = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "stunRate"))
		{
			stats.stun_rate = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "poisonRate"))
		{
			stats.poison_rate = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "weakeningRate"))
		{
			stats.weakening_rate = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "weakeningResist"))
		{
			stats.weakening_resist = atof(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "poisonResist"))
		{
			stats.poison_resist = atof(string_split_get_right(line, '=').c_str());
		}
		
		else if (stringStartsWith(line, "gatherSpeed"))
		{
			stats.gather_speed = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "mineSpeed"))
		{
			stats.mine_speed = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "harvestSpeed"))
		{
			stats.harvest_speed = atoi(string_split_get_right(line, '=').c_str());
		}
		else if (stringStartsWith(line, "craftSpeed"))
		{
			stats.craft_speed = atoi(string_split_get_right(line, '=').c_str());
		}

		line.clear();
		currsor = get_line(currsor, line);
	}

	return currsor;
}



bool WINAPI s_stats_parse_class_base_stats_file(char* file) {
	std::string line;
	char* currsor = file;
	while (currsor)
	{
		line.clear();
		currsor = get_line(currsor, line);
		if (
			line.size() >= 0 &&
			line[0] != '#' &&
			line[0] != '{' &&
			line[0] != '\n')
		{
			if (stringStartsWith(line, "."))
			{
				uint32 id = atoi(string_split_get_right(line, ':').c_str());
				currsor = parse_stats(currsor, skylake_stats.class_base_stats[id]);
			}
		}


	}

	return true;
}

bool WINAPI s_stats_parse_race_base_stats_file(char* file) {
	std::string line;
	char* currsor = file;
	while (currsor)
	{
		line.clear();
		currsor = get_line(currsor, line);
		if (
			line.size() >= 0 &&
			line[0] != '#' &&
			line[0] != '{' &&
			line[0] != '\n')
		{
			if (stringStartsWith(line, "."))
			{
				uint32 id = atoi(string_split_get_right(line, ':').c_str());
				currsor = parse_stats(currsor, skylake_stats.race_base_stats[id]);
			}
		}
	}
	return true;
}



char* WINAPI parse_r_progress(char* file, s_stats::r_progress& progress) {
	std::string line;
	char* currsor = file;
	while (currsor)
	{
		line.clear();
		currsor = get_line(currsor, line);
		if (!currsor) break;

		if (line[0] == '}') break;

		if (stringStartsWith(line, "."))
		{
			uint32 id = atoi(string_split_get_right(line, ':').c_str());
			currsor = parse_stats(currsor, progress.race_progress_stats[id]);
		}

	}

	return currsor;
}

bool  WINAPI s_stats_parse_race_progress_file(char* file) {
	std::string line;
	char* currsor = file;
	while (currsor)
	{
		line.clear();
		currsor = get_line(currsor, line);
		if (!currsor) break;
		if (
			line.size() >= 0 &&
			line[0] != '#' &&
			line[0] != '{' &&
			line[0] != '\n')
		{

			if (stringStartsWith(line, "@"))
			{
				s_stats::r_progress progress;
				memset(&progress, 0, sizeof(progress));
				progress.level = atoi(string_split_get_right(line, '@').c_str());
				currsor = parse_r_progress(currsor, progress);
				skylake_stats.race_progress.push_back(progress);
			}

		}


	}
	return true;
}




char* WINAPI parse_c_progress(char* file, s_stats::c_progress& p) {
	std::string line;
	char* currsor = file;
	while (currsor)
	{
		line.clear();
		currsor = get_line(currsor, line);
		if (!currsor) break;

		if (line[0] == '}') break;

		if (stringStartsWith(line, "."))
		{
			uint32 id = atoi(string_split_get_right(line, ':').c_str());
			currsor = parse_stats(currsor, p.class_progress_stats[id]);
		}

	}
	return currsor;
}

bool WINAPI s_stats_parse_class_progress_file(char* file) {
	std::string line;
	char* currsor = file;
	while (currsor)
	{
		line.clear();
		currsor = get_line(currsor, line);
		if (!currsor) break;
		if (
			line.size() >= 0 &&
			line[0] != '#' &&
			line[0] != '{' &&
			line[0] != '\n')
		{
			if (stringStartsWith(line, "@"))
			{
				s_stats::c_progress progress;
				memset(&progress, 0, sizeof(progress));
				progress.level = atoi(string_split_get_right(line, '@').c_str());
				currsor = parse_c_progress(currsor, progress);
				skylake_stats.class_progress.push_back(progress);
			}
		}


	}
	return true;
}


bool WINAPI s_stats_load_scripts()
{
	skylake_stats.race_progress.clear();
	skylake_stats.class_progress.clear();

	memset(skylake_stats.class_base_stats, 0, sizeof(s_stats::stats) * 13);
	memset(skylake_stats.race_base_stats, 0, sizeof(s_stats::stats) * 8);

	std::string error_msg;
	char* class_base_stats_file = nullptr;
	char* race_base_stats_file = nullptr;
	char* class_progress_file = nullptr;
	char* race_progress_file = nullptr;

	uint32 size = 0;

#pragma region read
	//-----------------------------------------------
	std::string dir = config::dir.dataScripts;
	dir += "//class_base_stats.skylake";
	std::ifstream file;
	file.open(dir.c_str());
	if (!file.is_open()) {
		error_msg = "could not find 'class_base_stats.skylake' in ";
		error_msg += config::dir.dataScripts;
		goto error_proc;
	}
	file.seekg(0, std::ifstream::end);
	class_base_stats_file = new char[(size = (int)file.tellg()) + 1];
	class_base_stats_file[size] = 0xff;
	file.seekg(0, std::ifstream::beg);
	file.read(class_base_stats_file, size);
	file.close();


	//-----------------------------------------------
	dir = config::dir.dataScripts;
	dir += "//race_base_stats.skylake";
	file.open(dir.c_str());
	if (!file.is_open()) {
		error_msg = "could not find 'race_base_stats.skylake' in ";
		error_msg += config::dir.dataScripts;
		goto error_proc;
	}
	file.seekg(0, std::ifstream::end);
	race_base_stats_file = new char[(size = (int)file.tellg()) + 1];
	race_base_stats_file[size] = 0xff;
	file.seekg(0, std::ifstream::beg);
	file.read(race_base_stats_file, size);
	file.close();
	//-----------------------------------------------


	dir = config::dir.dataScripts;
	dir += "//progress_class.skylake";
	file.open(dir.c_str());
	if (!file.is_open()) {
		error_msg = "could not find 'progress_class.skylake' in ";
		error_msg += config::dir.dataScripts;
		goto error_proc;
	}
	file.seekg(0, std::ifstream::end);
	class_progress_file = new char[(size = (int)file.tellg()) + 1];
	class_progress_file[size] = 0xff;
	file.seekg(0, std::ifstream::beg);
	file.read(class_progress_file, size);
	file.close();
	//-----------------------------------------------


	dir = config::dir.dataScripts;
	dir += "//progress_race.skylake";
	file.open(dir.c_str());
	if (!file.is_open()) {
		error_msg = "could not find 'progress_race.skylake' in ";
		error_msg += config::dir.dataScripts;
		goto error_proc;
	}
	file.seekg(0, std::ifstream::end);
	race_progress_file = new char[(size = (int)file.tellg()) + 1];
	race_progress_file[size] = 0xff;
	file.seekg(0, std::ifstream::beg);
	file.read(race_progress_file, size);
	file.close();
	//-----------------------------------------------
#pragma endregion

	if (!s_stats_parse_class_base_stats_file(class_base_stats_file)) {
		error_msg = "FAILED_TO_PARSE class_base_stats.skylake";
		goto error_proc;
	}

	if (!s_stats_parse_race_base_stats_file(race_base_stats_file)) {
		error_msg = "FAILED_TO_PARSE race_base_stats.skylake";
		goto error_proc;
	}

	if (!s_stats_parse_class_progress_file(class_progress_file)) {
		error_msg = "FAILED_TO_PARSE progress_class.skylake";
		goto error_proc;
	}

	if (!s_stats_parse_race_progress_file(race_progress_file)) {
		error_msg = "FAILED_TO_PARSE progress_race.skylake";
		goto error_proc;
	}




	if (class_base_stats_file) {
		delete[]class_base_stats_file;
		class_base_stats_file = 0;
	}

	if (race_base_stats_file) {
		delete[]race_base_stats_file;
		race_base_stats_file = 0;
	}

	if (class_progress_file) {
		delete[]class_progress_file;
		class_progress_file = 0;
	}

	if (race_progress_file) {
		delete[]race_progress_file;
		race_progress_file = 0;
	}


	return true;

error_proc:

	if (class_base_stats_file) {
		delete[]class_base_stats_file;
		class_base_stats_file = 0;
	}

	if (race_base_stats_file) {
		delete[]race_base_stats_file;
		race_base_stats_file = 0;
	}

	if (class_progress_file) {
		delete[]class_progress_file;
		class_progress_file = 0;
	}

	if (race_progress_file) {
		delete[]race_progress_file;
		race_progress_file = 0;
	}

	printf("::ERROR_ON_LOADING_SCRIPTS. [%s]\n", error_msg.c_str());
	return false;
}







void WINAPI s_stats_get_progress(p_ptr p) {

	for (size_t i = 0; i < skylake_stats.class_progress.size(); i++)
	{
		if (p->level >= skylake_stats.class_progress[i].level) {
			s_stats_add_to_base(skylake_stats.class_progress[i].class_progress_stats[CLASS_MAX], p->stats);
			s_stats_add_to_base(skylake_stats.class_progress[i].class_progress_stats[p->pClass], p->stats);
		}
	}

	for (size_t i = 0; i < skylake_stats.race_progress.size(); i++)
	{
		if (p->level >= skylake_stats.race_progress[i].level) {
			s_stats_add_to_base(skylake_stats.race_progress[i].race_progress_stats[RACE_MAX], p->stats);
			s_stats_add_to_base(skylake_stats.race_progress[i].race_progress_stats[p->pRace], p->stats);
		}
	}
	return;
}

void WINAPI s_stats_get_base_stats(p_ptr p) {
	s_stats_add_to_base(skylake_stats.class_base_stats[p->pClass], p->stats);
	s_stats_add_to_base(skylake_stats.race_base_stats[p->pRace], p->stats);

	s_stats_add_to_base(skylake_stats.class_base_stats[CLASS_MAX], p->stats);
	s_stats_add_to_base(skylake_stats.race_base_stats[RACE_MAX], p->stats);
	return;
}

void WINAPI s_stats_init_player(p_ptr p) {
	memset(&p->stats, 0, sizeof(p->stats));

	s_stats_get_base_stats(p);
	s_stats_get_progress(p);

	p->i_.refresh_enchat_effect();
	p->i_.refresh_items_modifiers();

	//load active effects
	return;
}

void WINAPI s_stats_process_progress(p_ptr p, uint16 new_level)
{
	if (p->level >= new_level) return;

	for (size_t i = 0; i < skylake_stats.class_progress.size(); i++)
	{
		if (skylake_stats.class_progress[i].level > p->level &&
			skylake_stats.class_progress[i].level <= new_level
			)
		{
			s_stats_add_to_base(skylake_stats.class_progress[i].class_progress_stats[p->pClass], p->stats);
			s_stats_add_to_base(skylake_stats.class_progress[i].class_progress_stats[CLASS_MAX], p->stats);
		}
	}

	for (size_t i = 0; i < skylake_stats.race_progress.size(); i++)
	{
		if (skylake_stats.race_progress[i].level > p->level &&
			skylake_stats.race_progress[i].level <= new_level
			)
		{
			s_stats_add_to_base(skylake_stats.race_progress[i].race_progress_stats[p->pRace], p->stats);
			s_stats_add_to_base(skylake_stats.race_progress[i].race_progress_stats[RACE_MAX], p->stats);

		}
	}


	p->level = new_level;

	std::unique_ptr<Stream> data = std::make_unique<Stream>();
	data->Clear();
	data->WriteInt16(16);
	data->WriteInt16(S_USER_LEVELUP);
	data->WriteWorldId(p);
	data->WriteInt32(new_level);

	p->spawn.bordacast(data.get());
	connection_send(p->con, data.get());

	player_send_stats(p);
	player_send_external_change(p, 1);
	return;
}

void WINAPI s_stats_add_to_base(s_stats::stats &from, p_stats &to) {
	to.base_max_hp += from.hp;
	to.base_max_mp += from.mp;
	to.base_power += from.power;
	to.base_endurance += from.endurance;
	to.base_impact += from.impact;
	to.base_balance += from.balance;
	to.base_attack += from.attack;

	to.base_three_hp_regen += from.three_hp_regen;
	to.base_three_mp_regen += from.three_mp_regen;

	to.base_five_hp_regen += from.five_hp_regen;
	to.base_five_mp_regen += from.five_mp_regen;

	to.base_special += from.special;
	to.base_special_regen += from.special_regen;
	to.base_special_regen_rate += from.special_regen_rate;

	to.base_defense += from.defense;
	to.base_pvp_attack += from.pvp_attack;
	to.base_pvp_defense += from.pvp_defense;
	to.base_attack_speed += from.attack_speed;
	to.base_run_speed += from.run_speed;
	to.base_movement_speed += from.movement_speed;
	to.base_gather_speed += from.gather_speed;
	to.base_mine_speed += from.mine_speed;
	to.base_harvest_speed += from.harvest_speed;
	to.base_craft_speed += from.craft_speed;

	to.base_crit_rate += from.crit_rate;
	to.base_crit_resist += from.crit_resist;
	to.base_crit_power += from.crit_power;
	to.base_stun_rate += from.stun_rate;
	to.base_poison_rate += from.poison_rate;
	to.base_weakening_rate += from.weakening_rate;
	to.base_weakening_resist += from.weakening_resist;
	to.base_poison_resist += from.poison_resist;
	to.base_stun_resist += from.stun_resist;

	/*
	a_store(to.critRate, from.critRate + a_load(to.critRate));
	a_store(to.critResist, from.critResist + a_load(to.critResist));
	a_store(to.critPower, from.critPower + a_load(to.critPower));
	a_store(to.stunRate, from.stunRate + a_load(to.stunRate));
	a_store(to.poisonRate, from.poisonRate + a_load(to.poisonRate));
	a_store(to.weakeningRate, from.weakeningRate + a_load(to.weakeningRate));
	a_store(to.weakeningResist, from.weakeningResist + a_load(to.weakeningResist));
	a_store(to.poisonResist, from.poisonResist + a_load(to.poisonResist));
	a_store(to.stunResist, from.stunResist + a_load(to.stunResist));
	*/

	return;
}