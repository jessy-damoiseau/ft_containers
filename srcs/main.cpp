

#include <iostream>
#include <vector>
#include <stack>
#include "../header/ft_Iter.hpp"
#include "../header/ft_RandAccessIter.hpp"
#include "../header/ft_RevIter.hpp"
#include "../header/ft_Integral.hpp"
#include "../header/ft_Utility.hpp"
#include "../header/ft_Pair.hpp"
#include "../header/ft_Vector.hpp"
#include "../header/ft_Stack.hpp"
#include "../header/ft_Map.hpp"
#include <exception>



template <class T>
		typename ft::enable_if<ft::is_integral<T>::value, bool>::type
		is_odd(T i) { std::cout << "check" << std::endl ;return bool(i%2);}


int main(){

	// *** ITERATOR / REVERSE_ITERATOR *** //

	int tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	typedef ft::random_access_iterator<int> iterator;
	typedef ft::reverse_iterator<iterator> rev_iter;
	iterator it(&tab[0]);
	iterator ite(&tab[10]);
	rev_iter rev_it(ite);
	rev_iter rev_ite(it);

	std::cout << ite - it << std::endl;

	for (iterator t = it; t < ite; t++) {
		std::cout << *t << std::endl;
	}

	std::cout << "len -> " << (rev_ite - rev_it) << std::endl;
	for (rev_iter t = rev_it; t > rev_ite; t++){
		std::cout << *t << std::endl;
	}

	// *** ENABLE_IF *** //

	std::cout << std::boolalpha;
	std::cout << "int -> " << (ft::is_integral<int>::value) << std::endl;
	std::cout << "float -> " << (ft::is_integral<float>::value) << std::endl;

	std::cout << "enable_if, odd -> " << is_odd(1) << std::endl;
	std::cout << "enable_if, odd -> " << is_odd(2) << std::endl;

	// *** EQUAL *** //

	std::vector<int> myvector(tab, tab+10);

	if ( ft::equal(myvector.begin(), myvector.end(), tab))
		std::cout << "vector and tab is equal" << std::endl;
	else
		std::cout << "vector and tab is diff" << std::endl;
	myvector[2] = 12;
	if ( ft::equal(myvector.begin(), myvector.end(), tab))
		std::cout << "vector and tab is equal" << std::endl;
	else
		std::cout << "vector and tab is diff" << std::endl;

	// *** PAIR / MAKE_PAIR *** //

	char foo[] = "apple";
	char bar[] = "apartment";
	std::cout << "lexico foo/bar -> " << ft::lexicographical_compare(foo, foo+5, bar, bar+9) << std::endl;
	std::cout << "lexico bar/foo -> " << ft::lexicographical_compare(bar, bar+9, foo, foo+5) << std::endl;

	ft::pair<std::string, int> test1;
	ft::pair<int, double> test2(42, 12.25);

	test1 = ft::make_pair(std::string("bonjour ceci est un test"), 90);
	std::cout << "pair: test1.first -> "<< test1.first << " , test1.second -> " << test1.second << std::endl;
	std::cout << "pair: test2.first -> "<< test2.first << " , test2.second -> " << test2.second << std::endl;

	std::cout << std::endl;
	ft::vector<int> testvector(5, 10);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	std::cout << testvector.size() << " " << testvector.capacity() << " " << testvector.max_size() << " " << testvector.empty() << std::endl;
	std::cout << std::endl;
	testvector.resize(3);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	testvector.resize(10);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;

	testvector.resize(25, 55);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}

	testvector.reserve(100);
	std::cout << testvector.size() << " " << testvector.capacity() << " " << testvector.max_size() << " " << testvector.empty() << std::endl;
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}

	std::cout << std::endl;
	std::cout << testvector[2] << std::endl;
	std::cout << std::endl;
	std::cout << testvector.at(20) << std::endl;
	std::cout << std::endl;
	try {
		std::cout << testvector.at(50) << std::endl;
	}
	catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
	std::cout << testvector.front() << std::endl;
	std::cout << std::endl;
	std::cout << testvector.back() << std::endl;

	std::cout << std::endl;
	testvector.assign(5, 20);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	testvector.push_back(8);
	testvector.push_back(30);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	testvector.pop_back();
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	testvector.insert(testvector.begin() + 2,3,  40);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	testvector.insert(testvector.end() ,3,  40);
	for (iterator i = testvector.begin(); i != testvector.end(); i++){
		std::cout << *i << std::endl;
	}

	std::cout << std::endl;
	ft::vector<int> test2vec(5, 10);
	test2vec.insert(test2vec.end(), testvector.begin(), testvector.begin() + 2);
	for (iterator i = test2vec.begin(); i != test2vec.end(); i++){
		std::cout << *i << std::endl;
	}
	std::cout << std::endl;
	test2vec.erase(test2vec.begin() + 2, test2vec.end());
	for (iterator i = test2vec.begin(); i != test2vec.end(); i++){
		std::cout << *i << std::endl;
	}

	std::cout << std::endl;

	ft::stack<int> stack_test;
	stack_test.push(1);
	if (stack_test.empty())
		std::cout << "stack empty" << std::endl;
	else
		std::cout << "stack no empty" << std::endl;
	std::cout << stack_test.top() << std::endl;
	stack_test.push(42);
	ft::stack<int> stack2;
	stack2.push(1);
	stack2.push(42);

	std::cout << "-----------------------------------------------------------------------" << std::endl;
	std::cout << "-                                  MAP                                -" << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;

	ft::map<char, std::string> testmap;
	testmap['a'] = "test1";
	testmap['b'] = "test2";
	testmap['c'] = "test3";
	testmap['d'] = "test4";
	testmap['e'] = "test5";
	testmap['f'] = "test6";
	ft::map<char, std::string> testmap2;
	testmap2.insert(testmap.begin(), testmap.end());
	typedef ft::map<char, std::string>::iterator map_iter;

	map_iter map_it = testmap2.begin();
	map_iter map_ite = testmap2.end();
	for(; map_it != map_ite; map_it++){
		std::cout << "key -> " << map_it->first << ", value -> " << map_it->second << std::endl;
	}
	std::cout << "size -> " << testmap2.size() << std::endl;
	if (testmap2.count('e'))
		std::cout << "e exist" << std::endl;
	else
		std::cout << "e doesn't exist" << std::endl;
	testmap2.erase('e');

	map_it = testmap2.begin();
	map_ite = testmap2.end();
	for(; map_it != map_ite; map_it++){
		std::cout << "key -> " << map_it->first << ", value -> " << map_it->second << std::endl;
	}
	std::cout << "size -> " << testmap2.size() << std::endl;
	if (testmap2.count('e'))
		std::cout << "e exist" << std::endl;
	else
		std::cout << "e doesn't exist" << std::endl;

}