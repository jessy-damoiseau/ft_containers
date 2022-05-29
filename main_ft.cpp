

#include <iostream>
#include <exception>
#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "ft_Pair.hpp"

/*
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
	vec2.erase(vec2.begin() + 11);

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

void check_map(){

	typedef ft::map<char,int>::iterator iterator;
	typedef ft::map<char,int>::reverse_iterator reverse_iterator;

	ft::map<char, int> map1;

	map1['a'] = 42;
	map1['b'] = 1337;
	map1['c'] = 31415;
	map1['d'] = 24;

	ft::map<char, int> map2(map1.begin(), map1.end());
	ft::map<char, int> map3(map2);
	ft::map<char, int> map4;

	map4 = map1;


	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "|                    Check_Map                   |" << std::endl;
	std::cout << "--------------------------------------------------\n" << std::endl;

	std::cout << "Constructor\n" << std::endl;

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Map 2:" << std::endl;
	std::cout << "Size -> " << map2.size() << std::endl;
	for(iterator it = map2.begin(); it != map2.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Map 3:" << std::endl;
	std::cout << "Size -> " << map3.size() << std::endl;
	for(iterator it = map3.begin(); it != map3.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Map 4:" << std::endl;
	std::cout << "Size -> " << map4.size() << std::endl;
	for(iterator it = map4.begin(); it != map4.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Iterator\n" << std::endl;

	std::cout << "begin/end\n" << std::endl;
	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "rbegin/rend\n" << std::endl;
	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(reverse_iterator it = map1.rbegin(); it != map1.rend(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Capacity\n" << std::endl;

	std::cout << "Empty" << std::endl;
	if (map1.empty())
		std::cout << "map1 is empty" << std::endl;
	else
		std::cout << "map1 is not empty" << std::endl;
	std::cout << "map1.size() ->" << map1.size() <<  std::endl;
	std::cout << "map1.max_size() ->" << map1.max_size() <<  std::endl;


	std::cout << "Element access\n" << std::endl;

	std::cout << "Operator []" << std::endl;

	std::cout << "map1['a'] = " << map1['a'] << std::endl;
	std::cout << "map1['z'] = " << map1['z'] << std::endl;

	std::cout << "Modifiers\n" << std::endl;

	ft::map<char,int> map5;
	map5['z'] = 66;
	map5['p'] = 33;
	map5['x'] = -1;
	ft::pair<char, int> fillmap = ft::make_pair('w', 54);

	std::cout << "Insert fillmap to map2" << std::endl;
		ft::pair<iterator, bool> res = map2.insert(fillmap);
		if (res.second)
			std::cout << "insert done\n" << std::endl;
		else
			std::cout << "insert fail\n" << std::endl;

		std::cout << "insert fillmap to map3" << std::endl;
		iterator res_it = map3.insert(map3.begin(), fillmap);
		std::cout << "Key -> " << res_it->first << ", Value -> " << res_it->second << "\n" << std::endl;

		std::cout << "Insert map5 in map1" << std::endl;

	map1.insert(map5.begin(), map5.end());

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Erase map1.begin() + 1" << std::endl;
	map1.erase(++map1.begin());

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Erase map1['d']" << std::endl;
	map1.erase('d');

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Erase map1.begin() + 3 to map1.end()" << std::endl;
	iterator b3 = map1.begin();
	map1.erase(++b3, map1.end());

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Swap map1 and map2" << std::endl;

	std::cout << "Before" << std::endl;

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Map 2:" << std::endl;
	std::cout << "Size -> " << map2.size() << std::endl;
	for(iterator it = map2.begin(); it != map2.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	map1.swap(map2);
	std::cout << "After" << std::endl;

	std::cout << "Map 1:" << std::endl;
	std::cout << "Size -> " << map1.size() << std::endl;
	for(iterator it = map1.begin(); it != map1.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Map 2:" << std::endl;
	std::cout << "Size -> " << map2.size() << std::endl;
	for(iterator it = map2.begin(); it != map2.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "Clear map2" << std::endl;

	map2.clear();

	std::cout << "Map 2:" << std::endl;
	std::cout << "Size -> " << map2.size() << std::endl;
	for(iterator it = map2.begin(); it != map2.end(); it++)
		std::cout << "Key -> " << it->first << ", Value -> " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "key/value compare" << std::endl;

	ft::map<char, int>::key_compare mycomp = map1.key_comp();

	if (mycomp(map1.begin()->first, 'a'))
		std::cout << "key is 'a'" << std::endl;
	else
		std::cout << "key is not 'a'" << std::endl;

	ft::pair<char, int> highest = *map1.rbegin();
	iterator value_comp_it = map1.begin();

	do {
		std::cout << value_comp_it->first << " => " << value_comp_it->second << std::endl;
	} while (map1.value_comp()(*value_comp_it++, highest));

	std::cout << "Find x" << std::endl;

	iterator it_x = map1.find('x');

	std::cout << "it_x->first : " << it_x->first << ", it_x->second : " << it_x->second << std::endl;

	std::cout << "Count" << std::endl;

	std::cout << "z" << std::endl;

	if (map1.count('z'))
		std::cout << "z is an element of map1" << std::endl;
	else
		std::cout << "z is not an element of map1" << std::endl;

	std::cout << "w" << std::endl;

	if (map1.count('w'))
		std::cout << "w is an element of map1" << std::endl;
	else
		std::cout << "w is not an element of map1" << std::endl;

	std::cout << "Lower/Upper bound" << std::endl;

	iterator lower_it = map1.lower_bound('w');
	iterator upper_it = map1.upper_bound('a');

	std::cout << "w : first -> " << lower_it->first << ", second -> " << lower_it->second << std::endl;
	std::cout << "a : first -> " << upper_it->first << ", second -> " << upper_it->second << std::endl;

	std::cout << "Equal range" << std::endl;

	ft::pair<iterator, iterator> ERpair = map1.equal_range('d');

	std::cout << "ERpair.first : first -> " << ERpair.first->first << ", second -> " << ERpair.first->second << std::endl;
	std::cout << "ERpair.second : second -> " << ERpair.second->first << ", second -> " << ERpair.second->second << std::endl;

}

int main(){
	check_vector();
	check_stack();
	check_map();

	return 0;
}
*/


#include <list>
#include "common.hpp"

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;
using namespace std;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
		cout << it->first << " => " << it->second << '\n';
}

int main ()
{
  map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;


  map<char, int>::const_iterator tmp = foo.begin(); //tmp iterates through foo
  map<char, int>::const_iterator tmp2 = bar.begin(); //tmp2 iterates through bar

  swap(bar, foo); //tmp iterates through bar
				//tmp2 iterates through foo


  map<char, int>	other;

  other['1'] = 73;
  other['2'] = 173;
  other['3'] = 763;
  other['4'] = 73854;
  other['5'] = 74683;
  other['6'] = 753;

  map<char, int>::const_iterator tmp3 = other.begin(); // tmp3 iterates through other

  cout << "foo contains:\n";
  for (map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

  cout << "bar contains:\n";
  for (map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    cout << it->first << " => " << it->second << '\n';

	while(tmp != bar.end())
	{
		cout << tmp->first << " => " << tmp->second << '\n';
		tmp++;
	}
	tmp--;

	while(tmp2 != foo.end())
	{
		cout << tmp2->first << " => " << tmp2->second << '\n';
		tmp2++;
	}
	tmp2--;
	swap(other, foo); //tmp2 iterates through other
					//tmp3 iterates throught foo
	print(other);
	print(foo);
	print(bar);
	std::cout << "check" << std::endl;
	while(tmp != bar.begin())
	{
		std::cout << "check1" << std::endl;
		cout << tmp->first << " => " << tmp->second << '\n';
		std::cout << "check2" << std::endl;
		tmp--;
	}
	cout << tmp->first << " => " << tmp->second << '\n';

	while(tmp2 != other.begin())
	{
		cout << tmp2->first << " => " << tmp2->second << '\n';
		tmp2--;
	}
	cout << tmp2->first << " => " << tmp2->second << '\n';

	while(tmp3 != foo.end())
	{
		cout << tmp3->first << " => " << tmp3->second << '\n';
		tmp3++;
	}
	tmp3--;

	swap(bar, foo);
	swap(foo, bar);
	swap(bar, foo); //tmp3 iterates through bar
				//tmp iterates through foo

	print(other);
	print(foo);
	print(bar);

	while(tmp != foo.end())
	{
		cout << tmp->first << " => " << tmp->second << '\n';
		tmp++;
	}

	while(tmp2 != other.end())
	{
		cout << tmp2->first << " => " << tmp2->second << '\n';
		tmp2++;
	}

	while(tmp3 != bar.begin())
	{
		cout << tmp3->first << " => " << tmp3->second << '\n';
		tmp3--;
	}
	cout << tmp3->first << " => " << tmp3->second << '\n';
}



