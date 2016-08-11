#ifndef VEC3_H
#define VEC3_H

namespace isat_utils
{


class Vec3
{
   public:

      Vec3() { x = 0.0; y = 0.0; z = 0.0; }
      Vec3(double x, double y, double z) { this->x = x; this->y = y; this->z = z; }

      double x;
      double y;
      double z;
};

}  // namespace isat_utils

#endif // VEC3_h
