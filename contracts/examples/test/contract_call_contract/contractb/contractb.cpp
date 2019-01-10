#include <graphenelib/action.h>
#include <graphenelib/action.hpp>
#include <graphenelib/contract.hpp>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/print.hpp>

using namespace graphene;

class contractb : public contract
{
  public:
    contractb(uint64_t uname)
        : contract(uname)
    {
    }

    struct p {
    	bool circlecall;
    };

    // @abi action
    // @abi payable
    void hi(uint64_t a, uint64_t b)
    {
        uint64_t c = a+b;
        print("hi im contractb, the sum(a,b)=", c, "\n");
        p p1{true};
        action bb(528, N(hi), std::move(p1), _self, {100000, 1});//call contractc(function hi)
        bb.send();
    }
};

GRAPHENE_ABI(contractb, (hi))
