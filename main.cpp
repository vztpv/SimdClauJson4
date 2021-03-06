
#define _CRT_SECURE_NO_WARNINGS

#ifdef _DEBUG 
#else
#include "mimalloc-new-delete.h"
#endif

#include <iostream>
#include <string>
#include <ctime>

#include "claujson.h"


using namespace std::literals::string_view_literals;

namespace claujson {
	UserType* ChkPool(UserType*& node, PoolManager& new_manager) {
		if (nullptr == node) { return nullptr; }
	
		UserType* x = node;
		node = new_manager.Alloc();
		*node = *x;

		node->next_dead = nullptr;

		for (size_t i = 0; i < node->data.size(); ++i) {
			node->data[i]->parent = node;
			ChkPool(node->data[i], new_manager);
		}

		return node;
	}
}



int main(int argc, char* argv[])
{
	//test();

	claujson::UserType ut;
	try {
		int a = clock();
		std::vector<claujson::Block> blocks;
		
		auto x = claujson::Parse(argv[1], 0, &ut, blocks);
		if (!x.first) {
			std::cout << "fail\n";
			return 2;
		}
		claujson::PoolManager poolManager(x.first, std::move(blocks)); // using pool manager, add Item or remove

		//std::vector<claujson::Block> blocks2{ claujson::Block{0, (int64_t)x.second}};
		//claujson::PoolManager poolManager2{};

		int b = clock();
		std::cout << "total " << b - a << "ms\n";
		//claujson::LoadData::_save(std::cout, &ut);
		//claujson::LoadData::save("output.json", ut);

		//test2(&ut);
/*
		{
			//claujson::ChkPool(ut.get_data_list(0), poolManager2);
			
			//poolManager.Clear();

			//claujson::LoadData::_save(std::cout, &ut);
			
			for (int i = 0; i < 5; ++i)
			{
				int a = clock();
				double sum = 0;
				int64_t chk = 0;

				claujson::UserType* A = ut.get_data_list(0)->find_ut("features"sv);

				// no l,u,d  any 
				// true      true
				// false     true

				for (auto iter = A->get_data().begin(); iter != A->get_data().end(); ++iter)
				{
						claujson::UserType* y = (*iter)->find_ut("geometry"sv); // as_array()[t].as_object()["geometry"];

						//chk = (int)y;

					
					if(y) {
					//	chk += y->get_data_size();
						claujson::UserType* yyy =  y->find_ut("coordinates"sv);
						
						//chk += (int)yyy;
						
						//if (yyy) {
							yyy = yyy->get_data_list(0);
						//}

						//if (yyy) {
							//chk += yyy->get_data_size();
							for (claujson::UserType* z : yyy->get_data()) {
								for (claujson::UserType* _z : z->get_data()) {  //size3; ++w2) {
									if (_z->get_value().data.type == simdjson::internal::tape_type::DOUBLE) {
										sum += _z->get_value().data.float_val;
									}
								}
							}
						//}
						
						//	//std::cout << dur.count() << "ns\n";

					}

				}


				std::cout << sum << "\n";
				std::cout << clock() - a << "ms\n";
				std::cout << "chk " <<  chk << "\n";
				////std::cout << "time " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms\n";
			}
		}
		*/
		bool ok = nullptr != x.first;

		//ut.remove_all(poolManager);
		poolManager.Clear();


		return !ok;
	}
	catch (...) {
		return 1;
	}
}
