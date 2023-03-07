#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

vector <string> components({"A","B","C"});

vector < vector <string> > ss;

bool operator > (const vector <string> &l, const vector <string> &r)
{
	string ls;
	for_each (l.begin(), l.end(), [&](const string &s){ ls += s; });
	string rs;
	for_each (r.begin(), r.end(), [&](const string &s){ rs += s; });
	return ls > rs;
}



ostream &operator << (ostream &os , const vector <string> &v )
{
	//os << "{";
	if ( v.size())
	{
		copy( v.begin() , v.end() - 1, ostream_iterator <string> (os, ","));
		os << *(v.end() - 1);
	}
	//os << "}";
	return os;
}

ostream &operator << (ostream &os , const vector <vector <string> > &vv )
{
	for_each( vv.begin() , vv.end() , [&](const vector <string> &s){ os << s; os << endl; });
	return os;
}

vector < vector <string> > make_combination ( int s , const vector <string> &c )
{
	cerr << "s = " << s << endl;
	vector < vector<string> > ts,rs;
	
	if ( s == 1 )
	{
		transform (c.begin(),c.end(),back_inserter( rs ), [&](const string &cc){ return vector <string> (1,cc); });
	}
	else
	{
		ts = make_combination( s - 1 , c );
		cerr << "back from " << s - 1 << ", now s = " << s << endl;

		for_each ( c.begin(), c.end(), [&]( const string &cc )
		{
			cerr << "ts:" <<ts;
			cerr << "cc = " << cc << endl;
			for_each( ts.begin(), ts.end(), [&]( const vector <string> &vv )
			{ 
				vector <string> uu(vv);
				uu.push_back( cc );
				rs.push_back( uu ); 
			});
			cerr << "rs:" << rs;
		});
	}
	cerr << "rs:" << rs;
	return rs;
}

int main (int argc, char *argv[])
{
	vector <vector <string> > ts = make_combination(5,components);
	
	map < vector <string>, vector <string> >m;

	cerr << "ts.size=[" << ts.size() << "]" << endl;

	for ( vector <string> &v : ts )
	{
		cout << v << endl;
		sort ( v.begin() , v.end() );
		if (!m.count(v))
			m[v] = v;
	}
	
	cerr << "m.size=[" << m.size() << "]" << endl;
	
	for ( auto o = m.begin(); o != m.end() ; o++)
	{
		cout << o->first << endl;
	}
}
