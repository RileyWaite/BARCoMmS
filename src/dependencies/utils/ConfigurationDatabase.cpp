#include <string.h>
#include <istream>
#include <fstream>
#include <jansson.h>

#include "isat/utils/ConfigurationDatabase.h"
#include "isat/utils/LogManager.h"


namespace isat_utils
{

ConfigurationDatabase::ConfigurationDatabase()
   : logger("ConfigDatabase")
{
   LogManager& lm = LogManager::getInstance();
   logger.setLog(lm.getDefaultLog());
}

ConfigurationDatabase::~ConfigurationDatabase()
{
}

ConfigurationDatabase&
ConfigurationDatabase::getInstance()
{
   static ConfigurationDatabase instance;

   return instance;
}

bool
ConfigurationDatabase::parseConfig(json_t* jsonobj)
{
   // Get the "parameters" array.
   json_t *paramArray = json_object_get(jsonobj, "parameters");
   if (paramArray == 0)
      return false;

   int numParams = json_array_size(paramArray);
   for (int i = 0; i < numParams; i++)
   {
      json_t *element   = json_array_get(paramArray, i);
      json_t *name      = json_object_get(element, "name");
      json_t *paramType = json_object_get(element, "type");
      json_t *value     = json_object_get(element, "value");
      //      json_t *descrip   = json_object_get(element, "description");

      if ((name == 0) || (paramType == 0) || (value == 0))
      {
         cout << "What?!?!? null?\n";
         // XXX: log it
         continue;
      }


      ConfDBRecord rec;
      rec.paramName = json_string_value(name);

      String typestr = json_string_value(paramType);
      if (typestr == "bool")
      {
         rec.paramType = ConfDBRecord::BOOL;
         rec.bool_val   = json_is_true(value);
      }
      else if (typestr == "int")
      {
         rec.paramType = ConfDBRecord::INT;
         rec.int_val    = json_integer_value(value);         
      }
      else if (typestr == "real")
      {
         rec.paramType = ConfDBRecord::REAL;
         rec.real_val   = json_real_value(value);
      }
      else if (typestr == "string")
      {
         rec.paramType = ConfDBRecord::STRING;
         rec.string_val = json_string_value(value);         
      }
      else if (typestr == "hex")
      {
         // JSON doesn't support hex literals, so it's really a string literal. We have to convert it.
         rec.paramType = ConfDBRecord::INT;
         String hexLiteral = json_string_value(value);
         long hexval = 0;
         if (hexLiteral.parseHex(hexval))
            rec.int_val = hexval;
         else
            // XXX: Log it
            cout << "Error parsing hex constant '" << hexLiteral << "' in ConfigurationDatabase::parseConfig()." << endl;
      }
      else
      {
         // XXX: Log it
         cout << "Unknown type '" << typestr << "' for parameter '"
              << rec.paramName << "'\n";
      }

      symboltable.add(rec);
   }

   return true;
}

   
bool
ConfigurationDatabase::findParam(String paramName, int& index) const
{
   // XXX: Yes, this sucks. It sucks out loud. It sucks on ice.
   // XXX: What I really want to do is use a map<> but we currently CAN NOT
   // XXX: because the coding standard prevents the use of STL (because it throws
   // XXX: exceptions.) So, this is here until I code something faster.

   bool found = false;
   int i = 0;
   while (!found && (i < symboltable.size()))
   {
      ConfDBRecord rec;
      symboltable.get(i, rec);

      if (rec.paramName == paramName)
         found = true;
      else
         i++;
   }

   if (found)
      index = i;

   return found;
}
   

bool
ConfigurationDatabase::load(File configPath)
{
   if (!configPath.exists())
   {
      logger.error("Config path '" + std::string(configPath.getName().c_str()) + "' does not exist.");
      return false;
   }

   if (!configPath.isDirectory())
   {
      logger.error("ConfigurationDatabase::load - Config path '" +
                   std::string(configPath.getName().c_str()) + "' is not a directory.");
      return false;
   }

   ArrayList<String> entries = configPath.list();
   for (int i = 0; i < entries.size(); i++)
   {
      String entry;
      entries.get(i, entry);
      if (entry.matches(".*\\.cfg$"))
      {
         String cfgfile = configPath.getName() + "/" + entry;

         json_error_t jerror;
         json_t *jobj = json_load_file(cfgfile.c_str(), 0, &jerror);

         if (jobj != 0)
         {
            String debugmsg;
            debugmsg = debugmsg + "Loaded config file '";
            debugmsg = debugmsg + cfgfile + "'";
            logger.debug(std::string(debugmsg.c_str()));
            parseConfig(jobj);
         }
         else
         {
            String errormsg = errormsg + "Error: '" + jerror.text + String::format("' line: %d",jerror.line);
            errormsg = errormsg + String::format("   column: %d", jerror.column);
            logger.error(std::string(errormsg.c_str()));
         }
      }

   }
   return true;
}


bool
ConfigurationDatabase::exists(String paramName) const
{
   int index;
   return findParam(paramName, index);
}

bool
ConfigurationDatabase::getBool(String paramName, bool defaultValue) const
{
   int index;
   if (!findParam(paramName, index))
      return defaultValue;

   ConfDBRecord rec;
   symboltable.get(index, rec);

   if (rec.paramType != ConfDBRecord::BOOL)
      logger.error("Requested bool parameter '" +
                   std::string(paramName.c_str()) + "' is not of type bool in config database.");

   return rec.bool_val;
}
   

long
ConfigurationDatabase::getInt(String paramName, long defaultValue) const 
{
   int index;
   if (!findParam(paramName, index))
      return defaultValue;

   ConfDBRecord rec;
   symboltable.get(index, rec);

   if (rec.paramType != ConfDBRecord::INT)
      logger.error("Requested int parameter '" + std::string(paramName.c_str())
                   + "' is not of type int in config database.");

   return rec.int_val;      
}

double
ConfigurationDatabase::getReal(String paramName, double defaultValue) const
{
   int index;
   if (!findParam(paramName, index))
      return defaultValue;

   ConfDBRecord rec;
   symboltable.get(index, rec);

   if (rec.paramType != ConfDBRecord::REAL)
      logger.error("Requested real parameter '" + std::string(paramName.c_str()) + "' is not of type real in config database.");
   
   return rec.real_val;         
}

String
ConfigurationDatabase::getString(String paramName, String defaultValue) const
{
   int index;
   if (!findParam(paramName, index))
      return defaultValue;

   ConfDBRecord rec;
   symboltable.get(index, rec);

   if (rec.paramType != ConfDBRecord::STRING)
      logger.error("Requested string parameter '" + std::string(paramName.c_str()) + "' is not of type string in config database.");
   
   return rec.string_val;            
}


void
ConfigurationDatabase::setBool(String paramName, bool value)
{
   ConfDBRecord rec;   
   rec.paramName = paramName;
   rec.paramType = ConfDBRecord::BOOL;
   rec.bool_val = value;
   
   int index = 0;
   if (findParam(paramName, index))
      symboltable.put(index, rec);
   else
      symboltable.add(rec);
}

void
ConfigurationDatabase::setInt(String paramName, long value)
{
   ConfDBRecord rec;   
   rec.paramName = paramName;
   rec.paramType = ConfDBRecord::INT;
   rec.int_val = value;
   
   int index = 0;
   if (findParam(paramName, index))
      symboltable.put(index, rec);
   else
      symboltable.add(rec);   
}

void
ConfigurationDatabase::setReal(String paramName, double value)
{
   ConfDBRecord rec;   
   rec.paramName = paramName;
   rec.paramType = ConfDBRecord::REAL;
   rec.real_val = value;
   
   int index = 0;
   if (findParam(paramName, index))
      symboltable.put(index, rec);
   else
      symboltable.add(rec);   
}

void
ConfigurationDatabase::setString(String paramName, String value)
{
   ConfDBRecord rec;   
   rec.paramName = paramName;
   rec.paramType = ConfDBRecord::STRING;
   rec.string_val = value;
      
   int index = 0;
   if (findParam(paramName, index))
      symboltable.put(index, rec);
   else
      symboltable.add(rec);   
}

ArrayList<String>
ConfigurationDatabase::getParamNames() const
{
   ArrayList<String> names;
   for (int i = 0; i < symboltable.size(); i++)
   {
      ConfDBRecord currec;
      symboltable.get(i, currec);

      names.add(currec.paramName);
   }

   return names;
}

} // namespace isat_utils

