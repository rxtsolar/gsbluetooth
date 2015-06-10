#include <iostream>

#include "gsbluetooth.h"

using namespace std;
using namespace gs;

int main(int argc, char* argv[])
{
	Scan scan;

	scan.inquiry();
	scan.list();

	return 0;
}
