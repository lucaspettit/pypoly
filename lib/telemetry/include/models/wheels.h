#ifndef WHEELS_H
#define WHEELS_H

namespace gt {
    class Wheels {
        public:
            Wheels() = default;
            Wheels(float fl, float fr, float rl, float rr);
            ~Wheels() = default;
            float frontLeft() { return _frontLeft; }
            float frontRight() { return _frontRight; }
            float rearLeft() { return _rearLeft; }
            float rearRight() { return _rearRight; }

            Wheels& operator=(const Wheels& other) {
                if(&other == this) { return *this; }
                if(_frontLeft != other._frontLeft) { _frontLeft = other._frontLeft; }
                if(_frontRight != other._frontRight) { _frontRight = other._frontRight; }
                if(_rearLeft != other._rearLeft) { _rearLeft = other._rearLeft; }
                if(_rearRight != other._rearRight) { _rearRight = other._rearRight; }
                return *this;
            } 

        private:
            float _frontLeft;
            float _frontRight;
            float _rearLeft;
            float _rearRight;
    };
}

#endif