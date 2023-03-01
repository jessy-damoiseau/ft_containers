# ft_containers

<img src="https://raw.githubusercontent.com/isocpp/logos/master/cpp_logo.png"  width="30" height="30" />

## Overview

 - Implement a few container types of the C++ standard template library in c++98
 - Containers to implement from scratch : vector, map, stack
 - Must also be implemented along with the containers :
    - iterators_traits
    - reverse_iterator
    - enable_if (it is C++11 so it has to be implemented in a C++98 manner). This is asked to learn SFINAE metaprogrammating concept.
    - is_integral
    - equal and/or lexicographical_compare
    - std::pair
    - std::make_pair
 - As usual per 42 standard : no memory leaks allowed (not even 'still reachable' type), and project is up to 42's coding norm
 - Each containers comes with its own custom unit tester to check its behavior
