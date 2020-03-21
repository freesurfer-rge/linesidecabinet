#include <memory>

#include <xercesc/parsers/XercesDOMParser.hpp>

std::shared_ptr<xercesc::XercesDOMParser> GetParser();


xercesc::DOMElement* GetRootElementOfFile(std::shared_ptr<xercesc::XercesDOMParser> parser,
					  const std::string filename);
