/* sample implementation of a routing table */

#include "routingtable.hh"
#include <stdlib.h>
#include <fstream>

#define MAXENTRY 4

using namespace std;

//vector <pkt_info> incf_table;

int accessCount = 0; // access counter to keep track of the LRU cache

static int tableCount = 0;
int main(int argc, char *argv[])
{
	pkt_info p;
	if (argc < 2)
	{
		p.print_help();
		exit (1);
	}	
	if (p.incf_table.size() == 0)
			p.create_incftable();	

	string str;
	ifstream myfile(argv[1]) ;
	if (myfile.is_open())	
	{
	while (getline(myfile, str))
	{
		#if 1
		if (tableCount == MAXENTRY)

		{	
			cout << "replacing entry" << endl;
			p.replace_incf_entry(str);
			p.print_table();
		}
		else
		{
			p.add_incf_entry(str);
			p.print_table();
		}
		#endif
	}
	}
	else	
		cout << "cant open file" << endl;
	return 0;
}


void pkt_info::add_incf_entry(string addr)

{
	accessCount++;
	int hit_flag = 0;
	// check if address is already present, if yes update the LRU count
	for (int i=0; i<MAXENTRY; i++)
	{	
		if (addr.compare(incf_table[i].address) == 0)
		{
			hit_flag = 1;
			// update access count for LRU
			incf_table[i].useTime = accessCount;
			break;
		}
		
	}
	// if entry is not present in the table, add it and update the LRU count
	if (!hit_flag)
	{
		incf_table[tableCount].address = addr;
		incf_table[tableCount].useTime = accessCount;
		tableCount++;
	}
}

/* remove one entry based on LRU and add the new entry */
void pkt_info::replace_incf_entry(string addr)
{
	long int min_time = accessCount++;
	int min_posn;
	for (int i=0; i<MAXENTRY; i++)
	{
		if (incf_table[i].useTime <= min_time)
		{
			min_time =  incf_table[i].useTime;
			min_posn = i;
		}
	}
	cout << "replacing:" << incf_table[min_posn].address << endl;
	/* replace at that position and update the LRU time */	
	incf_table[min_posn].address.assign(addr);
	incf_table[min_posn].useTime = accessCount;
}

void pkt_info::create_incftable()
{
	cout << "creating incf table" << endl;
	incf_table.resize(MAXENTRY);
	int i, j;
	// resetting the LRU time
	for (i=0; i<MAXENTRY; i++)	
	{
		incf_table[i].useTime = 0;
		// assign 64 bits for the address, decide how many to add
		incf_table[i].address = new char[64];		
		// init address to 0
		for (j =0; j<64; j++)
		{
			incf_table[i].address.insert(j, "0");
		}
		
	}
}

void pkt_info::print_help()
{
	cout << "Usage: ./prog <input.txt>" << endl;
}

void pkt_info::print_table()
{
	
}
	
