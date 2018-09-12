#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

class Bar {

};

class Foo {
    public:
    virtual ~Foo() {}
    virtual int GetSize() const {return 0;}
    virtual void f(int n) {}
    virtual string Describe(const char* name) {return "apple";}
    virtual string Describe(int type) {
        return "banana";
    }
    virtual bool Process(Bar elem, int count) {return true;}
};

class MockFoo : public Foo {
public:
    MOCK_CONST_METHOD0(GetSize,int());
    MOCK_METHOD1(Describe,string(const char* name));
    MOCK_METHOD1(f,void(int));
    MOCK_METHOD1(Describe,string(int type));
    MOCK_METHOD2(Process,bool(Bar elem,int count));
};

template <typename Elem>
class StackInterface {
    public:
    virtual ~StackInterface();
    virtual int GetSize() const = 0;
    virtual void Push(const Elem& x) =0;
};

template <typename Elem>
class MockStack : public StackInterface<Elem> {
    public:
    MOCK_CONST_METHOD0_T(GetSize,int());
    MOCK_METHOD1_T(Push,void(const Elem& x));
};

using ::testing::Return;
using ::testing::Le;
using ::testing::Ge;
using ::testing::AtLeast;

string TestFunc(Foo *pfoo) {
    string str;
    for (int i = 0;i < 3;i++) {
        str = pfoo->Describe(i == 3?6:5);
        cout << "str = " << str << endl;
    }
    int s = pfoo->GetSize();
    cout << "SIZE = " << s << endl;
    //cout << "SIZE = " << pfoo->GetSize() << endl;

    //pfoo->f(4); // will cause to fail Ge(5)
    pfoo->f(5); 
    pfoo->f(6); 

    return "good";
}

TEST(BarTest, DoesThis) {
    MockFoo foo;

    ON_CALL(foo,GetSize())
        .WillByDefault(Return(1));

    EXPECT_CALL(foo,f(Ge(5)))
        .Times(AtLeast(1));

    EXPECT_CALL(foo,Describe(5))
        .Times(3)
        .WillRepeatedly(Return("Category 5"));

    EXPECT_EQ("good",TestFunc(&foo));
}

int main(int argc, char*argv[]) {
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
