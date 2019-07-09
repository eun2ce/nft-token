#include <eospet/eospet.hpp>
#include <eosio/transaction.hpp>

void eospet::on_transfer(name from, name to, asset quantity, std::string memo) {
   if (from == _self) return;

   pets idx(_self, _self.value);
   const auto& it = idx.get(name(memo).value);

   idx.modify(it, same_payer, [&](auto& p) {
      p.activated = true;
   });
}

void eospet::createpet(name owner, name pname) {
   require_auth(owner);

   pets pts(_self, _self.value);

   const auto& idx = pts.get_index<"name"_n>();
   auto pt = idx.find(pet::hash(owner, pname));
   check(pt == idx.end(), "name already taken");

   pts.emplace( owner, [&](auto& p) {
         p.petname = pname;
         p.owner = owner;
         p.type = 0;
         p.created_at = time_point_sec(current_time_point());
         p.id = pet::hash(owner, pname);
   });
}

void eospet::transferpet(name receiver, name sender, uint64_t id) {
   require_auth(sender);

   pets idx(_self, _self.value);
   auto it = idx.find(id);

   check(it == idx.end(), "name already taken");
   check(it->owner == sender, "not match owner");

   idx.modify(it, _self, [&](auto& p) {
         p.owner = receiver;
   });
}

void eospet::burnpet(name owner, uint64_t id){
   require_auth(owner);

   pets idx(_self, _self.value);
   auto it = idx.find(id);

   check(it == idx.end(), "Invalid petname");
   check(it->owner == owner, "not match owner");

   idx.erase(it);
}
