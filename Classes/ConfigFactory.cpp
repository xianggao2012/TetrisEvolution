#include "ConfigFactory.h"
#include "TEHeader.h"
#include "cocos-ext.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;


USING_NS_CC;

ConfigFactory* ConfigFactory::p_ConfigFactory = NULL;

// one-time initialize.
ConfigFactory::ConfigFactory()
{

}

ConfigFactory::~ConfigFactory()
{
//    if(p_ConfigFactory) delete p_ConfigFactory;
}

ConfigFactory* ConfigFactory::getInstance()
{

    if(p_ConfigFactory == NULL)
    {
        p_ConfigFactory = new ConfigFactory();
    }
    return p_ConfigFactory;
}
bool ConfigFactory::LoadScene()
{
    string file_path = FileUtils::getInstance()->fullPathForFilename(CONF_DEFAULT_XML);
    XMLDocument* myDocment = new tinyxml2::XMLDocument();
    myDocment->LoadFile(file_path.c_str());

    tinyxml2::XMLElement* rootElement = myDocment->RootElement();
    XMLElement* Element = rootElement->FirstChildElement();

    while (Element) {

        XMLElement* element = Element->FirstChildElement();

        if(strcmp(element->GetText(),"scene") == 0)
        {
            // read according to scene's format in XML
            element = element->NextSiblingElement();
            a[0] = element->GetText();
            element = element->NextSiblingElement();
            a[1] = element->GetText();

//            while (element) {
//                log("信息 : %s",element->GetText());
//                element = element->NextSiblingElement();
//            }
        }
        Element = Element->NextSiblingElement();

    }

    return true;
}