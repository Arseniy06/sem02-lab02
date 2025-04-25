#include <cstddef>
#include <iostream>
#include <cstring>
#include <algorithm>

class String {
public:
    ~String() {
        delete[] Data;
    }

    String() : Data(nullptr) {}

    String(const String& rhs) {
        if (rhs.Data) {
            size_t len = strlen(rhs.Data);
            Data = new char[len + 1];
            strcpy(Data, rhs.Data);
        } else {
            Data = nullptr;
        }
    }

    String(const char* data) {
        if (data) {
            size_t len = strlen(data);
            Data = new char[len + 1];
            strcpy(Data, data);
        } else {
            Data = nullptr;
        }
    }

    String& operator=(const String& rhs) {
        if (this != &rhs) {
            String tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    String& operator+=(const String& rhs) {
        if (rhs.Empty()) return *this;
        if (Empty()) {
            *this = rhs;
            return *this;
        }
        size_t new_len = Size() + rhs.Size();
        char* new_data = new char[new_len + 1];
        strcpy(new_data, Data);
        strcat(new_data, rhs.Data);
        delete[] Data;
        Data = new_data;
        return *this;
    }

    String& operator*=(unsigned int m) {
        if (m == 0 || Empty()) {
            delete[] Data;
            Data = nullptr;
            return *this;
        }
        size_t len = Size();
        size_t new_len = len * m;
        char* new_data = new char[new_len + 1];
        new_data[0] = '\0';
        for (unsigned i = 0; i < m; ++i) {
            strcat(new_data, Data);
        }
        delete[] Data;
        Data = new_data;
        return *this;
    }

    bool operator==(const String& rhs) const {
        if (Size() != rhs.Size()) return false;
        return strcmp(Data, rhs.Data) == 0;
    }

    bool operator<(const String& rhs) const {
        return strcmp(Data, rhs.Data) < 0;
    }

    int Find(const String& substr) const {
        if (substr.Empty() || Empty()) return -1;
        const char* pos = strstr(Data, substr.Data);
        return pos ? pos - Data : -1;
    }

    void Replace(char oldSymbol, char newSymbol) {
        if (Empty()) return;
        for (size_t i = 0; i < Size(); ++i) {
            if (Data[i] == oldSymbol) {
                Data[i] = newSymbol;
            }
        }
    }

    size_t Size() const {
        return Data ? strlen(Data) : 0;
    }

    bool Empty() const {
        return Size() == 0;
    }

    char operator[](size_t index) const {
        return Data[index];
    }

    char& operator[](size_t index) {
        return Data[index];
    }

    void RTrim(char symbol) {
        if (Empty()) return;
        size_t len = Size();
        while (len > 0 && Data[len - 1] == symbol) {
            --len;
        }
        if (len == 0) {
            delete[] Data;
            Data = nullptr;
        } else {
            char* new_data = new char[len + 1];
            strncpy(new_data, Data, len);
            new_data[len] = '\0';
            delete[] Data;
            Data = new_data;
        }
    }

    void LTrim(char symbol) {
        if (Empty()) return;
        size_t start = 0;
        while (Data[start] == symbol) {
            ++start;
        }
        size_t new_len = Size() - start;
        if (new_len == 0) {
            delete[] Data;
            Data = nullptr;
        } else {
            char* new_data = new char[new_len + 1];
            strcpy(new_data, Data + start);
            delete[] Data;
            Data = new_data;
        }
    }

    void swap(String& oth) {
        std::swap(Data, oth.Data);
    }

    friend std::ostream& operator<<(std::ostream& out, const String& str) {
        if (!str.Empty()) {
            out << str.Data;
        }
        return out;
    }

private:
    char* Data;
};

inline String operator+(const String& a, const String& b) {
    String result(a);
    result += b;
    return result;
}

inline String operator*(const String& a, unsigned int b) {
    String result;
    if (b == 0 || a.Empty()) return result;
    result = a;
    result *= b;
    return result;
}

inline bool operator!=(const String& a, const String& b) {
    return !(a == b);
}

inline bool operator>(const String& a, const String& b) {
    return b < a;
}
