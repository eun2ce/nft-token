# pra
# contract name =$1

eosio-cpp -o $1.wasm $1.cpp --abigen
