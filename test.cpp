#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
int main()
{
	std::stack<int> test;
	typedef typename std::stack<int>::container_type::iterator iterator;
	test.push(3);
	test.push(4);

}