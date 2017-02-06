#include "contract_factory.h"
#include "bind_contract.h"

contract* contract_factory::new_contract(e_contract_type t, const uint32 id)
{
	switch (t)
	{
	case BIND_CONTRACT:
		return new bind_contract(id);
	case ENCHANT_CONTRACT:
		return nullptr;
	case UNIDENTIFY_CONTRACT:
		return nullptr;
	case FUSION_CONTRACT:
		return nullptr;
	}
	return nullptr;
}
