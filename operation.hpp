#ifndef OPERATION_H
#define OPERATION_H
#include <climits>

template<typename T>
struct tree_node{
	T value;
	int index;
};

namespace operation 
{
	template<typename T>
	class min
	{
		public:
		static const T NEUTRAL_ELEMENT = INT_MAX;
		tree_node<T> operator() (const tree_node<T>& lhs,const tree_node<T>& rhs) const 
		{
			return (lhs.value<rhs.value) ? lhs : rhs;
		}
	};

	template<typename T>
	class max
	{
		public:
		static const T NEUTRAL_ELEMENT = INT_MIN;
		tree_node<T> operator() (const tree_node<T>& lhs,const tree_node<T>& rhs) const 
		{
			return (lhs.value>rhs.value) ? lhs : rhs;
		}
	};

	template<typename T>
	class sum
	{
		public:
		static const T NEUTRAL_ELEMENT = 0;
		T operator()(const T& lhs,const T& rhs) const 
		{
			return lhs+rhs;
		}
	};

	template<typename T>
	class gcd
	{
		public:
		static const T NEUTRAL_ELEMENT = 0;
		T operator()(const T& lhs,const T& rhs) const 
		{
			return __gcd(lhs,rhs);
		}
	};
}

#endif