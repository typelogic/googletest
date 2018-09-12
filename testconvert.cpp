class ClosureTest : public CppUnit::TestFixture
{
public:
    ClosureTestCallee* fpTestCallee;
    void setUp()
    {
        fpTestCallee = new ClosureTestCallee();
    }
    void tearDown()
    {
        delete fpTestCallee;
    }
    void testClosureWithSingleParameter()
    {
        //...
        CPPUNIT_ASSERT_EQUAL(fExpectedCalls, fCallbackCalled);
    }
    //...
    CPPUNIT_TEST_SUITE( ClosureTest );
    CPPUNIT_TEST( testClosureWithSingleParameter );
    //...
    CPPUNIT_TEST_SUITE_END();
};
CPPUNIT_TEST_SUITE_REGISTRATION(ClosureTest);

///////////////////////////////////
class ClosureTest : public ::testing::Test
{
public:
    ClosureTestCallee* fpTestCallee;
    virtual void SetUp()
    {
        fpTestCallee = new ClosureTestCallee();
    }
    virtual void TearDown()
    {
        delete fpTestCallee;
    }
};

TEST_F(ClosureTest, closureWithSingleParameter) {
    //...
    EXPECT_EQ(fExpectedCalls, fCallbackCalled);
}
