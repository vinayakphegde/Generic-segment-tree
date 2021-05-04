namespace operation 
{
	template<typename T1>
	class min
	{
		public:
		static const T1 neutral_element = INT_MAX;
		template<typename T2>
		T2 operator() (T2 lhs, T2 rhs) const 
		{
			return (lhs.value<rhs.value) ? lhs : rhs;
		}
	};

	template<typename T1>
	class max
	{
		public:
		static const T1 neutral_element = INT_MIN;
		template<typename T2>
		T2 operator()(T2 lhs, T2 rhs) const 
		{
			return (lhs.value>rhs.value) ? lhs : rhs;
		}
	};

	template<typename T>
	class sum
	{
		public:
		static const int neutral_element = 0;
		T operator()(const T lhs,const T rhs) const 
		{
			return lhs+rhs;
		}
	};

	template<typename T>
	class gcd
	{
		public:
		static const int neutral_element = 0;
		T operator()(const T lhs,const T rhs) const 
		{
			return __gcd(lhs,rhs);
		}
	};

	template<typename T>
	class concat
	{
		public:
		static const string neutral_element ;
		T operator()(const T lhs,const T rhs) const 
		{
			return lhs+rhs;
		}
	};
	template<typename T>
	const string concat<T>::neutral_element = "";

}