
#ifndef FILE_H
#define FILE_H

#include "isat/utils/ArrayList.h"
#include "isat/utils/String.h"


namespace isat_utils
{


/**
 * Operations on a file or directory.
 *
 * Inspired by Java's File class, this class provides common
 * operations on files and directories. Any additional operations
 * added should be named the same (and as much as possible, act the
 * same) as the Java File class.
 */
class File
{
   public:

      File();

      /**
       * Creates a File instance from the given path name.
       */
      File(String name);

      File(File const& rhs);

      File& operator=(File rhs);
      
      /**
       * Returns the path name represented by this instance.
       *
       * @return the path name of the instance.
       */
      String getName() const;

      /**
       * Determine if the file or directory represented by path name exists.
       *
       * @return true if the pathname exists.
       */
      bool exists() const;
      

      /**
       * Determine if the path name in this instance is a file.
       *
       * @return true if the path name is a file.
       */
      bool isFile() const;

      /**
       * Determine if the path name in this instance is a directory.
       *
       * @return true if the path name is a directory.
       */
      bool isDirectory() const;

      /**
       * Determine the length of the file specified by this instance's path name.
       *
       * @return The length of the file in bytes. Returns 0 if the
       * file is unreadable or if it's not a file. This is not what
       * you'd want, but we can't throw an exception for an error, so
       * make sure the file exists and is a file before you ask for
       * the length. :)
       */
      long length() const;
      

      /**
       * Get the atime for this instance.
       *
       * @return The last access time in seconds from the unix epoch.
       */
      long lastAccessTime() const;


      /**
       * Get the mtime for this instance.
       *
       * @return The last data modification time in seconds from the unix epoch.
       */      
      long lastDataModificationTime() const;


      /**
       * Get the ctime for this instance.
       *
       * @return The last status change time in seconds from the unix epoch.
       */      
      long lastStatusChangeTime() const;
      
      /**
       * If this instance is a directory, return a list of files and directories
       * contained within it.
       *
       * @return a list of files and directories, or a zero length list if this instance is not a directory.
       */
      ArrayList<String> list() const;

      
   private:

      String pathName;
      
};

} // namespace isat_utils
      
#endif // FILE_H
