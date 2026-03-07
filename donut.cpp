#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

// 3d matrix for storing and modifying the donut
class matrix
{
public:
    matrix(int res)
    {
        resolution = res;
        m.assign(resolution, {});
        for (int i = 0; i < m.size(); ++i)
        {
            m.at(i).assign(resolution, {});
            for (int j = 0; j < m.at(i).size(); ++j)
            {
                m.at(i).at(j).assign(resolution, {});
                for (int k = 0; k < m.at(i).at(j).size(); k++)
                {
                    m.at(i).at(j).at(k) = 0;
                }
            }
        }
    }

    void modify(float (*f)(float))
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m.at(i).size(); ++j)
            {
                for (int k = 0; k < m.at(i).at(j).size(); k++)
                {
                    m.at(i).at(j).at(k) = f(m.at(i).at(j).at(k));
                }
            }
        }
    }

    void modify(float (*f)())
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m.at(i).size(); ++j)
            {
                for (int k = 0; k < m.at(i).at(j).size(); k++)
                {
                    m.at(i).at(j).at(k) = f();
                }
            }
        }
    }

private:
    std::vector<std::vector<std::vector<float>>> m;
    int resolution;
};

float donutToMatrix(float in);

void render(const std::vector<std::vector<std::vector<float>>> &matrix);

float translate(float in);

void main()
{
    matrix m(1);
    m.modify(translate);
}

float translate(float in)
{
    return 1;
}
