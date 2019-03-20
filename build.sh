#!/bin/sh
contract_name="eosio.pet"

eosio-cpp -o $contract_name.wasm $contract_name.cpp --abigen

