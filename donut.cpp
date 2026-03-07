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

    // Runs function f on all points within the matrix with the input being the value at that point.
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

    // Runs function f on all points within the matrix with the input being the coordinattes of that point
    void modify(float (*f)(int, int, int))
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m.at(i).size(); ++j)
            {
                for (int k = 0; k < m.at(i).at(j).size(); k++)
                {
                    m.at(i).at(j).at(k) = f(i, j, k);
                }
            }
        }
    }

private:
    std::vector<std::vector<std::vector<float>>> m;
    int resolution;
};

// Determines whether a point in a 3d matrix is inside the mathmatical representation of a donut
float donutToMatrix();

void render(const std::vector<std::vector<std::vector<float>>> &matrix);

float translate(float in);

void main()
{
    matrix m(1);
    m.modify(translate);
}

float donutToMatrix() {

}

float translate(float in)
{
    return 1;
}
