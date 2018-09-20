#include "stdafx.h"
#include "CircullarBuffer.h"
#include "gtest/gtest.h"

using namespace std;

TEST(BufferTests, Constructor) 
{
   CircularBuffer cb;
   EXPECT_TRUE(cb.isEmpty());
}

TEST(BufferTests, CopyConstructor__CapacityConstructor)
{
   CircularBuffer cb(1);
   cb.pushFront('a');
   CircularBuffer CB = cb;
   EXPECT_EQ(cb.front(), CB.front());
   EXPECT_TRUE(cb.capacity());
}

TEST(BufferTests, CapacityFilledByElementConstructor__At__Front__Back)
{
   CircularBuffer cb(3, 'a');
   EXPECT_EQ(cb.back(), cb.front());
   EXPECT_EQ(cb.at(2), cb.at(1));
   EXPECT_EQ(cb.at(0), 'a');
}

TEST(BufferTests, Linerize__isLinerazied__PushBack)
{
   CircularBuffer cb(5);

   cb.pushBack('a');
   EXPECT_EQ(cb[0], 'a');
   cb.pushBack('b');
   EXPECT_EQ(cb[1], 'b');
   cb.pushBack('c');
   EXPECT_EQ(cb[2], 'c');
   cb.pushBack('d');
   EXPECT_EQ(cb[3], 'd');
   cb.pushBack('e');
   EXPECT_EQ(cb[4], 'e');
   
   cb.popFront();
   EXPECT_EQ(cb[0], 'b');
   EXPECT_EQ(cb.front(), 'b');

   cb.linearize();

   EXPECT_EQ(cb.first(), 'b');
   EXPECT_TRUE(cb.isLinearized());
}

TEST(BufferTests, Rotate)
{
   CircularBuffer cb(4);

   cb.pushBack('e');
   cb.pushBack('f');
   cb.pushBack('g');
   cb.pushBack('h');

   cb.rotate(2);

   EXPECT_EQ(cb.first(), 'g');
}

TEST(BufferTests, Size__isEmpty__isFull__Reserve__Capacity)
{
   CircularBuffer cb(6);
   EXPECT_EQ(cb.capacity(), 6);
   EXPECT_TRUE(cb.isEmpty());
   
   cb.pushBack('a');
   cb.pushFront('f');
   cb.pushBack('b');

   EXPECT_EQ(cb.reserve(), 3);

   cb.pushFront('e');
   cb.pushBack('c');
   cb.pushFront('d');

   EXPECT_EQ(cb.size(), 6);
   EXPECT_TRUE(cb.isFull());
}

TEST(BufferTests, SetCapacity__Resize__Equalty__Assignment)
{
   CircularBuffer cb;
   cb.setCapacity(3);
   EXPECT_EQ(cb.capacity(), 3);
   cb.pushBack('x');
   cb.pushBack('y');
   cb.pushBack('z');
   cb.resize(5, 'w');
   
   CircularBuffer CB;

   EXPECT_TRUE(cb != CB);

   CB = cb;
   EXPECT_TRUE(cb == CB);
   EXPECT_EQ(CB.capacity(), cb.capacity());
   EXPECT_EQ(CB.size(), cb.size());
   EXPECT_EQ(CB.isFull(), cb.isFull());
   EXPECT_EQ(CB.isEmpty(), cb.isEmpty());
   EXPECT_EQ(CB.reserve(), cb.reserve());
   EXPECT_EQ(CB.front(), cb.front());
   EXPECT_EQ(CB.back(), cb.back());
   EXPECT_EQ(CB.at(3), cb.at(3));
}

TEST(BufferTests, Swap__Insert__Erase__Clear__Choise)
{
   CircularBuffer cb(6, 'a');
   cb.insert(1, 'b');
   cb.insert(2, 'c');
   cb.insert(3, 'd');
   cb.insert(4, 'e');
   cb.popBack();

   CircularBuffer CB(5);
   CB.pushBack('u');
   CB.pushBack('v');
   CB.pushBack('x');
   CB.pushBack('y');
   CB.pushBack('z');

   cb.swap(CB);

   EXPECT_EQ(CB[1], 'b');
   EXPECT_EQ(cb[2], 'x');

   cb.erase(2, 4);
   EXPECT_EQ(cb.size(), 2);

   CB.clear();
   EXPECT_TRUE(CB.isEmpty());

}

int main(int argc, char *argv[]) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
