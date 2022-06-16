#include "doctest.h"
#include "sources/OrgChart.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>



using namespace std;
using namespace ariel;

// test constructors
TEST_CASE("Constructors")
{
    CHECK_NOTHROW(OrgChart chart);
}

TEST_CASE("CHECK add root")
{
    OrgChart chart;
    chart.add_root("Gilad");
    CHECK_EQ(chart.getRoot()->name, "Gilad");
    chart.add_root("Gilad2");
    CHECK_EQ(chart.getRoot()->name, "Gilad2");
    chart.add_root("Gilad3");
    chart.add_root("Gilad4");
    CHECK_EQ(chart.getRoot()->name, "Gilad4");
}


TEST_CASE("main check"){
    OrgChart chart;
    
    chart.add_root("Gilad");

    chart.add_sub("Gilad","Gilad1");
    chart.add_sub("Gilad1","Gilad11");
    chart.add_sub("Gilad", "Gilad2");
    chart.add_sub("Gilad", "Gilad3");
    chart.add_sub("Gilad2", "Gilad22");
    chart.add_sub("Gilad3", "Gilad33");

    SUBCASE("CHECK Level order"){
        vector<string> v = {"Gilad", "Gilad1", "Gilad2", "Gilad3", "Gilad11", "Gilad22", "Gilad33"};
        size_t i = 0;
        for(auto iterat = chart.begin_level_order(); iterat != chart.end_level_order(); ++iterat)
        {
            CHECK_EQ(v[i++],*iterat);
        }
    }

    SUBCASE("CHECK Reverse order"){
        vector<string> v = {"Gilad11", "Gilad22", "Gilad33", "Gilad1", "Gilad2", "Gilad3", "Gilad"};
        size_t i = 0;
        for(auto iterat = chart.begin_reverse_order(); iterat != chart.reverse_order(); ++iterat)
        {
            CHECK_EQ(v[i++],*iterat);
        }
    }

    SUBCASE("CHECK Pre order"){
        vector<string> v = {"Gilad", "Gilad1", "Gilad11", "Gilad2", "Gilad22", "Gilad3", "Gilad33"};
        size_t i = 0;
        for(auto iterat = chart.begin_preorder(); iterat != chart.end_preorder(); ++iterat)
        {
            CHECK_EQ(v[i++],*iterat);
        }

    }
}

TEST_CASE("Operator <<")
{

    OrgChart c;
    c.add_root("root");
    c.add_sub("root","sub_root");
    c.add_sub("sub_root","sub_sub_root");
    c.add_sub("root", "sub_root1");
    c.add_sub("root", "sub_root2");
    c.add_sub("sub_root1", "sub_sub_root1");
    
    //check print
    stringstream stream;
    stream << c;
    string str = stream.str();
    string compare = "worker name -> root, worker's children: sub_root, sub_root1, sub_root2\n"
    "worker name -> sub_root, worker's children: sub__sub_root\n"
    "worker name -> sub_root1, worker's children: sub__sub_root1\n";
    CHECK(str.compare(compare));
}


TEST_CASE("Good_input")
{
    OrgChart chart;
    CHECK_NOTHROW(chart.add_root("Gilad"));
    CHECK_NOTHROW(chart.add_sub("Gilad","Gilad1"));
    CHECK_NOTHROW(chart.add_sub("Gilad1","Gilad11"));
    CHECK_NOTHROW(chart.add_sub("Gilad", "Gilad2"));
    CHECK_NOTHROW(chart.add_sub("Gilad", "Gilad3"));
    CHECK_NOTHROW(chart.add_sub("Gilad", "Gilad3"));
    CHECK_THROWS(chart.add_sub("Gilad22", "Gilad22"));  //false - no gathe named Gilad22
    CHECK_NOTHROW(chart.add_sub("Gilad3", "Gilad33"));
    
    CHECK_NOTHROW(chart.begin());
    CHECK_NOTHROW(chart.end());
    CHECK_NOTHROW(chart.begin_level_order());
    CHECK_NOTHROW(chart.end_level_order());
    CHECK_NOTHROW(chart.begin_reverse_order());
    CHECK_NOTHROW(chart.begin_preorder());
    CHECK_NOTHROW(chart.end_preorder());
    CHECK_NOTHROW(chart.reverse_order());
}

TEST_CASE("Bad_input")
{
    OrgChart chart;
    CHECK_THROWS(chart.add_sub("Gilad", "Gilad2"));
    CHECK_NOTHROW(chart.add_root("Gilad"));
    CHECK_NOTHROW(chart.add_sub("Gilad", "Gilad2"));

}

