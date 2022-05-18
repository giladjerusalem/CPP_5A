#include <iostream>
#include <sstream>
#include <stdexcept>
#include "sources/OrgChart.hpp"
#include "doctest.h"

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
    CHECK((*chart.begin()).compare("Gilad"));
    chart.add_root("Gilad2");
    CHECK((*chart.begin()).compare("Gilad2"));
    chart.add_root("Gilad3");
    chart.add_root("Gilad4");
    CHECK((*chart.begin()).compare("Gilad4"));
}


TEST_CASE("CHECK Level order")
{
    OrgChart chart;
    
    chart.add_root("Gilad");

    chart.add_sub("Gilad","Gilad1");
    chart.add_sub("Gilad1","Gilad11");
    chart.add_sub("Gilad", "Gilad2");
    chart.add_sub("Gilad", "Gilad3");
    chart.add_sub("Gilad2", "Gilad22");
    chart.add_sub("Gilad3", "Gilad33");
    
    string str = " ";
    
    for(auto iterat = chart.begin_level_order(); iterat != chart.end_level_order(); iterat++)
    {
        str = str + *iterat;
        str = str + ", ";
        str.push_back(' ');
    }

    str.pop_back();
    
    string good = "Gilad, Gilad1, Gilad2, Gilad3, Gilad11, Gilad22, Gilad33";
    string bad = "Gilad33, Gilad22, Gilad11, Gilad3, Gilad2, Gilad1, Gilad";
    
    CHECK(str.compare(good));
    CHECK(str.compare(bad));
}

TEST_CASE("CHECK Reverse order")
{

    OrgChart chart;
    
    chart.add_root("Gilad");

    chart.add_sub("Gilad","Gilad1");
    chart.add_sub("Gilad1","Gilad11");
    chart.add_sub("Gilad", "Gilad2");
    chart.add_sub("Gilad", "Gilad3");
    chart.add_sub("Gilad2", "Gilad22");
    chart.add_sub("Gilad3", "Gilad33");
    
    string str = " ";
    
    for(auto iterat = chart.begin_reverse_order(); iterat != chart.reverse_order(); iterat++)
    {
        str = str + (*iterat);
        str = str + ", ";
    }
    str.pop_back();
    string good = "Gilad33, Gilad22, Gilad11, Gilad3, Gilad2, Gilad1, Gilad";
    string bad = "Gilad, Gilad1, Gilad2, Gilad3, Gilad11, Gilad22, Gilad33";
    CHECK(str.compare(good));
    CHECK(str.compare(bad));
}


TEST_CASE("CHECK Pre order")
{
  
    OrgChart chart;
    
    chart.add_root("Gilad");

    chart.add_sub("Gilad","Gilad1");
    chart.add_sub("Gilad1","Gilad11");
    chart.add_sub("Gilad", "Gilad2");
    chart.add_sub("Gilad", "Gilad3");
    chart.add_sub("Gilad2", "Gilad22");
    chart.add_sub("Gilad3", "Gilad33");
    
    string str = " ";
    
    for(auto iterat = chart.begin_preorder(); iterat != chart.end_preorder(); iterat++)
    {
        str = str + (*iterat);
        str = str + ", ";
    }
    str.pop_back();
    string bad = "Gilad33, Gilad22, Gilad11, Gilad3, Gilad2, Gilad1, Gilad";
    string good = "Gilad, Gilad1, Gilad11, Gilad2, Gilad22, Gilad3, Gilad33";
    CHECK(str.compare(bad));
    CHECK(str.compare(good));
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
    stringstream stream;
    stream << c;
    string str = stream.str();
    string compare = "root sub_root sub_root1 sub_root2 sub_sub_root sub_sub_root1";
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
    CHECK_NOTHROW(chart.add_sub("Gilad22", "Gilad22"));
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

