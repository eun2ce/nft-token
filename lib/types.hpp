#pragma once

#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/time.hpp>

using std::map;
using std::string;
using namespace eosio;

namespace types {
    typedef uint64_t uuid;
    typedef uint8_t element_type;

    constexpr uint8_t PET_TYPES = 100;

    struct st_pet_stat{
        uuid        pet_id;
        uint8_t     pet_type;
        name        player;
    };

    struct [[eosio::table("pets"), eosio::contract("eosio.pet")]] st_pets {
        uuid        id;
        name        owner;
        string      name;
        uint32_t    created_at;
//      uint8_t     pet_type;

        uint64_t primary_key()const { return id; }
        uint64_t get_pets_by_owner()const { return owner.value; }
        EOSLIB_SERIALIZE (st_pets, (id)(owner)(name)(created_at))
    };

    typedef eosio::multi_index<"pets"_n, st_pets,
            eosio::indexed_by <"byowner"_n, const_mem_fun< st_pets, uint64_t, &st_pets::get_pets_by_owner>>
                > _tb_pet;
    /*
    struct st_transfer {
        name from;
        name to;
        asset quantity;
        string memo;
    };
*/
};

