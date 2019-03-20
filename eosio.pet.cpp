//#include "lib/types.hpp"
#include "lib/pet.hpp"
#include "lib/utils.hpp"

using namespace types;
namespace eosio {

void pet::createpet( name owner, string pet_name ){
    require_auth( owner );


    eosio_assert( pet_name.length() >= 1, " name must have at least 1character");
    eosio_assert( pet_name.length() <= 20, " name cannot exceed 20 chars");

    uuid id = get_next_id();

    pets.emplace (owner, [&](auto & r ){
            st_pets pet{};
            pet.name = pet_name;
            pet.owner = owner;
            pet.id = id;
            pet.pet_type = ( utils::hash_str(pet_name) + pet.id ) ;
            r = pet;
        });
}

void pet::transferpet( name to, uuid pet_id ){
    require_auth( to );

    //_tb_pet pets( _self, _self.value );

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
}
EOSIO_DISPATCH( eosio::pet, (createpet)(transferpet)(burnpet))
