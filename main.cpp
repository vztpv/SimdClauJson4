
#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG 
#else
#include "mimalloc-new-delete.h"
#endif

#include <iostream>
#include <string>
#include <ctime>

#include "claujson.h"



int main(int argc, char* argv[])
{
	//test();

	claujson::UserType ut;
	try {
		int a = clock();
		std::vector<claujson::Block> blocks;
		
		auto x = claujson::Parse(argv[1], 0, &ut, blocks);
		if (!x) {
			std::cout << "fail\n";
			return 2;
		}
		claujson::PoolManager poolManager(x, std::move(blocks)); // using pool manager, add Item or remove
		int b = clock();
		std::cout << "total " << b - a << "ms\n";
		//claujson::LoadData::_save(std::cout, &ut);
		//claujson::LoadData::save("output.json", ut);

		//test2(&ut);

		bool ok = nullptr != x;

		//ut.remove_all(poolManager);
		poolManager.Clear();


		return !ok;
	}
	catch (...) {
		return 1;
	}
}
