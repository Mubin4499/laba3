#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template <typename T>
class FiestaCalculator {
public:
    // �������� (����������� �������)
    std::vector<T> add(const std::vector<T>& a, const std::vector<T>& b) const {
        std::vector<T> result = a;
        result.insert(result.end(), b.begin(), b.end());
        return result;
    }

    // ��������� (����������� ��������)
    std::vector<T> subtract(const std::vector<T>& a, const std::vector<T>& b) const {
        if (a.size() != b.size()) {
            throw std::runtime_error("?Error! ������ ������� �������������������");
        }
        std::vector<T> result;
        for (size_t i = 0; i < a.size(); ++i) {
            result.push_back(a[i] - b[i]);
        }
        return result;
    }

    // ��������� (��������������� �������)
    std::vector<T> multiply(const std::vector<T>& vec, T factor) const {
        std::vector<T> result;
        for (const auto& item : vec) {
            result.push_back(item * factor);
        }
        return result;
    }

    // ������� (������� ����� �������)
    std::vector<T> divide(const std::vector<T>& vec, T divisor) const {
        checkDivision(divisor);
        return multiply(vec, 1 / divisor);
    }

    // �������� ��������� ����
    bool areLengthsEqual(const std::vector<T>& a, const std::vector<T>& b) const {
        return a.size() == b.size();
    }

protected:
    void checkDivision(T divisor) const {
        if (divisor == 0) {
            throw std::runtime_error("?Error! Divisi?n por cero");
        }
    }
};