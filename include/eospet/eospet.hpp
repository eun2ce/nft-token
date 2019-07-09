#pragma once

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>

#include <sio4/crypto/xxhash.hpp>

using namespace eosio;

class [[eosio::contract]] eospet : public contract {
public:
   using contract::contract;

   struct [[eosio::table]] pet {
      uint64_t    id;
      name        owner;
      name        petname;
      uint32_t    type;
      time_point_sec    created_at;
      bool        activated = false;

      static uint64_t hash(name owner, name pname) {
         std::array<char,2*8+32> data;
         datastream<char*> ds(data.data(), data.size());
         ds << owner.value;
         ds << pname.value;
         return sio4::xxh64(data.data(), data.size());
      }

      uint64_t primary_key()const { return id; }
      uint64_t by_owner()const { return owner.value; }
      uint64_t by_name()const { return petname.value; }

      EOSLIB_SERIALIZE( pet, (id)(owner)(petname)(type)(created_at)(activated))
   };

   typedef eosio::multi_index<"pets"_n, pet,
           eosio::indexed_by<"name"_n, const_mem_fun<pet, uint64_t, &pet::by_name>>
              > pets;

   [[eosio::action]]
   void createpet(name owner, name pname);

   [[eosio::action]]
   void transferpet(name receiver, name sender, uint64_t id);

   [[eosio::action]]
   void burnpet(name owner, uint64_t id);

   [[eosio::on_notify("eosio.token::transfer")]]
   void on_eos_transfer(name from, name to, asset quantity, std::string memo) {
      on_transfer(from, to, quantity, memo);
   }

   [[eosio::on_notify("*::transfer")]]
   void on_transfer(name from, name to, asset quantity, std::string memo);
   typedef action_wrapper<"transfer"_n, &eospet::on_transfer> transfer_action;

};
