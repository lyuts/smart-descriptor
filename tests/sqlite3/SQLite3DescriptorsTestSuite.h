#include <cppunit/extensions/HelperMacros.h>

#include <SQLite3Descriptors.h>

class SQLite3DescriptorsTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SQLite3DescriptorsTestSuite );

    CPPUNIT_TEST( openTest1 );

    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

    protected:
        void openTest1();

};

CPPUNIT_TEST_SUITE_REGISTRATION( SQLite3DescriptorsTestSuite );

