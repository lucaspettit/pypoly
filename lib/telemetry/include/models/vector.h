#ifndef MDL_VECTOR_H
#define MDL_VECTOR_H

namespace gt {
    class Vector {
        public:
            Vector() = default;
            Vector(float x, float y, float z);
            ~Vector() = default;
            float x() { return _x; }
            float y() { return _y; }
            float z() { return _z; }

            Vector& operator=(const Vector& other) {
                if(&other == this) { return *this; }
                if(_x != other._x) { _x = other._x; }
                if(_y != other._y) { _y = other._y; }
                if(_z != other._z) { _z = other._z; }
                return *this;
            }

        private:
            float _x;
            float _y;
            float _z;
            
    };
}

#endif