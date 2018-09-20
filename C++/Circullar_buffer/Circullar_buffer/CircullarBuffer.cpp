#include "stdafx.h"
#include <iostream>
#include <vector>

#include "CircullarBuffer.h"

using namespace std;

CircularBuffer::CircularBuffer() = default;
// done & tested
CircularBuffer::~CircularBuffer() = default;
// done
CircularBuffer::CircularBuffer(const CircularBuffer &cb)
{
   (*this) = cb;
}
// done & tested

CircularBuffer::CircularBuffer(int capacity)
{
   buffer_.resize(capacity);
}
// done & tested
CircularBuffer::CircularBuffer(int capacity, const valueType &elem)
{
   vector<valueType> newBuffer(capacity, elem);
   buffer_ = newBuffer;

   isEmpty_ = 0;
   size_ = newBuffer.capacity();
   last_ = newBuffer.capacity() - 1;
}
// done & tested

valueType& CircularBuffer::operator[](int i)
{
   i += first_;

   int capacity = (*this).capacity();

   if (i > capacity)
      return buffer_[i - capacity];
   else 
      return buffer_[i];
}
// done & tested
const valueType& CircularBuffer::operator[](int i) const
{
   i += first_;

   int capacity = (*this).capacity();

   if (i > capacity)
      return buffer_[i - capacity];
   else
      return buffer_[i];
}
// done & tested


valueType& CircularBuffer::at(int i) 
{
   if (i < 0 || i > size_)
      throw invalid_argument("invalid index (at)"); 
   
   i += first_;

   int capacity = (*this).capacity();

   if (i > capacity)
      return buffer_[i - capacity];
   else
      return buffer_[i];
}
// done & tested
const valueType& CircularBuffer::at(int i) const 
{
   if (i < 0 || i > size_)
      throw invalid_argument("invalid index (at)");

   i += first_;

   if (i > (*this).capacity())
      return buffer_[i - (*this).capacity()];
   else
      return buffer_[i];
}
// done & tested

valueType& CircularBuffer::front() 
{
   return at(0);
}
// done & tested
valueType& CircularBuffer::back() 
{
   return at(size_ - 1);
}
// done & tested
const valueType& CircularBuffer::front() const 
{
   return at(0);
}
// done & tested
const valueType& CircularBuffer::back() const 
{
   return at(size_ - 1);
}
// done & tested


valueType* CircularBuffer::linearize()
{
   (*this).rotate(first_);
   return &buffer_[0];
}
// done & tested
bool CircularBuffer::isLinearized() const
{
   return first_ == 0;
}
// done & tested
void CircularBuffer::rotate(int newBegin)
{
   vector<valueType> newBuffer((*this).buffer_.begin(), (*this).buffer_.end());
   for (int j = 0, i = newBegin;   i <= last_;   j++, i++)
      newBuffer[j] = buffer_[i];

   int capacity = buffer_.capacity();

   for (int j = capacity - 1, i = newBegin - 1;   i >= first_;   j--, i--)
      newBuffer[j] = buffer_[i];
      
   buffer_ = newBuffer;
      
   first_ = capacity- (newBegin - first_);
   first_ %= capacity;
   
   last_ = last_ - newBegin + capacity;
   last_ %= capacity;



   /*vector<valueType> newBuffer((*this).buffer_.begin(), (*this).buffer_.end());
   for (int j = 0, i = newBegin; i <= last_; j++, i++)
      newBuffer[j] = buffer_[i];

   for (int j = buffer_.capacity() - 1, i = newBegin - 1; i >= first_; j--, i--)
      newBuffer[j] = buffer_[i];

   buffer_ = newBuffer;

   first_ = newBegin;

   last_ = first_ + size_ - 1;
   last_ %= (*this).capacity();*/



}
// done & tested

valueType CircularBuffer::first()
{
   return buffer_[0];
}
// done & made for tests


int CircularBuffer::size() const
{
   return size_;
}
// done & tested
bool CircularBuffer::isEmpty() const
{
   return isEmpty_;
}
// done & tested
bool CircularBuffer::isFull() const
{
   return buffer_.size() == buffer_.capacity();
}
// done & tested
int CircularBuffer::reserve() const
{
   return (*this).capacity() - (*this).size();
}
// done & tested
int CircularBuffer::capacity() const
{
   return buffer_.capacity();
}
// done & tested

void CircularBuffer::setCapacity(int newCapacity)
{
   buffer_.resize(newCapacity);
}
// done & tested
void CircularBuffer::resize(int newSize,
                            const valueType &item)
{
   buffer_.resize(newSize, item);
}
// done & tested

CircularBuffer& CircularBuffer::operator = (const CircularBuffer &cb)
{
   vector<valueType> newBuffer(cb.buffer_.begin(), cb.buffer_.end());
   (*this).buffer_ = newBuffer;

   (*this).first_ = cb.first_;
   (*this).last_ = cb.last_;

   (*this).size_ = cb.size_;

   (*this).isEmpty_ = cb.isEmpty_;

   return (*this);
}
// done & tested
void CircularBuffer::swap(CircularBuffer &cb)
{
   //vector<valueType> newBuffer(cb.buffer_.begin(), cb.buffer_.end());

   //for (int i = 0; i < (*this).size_; i++) 
   //   cb.buffer_[i] = (*this).buffer_[i];

   //int first = cb.first_;
   //int last = cb.last_;

   //cb.first_ = (*this).first_;
   //cb.last_ = (*this).last_;

   ///**/

   //for (int i = 0; i < (*this).size_; i++)
   //   (*this).buffer_[i] = newBuffer[i];

   //(*this).first_ = first;
   //(*this).last_ = last;

   (*this).buffer_.swap(cb.buffer_);
}
// done & tested



void CircularBuffer::print()
{
   cout << "Buffer empty == " << (*this).isEmpty() << endl;

   if ((*this).isEmpty() == 0) {
      for (int i = 0; i < size_; i++) {
         cout << "buffer_[" << i << "] = " << buffer_[i] << endl;
      }
      cout << endl;
   }
   
}
// done & made for tests
void CircularBuffer::printFB()
{
   cout << "First: " << (*this).first_ << " = " << (*this).front() << endl;
   cout << "Last: " << (*this).last_ << " = " << (*this).back() << endl;
}
// done & made for tests

void CircularBuffer::pushBack(const valueType &item)
{
   size_++;

   if ((*this).isEmpty() == 1) {
      buffer_[size_ - 1] = item;
      isEmpty_ = 0;
      return;
   }

   if (last_ != (*this).capacity() - 1) 
      last_++;
   else 
      last_ = 0;

   buffer_[size_ - 1] = item;

   if (last_ == first_) {
      if (first_ != (*this).capacity() - 1)
         first_++;
      else
         first_ = 0;
      size_--;
   }
}
// done & tested
void CircularBuffer::pushFront(const valueType &item)
{
   size_++;

   if ((*this).isEmpty() == 1) {
      buffer_[first_] = item;
      isEmpty_ = 0;
      return;
   }

   if (first_ != 0)
      first_--;
   else
      first_ = (*this).capacity() - 1;
   buffer_[0] = item;

   if (first_ == last_) {
      if (last_ != 0)
         last_--;
      else
         last_ = (*this).capacity() - 1;
      size_--;
   }
}
// done & tested
void CircularBuffer::popBack()
{
   if ((*this).isEmpty() == 1 || size_ == 0) {
      isEmpty_ = 1;
      return;
   }

   size_--;

   if (last_ == first_) {
      isEmpty_ = 1;
      return;
   }

   if (last_ != 0)
      last_--;
   else
      last_ = (*this).capacity() - 1;

   if (size_ == 0)
      isEmpty_ = 1;
}
// done & tested
void CircularBuffer::popFront()
{
   if ((*this).isEmpty() == 1 || size_ == 0) {
      isEmpty_ = 1;
      return;
   }

   size_--;

   if (first_ == last_) {
      isEmpty_ = 1;
      return;
   }

   if (first_ != ((*this).capacity() - 1))
      first_++;
   else
      first_ = 0;

   if (size_ == 0)
      isEmpty_ = 1;
}
// done & tested

void CircularBuffer::insert(int pos, const valueType &item)
{
   if (first_ > pos || last_ < pos)
      throw invalid_argument("invalid index (insert)");

   buffer_[pos] = item;
}
// done & tested
void CircularBuffer::erase(int first, int last)
{
   if (last - first < 0)
      throw invalid_argument("indalid index (erase)");
   
   int border = size_ - last - 1;

   if (border > 0)
      for (int i = 0; i < border; i++)
         buffer_[first + i] = buffer_[last + i];

   size_ -= (last - first + 1);
}
// done & tested
void CircularBuffer::clear()
{
   isEmpty_ = 1;

   last_ = first_;
}
// done & tested

bool operator == (const CircularBuffer &a, const CircularBuffer &b)
{
   if (a.size() != b.size()) 
      return false;
   
   for (int i = 0; i < a.size() - 1; i++) 
      if (a.at(i) != b.at(i))
         return false;

   return true;
}
// done & tested
bool operator != (const CircularBuffer &a, const CircularBuffer &b)
{
   return !(a == b);
}
// done & tested