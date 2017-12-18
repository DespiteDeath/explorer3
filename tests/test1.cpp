#include "catch.hpp"
#include <explorer.hpp>

TEST_CASE("Try to write info about files", "[explorer]" ){
    
   WriteInfo("/Users/apple/Desktop/CmakeEx2Test.txt", "/Users/apple/Desktop/");
   REQUIRE(bf::exists("/Users/apple/Desktop/info_CmakeEx2Test.txt") == true);
}