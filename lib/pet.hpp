#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/transaction.hpp>
#include <eosiolib/singleton.hpp>
#include <math.h>
#include <map>
#include "types.hpp"

using namespace types;

using std::hash;

namespace eosiosystem {
    class system_contract;
}

namespace eosio {

  using std::string;

class [[eosio::contract("eosio.pet")]] pet: public contract {

    public:
        using contract::contract;

        pet(name receiver, name code, datastream<const char*> ds)
        : contract(receiver, code, ds),
          pets(receiver, receiver.value)
        {}

       _tb_pet pets;

        [[eosio::action]]
            void createpet( name owner, string pet_name );

        [[eosio::action]]
            void transferpet ( name to, uuid pet_id );

        [[eosio::action]]
            void burnpet ( uuid pet_id );

        [[eosio::action]]
            void transfer (uint64_t sender, uint64_t receiver);

        uint64_t get_next_id () { next_id++; return next_id; }
    private:
        uuid next_id = 0;
};
}
