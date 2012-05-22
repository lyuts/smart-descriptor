#include <cppunit/extensions/HelperMacros.h>

#include <LuaDescriptor.h>

class LuaDescriptorTestSuite : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( LuaDescriptorTestSuite );

    CPPUNIT_TEST( openTest1 );
    CPPUNIT_TEST( execFunctionTest1 );

    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

    protected:
        void openTest1();
        void execFunctionTest1();

};

CPPUNIT_TEST_SUITE_REGISTRATION( LuaDescriptorTestSuite );

