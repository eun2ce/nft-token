project(eospet)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract(eospet eospet eospet.cpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/../lib/libsio4 ${CMAKE_BINARY_DIR}/../lib/libsio4)
target_link_libraries(eospet sio4)
target_include_directories(eospet PUBLIC ${CMAKE_SOURCE_DIR}/../include)
