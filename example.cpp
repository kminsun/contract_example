#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT example: public contract {
    public:
        using contract::contract;

        ACTION hi(name user) {
            require_auth(user);

            example_index forHi(get_self(), get_self().value); //.value는 scope
            auto itr = forInsert.find(user.value, "insert account");
            
            print("hello, ", user);
        }

        ACTION getaccount(name user) {
            require_auth( get_self() );
            print( is_account(user) );
        }
        
  ACTION insert(name user) {
            require_auth(get_self());

            example_index forInsert(get_self(), get_self().value);
            auto itr = forInsert.find(user.value);

            check(itr == forInsert.end(), "already exists");

            forInsert.emplace(get_self(), [&](auto&row)  { 
                row.user = user;
            });
           
            print("insert success");

        }

        ACTION remove(name user) {
            require_auth(get_self());

            example_index forRemove(get_self(), get_self().value); 
            auto itr = forRemove.require_find(user.value, "no account");
            forRemove.erase(itr);

            print("erase success");
        }


    private:
    struct [[eosio::table]] allow {      //자료이름(?), 테이블명이 아님//
        name user;

        uint64_t primary_key() const { return user.value; }
    };
     typedef multi_index<"allowance"_n, allow > example_index;
};