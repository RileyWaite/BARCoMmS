
#ifndef CONFIGURATIONDATABASE_H
#define CONFIGURATIONDATABASE_H

#include "jansson.h"
#include "../dependencies/utils/File.h"
#include "../dependencies/utils/String.h"
#include "../dependencies/utils/ArrayList.h"
#include "../dependencies/utils/ConfDBRecord.h"
#include "../dependencies/utils/Logger.h"

namespace isat_utils
{

   /**
    * The ConfigurationDatabase provides access to the contents of the
    * configuration files in the config/ directory.
    *
    * The load method should be called once to initialize the
    * database, passing the location of the config/ directory. All
    * configuration files with extension ".cfg" are passed to a lua
    * interpreter instance for parsing / execution.
    */
   class ConfigurationDatabase
   {
      public:

         static ConfigurationDatabase& getInstance();
      

         /**
          * Load all configuration files located in directory configPath.
          * @return true if load was successful.
          */
         bool load(File configDirectory);


         /**
          * Determine if a parameter has a value in the database.
          * @return true if parameter exists.
          */
         bool exists(String paramName) const;

         bool getBool(String paramName, bool defaultValue = false) const;
         long  getInt(String paramName, long defaultValue = 0) const;
         double getReal(String paramName,  double defaultValue = 0.0f) const;

         /**
          * Get a string value from the configuration database.
          * Callers should not free the returned pointer, the memory is managed by ConfigurationDatabase.
          *
          * @return 
          */
          
         String getString(String paramName, String defaultValue = "") const;


         void setBool(String paramName, bool value);
         void setInt(String paramName, long value);
         void setReal(String paramName, double value);
         void setString(String paramName, String value);
         
         ArrayList<String> getParamNames() const;


      protected:

         ConfigurationDatabase();
         ~ConfigurationDatabase();

         bool parseConfig(json_t* jsonobj);

         bool findParam(String paramName, int& index) const;
         
         ArrayList<ConfDBRecord> symboltable;

         mutable Logger logger;
         
   };
} // namespace isat_utils   


#endif  // STRING_H
