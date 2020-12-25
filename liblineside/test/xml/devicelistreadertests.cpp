#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "tendril/devices/i2cdevicedata.hpp"
#include "tendril/devices/pca9685.hpp"
#include "tendril/devices/directdrivesn74x595data.hpp"

#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/devicelistreader.hpp"

// ==============

const std::string i2cdevicelistFragment = "devicelist-fragment.xml";

// ==============

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( DeviceListReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, i2cdevicelistFragment);
  BOOST_REQUIRE(rootElement);

  Lineside::xml::DeviceListReader reader;
  BOOST_REQUIRE( reader.HasDeviceList(rootElement) );
  auto deviceListElement = reader.GetDeviceListElement(rootElement);
  auto result = reader.Read(deviceListElement);
  BOOST_REQUIRE_EQUAL( result.size(), 2 );

  auto dev0 = result.at(0);
  BOOST_CHECK_EQUAL( dev0->name, "MyPCA9685" );
  auto pca9685data = std::dynamic_pointer_cast<Tendril::Devices::I2CDeviceData<Tendril::Devices::PCA9685>>(dev0);
  BOOST_REQUIRE(pca9685data);
  BOOST_CHECK_EQUAL( pca9685data->i2cCommsRequest.providerName, "1" );
  BOOST_CHECK_EQUAL( pca9685data->i2cCommsRequest.idOnProvider, "0x30" );
  BOOST_REQUIRE_EQUAL( pca9685data->settings.size(), 1 );
  BOOST_CHECK_EQUAL( pca9685data->settings.at("pwmFrequency"), "60" );

  auto dev1 = result.at(1);
  BOOST_CHECK_EQUAL( dev1->name, "MyShifter" );
  auto dd595data = std::dynamic_pointer_cast<Tendril::Devices::DirectDriveSN74x595Data>(dev1);
  BOOST_REQUIRE( dd595data );
  BOOST_CHECK_EQUAL( dd595data->clockPin.providerName, "GPIO1" );
  BOOST_CHECK_EQUAL( dd595data->clockPin.idOnProvider, "01" );
  BOOST_CHECK_EQUAL( dd595data->latchPin.providerName, "GPIO02" );
  BOOST_CHECK_EQUAL( dd595data->latchPin.idOnProvider, "002" );
  BOOST_CHECK_EQUAL( dd595data->dataPin.providerName, "GPIO03" );
  BOOST_CHECK_EQUAL( dd595data->dataPin.idOnProvider, "003" );
  BOOST_CHECK_EQUAL( dd595data->clearPin.providerName, "GPIO04" );
  BOOST_CHECK_EQUAL( dd595data->clearPin.idOnProvider, "004" );
  BOOST_CHECK_EQUAL( dd595data->enablePin.providerName, "GPIO05" );
  BOOST_CHECK_EQUAL( dd595data->enablePin.idOnProvider, "005" );
  BOOST_REQUIRE_EQUAL( dd595data->settings.size(), 1 );
  BOOST_CHECK_EQUAL( dd595data->settings.at("chainLength"), "2" );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
