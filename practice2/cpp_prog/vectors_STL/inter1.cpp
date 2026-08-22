#include<iostream>
#include<vector>
#include<string>
using namespace std;


/* john: hi  //count 2
 * meer: hello //count 5
 * john: what r u doin //count 10
 */

struct message{
	string name;
	int count;
};


vector<message> parse(void )
{
  vector<message> gotconv ={{"john",2},{"meer",5},{"john",10}};
  return gotconv;

}

int main()
{

	vector<message> vect=parse();
	int max=0;
	for(int i=0;i<vect.size();i++)
	{

        	if(vect[i].count > vect[max].count)
         	{
                  max=i;
        	}

	}

	cout<<vect[max].name<<endl;
	cout<<vect[max].count<<endl;
	return 0;
}
