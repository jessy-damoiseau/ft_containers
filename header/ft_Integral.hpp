#ifndef FT_INTEGRAL_HPP
#define FT_INTEGRAL_HPP

namespace ft {

	template <class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<class T>
	struct is_integral : false_type {};

	template<> struct is_integral<bool> : true_type {};
	template<> struct is_integral<char> : true_type {};
	template<> struct is_integral<char16_t> : true_type {};
	template<> struct is_integral<char32_t> : true_type {};
	template<> struct is_integral<wchar_t> : true_type {};
	template<> struct is_integral<signed char> : true_type {};
	template<> struct is_integral<short int> : true_type {};
	template<> struct is_integral<int> : true_type {};
	template<> struct is_integral<long int> : true_type {};
	template<> struct is_integral<long long int> : true_type {};
	template<> struct is_integral<unsigned char> : true_type {};
	template<> struct is_integral<unsigned short int> : true_type {};
	template<> struct is_integral<unsigned int> : true_type {};
	template<> struct is_integral<unsigned long int> : true_type {};
	template<> struct is_integral<unsigned long long int> : true_type {};

	template<> struct is_integral<const bool> : true_type {};
	template<> struct is_integral<const char> : true_type {};
	template<> struct is_integral<const char16_t> : true_type {};
	template<> struct is_integral<const char32_t> : true_type {};
	template<> struct is_integral<const wchar_t> : true_type {};
	template<> struct is_integral<const signed char> : true_type {};
	template<> struct is_integral<const short int> : true_type {};
	template<> struct is_integral<const int> : true_type {};
	template<> struct is_integral<const long int> : true_type {};
	template<> struct is_integral<const long long int> : true_type {};
	template<> struct is_integral<const unsigned char> : true_type {};
	template<> struct is_integral<const unsigned short int> : true_type {};
	template<> struct is_integral<const unsigned int> : true_type {};
	template<> struct is_integral<const unsigned long int> : true_type {};
	template<> struct is_integral<const unsigned long long int> : true_type {};

}

#endif