#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "tendril/devices/device.hpp"
#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/i2cdevicedatareader.hpp"

// ==============

const std::string i2cdevicedataFragment = "i2cdevice-fragment.xml";

class SomeI2CDevice : public Tendril::Devices::Device {
public:
  SomeI2CDevice(const std::string name,
		const Tendril::SettingsMap& settings,
		std::unique_ptr<Tendril::I2CCommunicator>& i2cComms)
    :
    Device(name),
    settings(settings),
    i2cComms(i2cComms.get()) {}

  Tendril::SettingsMap settings;
  std::unique_ptr<Tendril::I2CCommunicator> i2cComms;
};

// ==============

BOOST_AUTO_TEST_SUITE( xml )

BOOST_AUTO_TEST_SUITE( I2CDeviceDataReader )

BOOST_AUTO_TEST_CASE( SmokeReader )
{
  Lineside::xml::XercesGuard xg;
  auto parser = GetParser();

  auto rootElement = GetRootElementOfFile(parser, i2cdevicedataFragment);
  BOOST_REQUIRE(rootElement);
  
  Lineside::xml::I2CDeviceDataReader<SomeI2CDevice> reader;
#if 0
  BOOST_REQUIRE( reader.HasI2CDevice(rootElement) );
  BOOST_CHECK( !reader.IsI2CDeviceElement(rootElement) );
  auto i2cDeviceElement = reader.GetI2CDeviceElement(rootElement);
  BOOST_CHECK( reader.IsI2CDeviceElement( i2cDeviceElement ) );
  auto result = reader.Read(i2cDeviceElement);
  BOOST_CHECK_EQUAL( result.kind, "devKind" );
  BOOST_CHECK_EQUAL( result.bus, 1 );
  BOOST_CHECK_EQUAL( result.address, 0x10 );
  BOOST_CHECK_EQUAL( result.name, "dev1" );
  BOOST_REQUIRE_EQUAL( result.settings.size(), 2 );
  BOOST_CHECK_EQUAL( result.settings.at("A"), "B" );
  BOOST_CHECK_EQUAL( result.settings.at("1"), "2" );
#endif
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
