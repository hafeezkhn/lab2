#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<fstream>
#include<boost/lexical_cast.hpp>

using namespace std;
using namespace boost;


enum class Relationship
{
 parent,
 child,
 sibling
};

struct Person{
string name;
};


struct Relationships{
vector<tuple<Persion,Relationship,Person>> relations;

void add_parent_and_child(const Person& parent,const Person& child)
{
 relations.push_back({parent,Relationship::parent,child});
 relations.push_back({child,Relationship::child,parent});

}

struct Research{

	Research(Relationships &releationships)
	{
	  auto& relations = relationships.relations;
	  for(auto&& [first,rel,second]:relationship::parent)
	  {
	    cout<<"john has child called"<<second.name << endl;
	  }
	
	}

};

int main()
{
Person parent{"john"};
Person child1{"crist"},child2{"matt"};

Relationships relationships;

relationships.add_parent_and_child(parent,child1); 
relationships.add_parent_and_child(parent,child2);

return 0;
}
