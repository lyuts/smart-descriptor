#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>

#include <iostream>

int main(int /*argc*/, char /**argv*/[])
{
    CppUnit::TestRunner runner;

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    runner.addTest(registry.makeTest());

    CppUnit::TestResult controller;
    CppUnit::TestResultCollector result;
    controller.addListener(&result);

    runner.run(controller);

    CppUnit::CompilerOutputter outputter(&result, std::cerr);
    outputter.write();

    /** STATS **/
    int numErrors = result.testErrors();
    int numFailures = result.testFailures();
    int numFailuresTotal = result.testFailuresTotal();
    int numTests = result.runTests();

    std::cout << "=============================================" << std::endl;
    std::cout << " STATISTICS" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Number of errors (uncaught exception):  " << numErrors << std::endl;
    std::cout << "Number of failures (failed assertions): " << numFailures << std::endl;
    std::cout << "Total number of detected failures:      " << numFailuresTotal << std::endl;
    std::cout << "Total number of tests:                  " << numTests << std::endl;
    std::cout << "=============================================" << std::endl;

    return result.wasSuccessful() ? 0 : 1;
}

