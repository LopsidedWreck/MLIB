/// MLIB hpp
/// This file contains a bunch of useful functions.

/* Please note that the format for curly brackets in classes is like it is for space purposes */
/* I'm aware some people may hate it, but I don't like stuff sticking out in classes too much. */
/* Thanks for understanding */
/* ~MLIB Creator */

#include<Windows.h>
#include<conio.h>
#include<mmsystem.h>

#include<chrono>
#include<string>
#include<vector>

#include<iostream>
#include<fstream>
#include<stdlib.h>

#include<math.h>

#pragma comment(lib, "winmm.lib")

#define STREAM_SIZE 256
#define MAX_TABLE_SIZE 512

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace mlib
{
	// Reads and parses through a text file.
	// Params:
	//	file - The file object.
	//	seperating_char - The seperating character used for formatting.
	//	file_name - The directory of the file.
	// Returns: A list of strings pulled from the file.
	inline std::vector<std::string>& ParseFile(std::ifstream& file, char seperating_char, std::string file_name)
	{
		static std::vector<std::string> list;
		std::string storage;
		if (!file.is_open())
			file.open(file_name, std::ios::in);

		for (int i = 0; file.eof() != true; ++i)
		{
			char stream[STREAM_SIZE] = { 0 };
			file.getline(stream, STREAM_SIZE);

			for (int j = 0; j < STREAM_SIZE; ++j)
			{

				if (stream[j] == seperating_char)
				{
					continue;
				}

				storage.push_back(stream[j]);
			}

			list.push_back(storage);
		}

		// Close the file.
		file.close();

		return list;
	}


	// Shrink to fit function.
	// Shrinks a static array.
	// Params:
	//	_array - A pointer to the array to shrink.
	// Returns: The new size of the array.
	/* NOTE: THIS FUNCTION MAY BE DEPRECATED */
	inline int shrink_to_fit(char *_array)
	{
		// Assume that FillArray() was used.
		std::string _a(_array);
		std::string temp;
		for (unsigned int i = 0; i < _a.size(); ++i)
		{
			if (_a.at(i) != 0)
			{
				temp.push_back(_a.at(i));
			}
		}

		_a.clear();
		_a = temp;

		for (unsigned int i = 0; i < _a.size(); ++i)
		{
			_array[i] = _a.at(i);
		}

		char *t = _array;

		_array = new char[_a.size() + 1];
		if (_array == nullptr)
			std::cout << "NOTICE: " << _array << " shrink_to_fit in mlib.hpp, line 71 doesn't work.";

		int s = sizeof(t) + 1;
		for (int i = 0; i < s; ++i)
		{
			_array[i] = t[i];
		}

		for (int i = 0; i < sizeof(_array) + 1; ++i)
		{
			if (_array[i] >= 32 && _array[i] < 126)
				continue;

			_array[i] = NULL;
		}

		return _a.size();
	}


	// Sleep function.
	// This function literally just makes it so you don't have to do simple math.
	// Params:
	//	time_ - The time to sleep the program for.
	inline void SLEEP(unsigned int long time_)
	{
		Sleep(time_ * 1000); // Compensating for milliseconds.
	}


	// Get function.
	// Returns: The struct used to access the current time.
	inline struct tm *GetCurrTime()
	{
		time_t t;
		struct tm *now = { 0 };
		t = time(NULL);

		now = localtime(&t);

		return now;
	}

	
	// Clear function.
	// Clears an array of values.
	// Params:
	//	_array - The array to clear.
	//	size - The size of the array.
	// Returns: The new array.
	template<typename T>
	inline T *ClearArray(T * _array, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_array[i] = NULL;
		}

		return _array;
	}


	// Fill function.
	// Fills an array with NULL values.
	// Params:
	//	_array - The array to fill.
	//	size - The size of the array.
	template<typename T>
	inline T *FillArray(T * _array, int size)
	{
		if (_array == nullptr) // Check if the array exists.
		{
			_array = new char[size](); // If not, just create one.
		}

		for (int i = 0; i < size; ++i)
		{
			if (_array[i] != NULL || (_array[i] >= 32 && _array[i] <= 126)) // Check ascii values.
				continue; // This makes sure we aren't writing over any existing data.

			_array[i] = NULL; // Place a zero.
		}

		return _array;
	}

	template <class T>
	class DynamicArray
	{
	public:
		DynamicArray<T>() : size_(0) { list = new T[size_]; } // Default constructor.
		DynamicArray<T>(ULONG allocator_size, T* list_) {
			size_ = allocator_size;
			list = new T[size_];
			for (int i = 0; i < size_; ++i)
				this->list[i] = list_[i];
		} // Non-Default Constructor.
		DynamicArray<T>(const DynamicArray& other) : list(other.list), size_(other.size_) {} // Copy Constructor.

		~DynamicArray<T>() {
			clear();
			list = nullptr;
		} // Destructor.

		// Get function.
		// Returns: The size of the DynamicArray.
		ULONG size() { return size_; }

		// Add function.
		// Params:
		//	data - The data to add.
		inline void add(T* data) {
			list = (T*)realloc(list, size_ + (sizeof(data) / sizeof(T)));
			for (int i = 0; i < sizeof(data) / sizeof(T); ++i) {
				list[size_ + i] = data[i];
			}

			size_ = size_ + (sizeof(data) / sizeof(T));
		}

		// Remove function.
		// Removes the last element in the list.
		void remove() {
			erase(size_);
		}

		// At function.
		// Returns: The data at 'place'
		T& at(ULONG place) {
			if (place < size_ - size_ || place > size_)
				return nullptr;
			return list[place];
		}

		// Erase function.
		// Params:
		//	place - The element to erase.
		inline void erase(ULONG place) {
			if (place < size_ - size_ || place > size_)
				return;
			delete &list[place];
			list[place] = (T)nullptr;
			list = (T*)realloc(list, size_ - 1);
			size_ -= 1;
		}

		// Clear function.
		// Clears the entire array.
		void clear() {
			for (ULONG i = size_; i > -1; ++i)
				erase(i);
			size_ = 0;
		}

		// Shrink to fit function.
		// Shrinks the DynamicArray down.
		inline void shrink_to_fit() {
			for (ULONG i = 0; i < size_; ++i)
				if (list[i] == (T)nullptr)
					erase(i); // Man, erase is really handy.
		}

		// Resize function.
		// Params:
		//	s - The new size for the DynamicArray.
		inline void resize(ULONG s) {
			if (size_ > s) // remove elememts after s.
				for (ULONG i = size_; i > s; ++i)
					erase(i);
			else if (size_ < s) {
				auto t_size = size_;
				T* temp = list;
				clear();
				list = (T*)malloc(s);
				for (ULONG i = 0; i < t_size; ++i)
					list[i] = temp[i];
				for (ULONG i = size_ + 1; i < s; ++i)
					list[i] = (T)nullptr; // Safe-gaurd.
			}
			size_ = s;
		}

		// Format function.
		// Makes all elements nullptr.
		void format() {
			for (ULONG i = 0; i < size_; ++i)
				list[i] = nullptr;
		}

		// Display function.
		// Returns: The contents of the list.
		T* list_() {
			return list;
		}

	private:

		ULONG size_; // The size of the list.
		T *list; // The list of elements.

		// Overload the assignment operator.
		DynamicArray& operator=(const DynamicArray& left_) {
			this->clear();
			this->list = (T*)malloc(left_.size());
			this->size_ = left_.size_;
			for (ULONG i = 0; i < size_; ++i)
				this->list[i] = left_.list[i];
		}
	};

	/* Math mlib */
	class Mmlib
	{
	public:

		// Get function.
		// Returns: An instance of the class.
		static Mmlib& GI() {
			static Mmlib instance;
			return instance;
		}

		// [S]olve [T]riangle [S]ide
		// Solves for the given side.
		// Params:
		// a, b, c - The sides. Any side left as a negative number (or 0) is the one that will be solved for.
		// Returns: The side length of a triangle.
		double STS(double a = -1, double b = -1, double c = -1) {
			double answer = -1;

			if (a <= 0) { // Solve for a.
				if (b <= 0 || c <= 0) { // Check if any other side is not set.
					return answer; // Could not solve.
				}

				// a^2 = c^2 - b^2
				answer = (c*c) - (b*b);
				return sqrt(answer);
			}

			else if (b <= 0) { // Solve for b.
				if (a <= 0 || c <= 0) {
					return answer;
				}

				// b^2 = c^2 - a^2
				answer = (c*c) - (a*a);
				return sqrt(answer);
			}

			else if (c <= 0) {
				if (a <= 0 || b <= 0) {
					return answer;
				}

				// a^2 + b^2 = c^2
				answer = (a*a) + (b*b);
				return sqrt(answer);
			}

			return answer; // Just so the visual studio compiler doesn't yell at me.
		}

		// [S]olve [C]ircle [A]rea
		// Solves for the area of a circle.
		// Note: Leave the variables that you don't want to use as default.
		// Params:
		//	r - The radius of the circle.
		//	c - Circumference of the circle.
		//	d - Diameter of the circle.
		// Returns: The area of a circle.
		double SCA(double r = -1, double c = -1, double d = -1) {
			if (r > 0)
				return M_PI * (r*r);

			else if (c > 0)
				return (c*c) / (4*M_PI);
			
			else if (d > 0)
				return (M_PI/4) * (d*d);
			
			return -1;
		}

		// [S]olve [S]quare [A]rea
		// Solves for the area of a square (although, it might be quicker just to do this one yourself).
		// Params:
		// s1 - side length 1.
		// s2 - side length 2.
		// If it's a true square, just leave s2 as default. s1 will be squared.
		// Returns: The area of a square.
		double SSA(double s1, double s2 = -1) {
			if (s2 <= 0)
				return s1*s1;
			return s1*s2;
		}

		// [S]olve [S]phere [S]urface [A]rea
		// Solve for the surface area of a sphere.
		// Params:
		//	r - The radius of the sphere.
		// Returns: The surface area.
		double SSSA(double r) {
			if (r <= 0)
				return -1;
			return 4 * M_PI * (r*r);
		}

		// [S]olve [C]ube [S]urface [A]rea
		// Solve for the surface area of a cube.
		// Params:
		//	el - The length of one of the edges.
		// Returns: The surface area of the cube.
		double SCSA(double el) {
			if (el <= 0)
				return -1;
			return 6 * (el*el);
		}

		// [S]olve [P]yramid [S]urface [A]rea
		// Sovle for the surface area of a pyramid.
		// Params:
		//	l - the length of the base.
		//	w - the width of the base.
		//	h - The height of the pyramid.
		// Returns: The surface area of the pyramid.
		double SPSA(double l, double w, double h) {
			// EQUATION: (length * width) + (length * square root of (width / 2) ^ 2 + h^2) + width * square root of ((length / 2) ^ 2 + h^2)
			/// Whoo! That's a doozy.

			double first_part; // The first part of the equation.
			double second_part; // The second part of the equation.

			/* This math had to be spaced out otherwise I would lose my mind. */
			first_part = (l * w) + (l * sqrt(((w / 2) * (w / 2)) + (h * h)));
			second_part = w * sqrt(((l / 2) * (l / 2)) + (h * h));

			/* That was a lot of parentheses. */
			return first_part + second_part;
		}

		// [S]olve [C]one [S]urface [A]rea
		// Solves for a cone's surface area.
		// Params:
		//	r - The radius of the base.
		//	h - The height of the cone.
		// Returns: The surface area of the cone.
		double SCSA(double r, double h) {
			if (r <= 0 || h <= 0)
				return -1;
			// pi * r * (r + sqrt(((h*h) + (r*r))))
			return (M_PI * r) * (r + sqrt(((h * h) + (r * r)))); // This math also had to be spaced out. Too many parentheses.
		}

		// [S]olve [C]ylinder [S]urface [A]rea
		// Solves for a cylinders surface area.
		// Params:
		//	r - The radius of the top and base.
		//	h - The height of the cylinder.
		//	flag - To tell the compiler we want to use this one, instead of the Cone surface area.
		//		You can make the flag true or false. It doesn't matter.
		// Returns: The surface area of the cylinder.
		double SCSA(double r, double h, bool flag) {
			if (flag);

			// (2 * pi * r * h) + (2 * pi * (r * r))
			return (2*M_PI*r*h) + (2*M_PI*(r*r));
		}
	};

	template<class T>
	struct LL // Skeleton of a linked list.
	{
		// Default Constructor.
		LL<T>() : next_node(), node_name(), var_one(), var_two(),
		obj_one(), obj_two() {}

		// Copy Constructor & Assignment Operator (disabled).
		LL<T>(const LL&) = delete;
		LL& operator=(const LL&) = delete;

		// Non-Default Constructor.
		LL<T>(T *next_, char *name_, T v1, T v2, T *o1, T *o2) : next_node(next_),
		node_name(name_), var_one(v1), var_two(v2), obj_one(o1),
		obj_two(o2) {}

		// Destructor.
		~LL() {}

		T *next_node; // The next node in the list.
		char *node_name; // The name of the node (to keep track of everything).

		// Some simple variables
		T var_one;
		T var_two;

		// Some simple objects
		T *obj_one;
		T *obj_two;
	};

	/* Class for encrypting a file */
	class Encryption
	{
	public:

		// Get function.
		// Returns: An instance to the class.
		static Encryption& GetInstance() {
			static Encryption instance;
			return instance;
		}

		
		// Init function (RUN THIS FIRST!).
		void Init() {
			std::cout << "\n\nPlease enter the file directory: ";
			std::cin >> file_dir;

			// Open the in file.
			in_file.open(file_dir.c_str(), std::ios::in);
		}

		// Encrypt function.
		// Encrypts the text in the file 'file_dir'.
		void EncryptFile() {
			do {
				char temp[STREAM_SIZE] = { 0 };
				in_file.getline(temp, STREAM_SIZE);
				current_line = temp;

				current_line.shrink_to_fit();
				for (unsigned int i = 0; i < current_line.size(); ++i) {
					/* For now, lets just subtract the ascii value by 12. */
					output_buffer.push_back(current_line.at(i) - 12);
				}
			} while (!in_file.eof() && in_file.is_open());

			in_file.close();

			// Open the output file.
			out_file.open(file_dir.c_str(), std::ios::out);
			out_file.clear();

			if (out_file.is_open()) {
				out_file << output_buffer.c_str();
			}
			out_file.close();
		}

		// Shutdown function (RUN THIS LAST!).
		void Shutdown() {
			file_dir.clear();
			current_line.clear();
			output_buffer.clear();
		}


	private:

		// Default Constructor.
		Encryption() : file_dir(), current_line(), output_buffer(),
		in_file(), out_file() {}

		// Destructor.
		~Encryption() {}

		// Disable the Copy Constructor and Assignment Operator.
		Encryption(const Encryption&) = delete;
		Encryption& operator=(const Encryption&) = delete;

		std::string file_dir;
		std::string current_line;
		std::string output_buffer;

		std::ifstream in_file;
		std::ofstream out_file;
	};

	// Parse functon.
	// Parses a string and replaces the seperating char with a different char.
	// Params:
	//	s - The string to parse.
	//	sc - The seperating character to look for.
	//	rc - The replacement character (default space).
	//	flag - Tells the function if you want the c string instead.
	// Returns: The modified string.
	template<typename T>
	T * ParseString(std::string& s, char sc, char rc, bool flag = false) {
		for (unsigned int i = 0; i < s.size(); ++i)
			if (s.at(i) == sc)
				s.at(i) = rc;

		if (!flag)
			return &s;
		
		return s.c_str();
	}

	// Play function.
	// Plays a .WAV file.
	// Params:
	//	dir - The file dir of the sound file.
	void Play(std::string& dir) {
		if (!dir.empty())
			PlaySoundA(dir.c_str(), NULL, SND_FILENAME);
	}
}
