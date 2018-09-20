#pragma once

#include <vector>

typedef char valueType;

using namespace std;

class CircularBuffer 
{
   public:
      CircularBuffer();
      ~CircularBuffer();
      CircularBuffer(const CircularBuffer &cb);
    
      explicit CircularBuffer(int capacity);               // Creates a buffer of a given capacity;
      CircularBuffer(int capacity, const valueType &elem); // ..filled by "elem"; 
    
      valueType &operator[](int i);             // Access by index;
      const valueType &operator[](int i) const; // Don't check the correectness of the index;
    
      valueType &at(int i);             // Access by index;
      const valueType &at(int i) const; // If isn't correct than use exeption;

      valueType &front();             // Link to the first element;
      valueType &back();              // Link to the last element;
      const valueType &front() const;
      const valueType &back() const;
    
      valueType *linearize();     // Gives pointer at first element;
      bool isLinearized() const;  // Check buffer for linearize;
      void rotate(int newBegin);  // Create buffer with 
                                  // element[newBegin] at 0 index;
    
      int size() const;     // Amount of elements in buffer;
      bool isEmpty() const; // True if size() == 0;
      bool isFull() const;  // True if size() == capacity();
      int reserve() const;  // Amount of free elements in buffer;
      int capacity() const; // Capacity of buffer;

      void setCapacity(int new—apacity); 
      void resize(int newSize, 
                  const valueType &item = valueType()); // Change buffer's size;
                                                        // If it gonna be bigger new elements will be "item"
                                     
      CircularBuffer &operator = (const CircularBuffer &cb); // Assignment operator;
      void swap(CircularBuffer &cb); 

      void pushBack(const valueType &item = valueType());
      void pushFront(const valueType &item = valueType());
      void popBack();
      void popFront();

      void insert(int pos, const valueType &item = valueType());
      void erase(int first, int last);
      void clear();

      void print();
      void printFB();

      valueType first();
 
   private:
      vector<valueType> buffer_;

      int first_ = 0;
      int last_ = 0;

      int size_ = 0;

      int isEmpty_ = 1;
};

bool operator == (const CircularBuffer &a, const CircularBuffer &b);
bool operator != (const CircularBuffer &a, const CircularBuffer &b);
