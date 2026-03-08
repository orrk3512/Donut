#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>
#include <chrono>
#include <thread>

// 3d matrix for storing and modifying the donut
class matrix
{
public:
    // Input is resolution size of the matrix
    matrix(int res);

    // Runs function f on all points within the matrix with the input being the value at that point.
    void modify(float (*f)(float, int, int, int, int));

    // Runs function f on all points within the matrix with the input being the coordinattes of that point and the resolution
    void modify(float (*f)(int, int, int, int, float), float time);

    // Calls castTo2d()
    // Prints the 2d matrix to the terminal via converting values to their corrosponding shading values
    void render(std::vector<char> shading);

private:
    // Looks at the 3d vector from one side and puts the first non-zero number it finds into the corrosping place in the 2d vector
    std::vector<std::vector<float>> castTo2d();

    std::vector<std::vector<std::vector<float>>> m;
    int resolution;
};

// Determines whether a point in a 3d matrix is inside the mathmatical representation of a donut
float donutToMatrix(int x, int y, int z, int resolution, float time_offset);

float translate(float in);

float gradientShade(float value, int x, int y, int z, int resolution);

int main()
{
    const std::vector<char> shading_binary = {' ', '#'};
    const std::vector<char> shading_simple = {' ', '.', '-', '=', '+', '*', '#'};

    float time = 0;

    for (int i = 0; i < 50; ++i)
    {
        matrix m(32);
        m.modify(donutToMatrix, time);
        m.modify(gradientShade);
        m.render(shading_simple);

        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        time += 0.3;
    }
    return 0;
}

float donutToMatrix(int x, int y, int z, int resolution, float time_offset)
{
    // Offset from the origin of the matrix to the center of the of the cartesian space
    const float offset = 0.5 * resolution;
    // Radius from the center of mass to outer edge of the donut
    const float outer_radius = 0.3 * resolution;
    // Radius from the inside of the tube to outside of the tube of the torus
    const float tube_radius = 0.1 * resolution;

    // transformations to cartesian space
    x = x - offset + std::sin(time_offset) * 10; // Floating animation
    y = y - offset;
    z = z - offset;

    float angle = time_offset;

    float x_rotateY = x * std::cos(angle) + z * std::sin(angle);
    float y_rotateY = y;
    float z_rotateY = -x * std::sin(angle) + z * std::cos(angle);

    float x_new = x_rotateY;
    float y_new = y_rotateY * std::cos(angle) - z_rotateY * std::sin(angle);
    float z_new = y_rotateY * std::sin(angle) + z_rotateY * std::cos(angle);

    // Distance from the point to the torus formed by the tube_radius
    // Equation of torus is: (outer_radius - sqrt(x^2 + y^2))^2 + z^2 <= tube_radius^2
    const float torus = std::sqrt(std::pow(outer_radius - std::sqrt(std::pow(x_new, 2) + std::pow(y_new, 2)), 2) + std::pow(z_new, 2));
    if (torus <= tube_radius)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}

float gradientShade(float value, int x, int y, int z, int resolution)
{
    if (value == 0)
        return 0;
    return value * (static_cast<float>(y) / resolution + static_cast<float>(z) / resolution) / 2;
}

float translate(float in)
{
    return 1;
}

matrix::matrix(int res)
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

void matrix::modify(float (*f)(float, int, int, int, int))
{
    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m.at(i).size(); ++j)
        {
            for (int k = 0; k < m.at(i).at(j).size(); k++)
            {
                m.at(i).at(j).at(k) = f(m.at(i).at(j).at(k), i, j, k, resolution);
            }
        }
    }
}

void matrix::modify(float (*f)(int, int, int, int, float), float time)
{
    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m.at(i).size(); ++j)
        {
            for (int k = 0; k < m.at(i).at(j).size(); k++)
            {
                m.at(i).at(j).at(k) = f(i, j, k, resolution, time);
            }
        }
    }
}

void matrix::render(std::vector<char> shading)
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "\n";
    }

    std::vector<std::vector<float>> out = castTo2d();

    for (const auto x : out)
    {
        for (const auto y : x)
        {
            std::cout << shading.at(static_cast<int>(y * (shading.size() - 2))) << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<float>> matrix::castTo2d()
{
    std::vector<std::vector<float>> out;
    out.assign(resolution, {});
    for (int i = 0; i < resolution; ++i)
    {
        out.at(i).assign(resolution, 0);
    }

    for (int i = 0; i < resolution; ++i)
    {
        for (int j = 0; j < resolution; ++j)
        {
            for (int z = 0; z < resolution; ++z)
            {
                float current_value = m.at(i).at(j).at(z);
                if (current_value != 0)
                {
                    out.at(i).at(j) = current_value;
                    break;
                }
            }
        }
    }
    return out;
}
