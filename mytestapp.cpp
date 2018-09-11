#include <iostream>
#include <limits.h>

#include <gtest/gtest.h>

int g = 50;

class Stack {
    std::vector<int> vstack = {};
    public:
    void push(int value) {vstack.push_back(value);}
    int pop() {
        if (vstack.size() > 0) {
            int value = vstack.back();
            vstack.pop_back();
            return value;
        } else {
            return -1;
        }
    }

    int size() {
        return vstack.size();
    }
};

struct StackTest : public testing::Test {
    Stack s1;
    void SetUp() {
        int value[] = {1,2,3};
        for (auto &v : value) {
            s1.push(v);
        }
    }

    void TearDown() {

    }
};

TEST_F(StackTest,sss) {
    int lpv = 3;
    while (lpv != 1)
        ASSERT_EQ(s1.pop(),lpv--);
}

TEST_F(StackTest,sssss) {
    int val = s1.size();
    for (val;val > 0;val--)
        ASSERT_NE(s1.pop(),-1);
}

class MyClass {
    std::string id;
    int baseValue;
    public:
    MyClass (std::string _id): id(_id) {}
    MyClass (int _bv): baseValue(_bv) {}
    std::string GetId() { return id;}
    int getValue() { return baseValue;}
    void Increment(int n) { baseValue += n; }

    MyClass() { std::cout << "CONS\n";}
    ~MyClass() { std::cout << "DESTX\n";}
};

struct MyClassTest : public testing::Test {
    MyClass *mc;
    void SetUp() { mc = new MyClass(100); }
    void TearDown() { delete mc; }

    MyClassTest() { std::cout << "conx\n";}
    ~MyClassTest() { std::cout << "destx\n";}
};

TEST_F(MyClassTest, aaa) {
    mc->Increment(5);
    ASSERT_EQ(mc->getValue(),105);
}

TEST_F(MyClassTest, aaa2) {
    mc->Increment(6);
    ASSERT_EQ(mc->getValue(),106);
}

TEST(ClassTest, increment_by_5) {
    
}

TEST(Test1,Testing4) {
    //g++;
    std::string s = "apple";
    ASSERT_STREQ(s.c_str(),"apple");
}

TEST(Test1,Testing) {
    int sum = 0;
    int n = 5000 + g;
    for (int i = 0;i <= 100;i++) {
        sum += i;
    }
    //sleep(5);
    //g--;
    ASSERT_EQ(sum,n);
}

TEST(Test1,Testing3) {
    int sum = 0;
    int n = 5000 + g;
    for (int i = 0;i <= 100;i++) {
        sum += i;
        //std::cout << "." << std::flush;
        //sleep(0.2);
    }
    ASSERT_EQ(sum,n);
}

GTEST_API_ int main(int argc, char **argv) 
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
