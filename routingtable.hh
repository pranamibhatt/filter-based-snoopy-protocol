/* header for routing table.cc */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void add_incf_entry(string);
void replace_incf_entry(string);
void create_incftable();
void print_help(void);
void print_table(void);


#if 1
class pkt_info
{
	public:

	#if 0
	// standard constructor, to be added
	pkt_info();
	
	// standard destrucor
	~pkt_info(){};
	#endif
	/* adding entry to the routing table */
	void add_incf_entry(string);

	/* deleting entry from the routing table */
	void replace_incf_entry(string);

	/* creating table */
	void create_incftable();
	
	/* print help */
	void print_help();

	void print_table();

//	private:	

	vector <pkt_info> incf_table;
	// address of the shared/snooped region
	string address;

	// update time to keep track of LRU
	int useTime;	

	// assign shared status
	int sharedBit;
};
#endif
