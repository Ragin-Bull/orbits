#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

class Vector2D {
public:
    float x, y;

    // Default constructor — no parameters
    Vector2D(){
        this->x=0;
        this->y=0;
    }

    Vector2D(const float x, const float y){
        this->x = x;
        this->y = y;
    }

    Vector2D operator+(const Vector2D &a) const {
        return Vector2D(x + a.x, y + a.y);
    }
    
    Vector2D operator-(const Vector2D &a) const {
        return Vector2D(x - a.x, y - a.y);
    }

    Vector2D &operator+=(const Vector2D &a){
        this->x += a.x;
        this->y += a.y;
        return *this;
    }

    Vector2D &operator-=(const Vector2D &a){
        this->x -= a.x;
        this->y -= a.y;
        return *this;
    }

    Vector2D operator*(float a) const {
        return Vector2D(x * a, y * a);
    }

    Vector2D operator/(float a) const {
        if(a==0)
            throw std::invalid_argument("Division by zero");
        return Vector2D(x / a, y / a);
    }

    friend Vector2D operator*(float a, const Vector2D& b) {
        return b * a;
    }

    Vector2D &operator*=(float a){
        this->x *= a;
        this->y *= a;
        return *this;
    }

    Vector2D &operator/=(float a){
        if(a==0)
            throw std::invalid_argument("Division by zero");
        this->x /= a;
        this->y /= a;
        return *this;
    }

    float dotProduct(const Vector2D &a) const {
        return (this->x)*a.x + (this->y)*a.y;
    }

    float magnitudeSqr() const {
        float xV = this->x;
        float yV = this->y;
        return (xV*xV + yV*yV);
    }

    float magnitude() const {
        return std::sqrt(this->magnitudeSqr());
    }

    Vector2D normalize() const {
        return (*this)/this->magnitude();
    }

};

void printVector(const std::string &label, const Vector2D &v) {
    std::cout << label << " = (" << v.x << ", " << v.y << ")\n";
}
 
bool nearlyEqual(float a, float b, float epsilon = 0.0001f) {
    return std::abs(a - b) < epsilon;
}

int main() {
    Vector2D A(3, 4);
    Vector2D B(1, 2);
    float s = 2;
 
    std::cout << "--- Basic operations ---\n";
 
    Vector2D r1 = A + B;
    printVector("A + B", r1);
    assert(nearlyEqual(r1.x, 4) && nearlyEqual(r1.y, 6));
 
    Vector2D r2 = A - B;
    printVector("A - B", r2);
    assert(nearlyEqual(r2.x, 2) && nearlyEqual(r2.y, 2));
 
    Vector2D r3 = B - A;
    printVector("B - A", r3);
    assert(nearlyEqual(r3.x, -2) && nearlyEqual(r3.y, -2));
 
    Vector2D r4 = A * s;
    printVector("A * s", r4);
    assert(nearlyEqual(r4.x, 6) && nearlyEqual(r4.y, 8));
 
    Vector2D r5 = s * A;
    printVector("s * A", r5);
    assert(nearlyEqual(r5.x, 6) && nearlyEqual(r5.y, 8));
 
    Vector2D r6 = A / s;
    printVector("A / s", r6);
    assert(nearlyEqual(r6.x, 1.5f) && nearlyEqual(r6.y, 2));
 
    float dot = A.dotProduct(B);
    std::cout << "A.dotProduct(B) = " << dot << "\n";
    assert(nearlyEqual(dot, 11));
 
    float mag = A.magnitude();
    std::cout << "A.magnitude() = " << mag << "\n";
    assert(nearlyEqual(mag, 5));
 
    float magSqr = A.magnitudeSqr();
    std::cout << "A.magnitudeSqr() = " << magSqr << "\n";
    assert(nearlyEqual(magSqr, 25));
 
    Vector2D norm = A.normalize();
    printVector("A.normalize()", norm);
    assert(nearlyEqual(norm.x, 0.6f) && nearlyEqual(norm.y, 0.8f));
 
    float normMag = norm.magnitude();
    std::cout << "A.normalize().magnitude() = " << normMag << "\n";
    assert(nearlyEqual(normMag, 1.0f));
 
    std::cout << "\n--- Compound assignment round trip ---\n";
 
    Vector2D C = A;
    printVector("C (start)", C);
 
    C += B;
    C -= B;
    printVector("C after += B, -= B", C);
    assert(nearlyEqual(C.x, A.x) && nearlyEqual(C.y, A.y));
 
    C *= s;
    C /= s;
    printVector("C after *= s, /= s", C);
    assert(nearlyEqual(C.x, A.x) && nearlyEqual(C.y, A.y));
 
    std::cout << "\n--- Edge cases ---\n";
 
    try {
        Vector2D zero(0, 0);
        Vector2D result = zero.normalize();
        std::cout << "ERROR: normalize() on zero vector did not throw!\n";
    } catch (const std::invalid_argument &e) {
        std::cout << "normalize() on zero vector threw as expected: " << e.what() << "\n";
    }
 
    try {
        Vector2D result = A / 0.0f;
        std::cout << "ERROR: division by zero did not throw!\n";
    } catch (const std::invalid_argument &e) {
        std::cout << "A / 0 threw as expected: " << e.what() << "\n";
    }
 
    std::cout << "\nAll checks passed if no ERROR lines and no assertion failures appeared above.\n";
    return 0;
}