#include "bitset.h"

void BitsetTest() {
	bitset bs(10000);
	bs.Set(5);
	bool ret = bs.Test(5);
	bs.Set(2);
	bs.ReSet(5);
	

}

int main() {
	BitsetTest();

	return 0;
}