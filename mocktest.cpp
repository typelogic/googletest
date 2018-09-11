#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::DoDefault;

bool gfn() {
    return true;
}

void fn() {
    cout << "fn\n";    
}

void fn2() {
    cout << "fn2\n";    
}

bool fn3() {
    cout << "fn3\n";    
    return true;
}

struct testABC {
    bool dummyLogin(string username,string password) {
        return true;
    }
};

class DataBaseConnect {
public:
    virtual bool login(string username,string password) {
        cout << "THE REAL LOGIN\n";
        return true;
    }
    virtual bool login2(string username,string password) {
        cout << "THE REAL LOGIN\n";
        return true;
    }
    virtual bool logout(string username) { return true;}
    virtual int fetchRecord() { return -1;}
};

class Mock_DataBaseConnect : public DataBaseConnect {
public:
    MOCK_METHOD0(fetchRecord,int());
    MOCK_METHOD1(logout,bool (string username));
    MOCK_METHOD2(login,bool (string username,string password));
    MOCK_METHOD2(login2,bool (string username,string password));
};

class MyDatabase {
    DataBaseConnect &dbC;
public:

    MyDatabase(DataBaseConnect & _dbC): dbC(_dbC) {
        srand(time(nullptr)); 
    }

    int Init(string username,string password) {
        int rvalue = rand() % 2;
        if (rvalue == 0) {
        //if (true) {
            if (dbC.login(username,password) != true) {
                cout << "DB FAILURE\n"; return -1;
            } else {
                cout << "DB SUCCESS\n"; return 1;
            }
        } else {
            return dbC.login2(username,password)?1:-1;
            //return dbC.login2(username,password);
        }
    }
};

class Dx {
public:    
    virtual int f(int n) {
        return 5;
    }
};

class Mock_Dx : public Dx {
public:
    MOCK_METHOD1(f,int(int));
};

class UserOfDx {
public:
    int g(Dx &dx,int n) {
        if (dx.f(n) == 0) {
            return 0;
        } else {
            return 1;
        }
    }
};

struct TMaster {
    void f(){}
    void g(string u,string p){ }
    void h(string u,string p){ }
};

TEST(MockingBird,Hello) {
    Mock_Dx mockdx;
    UserOfDx obj;

    EXPECT_CALL(mockdx,f(_))
    .Times(1)
    .WillOnce(Return(6)); // this controls the behaviour of f

    int retval = obj.g(mockdx,123);
    EXPECT_EQ(retval,1);

}


#if 1
TEST(MyDB,GlobalFunc) {
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb,login("Terminator","I'm Back"))
    .Times(1)
    .WillOnce(DoAll(
        InvokeWithoutArgs(fn),
        InvokeWithoutArgs(fn2),
        Return(true)));

    int retValue = db.Init("Terminator","I'm Back");
    EXPECT_EQ(retValue,1);
}

TEST(MyDB,Default) {
    testABC dbc;
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);

    ON_CALL(mdb,login(_,_)).WillByDefault(Invoke(&dbc,&testABC::dummyLogin));

    EXPECT_CALL(mdb,login("Terminator","I'm Back"))
    .Times(1)
    .WillOnce(DoDefault());

    int retValue = db.Init("Terminator","I'm Back");
    EXPECT_EQ(retValue,1);
}

TEST(MyDB,DoAll) {
    testABC dbc;
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);
    TMaster obj;

    EXPECT_CALL(mdb,login("Terminator","I'm Back"))
    .Times(1)
    .WillOnce(DoAll(
    Invoke(&obj,&TMaster::g), 
    Invoke(&obj,&TMaster::h), 
    InvokeWithoutArgs(fn), 
    InvokeWithoutArgs(fn3) 
    ));

    int retValue = db.Init("Terminator","I'm Back");
    EXPECT_EQ(retValue,1);
}

TEST(MyDBTest,CallOrig) {
    DataBaseConnect dbc;
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb,login("Terminator","I'm Back"))
    .Times(1)
    .WillOnce(Invoke(&dbc,&DataBaseConnect::login));

    int retValue = db.Init("Terminator","I'm Back");
    EXPECT_EQ(retValue,1);
}

TEST(MyDBTest, LoginTest) {
    // arrange
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);

    // so, this directive is controlling the behaviour of login
    // function. Here, it must be called once and will return true
    // This will later, below, affect the flow of db.Init()
    EXPECT_CALL(mdb,login("Terminator","I'm Back"))
    .Times(1)
    .WillOnce(Return(true));

    // act
    int retValue = db.Init("Terminator","I'm Back");

    // Assert
    EXPECT_EQ(retValue,1);
}

TEST(MyDBTest,LoginFailure) {
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb,login(_,_))
    .Times(AtLeast(1))
    .WillOnce(Return(false));

    //act
    int retValue = db.Init("Terminator","I'm Back");

    // assert
    EXPECT_EQ(retValue,-1);
}

TEST(MyDBTest, LoginTest2) {
    // arrange
    Mock_DataBaseConnect mdb;
    MyDatabase db(mdb);

    ON_CALL(mdb,login(_,_)).WillByDefault(Return(true));
    ON_CALL(mdb,login2(_,_)).WillByDefault(Return(true));

    // act
    int retValue = db.Init("Terminator","I'm Back");

    // Assert
    EXPECT_EQ(retValue,1);
}
#endif 

int main(int argc,char *argv[]) {
    int g = true;
    cout << "g = " << g << endl;
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
