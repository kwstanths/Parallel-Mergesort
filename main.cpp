#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <algorithm>

#include "mergesort.hpp"

#define MY_MAX_INT 2147483647

typedef struct some_struct{
	some_struct(int _test_int, std::string _test_str): test_int(_test_int), test_str(_test_str){};
	int test_int;
	std::string test_str;
} some_struct_type;

bool sortintdesc(int left, int right){
	return left < right;
}

bool sortintasc(int left, int right){
	return left > right;
}

bool sortsomeotherstructstrasc(some_struct_type * left, some_struct_type * right){
	return left->test_str > right->test_str;
}

bool sortsomeotherstructstrdesc(some_struct_type * left, some_struct_type * right){
	return left->test_str < right->test_str;
}

void test(std::vector<int> test_vector, int numbers, int threads, bool mine) {
	struct timeval time_start, time_stop;

	std::cout << ((mine)?("Merge: "):("Quick: "));
	std::cout << "Numbers: " << numbers << ", Threads: " << pow(2,threads) << " ... " << std::flush;
	gettimeofday(&time_start, NULL);
	if (true) mns::sort<int>(&test_vector, sortintdesc, threads);
	else std::sort(test_vector.begin(), test_vector.end());
	gettimeofday(&time_stop, NULL);
	std::cout << 1000 * (time_stop.tv_sec - time_start.tv_sec) + (time_stop.tv_usec - time_start.tv_usec) / 1000 << " msec" << std::endl;
}

int main(){
	std::cout << "--Tests:" << std::endl;
	std::vector<int> test_vector;
	test_vector.push_back(1);
	test_vector.push_back(56);
	test_vector.push_back(23);
	test_vector.push_back(678);
	test_vector.push_back(33);
	test_vector.push_back(9);
	test_vector.push_back(21);
	test_vector.push_back(33);
	test_vector.push_back(9);
	test_vector.push_back(21);
	test_vector.push_back(33);
	test_vector.push_back(9);
	test_vector.push_back(21);

	mns::sort<int>(&test_vector, sortintasc, 0);
	for(int i =0; i< test_vector.size(); i++) std::cout << test_vector[i] << " " ;
	std::cout << std::endl;
	mns::sort<int>(&test_vector, sortintdesc, 0);
	for(int i =0; i< test_vector.size(); i++) std::cout << test_vector[i] << " " ;
	std::cout << std::endl;
	mns::sort<int>(&test_vector, [](int l,int r) -> bool {return l>r;}, 0);
	for(int i =0; i< test_vector.size(); i++) std::cout << test_vector[i] << " " ;
	std::cout << std::endl;
	mns::sort<int>(&test_vector, [](int l,int r) -> bool {return l<r;}, 0);
	for(int i =0; i< test_vector.size(); i++) std::cout << test_vector[i] << " " ;
	std::cout << std::endl;

	std::vector<some_struct_type *> test_vector2;
	test_vector2.push_back(new some_struct_type(4,"he"));
	test_vector2.push_back(new some_struct_type(44,"hell"));
	test_vector2.push_back(new some_struct_type(87,"helloda"));
	test_vector2.push_back(new some_struct_type(56,"hellodark"));
	test_vector2.push_back(new some_struct_type(23,"hellodarkne"));
	test_vector2.push_back(new some_struct_type(2,"hellodarkness"));
	test_vector2.push_back(new some_struct_type(678,"hellodarknessmy"));
	test_vector2.push_back(new some_struct_type(24,"hellodarknessmyol"));
	test_vector2.push_back(new some_struct_type(456,"hellodarknessmyoldf"));
	test_vector2.push_back(new some_struct_type(245,"hellodarknessmyoldfri"));
	test_vector2.push_back(new some_struct_type(223,"hellodarknessmyoldfriend"));

	mns::sort<some_struct_type *>(&test_vector2, [](some_struct_type * l, some_struct_type * r) -> bool {return l->test_int < r->test_int;}, 0);
	for(int i =0; i< test_vector2.size(); i++) std::cout << (test_vector2[i])->test_int << " " ;
	std::cout << std::endl;std::cout << std::endl;
	mns::sort<some_struct_type *>(&test_vector2, [](some_struct_type * l, some_struct_type * r) -> bool {return l->test_str < r->test_str;}, 1);
	for(int i =0; i< test_vector2.size(); i++) std::cout << (test_vector2[i])->test_str << " " ;
	std::cout << std::endl;std::cout << std::endl;
	mns::sort<some_struct_type *>(&test_vector2, sortsomeotherstructstrasc, 0);
	for(int i =0; i< test_vector2.size(); i++) std::cout << (test_vector2[i])->test_str << " " ;
	std::cout << std::endl;std::cout << std::endl;
	mns::sort<some_struct_type *>(&test_vector2, sortsomeotherstructstrdesc, 1);
	for(int i =0; i< test_vector2.size(); i++) std::cout << (test_vector2[i])->test_str << " " ;
	std::cout << std::endl;std::cout << std::endl;

	std::cout << "--Benchmarks:" << std::endl;
	std::cout << "Creating arrays..." << std::flush;
	int numbers = 10000;
	std::vector<int> test_vector3;
	for(int i=0; i<numbers; i++) test_vector3.push_back(rand()%MY_MAX_INT +1);
	numbers = 100000;
	std::vector<int> test_vector4;
	for(int i=0; i<numbers; i++) test_vector4.push_back(rand()%MY_MAX_INT +1);
	numbers = 1000000;
	std::vector<int> test_vector5;
	for(int i=0; i<numbers; i++) test_vector5.push_back(rand()%MY_MAX_INT +1);
	numbers = 10000000;
	std::vector<int> test_vector6;
	for(int i=0; i<numbers; i++) test_vector6.push_back(rand()%MY_MAX_INT +1);
	numbers = 20000000;
	std::vector<int> test_vector7;
	for(int i=0; i<numbers; i++) test_vector7.push_back(rand()%MY_MAX_INT +1);
	std::cout << " Done" << std::endl;

	test(test_vector3,test_vector3.size(),0, true);
	test(test_vector3,test_vector3.size(),1, true);
	test(test_vector3,test_vector3.size(),0, false);
	std::cout << "\n";
	test(test_vector4,test_vector4.size(),0, true);
	test(test_vector4,test_vector4.size(),1, true);
	test(test_vector4,test_vector4.size(),0, false);
	std::cout << "\n";
	test(test_vector5,test_vector5.size(),0, true);
	test(test_vector5,test_vector5.size(),1, true);
	test(test_vector5,test_vector5.size(),0, false);
	std::cout << "\n";
	test(test_vector6,test_vector6.size(),0, true);
	test(test_vector6,test_vector6.size(),1, true);
	test(test_vector6,test_vector6.size(),0, false);
	std::cout << "\n";
	test(test_vector7,test_vector7.size(),0, true);
	test(test_vector7,test_vector7.size(),1, true);
	test(test_vector7,test_vector7.size(),2, true);
	test(test_vector7,test_vector7.size(),0, false);





	return 0;
}
