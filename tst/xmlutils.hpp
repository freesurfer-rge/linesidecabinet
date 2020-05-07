#include <memory>
#include <string>

#include <xercesc/parsers/XercesDOMParser.hpp>

std::string GetPathToSampleXML( const std::string filename );

std::shared_ptr<xercesc::XercesDOMParser> GetParser();


xercesc::DOMElement* GetRootElementOfFile(std::shared_ptr<xercesc::XercesDOMParser> parser,
					  const std::string filename);
