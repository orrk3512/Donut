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

    // Runs function f on all points within the matrix with the input being the coordinattes of that point and the resolution
    void modify(float (*f)(int, int, int, int))
    {
        for (int i = 0; i < m.size(); ++i)
        {
            for (int j = 0; j < m.at(i).size(); ++j)
            {
                for (int k = 0; k < m.at(i).at(j).size(); k++)
                {
                    m.at(i).at(j).at(k) = f(i, j, k, resolution);
                }
            }
        }
    }

private:
    std::vector<std::vector<std::vector<float>>> m;
    int resolution;
};

// Determines whether a point in a 3d matrix is inside the mathmatical representation of a donut
float donutToMatrix(int x, int y, int z, int resolution);

void render(const std::vector<std::vector<std::vector<float>>> &matrix);

float translate(float in);

void main()
{
    matrix m(32);
    m.modify(donutToMatrix);
}

float donutToMatrix(int x, int y, int z, int resolution) {
    // Offset from the origin of the matrix to the center of the of the cartesian space
    const float offset = 0.5 * resolution;
    // Radius from the center of mass to outer edge of the donut
    const float outer_radius = 0.7 * resolution;
    // Radius from the inside of the tube to outside of the tube of the torus
    const float tube_radius = 0.2 * resolution;

    // transformations to cartesian space
    const float x_cart = x - offset;
    const float y_cart = y - offset;
    const float z_cart = z - offset;

    // Distance from the point to the torus formed by the tube_radius
    // Equation of torus is: (outer_radius - sqrt(x^2 + y^2))^2 + z^2 <= tube_radius^2
    const float torus = std::sqrt(std::pow(outer_radius - std::sqrt(std::pow(x_cart, 2) + std::pow(y_cart, 2)), 2) + std::pow(z_cart, 2));
    if (torus <= tube_radius) {
        return 1.0;
    } else {
        return 0.0;
    }
}

float translate(float in)
{
    return 1;
}
