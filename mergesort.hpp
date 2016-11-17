#ifndef __MERGESORT_HPP__
#define __MERGESORT_HPP__

#include <iostream>
#include <vector>
#include <thread>
//#include <ThreadPool>


namespace mns{

namespace mergesort{

	template<typename T>
	void copyarray(T * _src, int start, int end, T * _dst){
		for(int i = start; i < end; i++) (*_dst)[i] = (*_src)[i];
	}

	template<typename T>
	void merge(std::vector<T> * _array, int start, int middle, int end, std::vector<T> * _temp_array, bool (*func)(T,T)){
		int i = start;
		int j = middle;

		for(int k = start; k<end; k++){
			if (i < middle && (j >= end || func((*_array)[i],(*_array)[j]))) {
				(*_temp_array)[k] = (*_array)[i];
				i++;
			} else {
				(*_temp_array)[k] = (*_array)[j];
				j++;
			}
		}
	}

	template<typename T>
	void splitmerge(std::vector<T> * _temp_array, int start, int end, std::vector<T> * _array, bool (*func)(T,T), int threads){

		if (end - start < 2) return;
		int middle = (start + end)/2;

		if (threads - 1 >= 0){
			std::thread * t1;
			std::thread * t2;
			t1 = new std::thread(splitmerge<T>, _array, start, middle, _temp_array, func, threads-1);
			t2 = new std::thread(splitmerge<T>, _array, middle, end, _temp_array, func, threads-1);
			t1->join();
			t2->join();
			merge(_temp_array, start, middle, end, _array, func);
		}else{
			splitmerge(_array, start, middle, _temp_array, func, 0);
			splitmerge(_array, middle, end, _temp_array, func, 0);
			merge(_temp_array, start, middle, end, _array,func);
		}
	}

	template<typename T>
	void sort(std::vector<T> * _vector, bool (*func)(T,T), int threads){
		/*
			threads --> 2^(threads) will be created
			terrible name, more like depth_of_recursion_to_create_threads... well that's terrible as well
		*/

		std::vector<T> * array, * temp_array;
		int size;
		array = _vector;
		size = _vector->size();
		temp_array = new std::vector<T>(size);

		copyarray(array, 0, size, temp_array);
		splitmerge(temp_array, 0, size, array, func, threads);
	}
}

}

#endif
