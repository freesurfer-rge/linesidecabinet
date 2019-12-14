#pragma once

#include <functional>
#include <string>
#include <sstream>

#include <boost/test/unit_test.hpp>

template<typename T>
std::function<bool(const T&)> GetExceptionMessageChecker( std::string expected ) {
  return [=]( const T& e ) {
    std::stringstream stream;
    stream << "Exception Message: " << e.what() << std::endl;
    stream << "         Expected: " << expected << std::endl;
    BOOST_TEST_INFO(stream.str());
    return expected == e.what();
  };
}
