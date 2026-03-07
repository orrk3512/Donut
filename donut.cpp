#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

std::vector<std::vector<std::vector<float>>> create3D(int resolution);

void modify(std::vector<std::vector<std::vector<float>>> &matrix, float (*f)(float));

void render(const std::vector<std::vector<std::vector<float>>> &matrix);

float translate(float in);

void main()
{
    std::vector<std::vector<std::vector<float>>> m;
    m = create3D(1);
    m.at(0).at(0).at(0) = 1.0;

    modify(m, translate);
}

std::vector<std::vector<std::vector<float>>> create3D(int resolution) {
    assert(resolution > 0);

    std::vector<std::vector<std::vector<float>>> m;
    m.assign(resolution, {});
    for (int i = 0; i < m.size(); ++i) {
        m.at(i).assign(resolution, {});
        for (int j = 0; j < m.at(i).size(); ++j) {
            m.at(i).at(j).assign(resolution, {});
            for (int k = 0; k < m.at(i).at(j).size(); k++) {
                m.at(i).at(j).at(k) = 0;
            }
        }
    }
    return m;
}

void modify(std::vector<std::vector<std::vector<float>>> &matrix, float (*f)(float))
{
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.at(i).size(); ++j) {
            for (int k = 0; k < matrix.at(i).at(j).size(); k++) {
                matrix.at(i).at(j).at(k) = f(matrix.at(i).at(j).at(k));
            }
        }
    }
}

float translate(float in) {
    return 0;
}
