#include <iomanip>
#include <sstream>

#include <boost/endian/arithmetic.hpp>

#include "itemid.hpp"

namespace Lineside {
  const size_t fieldWidth = 2;
  const char delim = ':';
  
  void puthex(std::ostream& os, const uint8_t v) {
    os << std::hex << std::setfill('0') << std::setw(fieldWidth);
    // Need the following cast to make get neat output
    os << static_cast<uint16_t>(v);
  }

  void extractdelim(std::istream& is) {
    char c;

    is.get(c);
    if( c != delim ) {
      throw std::runtime_error("Did not find expected delimiter in ItemId");
    }
  }
  
  std::ostream& operator<<(std::ostream& os, const Lineside::ItemId& item) {
    Lineside::ItemId::IdType tmp;
    item.Get(&tmp);

    // We want to serialise with big-endian order
    boost::endian::big_uint32_t beId(tmp);
    
    uint8_t *elements = reinterpret_cast<uint8_t*>(&beId);

    puthex(os, elements[0]);
    os << delim;
    puthex(os, elements[1]);
    os << delim;
    puthex(os, elements[2]);
    os << delim;
    puthex(os, elements[3]);
    
    return os;
  }

  std::istream& operator>>(std::istream& is, Lineside::ItemId& item) {
    char raw[fieldWidth];
    std::string str;
    
    is.read(raw, fieldWidth);
    str.append(raw, fieldWidth);
    extractdelim(is);
    is.read(raw, fieldWidth);
    str.append(raw, fieldWidth);
    extractdelim(is);
    is.read(raw, fieldWidth);
    str.append(raw, fieldWidth);
    extractdelim(is);
    is.read(raw, fieldWidth);
    str.append(raw, fieldWidth);
    
    Lineside::ItemId::IdType val = std::stoull(str,NULL,16);
    item.Set(val);

    return is;
  }

  void ItemId::Parse(std::string str) {
    if( str.size() != (4*fieldWidth)+(3*1) ) {
      throw std::invalid_argument("str has incorrect length");
    }

    // Remove the delimiters (from end for ease of indexing)
    for( unsigned int delimPos : {8, 5, 2} ) {
      if( str.at(delimPos) != delim ) {
	throw std::invalid_argument("str does not contain correct ':' delimiters");
      }

      str.erase(delimPos,1);
    }

    Lineside::ItemId::IdType val = std::stoull(str,NULL,16);
    this->Set(val);
  }

  std::string ItemId::ToString() const {
    std::stringstream s;
    s << (*this);
    return s.str();
  }
}
