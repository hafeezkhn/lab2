#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<fstream>
#include<boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Journal{
	string title;
	vector<string> entries;

	Journal(const string &title):title(title){}

	void add_entry(const string& entry)
	{
	 static int count = 1 ;
	 entries.push_back(lexical_cast<string>(count++) + " " +entry);
	}

	/* void save(const string &filename){
	 *
	 * if want to change in future everything need to 
	 * change inside this struct, hence better to seperate 
	 *
	 * }*/
};

//seperation of concern 
//persist manager (may be database)
struct PersistenceManager{

	 void save(const Journal &j,const string &filename){
		 ofstream ofs(filename);
		 for(auto& e : j.entries)
			 ofs << e << endl;
	 }

};

int main()
{
Journal journal("dear diary!!");
journal.add_entry("i ate a ug");
journal.add_entry("dededde  dede");

return 0;
}
