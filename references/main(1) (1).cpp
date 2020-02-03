
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <stack>
#include <iostream>
#include "stack.h"

using namespace std;

//http://www.cplusplus.com/doc/oldtutorial/templates/

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}
#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))




// ##### TEMPLATE FUNCTIONS ##### 
//
// A _template function_ works as a "blueprint" for 
// the same function with different types:
//
template <typename W>
W min_tmpl(W a, W b, W c)
{
	W m = a;
	if (b < m)
		m = b;
	if (c < m)
		m = c;
	return m;
}
//
// Using a template function is done just like any other function:
//
void test_min_template_function()
{
	int A[3] = {7, 3, 5}; 
	test(min_tmpl(A[0], A[1], A[2]) == 3);

	float B[3] = {2.6f, 9.1f, -8.3f};
	test(min_tmpl(B[0], B[1], B[2]) == -8.3f);

	string C[3] = {"ghi", "abc", "def"};
	test(min_tmpl(C[0], C[1], C[2]) == "abc");
}



// ##### TEMPLATE CLASSES #####
// 
// Often, you find that you want the same class, but with different types.
// You can do that with a _template class_. 
//
// Here we use the Stack template class declared (and implemented) in stack.h:
//
void test_stack_template_class()
{
	Stack<int> S1;
	S1.push(5);
	S1.push(3);
	S1.push(8);
	test(S1.top() == 8);
	S1.pop();
	test(S1.top() == 3);
	S1.pop();
	test(S1.top() == 5);
	
	Stack<string> S2;
	S2.push("hello");
	S2.push("goodbye");
	S2.push("beep");
	test(S2.top() == "beep");	
	S2.pop();
	test(S2.top() == "goodbye");
	S2.pop();
	test(S2.top() == "hello");
}
//
// The C++ STL (standard template library) is filled with these
// template classes (and functions) that implement various data structures.
//
// The template-ness of these implementations lets you use these
// data structures with whatever type of data you want.
// 
// One of the most popular STL template classes is vector:
//
void test_vector()
{	
        vector<int> V;
	V.push_back(4);
	V.push_back(5);
	V.push_back(6);
	test(V.size() == 3);
        test(V[0] == 4); 
        test(V[1] == 5); 
        test(V[2] == 6); 

	V[0] = 14;
        V[1] = 15;
        V[2] = 16;
	test(V.size() == 3);
        test(V[0] == 14); 
        test(V[1] == 15); 
        test(V[2] == 16); 

	V.insert(V.begin()+1, 100);
	test(V.size() == 4);
        test(V[0] == 14); 
        test(V[1] == 100); 
        test(V[2] == 15); 
        test(V[3] == 16); 

        for (int i = 0; i < V.size(); ++i)
                cout << V[i] << endl;
}



// ##### Iterators #####
//
// If you want to iterate through the elements of an unordered_map,
// unordered_set, vector, or other class from the C++ standard library,
// you should use an _iterator_: C++'s general way of accessing elements.
void test_vector_iterators()
{
        vector<int> V;
	V.push_back(4);
	V.push_back(5);
	V.push_back(6);
        
        vector<int>::iterator i = V.begin(); 
        test(*i == 4);
        ++i;
        test(*i == 5);
        ++i;
        test(*i == 6);
        ++i;
        test(i == V.end()); 
        --i;
        test(*i == 6);

        
	for (vector<int>::iterator i = V.begin(); i != V.end(); ++i)
		cout << *i << endl;

        // Can also used "range-based" for-loop (uses iterators underneath)
        // for (type varname : vectorname) 
	for (int a : V) 
		cout << a << endl;
}


// ##### ITERATORS WITH OTHER STL CONTAINERS #####
//
// Unordered sets are containers that store unique elements in // no particular order, and which allow for fast retrieval of 
// individual elements based on their value.
/*http://www.cplusplus.com/reference/unordered_set/unordered_set/
*/

void test_unordered_set()
{
	unordered_set<int> S;
	test(S.size() == 0);	
	
	S.insert(2);
	test(S.size() == 1);

	S.insert(2);
	test(S.size() == 1);

	S.insert(3);
	test(S.size() == 2);

	S.insert(4);
	S.insert(5);
	S.insert(6);
	S.insert(700000);
	S.insert(800);

	S.erase(700000);

	test(S.find(800) != S.end());	
	test(S.find(999) == S.end());

	for (unordered_set<int>::iterator i = S.begin(); i != S.end(); ++i)
		cout << *i << endl;

	for (int x : S)
		cout << x << endl;

}

/*
Unordered maps are associative containers that store elements formed by the combination of a key value and a mapped value, and which allows for fast retrieval of individual elements based on their keys.
http://www.cplusplus.com/reference/unordered_map/unordered_map/*/

void test_unordered_map()
{
	unordered_map<string, int> M;

	M["hello"] = 8;	
	test(M["hello"] == 8);

	M["goodbye"] = 8;
	test(M["goodbye"] == M["hello"]);

      M["hello"] = 50;
	test(M["goodbye"] != M["hello"]);

     for (unordered_map<string, int>::iterator i = M.begin(); i != M.end(); ++i)
       cout << i->first << " maps to " << i->second << endl;
}



// ##### REFERENCES #####
//
// References are "safe and clean" pointers.
//
void references_and_pointers()
{
	int x = 5;

	int &r = x;  // Creates a reference r
	int *p = &x; // Creates a pointer p 
	test(r == 5);
	test(*p == 5);

	x = 6;
	test(r == 6);
	test(*p == 6);

	r = 7;
	test(x == 7);
	*p = 8;
	test(r == 8);
	test(x == 8);

        int &a; // Not valid C++ code!

}
//
// Passing by reference is similar to passing by pointer,
// but with different syntax for defereferencing.
//
// Both are very different than passing by value: 
void double_all(vector<int> A, vector<int> &B, vector<int> *C)
{
	for (int i = 0; i < A.size(); ++i)
		A[i] *= 2; 
        for (int i = 0; i < B.size(); ++i)
                B[i] *= 2;
	for (int i = 0; i < C->size(); ++i)
		(*C)[i] *= 2; 
}
//
void test_double_all()
{
	vector<int> A{-1, 2, 3};
        test(A.size() == 3);
	test(A[0] == -1); 
	test(A[1] == 2);		
	test(A[2] == 3);		

        vector<int> B = A;
        vector<int> C = A;

	double_all(A, B, &C);
	test(A[0] == -1); 
	test(A[1] == 2);		
	test(A[2] == 3);		
	test(B[0] == -2); 
	test(B[1] == 4);		
	test(B[2] == 6);		
	test(C[0] == -2); 
	test(C[1] == 4);		
	test(C[2] == 6);		
}
// 
// Still need pointers for linked lists, arrays, etc.



// ##### THE CONST KEYWORD #####
//
// C++ has a keyword "const" (short for "constant") 
// that can be used in lots of scenarios to enforce guarantees
// that something won't be modified.

// For instance, if a function takes a const parameter,
// the function is promising not to modify the parameter. 
// 
const int* cannot_change_parameter(const int &x)
{
        cout << x << endl; // Ok, since x is not modified
        //++x; // Not ok

        const int y = x;
        cout << y << endl; // Ok, since y is not modified
        //++y; // Not ok
        int z = y; 
        ++z;

        const int* xp = &x; // Ok, since "constant-ness" of x is preserved by xp
        int* p;
        p = &z;
        //p = &x; // Not ok 
        return xp; 
} 

void test_cannot_change_parameter()
{
        int x = 3;
        const int* p = cannot_change_parameter(x); // x will not be changed

        cout << *p << endl; // Ok, since float pointed at by fp is not changed
        //++(*p); // Not ok
}




int main()
{
	test_min_template_function();
	test_stack_template_class();

	test_vector();
      test_vector_iterators();
	test_unordered_set();
	test_unordered_map();

	references_and_pointers();
	test_double_all();

     test_cannot_change_parameter();

	cout << "Tests complete." << endl;		
}






