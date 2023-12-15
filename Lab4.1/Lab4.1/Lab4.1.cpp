#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class VectorFloat {
private:
    float* elements;
    int size;
    int codeError;

public:
    static int objectCount;

    // Constructors and Destructor
    VectorFloat() : size(1), elements(new float[1] {0.0}), codeError(0) {
        objectCount++;
    }

    VectorFloat(int newSize) : size(newSize), elements(new float[newSize] {0.0}), codeError(0) {
        objectCount++;
    }

    VectorFloat(int newSize, float initValue) : size(newSize), elements(new float[newSize]), codeError(0) {
        for (int i = 0; i < newSize; i++) {
            elements[i] = initValue;
        }
        objectCount++;
    }

    ~VectorFloat() {
        delete[] elements;
        objectCount--;
    }

    // Copy Constructor
    VectorFloat(const VectorFloat& other) : size(other.size), elements(new float[other.size]), codeError(other.codeError) {
        for (int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
        objectCount++;
    }

    // Copy Assignment Operator
    VectorFloat& operator=(const VectorFloat& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            elements = new float[size];
            codeError = other.codeError;
            for (int i = 0; i < size; i++) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    // Compound Assignment Operators
    VectorFloat& operator+=(const VectorFloat& other) {
        if (size == other.size) {
            for (int i = 0; i < size; i++) {
                elements[i] += other.elements[i];
            }
        }
        else {
            codeError = 1;
        }
        return *this;
    }

    VectorFloat& operator-=(const VectorFloat& other) {
        if (size == other.size) {
            for (int i = 0; i < size; i++) {
                elements[i] -= other.elements[i];
            }
        }
        else {
            codeError = 1;
        }
        return *this;
    }

    VectorFloat& operator*=(float scalar) {
        for (int i = 0; i < size; i++) {
            elements[i] *= scalar;
        }
        return *this;
    }

    VectorFloat& operator/=(float scalar) {
        if (scalar != 0.0) {
            for (int i = 0; i < size; i++) {
                elements[i] /= scalar;
            }
        }
        else {
            codeError = 2;
        }
        return *this;
    }

    VectorFloat& operator%=(float scalar) {
        if (scalar != 0.0) {
            for (int i = 0; i < size; i++) {
                elements[i] = fmod(elements[i], scalar);
            }
        }
        else {
            codeError = 2;
        }
        return *this;
    }

    // Unary Operators
    VectorFloat operator-() const {
        VectorFloat result(*this);
        for (int i = 0; i < size; i++) {
            result.elements[i] = -result.elements[i];
        }
        return result;
    }

    VectorFloat& operator++() {
        for (int i = 0; i < size; i++) {
            elements[i]++;
        }
        return *this;
    }

    VectorFloat operator++(int) {
        VectorFloat temp(*this);
        ++(*this);
        return temp;
    }

    VectorFloat& operator--() {
        for (int i = 0; i < size; i++) {
            elements[i]--;
        }
        return *this;
    }

    VectorFloat operator--(int) {
        VectorFloat temp(*this);
        --(*this);
        return temp;
    }

    // Binary Operators
    VectorFloat operator+(const VectorFloat& other) const {
        VectorFloat result(*this);
        result += other;
        return result;
    }

    VectorFloat operator-(const VectorFloat& other) const {
        VectorFloat result(*this);
        result -= other;
        return result;
    }

    VectorFloat operator*(float scalar) const {
        VectorFloat result(*this);
        result *= scalar;
        return result;
    }

    VectorFloat operator/(float scalar) const {
        VectorFloat result(*this);
        result /= scalar;
        return result;
    }

    VectorFloat operator%(float scalar) const {
        VectorFloat result(*this);
        result %= scalar;
        return result;
    }

    // Relational Operators
    bool operator==(const VectorFloat& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (elements[i] != other.elements[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const VectorFloat& other) const {
        return !(*this == other);
    }

    // Index Operator
    float& operator[](int index) {
        if (index < 0 || index >= size) {
            index = size - 1;
            codeError = 3;
        }
        return elements[index];
    }

    friend ostream& operator<<(ostream& os, const VectorFloat& vector);

    friend istream& operator>>(istream& is, VectorFloat& vector);
};

int VectorFloat::objectCount = 0;

ostream& operator<<(ostream& os, const VectorFloat& vector) {
    os << "[ ";
    for (int i = 0; i < vector.size; i++) {
        os << vector.elements[i] << " ";
    }
    os << "]";
    return os;
}

istream& operator>>(istream& is, VectorFloat& vector) {
    for (int i = 0; i < vector.size; i++) {
        if (!(is >> vector.elements[i])) {
            // If input fails, set error code and break
            vector.codeError = 4;
            break;
        }
    }
    return is;
}

int main() {
    VectorFloat v1(3, 2.0);
    VectorFloat v2(3, 1.0);
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    VectorFloat v3 = v1 + v2;
    cout << "v3 = v1 + v2: " << v3 << endl;
    VectorFloat v4 = v1 * 1.5;
    cout << "v4 = v1 * 1.5: " << v4 << endl;
    v1++;
    cout << "v1++: " << v1 << endl;
    v2--;
    cout << "v2--: " << v2 << endl;
    return 0;
}
