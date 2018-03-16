// Example from www.musicdsp.org
// by zioguido@gmail.com
class CParamSmooth
{
public:
    CParamSmooth() { a = 0.99f; b = 1.f - a; z = 0; };
//    ~CParamSmooth();
    inline float Process(float in) { z = (in * b) + (z * a); return z; }
private:
    float a, b, z;
};

