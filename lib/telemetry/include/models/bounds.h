#ifndef BOUNDS_H
#define BOUNDS_H

namespace gt {
    class Bounds {
        public:
            Bounds() = default;
            Bounds(float min, float max);
            ~Bounds() = default;
            float min() { return _min; }
            float max() { return _max; }

            Bounds& operator=(const Bounds& other) {
                if(&other == this) { return *this; }
                if(_min != other._min) { _min = other._min; }
                if(_max != other._max) { _max = other._max; }
                return *this;
            }

        private: 
           float _min;
           float _max; 
    };
}

#endif