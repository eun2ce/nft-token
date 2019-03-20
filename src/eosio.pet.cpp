#include <eosiolib/system.hpp>
#include "../lib/pet.hpp"
#include "../lib/utils.hpp"
#include "../lib/types.hpp"

using namespace types;
namespace eosio {

void pet::createpet( name owner, string pet_name ){
    require_auth( owner );

   // pets( owner, owner.value);

    eosio_assert( pet_name.length() >= 1, " name must have at least 1character");
    eosio_assert( pet_name.length() <= 20, " name cannot exceed 20 chars");

 //   uuid id = get_next_id();

    pets.emplace (owner, [&](auto & r ){
            st_pets pet{};
            pet.name = pet_name;
            pet.owner = owner;
            pet.created_at = current_time();
//            timepoint.time_point_sec();
            pet.id = (utils::hash_str(pet_name)+pet.created_at);
            r = pet;
        });
}

void pet::transferpet( name to, uuid pet_id ){
    require_auth( to );

    auto itr = pets.find( pet_id );
    eosio_assert( itr != pets.end(), "E404 | invalid pet" );
    auto pet = *itr;

    pets.modify(itr,_self,[&]( auto&r ){
            r.owner = to;
        });
    print(" new owner :", to);

    return;
}

void pet::burnpet( uuid pet_id ){
    _tb_pet pets(_self, _self.value);

    const auto& pet = pets.get( pet_id, "E404 | invalid pet");

    require_auth( pet.owner );

    pets.erase( pet );
    return;
}

/*
void pet::transfer(uint64_t sender, uint64_t receiver){
    print("\n>>> sender >>>",sender," - name ", name{sender});
    print("\n>>> receiver >>>",receiver, " - name ", name{receiver});

   auto transfer_data = unpack_action_data<st_transfer>();
   if (transfer_data.from == _self || transfer_data.to != _self){
       return;
   }
    print("\n>>> transfer data quantity >>>" transfer_data.quantity);

}
*/
}
EOSIO_DISPATCH( eosio::pet, (createpet)(transferpet)(burnpet))
