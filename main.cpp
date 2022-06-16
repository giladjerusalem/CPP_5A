#include "sources/OrgChart.cpp"
using namespace std;
using namespace ariel;

int main(){
    OrgChart orgChart;
    orgChart.add_root("1");
    orgChart.add_sub("1","2");
    orgChart.add_sub("1","3");
    orgChart.add_sub("2","4");
    orgChart.add_sub("4","5");
    orgChart.add_sub("2","6");
    orgChart.add_sub("1","7");

    cout << orgChart;
    cout << "\n--------\n";
    for(auto iterat = orgChart.begin_reverse_order(); iterat != orgChart.reverse_order(); ++iterat)
    {
        cout << *iterat << ", ";
    }
    cout << "\n--------\n";
    for(auto iterat = orgChart.begin_level_order(); iterat != orgChart.end_level_order(); ++iterat)
    {
        cout << *iterat << ", ";
    }
    cout << "\n--------\n";
    for(auto iterat = orgChart.begin_preorder(); iterat != orgChart.end_preorder(); ++iterat)
    {
        cout << *iterat << ", ";
    }
    return 0;
}


