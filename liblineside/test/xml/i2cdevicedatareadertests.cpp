#include <boost/test/unit_test.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "xmlutils.hpp"

#include "tendril/devices/device.hpp"
#include "lineside/xml/xercesguard.hpp"
#include "lineside/xml/utilities.hpp"

#include "lineside/xml/i2cdevicedatareader.hpp"

// ==============

const std::string i2cdevicedataFragment = "i2cdevice-fragment.xml";

class SomeI2CDevice : public Tendril::Devices::Device,
		      public Tendril::HardwareProvider<Tendril::BinaryOutputPin> {
public:
  SomeI2CDevice(const std::string name,
		const Tendril::SettingsMap& settings,
		std::unique_ptr<Tendril::I2CCommunicator>& i2cComms)
    :
    Device(name),
    HardwareProvider(),
    settings(settings),
    i2cComms(i2cComms.get()) {}

  virtual void Register(Tendril::HardwareManager& hwmanager) override {
    auto ptr = this->shared_from_this();
    auto ptrSomeI2CDevice = std::dynamic_pointer_cast<SomeI2CDevice>(ptr);
    hwmanager.bopProviderRegistrar.Register(this->name, ptrSomeI2CDevice);
  }
  
  virtual
  std::unique_ptr<Tendril::BinaryOutputPin>
  GetHardware(const std::string& hardwareId,
	      const Tendril::SettingsMap& settings) override {
    std::stringstream msg;
    msg << __FUNCTION__ << ": Not implemented. ";
    msg << hardwareId << " " << settings.size();
    throw std::logic_error(msg.str());
  }
  
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
  
  auto deviceElement = Lineside::xml::GetSingleElementByName(rootElement, "SomeI2CDevice" );
  BOOST_REQUIRE( deviceElement );
  
  Lineside::xml::I2CDeviceDataReader<SomeI2CDevice> reader("SomeI2CDevice");
  BOOST_REQUIRE( !reader.CheckReadableElement(rootElement) );
  BOOST_REQUIRE( reader.CheckReadableElement(deviceElement) );

  auto result = reader.Read(deviceElement);
  BOOST_REQUIRE( result );
  auto i2cDevData = std::dynamic_pointer_cast<Tendril::Devices::I2CDeviceData<SomeI2CDevice>>(result);
  BOOST_REQUIRE( result );

  BOOST_CHECK_EQUAL( i2cDevData->name, "dev1" );
  BOOST_CHECK_EQUAL( i2cDevData->i2cCommsRequest.providerName, "1" );
  BOOST_CHECK_EQUAL( i2cDevData->i2cCommsRequest.idOnProvider, "0x10" );
  BOOST_CHECK_EQUAL( i2cDevData->i2cCommsRequest.settings.size(), 0 );
  BOOST_REQUIRE_EQUAL( i2cDevData->settings.size(), 2 );
  BOOST_CHECK_EQUAL( i2cDevData->settings.at("A"), "B" );
  BOOST_CHECK_EQUAL( i2cDevData->settings.at("1"), "2" );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
