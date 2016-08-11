#ifndef CONFDBRECORD_H
#define CONFDBRECORD_H

namespace isat_utils
{

struct ConfDBRecord
{
   public:
      
      enum ParamType { BOOL, INT, REAL, STRING };

      
      String paramName;
      ParamType paramType;
      String description;

      bool bool_val;
      long  int_val;
      double real_val;
      String string_val;
};

} // namespace isat_utils;


#endif // CONFDBRECORD_H
