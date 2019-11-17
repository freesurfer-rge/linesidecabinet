#include <limits>

#include <boost/test/unit_test.hpp>

#include "itemid.hpp"

BOOST_AUTO_TEST_SUITE(ItemId)

BOOST_AUTO_TEST_CASE(CheckNil)
{
  Lineside::ItemId id = Lineside::ItemId::Nil();

  Lineside::ItemId::IdType val;
  id.Get(&val);

  BOOST_CHECK_EQUAL(val,0);
}

BOOST_AUTO_TEST_CASE(CheckConstruct)
{
  const Lineside::ItemId::IdType anyVal = 12121;

  Lineside::ItemId id(anyVal);

  Lineside::ItemId::IdType result;

  id.Get(&result);
  BOOST_CHECK_EQUAL(result, anyVal);
}

BOOST_AUTO_TEST_CASE(CheckEquality)
{
  const Lineside::ItemId::IdType v0 = 12121;
  const Lineside::ItemId::IdType v1 = 15674123;

  Lineside::ItemId id0(v0), id1(v1), id2(v0);

  BOOST_CHECK( id0 == id2 );
  BOOST_CHECK( id0 != id1 );
}

// ===================================

BOOST_AUTO_TEST_SUITE(Serialisation)

BOOST_AUTO_TEST_CASE(SmokeWithNil)
{
  Lineside::ItemId id = Lineside::ItemId::Nil();

  std::stringstream s;
  s << id;

  std::string expected("00:00:00:00");
  BOOST_CHECK_EQUAL(expected, s.str());
}

BOOST_AUTO_TEST_CASE(SmokeWithOne)
{
  Lineside::ItemId id(1);

  std::stringstream s;
  s << id;

  std::string expected("00:00:00:01");
  BOOST_CHECK_EQUAL(expected, s.str());
}

BOOST_AUTO_TEST_CASE(SmokeWith255)
{
  Lineside::ItemId id(255);

  std::stringstream s;
  s << id;

  std::string expected("00:00:00:ff");
  BOOST_CHECK_EQUAL(expected, s.str());
}

BOOST_AUTO_TEST_CASE(SmokeWithMax)
{
  Lineside::ItemId id(std::numeric_limits<Lineside::ItemId::IdType>::max());

  std::stringstream s;
  s << id;

  std::string expected("ff:ff:ff:ff");
  BOOST_CHECK_EQUAL(expected, s.str());
}

BOOST_AUTO_TEST_CASE(SmokeGoldenValues)
{
  std::map<Lineside::ItemId::IdType,std::string> gv;
  gv[145875] = "00:02:39:d3";
  gv[1234553784] = "49:95:cb:b8";
  gv[4294967295] = "ff:ff:ff:ff";
  gv[4278190081] = "ff:00:00:01";
  gv[2341] = "00:00:09:25";
  gv[12419] = "00:00:30:83";
  gv[345629] = "00:05:46:1d";
  gv[125688] = "00:01:ea:f8";
  gv[445337500] = "1a:8b:4f:9c";
  
  for( auto it=gv.begin(); it !=gv.end(); ++it ) {
    Lineside::ItemId id(it->first);
    
    std::stringstream s;
    s << id;
    
    BOOST_CHECK_EQUAL(it->second, s.str());
  }
}

BOOST_AUTO_TEST_SUITE_END();

// ==========================================

BOOST_AUTO_TEST_SUITE(Deserialisation)

BOOST_AUTO_TEST_CASE(SmokeWithNil)
{
  Lineside::ItemId expected = Lineside::ItemId::Nil();
  std::stringstream src;
  src << "00:00:00:00";
  Lineside::ItemId id;

  src >> id;

  BOOST_CHECK_EQUAL(expected, id);
}

BOOST_AUTO_TEST_CASE(SmokeWithOne)
{
  Lineside::ItemId expected(1);
  std::stringstream src;
  src << "00:00:00:01";
  Lineside::ItemId id;

  src >> id;

  BOOST_CHECK_EQUAL(expected, id);
}

BOOST_AUTO_TEST_CASE(SmokeWith255)
{
  Lineside::ItemId expected(255);
  std::stringstream src;
  src << "00:00:00:ff";
  Lineside::ItemId id;

  src >> id;

  BOOST_CHECK_EQUAL(expected, id);
}

BOOST_AUTO_TEST_CASE(SmokeWith256)
{
  Lineside::ItemId expected(256);
  std::stringstream src;
  src << "00:00:01:00";
  Lineside::ItemId id;

  src >> id;

  BOOST_CHECK_EQUAL(expected, id);
}

BOOST_AUTO_TEST_CASE(SmokeWithMax)
{
  Lineside::ItemId expected(std::numeric_limits<Lineside::ItemId::IdType>::max());
  std::stringstream src;
  src << "ff:ff:ff:ff";
  Lineside::ItemId id;

  src >> id;

  BOOST_CHECK_EQUAL(expected,id);
}

BOOST_AUTO_TEST_CASE(SmokeGoldenValues)
{
  std::map<Lineside::ItemId::IdType,std::string> gv;
  gv[145875] = "00:02:39:d3";
  gv[1234553784] = "49:95:cb:b8";
  gv[4294967295] = "ff:ff:ff:ff";
  gv[4278190081] = "ff:00:00:01";
  gv[2341] = "00:00:09:25";
  gv[12419] = "00:00:30:83";
  gv[345629] = "00:05:46:1d";
  gv[125688] = "00:01:ea:f8";
  gv[445337500] = "1a:8b:4f:9c";
  
  for( auto it=gv.begin(); it !=gv.end(); ++it ) {
    Lineside::ItemId expected(it->first);
    
    std::stringstream s;
    s << it->second;

    Lineside::ItemId id;
    s >> id;
    
    BOOST_CHECK_EQUAL(expected, id);
  }
}

BOOST_AUTO_TEST_SUITE_END();

// ==========================================

BOOST_AUTO_TEST_SUITE(Parse)

BOOST_AUTO_TEST_CASE(SmokeWithNil)
{
  Lineside::ItemId expected = Lineside::ItemId::Nil();
  std::string str = "00:00:00:00";

  Lineside::ItemId target;

  target.Parse(str);

  BOOST_CHECK_EQUAL(expected, target);
}

BOOST_AUTO_TEST_CASE(SmokeWithOne)
{
  Lineside::ItemId expected(1);
  std::string str = "00:00:00:01";

  Lineside::ItemId target;

  target.Parse(str);

  BOOST_CHECK_EQUAL(expected, target);
}

BOOST_AUTO_TEST_CASE(SmokeWith255)
{
  Lineside::ItemId expected(255);
  std::string str = "00:00:00:ff";

  Lineside::ItemId target;

  target.Parse(str);

  BOOST_CHECK_EQUAL(expected, target);
}

BOOST_AUTO_TEST_CASE(SmokeWith256)
{
  Lineside::ItemId expected(256);
  std::string str = "00:00:01:00";

  Lineside::ItemId target;

  target.Parse(str);

  BOOST_CHECK_EQUAL(expected, target);
}

BOOST_AUTO_TEST_CASE(SmokeGoldenValues)
{
  std::map<Lineside::ItemId::IdType,std::string> gv;
  gv[145875] = "00:02:39:d3";
  gv[1234553784] = "49:95:cb:b8";
  gv[4294967295] = "ff:ff:ff:ff";
  gv[4278190081] = "ff:00:00:01";
  gv[2341] = "00:00:09:25";
  gv[12419] = "00:00:30:83";
  gv[345629] = "00:05:46:1d";
  gv[125688] = "00:01:ea:f8";
  gv[445337500] = "1a:8b:4f:9c";
  
  for( auto it=gv.begin(); it !=gv.end(); ++it ) {
    Lineside::ItemId expected(it->first);

    Lineside::ItemId id;
    id.Parse(it->second);
    
    BOOST_CHECK_EQUAL(expected, id);
  }
}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE_END();
