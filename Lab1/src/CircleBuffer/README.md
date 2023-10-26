#### CircularBuffer();
Create an empty CircularBuffer with zero capacity.

#### ~CircularBuffer();
Destroys CircularBuffer.

#### CircularBuffer(const CircularBuffer &cb);
Copy CircularBuffer.

#### explicit CircularBuffer(int capacity);
Creates a buffer of the specified capacity

#### CircularBuffer(int capacity, const value_type &elem);
Creates a buffer of the specified capacity and fills it with an element

#### value_type &operator[](int i);
Get the element at the index position. \
Do not check the correctness of the index.

#### const value_type &operator[](int i) const;
Get the element at the index position. \
Do not check the correctness of the index.

#### value_type &at(int i);
Get the element at the index position. \
Throws an exception ```std::out_of_range``` when the index is invalid.

#### const value_type &at(int i) const;
Get the element at the index position. \
Throws an exception ```std::out_of_range``` when the index is invalid.

#### value_type &front(); 
Get the first element.

#### value_type &back();  
Get the last element.

#### const value_type &front() const;
Get the first element.

#### const value_type &back() const;
Get the last element.

#### value_type *linearize();
Shifts the ring buffer so that its first element
moves to the beginning of the allocated memory. \
Returns a pointer to the first element.

#### bool is_linearized() const;
Checks if the buffer is linearized.

#### void rotate(int new_begin);
Rotate elements in the CircularBuffer.

#### int size() const;
Get the number of element in the CircularBuffer.

#### bool empty() const;
Checks if the buffer is empty.

#### bool full() const;
Checks if the buffer is full.

#### int reserve() const;
Get the number of free cells in the CircularBuffer.

#### int capacity() const;
Get the capacity of the CircularBuffer.

#### void set_capacity(int new_capacity);
Change the capacity of the CircularBuffer.

#### void resize(int new_size, const value_type &item = value_type());
Change the size of the CircularBuffer. If the new size is larger then it fills with ```item``` elements.

#### CircularBuffer &operator=(const CircularBuffer &cb);
Copy CircularBuffer.

#### void swap(CircularBuffer &cb);
Swap the contents of two CircularBuffer.

#### void push_back(const value_type &item = value_type());
Insert a new element at the end of the CircularBuffer. \
If ```capacity()``` == ```size()```, then
the first buffer element is overwritten.

#### void push_front(const value_type &item = value_type());
Insert a new element at the start of the CircularBuffer. \
If ```capacity()``` == ```size()```, then
the last buffer element is overwritten.
#### void pop_back();
Remove the last element from the CircularBuffer.

#### void pop_front();
Remove the first element from the CircularBuffer.


#### void insert(int pos, const value_type &item = value_type());
Insert an element ```item``` at the specified position.

#### void erase(int first, int last);
Removes elements from the buffer in the interval [first, last).

#### void clear();
Remove all elements from the circular_buffer.

#### bool operator==(const CircularBuffer &a, const CircularBuffer &b);
Compare two circular_buffers by size, by capacity and element by element to determine if they are equal.

#### bool operator!=(const CircularBuffer &a, const CircularBuffer &b);
Compare two circular_buffers by size, by capacity and element by element to determine if they are non-equal.