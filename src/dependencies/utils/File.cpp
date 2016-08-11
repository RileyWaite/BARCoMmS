
#include <dirent.h>
#include <sys/stat.h>
#include "isat/utils/File.h"


namespace isat_utils
{

   File::File()
   {
   }

   
   File::File(String name)
   {
      pathName = name;
   }

   File::File(File const& rhs)
   {
      pathName = rhs.pathName;
   }
   

   File&
   File::operator=(File rhs)
   {
      pathName = rhs.pathName;
      return *this;
   }

   
   String
   File::getName() const
   {
      return pathName;
   }


   bool
   File::exists() const
   {
      struct stat info;
      return stat(pathName.c_str(), &info) == 0;
   }

   bool
   File::isFile() const
   {
      struct stat info;
      if (stat(pathName.c_str(), &info) == 0)
         return S_ISREG(info.st_mode);

      return false;
   }
   

   bool
   File::isDirectory() const
   {
      struct stat info;
      if (stat(pathName.c_str(), &info) == 0)
         return S_ISDIR(info.st_mode);

      return false;
   }


   long
   File::length() const
   {
      struct stat info;
      if (!stat(pathName.c_str(), &info) == 0)
         return 0;

      if (!S_ISREG(info.st_mode)) // Is it a file?
         return 0;  // Nope, so zero.

      return info.st_size;
   }


   long
   File::lastAccessTime() const
   {
      struct stat info;
      if (!stat(pathName.c_str(), &info) == 0)
         return 0;

      return info.st_atime;
   }


   long
   File::lastDataModificationTime() const
   {
      struct stat info;
      if (!stat(pathName.c_str(), &info) == 0)
         return 0;

      return info.st_mtime;      
   }

   
   long
   File::lastStatusChangeTime() const
   {
      struct stat info;
      if (!stat(pathName.c_str(), &info) == 0)
         return 0;

      return info.st_ctime;            
   }
   
   
   ArrayList<String>
   File::list() const
   {
      ArrayList<String> entries;
      
      // Try to open the directory
      DIR *dirptr = opendir(pathName.c_str());
      if (dirptr == 0)
         return entries;

      // loop through the directory entries, adding to the array list.
      struct dirent *dptr = readdir(dirptr);
      while (dptr != 0)
      {
         entries.add(String(dptr->d_name));
         dptr = readdir(dirptr);         
      }
      closedir(dirptr);

      return entries;
   }
      
   
}  // namespace isat_utilsp
