#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

const int pagenums = 256;
//const int pagesize = 256;
#define pagesize 256
const int tlbnums = 16;
const int framesize = 256;
const int framenums = 128;

typedef struct
{
	int timestamp;
	int pageno;
	int frameno;
} tlb;

typedef struct
{
	bool valid;
	int frameno;
} page;

typedef struct
{
	int timestamp;
	char data[pagesize];
} frame;

void rptlb(int pageno, int frameno);
void rppage(int pageno, int frameno);

/*
frame frametable[framenums];
page pagetable[pagenums];
tlb tlbtable[tlbnums];
*/

frame* frametable;
page* pagetable;
tlb* tlbtable;

float pagerate = 0;
float tlbrate = 0;

static int timestamp = 0;
int cnt = 0;

FILE *addresses, *backstore, *out;

int main(int argc, char *argv[])
{
	assert(argc == 2);
	tlbtable=(tlb*) malloc(tlbnums* sizeof(tlb));
	pagetable=(page*) malloc(pagenums* sizeof(page));
	frametable=(frame*) malloc(framenums* sizeof(frame));
	for (int i = 0; i < tlbnums; ++i)
	{
		tlbtable[i].timestamp = -1;
		tlbtable[i].pageno = -1;
		tlbtable[i].frameno = -1;
	}

	for (int i = 0; i < pagenums; ++i)
	{
		pagetable[i].valid = false;
		pagetable[i].frameno = -1;
	}

	for (int i = 0; i < framenums; ++i)
	{
		frametable[i].timestamp = -1;
	}

	addresses = fopen(argv[1], "r");
	backstore = fopen("BACKING_STORE.bin", "rb");
	out = fopen("output.txt", "w");

	int address, offset, pageno, frameno, res;
	bool tlbhit, pagefault;
	fscanf(addresses, "%d", &address);
	while (!feof(addresses))
	{
		cnt++;
		timestamp++;
		tlbhit = false;
		pagefault = true;

		offset = address & 0x000000ff;
		pageno = (address >> 8) & 0x000000ff;

		// tlbhit
		for (int i = 0; i < tlbnums; ++i)
		{
			if (tlbtable[i].pageno == pageno)
			{
				tlbhit = true;
				tlbrate++;
				pagefault = false;
				frameno = tlbtable[i].frameno;
				frametable[frameno].timestamp = timestamp;
				tlbtable[i].timestamp = timestamp;
				break;
			}
		}

		// tlbmiss pagehit
		if (!tlbhit && pagetable[pageno].valid)
		{
			pagefault = false;
			frameno = pagetable[pageno].frameno;
			rptlb(pageno, frameno);
			frametable[frameno].timestamp = timestamp;
		}

		// pagemiss
		if (pagefault)
		{
			pagerate++;
			//pagetable[pageno].valid = true;
			int min = INT_MAX;
			for (int i = 0; i < framenums; ++i)
			{
				if (frametable[i].timestamp < min)
				{
					min = frametable[i].timestamp;
					frameno = i;
				}
			}

			/*
			for(int i=0;i<pagenums;++i)
			{
				if(pagetable[i].valid&&pagetable[i].frameno==frameno)
				{
					pagetable[i].valid=false;
					break;
				}

			}
			*/

			rppage(pageno, frameno);
			rptlb(pageno, frameno);
			//pagetable[pageno].frameno = frameno;
		}
		res = frametable[frameno].data[offset];
		fprintf(out, "Virtual address: %d Physical address: %d Value: %d\n", address, frameno * framesize + offset, res);
		fscanf(addresses, "%d", &address);
	}
	fclose(addresses);
	fclose(backstore);
	fclose(out);
	fprintf(stdout, "Page-fault rate: %.5f, tlbtable hit rate: %.5f\n", pagerate / cnt, tlbrate / cnt);
	return 0;
}

void rptlb(int pageno, int frameno)
{
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < tlbnums; ++i)
	{
		if (tlbtable[i].timestamp < min)
		{
			min = tlbtable[i].timestamp;
			index = i;
		}
	}

	tlbtable[index].timestamp = timestamp;
	tlbtable[index].pageno = pageno;
	tlbtable[index].frameno = frameno;
}

void rppage(int pageno, int frameno)
{
	for (int i = 0; i < pagenums; ++i)
	{
		if (pagetable[i].valid && pagetable[i].frameno == frameno)
		{
			pagetable[i].valid = false;
			break;
		}
	}
	frametable[frameno].timestamp = timestamp;
	fseek(backstore, pageno * pagesize, SEEK_SET);
	fread(frametable[frameno].data, sizeof(char), pagesize, backstore);
	pagetable[pageno].frameno = frameno;
	pagetable[pageno].valid=true;
}
