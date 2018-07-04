//
// http://www.drdobbs.com/windows/user-defined-hash-functions-for-unordere/231600210?pgno=2
// This program uses a simple user-defined function
// to provide a hash function for use in unordered_map
//
// Compile this example with Visual Studio 2010
// or g++ 4.5 using -std=c++0x
//
#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <functional>

using namespace std;

typedef pair<string,string> Name;

size_t name_hash( const Name & name )
{
    return hash<string>()(name.first) ^ hash<string>()(name.second);
}
class A {
	public:
	int a;
		A(int x=0):a(x) {cout << "new A" << this << " " << a << endl; }
		~A() { cout << __FUNCTION__ << ":" << this << " " << a << endl; }
		A(const A& x) : a(x.a) { 
		   cout << "new A: " << __FUNCTION__ << " " << this << " " << a << endl; }
};

ostream & operator<<(ostream & out, const A&a) {
	return out << a.a << endl;
}

int main(int argc, char* argv[])
{
    unordered_map<Name,A,function<decltype(name_hash)>> ids(100, name_hash );
    auto && mark  = Name("Mark", "Nelson");
    auto && andrew = Name("Andrew","Binstock");
    cout << "Init mark" << endl;
    ids[mark] = 40561;
    cout << "Init andrew" << endl;
    ids[andrew] = 40562;
    for ( auto ii = ids.begin() ; ii != ids.end() ; ii++ )
        cout << ii->first.first
                     << " "
                     << ii->first.second
                     << " : "
                     << ii->second
                     << endl;


    {
	    cout << "copy map entry" << endl;
    const auto& x = ids[andrew];
    ids.erase(andrew);
    cout << "xyz==\n" << endl;
    }

  multimap<char,int> mymm;
  multimap<char,int>::iterator it;
  char c;

  mymm.insert(pair<char,int>('x',50));
  mymm.insert(pair<char,int>('y',100));
  mymm.insert(pair<char,int>('y',150));
  mymm.insert(pair<char,int>('y',200));
  mymm.insert(pair<char,int>('z',250));
  mymm.insert(pair<char,int>('z',300));

  for(auto it = mymm.begin(), end = mymm.end();
        it != end; it = mymm.upper_bound(it->first))
  {
      cout << it->first << ' ' << it->second << endl;
  }

       return 0;
}
