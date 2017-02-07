#include "enchant_contract.h"
#include "player.h"
#include "inventory.h"
#include "entity_manager.h"
#include "opcodeEnum.h"
#include "connexion.h"
#include "chat.h"
#include "itemtemplate.h"
#include "passivitytemplate.h"

enchant_contract::enchant_contract(const uint32 id, byte type_) : contract(ENCHANT_CONTRACT, id), i_(nullptr), type(type_), action(nullptr) {}

bool enchant_contract::internal_init() {
	Stream st;
	st.WriteInt16(0);
	st.WriteInt16(S_REQUEST_CONTRACT);
	uint16 namePos = st.NextPos();
	uint16 unkPos = st.NextPos();
	uint16 unkPos2 = st.NextPos();
	uint16 unkPos3 = st.NextPos();

	st.WriteWorldId(owner);
	st.WritePos(unkPos3);
	st.WriteInt64(0);
	st.WriteInt32(type);
	st.WriteInt64(id);
	st.WriteInt32(0);
	st.WritePos(namePos);
	st.WriteString(owner->name);
	st.WritePos(unkPos);
	st.WriteInt16(0); //unk  text?
	st.WritePos(unkPos2);
	st.WriteInt32(0);
	st.WriteInt32(0);
	st.WriteInt32(0);
	st.WriteInt32(0);
	st.WriteUInt8(0); //awakened enchantment
	st.WriteUInt8(0);
	st.WriteUInt8(0);
	st.WriteUInt8(0);
	st.WritePos(0);

	return connection_send(owner->con, &st);
}

void enchant_contract::try_enchant(){



}

void enchant_contract::set_byte(byte type_) {
	type = type_;
}

void enchant_contract::cancel() {
	if (i_) {
		if (!owner->i_.insert_or_stack_item(i_)) {
			//todo send by percel
		}
	}

	contract::cancel();
}

bool enchant_contract::add_item_to_enchant(int32 unk1, item_eid i_eid, int32 unk2, int32 unk3)
{
	if (!action) {
		action = std::make_unique<enchant_action>();
	}

	if (i_) {//there is an item inside the temper window
		if (!owner->i_.insert_or_stack_item(i_)) {
			chat_send_simple_system_message("You need more space in inventory to do that!", owner);
			return false;
		}
		else {
			i_ = nullptr;
		}
	}

	i_ = owner->i_.get_inventory_item_by_eid(i_eid, 1);
	if (!i_) {
		chat_send_simple_system_message("Could not add item to temper!", owner);
		return false;
	}
	action->i_eid = i_eid;
	
	Stream st;

	st.WriteUInt16(0);
	st.WriteUInt16(S_TEMPER_MATERIALS);

	st.WriteUInt16(1); //count;
	st.WriteUInt16(8); //next

					  //array start
	st.WriteUInt16(8); //baseoffset
	st.WriteUInt16(0); //next

	st.WriteUInt16(0);
	st.WriteUInt32(0); //147
	st.WriteUInt16(0);

	st.WriteUInt32(i_->item_t->id);
	st.WriteUInt64(i_eid);

	st.WriteUInt32(0);
	st.WriteUInt32(0);
	st.WriteUInt32(0);
	st.WriteUInt32(0);

	st.WriteUInt32(0);
	st.WriteUInt32(0);
	st.WriteUInt32(i_->enchantLevel);
	st.WriteUInt32(0);
	st.WriteUInt32(0);

	st.WriteUInt8(1);

	uint32 writed = 0;
	for (size_t i = 0; i < i_->passivities.size(); i++)
	{
		if (i_->passivities[i])
		{
			st.WriteInt32(i_->passivities[i]->id);
			writed++;
		}
	}

	uint32 toWrite = 13 - writed;
	if (toWrite > 0)
		for (size_t i = 0; i < toWrite; i++)
			st.WriteUInt32(0);

	st.WriteUInt32(0);
	st.WriteUInt32(0);
	st.WriteUInt8(i_->isMasterworked);
	st.WriteUInt8(i_->isEnigmatic);
	st.WriteUInt8(0);
	st.WriteUInt8(0);
	st.WriteUInt8(0);

	st.WriteUInt32(0);//levels
	st.WriteUInt32(0);//levels
	st.WriteUInt32(0);//levels

	for (size_t i = 0; i < i_->hasCrystals; i++)
	{
		uint16 next = st.NextPos();
		st.WritePos(next);
		st.WriteInt16(st._pos);

		st.WriteInt32(i_->crystals[i]); //crystal id
	}

	st.WritePos(0);

	if (!connection_send(owner->con, &st))
		return false;

	owner->i_.send();
	return true;
}

bool enchant_contract::add_material_to_enchant_process(item_eid i_eid, int32 count, uint32 slot)
{
	if (!action) {
		action = std::make_unique<enchant_action>();
	}

	if (slot == 1) {
		action->m_1_count = count;
		action->material_eid_1 = i_eid;
	}
	else if (slot == 2) {
		action->m_2_count = count;
		action->material_eid_2 = i_eid;
	}

	return true;
}

enchant_contract::enchant_action::enchant_action() :i_eid(0), material_eid_1(0), material_eid_2(0), m_1_count(0), m_2_count(0) {}

