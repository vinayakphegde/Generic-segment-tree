namespace operation 
{
	template<typename T1>
	class min
	{
		public:
		static T1* n_element;
		template<typename T2>
		T2 operator() (T2 lhs, T2 rhs) const 
		{
			return (lhs.value<rhs.value) ? lhs : rhs;
		}
	};

	template<typename T>
	class max
	{
		public:
		static T* n_element;
		T* operator()(T* lhs, T* rhs) const 
		{
			return (*lhs>*rhs) ? lhs : rhs;
		}
	};

	template<typename T>
	class sum
	{
		public:
		static const int n_element = 0;
		T operator()(const T lhs,const T rhs) const 
		{
			return lhs+rhs;
		}
	};

	template<typename T>
	class gcd
	{
		public:
		static const int n_element = 0;
		T operator()(const T lhs,const T rhs) const 
		{
			return __gcd(lhs,rhs);
		}
	};

}

template<typename T>
T* operation::min<T>::n_element = new int(INT_MAX);

template<typename T>
T* operation::max<T>::n_element = new int(INT_MIN);