#ifndef _sort_obj_h_
template <typename T>class sortObj
{
public:
	bool operator ()(T t1, T t2)  
	{  
		return (sequence(t1) > sequence(t2));
	}
	virtual unsigned int sequence(T t)=0;
};

template <typename T>class sortRef
{
public:
	bool operator ()(T t1, T t2)  
	{  
		return (sequence(t1) < sequence(t2));
	}
	virtual unsigned int sequence(T t)=0;
};


#define _sort_obj_h_
#endif
