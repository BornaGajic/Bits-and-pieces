import 'dart:ffi';

class MyQueue<T> 
{
	late Array array;

    MyQueue (int size): assert(size > 0)
		{
				array = Array(size);
		}
}