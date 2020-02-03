
#ifndef STACK_H
#define STACK_H

// ##### TEMPLATE CLASSES #####
// 
// Often, you find that you want the same class, but with different types.
// You can do that with a _template class_. 
//
// For instance, a dynamic-array-based stack:
//
template <typename T>
class Stack
{
	public:
		Stack()
		{
			A = new T[10];
			size = 0;
			capacity = 10;
		}

		T top()
		{
			if (size == 0)
				return A[0];
			return A[size-1];
		}

		void push(T a)
		{
			if (size == capacity)
			{
				T* new_A = new T[capacity*2];
				for (int i = 0; i < capacity; ++i)
					new_A[i] = A[i];
				delete[] A;
				A = new_A;
				capacity *= 2;
			}
			A[size] = a;
			++size;	
		}

		void pop()
		{
			if (size > 0)
				--size;
		}

	private:
		T* A;
		int size;
		int capacity; 
};

#endif
