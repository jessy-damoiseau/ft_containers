

#include <iostream>
#include <vector>
#include <stack>
#include "../header/ft_Stack.hpp"
#include "../header/ft_Vector.hpp"
#include <exception>



/*template <class T>
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
*/
void check_vector(){
	typedef ft::vector<int>::iterator iterator;
	typedef ft::vector<int>::reverse_iterator reverse_iterator;

	ft::vector<int> vec1(10, 100);
	ft::vector<int> vec2(vec1);
	ft::vector<int> vec3;
	ft::vector<int> vec4(vec1.begin(), vec1.end());

	vec3 = vec4;
	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "|                  Check_Vector                  |" << std::endl;
	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Constructors\n" << std::endl;

	std::cout << "vector 1:" << std::endl;
	std::cout << "Capacity -> " << vec1.capacity() << ", Size -> " << vec1.size() << std::endl;
	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "vector 3:" << std::endl;
	std::cout << "Capacity -> " << vec3.capacity() << ", Size -> " << vec3.size() << std::endl;
	for(iterator it = vec3.begin(); it != vec3.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "vector 4:" << std::endl;
	std::cout << "Capacity -> " << vec4.capacity() << ", Size -> " << vec4.size() << std::endl;
	for(iterator it = vec4.begin(); it != vec4.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Clear\n" << std::endl;

	vec1.clear();

	std::cout << "vector 1:" << std::endl;
	std::cout << "Capacity -> " << vec1.capacity() << ", Size -> " << vec1.size() << std::endl;
	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Iterators\n" << std::endl;

	std::cout << "*** Fill Vector 1 with push_back ***\n" << std::endl;
	for (size_t i = 0; i < 50; i++){
		vec1.push_back(i);
	}

	std::cout << "Use iterator begin/end" << std::endl;
	iterator it = vec1.begin();
	iterator ite = vec1.end();

	for (; it != ite; it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Use reverse iterator rbegin/rend" << std::endl;
	reverse_iterator rit = vec1.rbegin();
	reverse_iterator rite = vec1.rend();
	for (; rit != rite; rit++)
		std::cout << *rit << " ";
	std::cout << "\n" << std::endl;

	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Capcity\n" << std::endl;

	std::cout << "Size -> " << vec1.size() << ", Max_size -> " << vec1.max_size() << ", Capacity -> " << vec1.capacity() << std::endl;

	std::cout << "Resize 20" << std::endl;

	vec1.resize(20);

	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Resize 50 with 30" << std::endl;

	vec1.resize(50, 30);

	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	if (vec1.empty())
		std::cout << "vector 1 is empty\n" << std::endl;
	else
		std::cout << "vector 1 is not empty\n" << std::endl;

	std::cout << "Reserve 100" << std::endl;

	vec1.reserve(100);
	std::cout << "Capacity -> " << vec1.capacity() << "\n" << std::endl;

	std::cout << "Resize 20" << std::endl;

	vec1.resize(20);

	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Element access\n" << std::endl;

	std::cout << "Use operator [n]" << std::endl;
	for (size_t i = 0; i < vec1.size(); i++)
		std::cout << vec1[i] << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Size -> " << vec1.size() << std::endl;

	std::cout << "Use at" << std::endl;
	try{
		for (size_t i = 0; i < 6; i++)
			std::cout << vec1.at(i) << " ";
		std::cout << "\n" << std::endl;
		std::cout << vec1.at(100) << std::endl;

	}
	catch (std::exception &e){
		std::cout << "Error:" << std::endl;
		std::cout << e.what() << "\n" << std::endl;
	}

	std::cout << "Use front/back" << std::endl;

	std::cout << "Front -> " << vec1.front() << ", Back -> " << vec1.back() << std::endl;

	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Modifiers\n" << std::endl;

	std::cout << "Copy vector 1 to vector 2" << std::endl;
	vec2 = vec1;

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Assign 7x100 in vector 2" << std::endl;
	vec2.assign(7, 100);

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Assign vector 1 in vector 2" << std::endl;
	vec2.assign(vec1.begin(), vec1.end());

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Use pop_back" << std::endl;

	vec2.pop_back();

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Use insert" << std::endl;

	vec2.insert(vec2.begin() + 11, 55);

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "insert 5x40" << std::endl;

	vec2.insert(vec2.begin() + 14, 5, 40);

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "insert vector 1" << std::endl;

	vec2.insert(vec2.begin() + 15, vec1.begin(), vec1.end());

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Use erase" << std::endl;

	std::cout << "Erase 55" << std::endl;
	vec2.erase(vec2.begin() + 12);

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Erase (begin + 13) to (begin + 38)" << std::endl;
	vec2.erase(vec2.begin() + 13, vec2.begin() + 38);

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Swap vector 1 and vector 3" << std::endl;

	std::cout << "Before" << std::endl;

	std::cout << "vector 1:" << std::endl;
	std::cout << "Capacity -> " << vec1.capacity() << ", Size -> " << vec1.size() << std::endl;
	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "vector 3:" << std::endl;
	std::cout << "Capacity -> " << vec3.capacity() << ", Size -> " << vec3.size() << std::endl;
	for(iterator it = vec3.begin(); it != vec3.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	vec1.swap(vec3);

	std::cout << "After" << std::endl;

	std::cout << "vector 1:" << std::endl;
	std::cout << "Capacity -> " << vec1.capacity() << ", Size -> " << vec1.size() << std::endl;
	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "vector 3:" << std::endl;
	std::cout << "Capacity -> " << vec3.capacity() << ", Size -> " << vec3.size() << std::endl;
	for(iterator it = vec3.begin(); it != vec3.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "Copy vector to vector 2" << std::endl;

	vec2 = vec1;

	std::cout << "Clear vector 1" << std::endl;

	vec1.clear();

	std::cout << "vector 1:" << std::endl;
	std::cout << "Capacity -> " << vec1.capacity() << ", Size -> " << vec1.size() << std::endl;
	for(iterator it = vec1.begin(); it != vec1.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	if (vec2 == vec3)
		std::cout << "vector 2 == vector 3" << std::endl;
	if (vec2 != vec3)
		std::cout << "vector 2 != vector 3" << std::endl;
	if (vec2 < vec3)
		std::cout << "vector 2 < vector 3" << std::endl;
	if (vec2 <= vec3)
		std::cout << "vector 2 <= vector 3" << std::endl;
	if (vec2 > vec3)
		std::cout << "vector 2 > vector 3" << std::endl;
	if (vec2 >= vec3)
		std::cout << "vector 2 >= vector 3" << std::endl;

	std::cout << "vector 2:" << std::endl;
	std::cout << "Capacity -> " << vec2.capacity() << ", Size -> " << vec2.size() << std::endl;
	for(iterator it = vec2.begin(); it != vec2.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

	std::cout << "vector 3:" << std::endl;
	std::cout << "Capacity -> " << vec3.capacity() << ", Size -> " << vec3.size() << std::endl;
	for(iterator it = vec3.begin(); it != vec3.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n" << std::endl;

}

void check_stack(){
	ft::vector<int> VecForStack(5,100);
	ft::stack<int> stack1(VecForStack);
	ft::stack<int> stack2;


	stack2 = stack1;

	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "|                   Check_Stack                  |" << std::endl;
	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Size stack 1 -> " << stack1.size() << ", size stack 2 -> " << stack2.size() << "\n" << std::endl;
	std::cout << "Check empty stack 1" << std::endl;
	if (stack1.empty())
		std::cout << "Stack 1 is empty\n" << std::endl;
	else
		std::cout << "Stack 1 is not empty\n" << std::endl;

	std::cout << "push(42) on stack 2\n" << std::endl;

	stack2.push(42);

	std::cout << "Check top/pop on stack 2" << std::endl;

	while (stack2.size()){
		std::cout << stack2.top() << " ";
		stack2.pop();
	}
	std::cout << "\n" << std::endl;

	std::cout << "Check empty stack 2" << std::endl;
	if (stack2.empty())
		std::cout << "Stack 2 is empty\n" << std::endl;
	else
		std::cout << "Stack 2 is not empty\n" << std::endl;

	std::cout << "Fill stack 2 [1;12]" << std::endl;

	for (size_t i = 0; i < 12; i++)
		stack2.push(i);

	if (stack1 == stack2)
		std::cout << "stack 1 == stack 2" << std::endl;
	if (stack1 != stack2)
		std::cout << "stack 1 != stack 2" << std::endl;
	if (stack1 < stack2)
		std::cout << "stack 1 < stack 2" << std::endl;
	if (stack1 <= stack2)
		std::cout << "stack 1 <= stack 2" << std::endl;
	if (stack1 > stack2)
		std::cout << "stack 1 > stack 2" << std::endl;
	if (stack1 >= stack2)
		std::cout << "stack 1 >= stack 2" << std::endl;

}

int main(){
	check_vector();
	check_stack();

	return 0;
}