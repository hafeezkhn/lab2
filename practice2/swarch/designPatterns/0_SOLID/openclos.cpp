#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<fstream>
#include<boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum Color{red,green,blue};
enum Size{small,medium,large};

struct Product
{
	string name;
	Color color;
	Size size;
};

//without openclose
struct ProductFilter{

	vector<Product*> by_color(vector<Product*> items,Color color)
	{
	 vector<Product*> result;
	 for(auto &i:items)
	 {
	   if(i->color == color)
		   result.push_back(i);
	   return result;
	 }
	}

/*	if we want to later add by_size we may alter this code that violates openclose principle
 *	vector<Product*> by_size(vector<Product*> items,Color color)
	{
	 vector<Product*> result;
	 for(auto &i:items)
	 {
	   if(i->color == color)
		   result.push_back(i);
	   return result;
	 }
	}*/
};

//with openclose
template <typename T> struct Specification
{
 virtual bool is_satisfied(T* item) =0;
}

template <typename T> struct Filter
{
  virtual vector<T*> filter(vector<T*> items,
		            specification<T>& spec)=0;

};

struct BetterFilter :Filter<Product>
{

  vector<Product*> filter(vector<Product*> items,
		          specification<Product>& spec)override
  {
   vector<Product*> result;
   for(auto& item : items)
	   if(spec.is_satisfied(item))
		   result.push_back(item);
   return result;
  }
};

struct ColorSpec:Specification<Product>
{
Color color;
ColorSpec(Color color):color(color){}


 bool is_satisfied(Product* item)override
 {
  return item->color == color;
 }

};

struct SizeSpec:Specification<Product>
{
  Size size;
  explicit SizeSpec(const Size size):size{size}{
  
  }
bool is_satisfied(Product* item) override
{
   return item->size == size;
}

};
int main()
{

	Product apple{"Apple",color::green,Size::small};
	Product tree{"Tree",color::green,Size::large};
	Product house{"House",color::blue,Size::large};

	vector<Product*> items = {&apple,&tree,&house};
	
/*	ProductFilter pf;
	auto green_things = pf.by_color(iterms,Color::green);
        for(auto& item:green_things)
		cout << item->name << "is green";
*/

	BetterFilter bf;
	ColorSpec  green(color::green);
	for(auto& item:bf.filter(items,green))
		cout<< item->name <<"is green\n";

	SizeSpec small(size::small);
	for(auto& item:)

return 0;
}

