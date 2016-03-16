#include "ConfigFactory.h"
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

unordered_map<string, unordered_map<string, string>> ConfigFactory::LoadLayer(string layername)
{
    unordered_map<string, unordered_map<string, string>> map_config;
    unordered_map<string, string> map_attri;
    string str_attri;
    string file_path = FileUtils::getInstance()->fullPathForFilename(CONF_DEFAULT_XML);
    XMLDocument* myDocment = new tinyxml2::XMLDocument();
    myDocment->LoadFile(file_path.c_str());
    
    tinyxml2::XMLElement* rootElement = myDocment->RootElement();
    XMLElement* Element = rootElement->FirstChildElement();
    
    while (Element) { // rootElement; Element-child of root; element-child of Element
        
        if(strcmp(Element->Name(),layername.c_str()) == 0)   // locate the element with layername
        {
            XMLElement* element = Element->FirstChildElement(); // element - background; leftbutton
            
            while(element)
            {
                str_attri = element->Name();                        // e.g background; leftbutton
                
                XMLElement* ele = element->FirstChildElement();
                while(ele)
                {
                    string a, b;
                    a=ele->Name();
                    b=ele->GetText();
                    map_attri[a] = b;
                    ele = ele->NextSiblingElement();
                }
                
                map_config[str_attri] = map_attri;
                element = element->NextSiblingElement();
            }
            
            return map_config;
        }
        Element = Element->NextSiblingElement();
    }
    
    return map_config;
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