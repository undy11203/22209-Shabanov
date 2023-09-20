#include <CircleBuffer/includes/CircleBuffer.hpp>

#include <gtest/gtest.h>

TEST(CircularBufferInitTest, InitTest) {
    CircularBuffer cb1{};
    CircularBuffer cb2{5};
    CircularBuffer cb3{cb2};
    CircularBuffer cb4{5, 'f'};

    EXPECT_EQ(cb1.capacity(), 0);
    EXPECT_TRUE(cb1.empty());

    EXPECT_EQ(cb2.capacity(), 5);
    EXPECT_TRUE(cb2.empty());

    EXPECT_EQ(cb3.capacity(), 5);
    EXPECT_EQ(cb2, cb3);

    EXPECT_EQ(cb4.capacity(), 5);
    EXPECT_EQ(cb4.size(), 5);
}

TEST(CircularBufferExtractTest, ExtractElementTest) {
    CircularBuffer cb{5, 'b'};
    const CircularBuffer cb1{5, 'b'};

    cb.insert(0, 'a');
    EXPECT_EQ(cb[0], 'a');
    EXPECT_EQ(cb.at(0), 'a');

    cb.push_back('t');
    EXPECT_EQ(cb.back(), 't');

    cb.push_front('r');
    EXPECT_EQ(cb.front(), 'r');

    EXPECT_EQ(cb1.back(), 'b');
    EXPECT_EQ(cb1.front(), 'b');
}

TEST(CircularBufferMoveTest, MoveCellsTest) {
    CircularBuffer cb{5, 'a'};
    cb.rotate(3);
    EXPECT_TRUE(cb.is_linearized());
    cb.rotate(10);
    EXPECT_TRUE(cb.is_linearized());
    cb.pop_back();
    cb.insert(2, 'e');
    cb.rotate(2);
    EXPECT_EQ(cb.at(0), 'e');

    cb.linearize();
    EXPECT_TRUE(cb.is_linearized());
    cb.pop_front();
    EXPECT_FALSE(cb.is_linearized());
}

TEST(CircularBufferSizeTest, CheckSizeTest) {
    CircularBuffer cb{5, 'a'};
    CircularBuffer cb1{5};

    EXPECT_FALSE(cb.empty());
    EXPECT_TRUE(cb1.empty());

    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb1.size(), 0);
    EXPECT_EQ(cb.capacity(), 5);

    EXPECT_TRUE(cb.full());
    EXPECT_FALSE(cb1.full());

    EXPECT_EQ(cb.reserve(), 0);
}

TEST(CircularBufferSizeTest, SetSizeTest) {
    CircularBuffer cb{5, 'a'};

    cb.set_capacity(6);
    EXPECT_EQ(cb.capacity(), 6);
    EXPECT_EQ(cb.size(), 5);
    cb.set_capacity(3);
    EXPECT_EQ(cb.size(), 3);

    cb.resize(8, 'u');
    EXPECT_EQ(cb.size(), 8);
}

TEST(CircularBufferSwapTest, SwapTest) {
    CircularBuffer cb1{5};
    CircularBuffer cb2{5, 'b'};
    CircularBuffer tmp{cb1};
    cb1 = cb2;
    cb2 = tmp;
    EXPECT_EQ(cb1.size(), 5);
    EXPECT_EQ(cb2.size(), 0);

    cb1.swap(cb2);
    EXPECT_EQ(cb1.size(), 0);
    EXPECT_EQ(cb2.size(), 5);
}

TEST(CircularBufferAddElementTest, AddElementTest) {
    CircularBuffer cb1{5, 'c'};
    CircularBuffer cb2{5};
    cb1.push_back('a');
    EXPECT_EQ(cb1.back(), 'a');
    cb1.push_front('b');
    EXPECT_EQ(cb1.front(), 'b');

    cb2.push_back('a');
    EXPECT_EQ(cb2.back(), 'a');

    cb2.push_front('b');
    EXPECT_EQ(cb2.front(), 'b');

    cb1.insert(1, 'g');
    EXPECT_EQ(cb1[1], 'g');

    cb1.insert(10, '1');
    EXPECT_EQ(cb1.at(0), '1');
}

TEST(CircularBufferRemoveElementTest, RemoveElementTest) {
    CircularBuffer cb1{5, 'a'};
    CircularBuffer cb2{5};
    CircularBuffer cb3{8, 'a'};
    CircularBuffer cb4{7, 'f'};

    cb1.pop_back();
    EXPECT_EQ(cb1.size(), 4);

    cb1.pop_front();
    EXPECT_EQ(cb1.size(), 3);

    cb2.push_back('a');
    cb2.pop_back();
    EXPECT_EQ(cb2.size(), 0);

    cb2.push_back('a');
    cb2.pop_front();
    EXPECT_EQ(cb2.size(), 0);

    cb1.clear();
    EXPECT_EQ(cb1.size(), 0);

    cb3.erase(1, 2);
    EXPECT_EQ(cb3.size(), 7);
    cb3.erase(6, 7);
    EXPECT_EQ(cb3.size(), 6);
    cb3.erase(0, 1);
    EXPECT_EQ(cb3.size(), 5);

    cb4.erase(0, 6);
    EXPECT_EQ(cb4.size(), 1);
    EXPECT_ANY_THROW(cb4.erase(-1, 1));
    cb4.pop_back();
    EXPECT_EQ(cb4.size(), 0);
    cb4.push_back('a');
    cb4.pop_front();
    EXPECT_EQ(cb4.size(), 0);
}

TEST(CircularBufferEqTest, EqTest) {
    CircularBuffer cb1{5};
    CircularBuffer cb2{5};

    EXPECT_TRUE(cb2 == cb1);

    cb2.push_back('a');
    EXPECT_FALSE(cb2 == cb1);

    cb2.pop_back();
    cb2.set_capacity(6);
    EXPECT_TRUE(cb2 == cb1);

    cb2.set_capacity(5);
    cb1.push_back('a');
    cb2.push_back('b');
    EXPECT_FALSE(cb2 == cb1);

    EXPECT_TRUE(cb1 != cb2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}