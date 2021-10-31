#include <iostream>
#include <mathlib/mathlib>

int main(int argc, char const *argv[]) {
    Vector2d v = Vector2d({3., 4.});

    Vector2i i = Vector2i({3, 4});

    std::cout << v.norm() << std::endl;

    v[0] = 1.;
    v[1] = 0.;
    std::cout << v.norm() << std::endl;
    Vector2d v2 = Vector2d(1.);

    v = v2;

    std::cout << v.norm() << std::endl;

    std::cout << (v + v2).norm() << std::endl;

    std::cout << v.sum() << std::endl;

    std::cout << v * (v2 + v2) << std::endl;

    Vector3d v3;
    v3 << 1., 2., 3.;
    std::cout << v3 << std::endl;

    std::cout << v3.min() << "/" << v3.max() << std::endl;

    Vector<6, double> v_;
    v_ << 1., 2., 3., 4., 5., 6.;

    std::cout << v_.head<3>() << std::endl;
    std::cout << v_.tail<3>() << std::endl;
    std::cout << v_.segment<1, 3>() << std::endl;

    std::cout << (v_.head<3>() == v_.segment<0, 3>()) << std::endl;

    return 0;
}
