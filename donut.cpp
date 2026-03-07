#include <iostream>
#include <vector>
#include <cmath>

void modify(std::vector<std::vector<std::vector<float>>> &matrix, float (*f)(float));

void render(const std::vector<std::vector<std::vector<float>>> &matrix);

float translate(float in);

void main()
{
    std::vector<std::vector<std::vector<float>>> m;
    m.emplace({});
    m.at(0).emplace({});
    m.at(0).at(0).emplace({});
    m.at(0).at(0).at(0) = 1.0;

    modify(m, translate);
}

void modify(std::vector<std::vector<std::vector<float>>> &matrix, float (*f)(float))
{
    for (const auto layer1 : matrix)
    {
        for (const auto layer2 : layer1)
        {
            for (const auto layer3 : layer2)
            {
                std::cout << layer3 << std::endl;
            }
        }
    }
}
