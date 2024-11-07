#include <assert.h>

#include <iostream>

#include "grid.h"



int test1() {
    int const dimensions = 3;
    size_t const sizes[dimensions] = { 2, 3, 4 };

    Grid<int, dimensions> grid(sizes[0], sizes[1], sizes[2], 3);

    std::cout << "Grid(template) operator []:\n";
    for(size_t i = 0; i < sizes[0]; i++) {
        for(size_t j = 0; j < sizes[1]; j++) {
            for(size_t k = 0; k < sizes[2]; k++) {
                std::cout << grid[i][j][k];
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    std::cout << "Grid(template) operator ():\n";
    for(size_t i = 0; i < sizes[0]; i++) {
        for(size_t j = 0; j < sizes[1]; j++) {
            for(size_t k = 0; k < sizes[2]; k++) {
                size_t const indexes[dimensions] = { i, j, k };
                std::cout << grid(i, j, k);
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    std::cout << "test 1 done!\n";
    return 0;
}

int test2() {
    Grid<float, 2> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<float, 1>::size_type;
    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;


    for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));


    std::cout << "test 2 done!\n";
    return 0;
}

int test3() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(3, 4, 2.0f);
    assert(2.0f == g2(1, 1));
    g2 = g3[1];
    assert(1.0f == g2(1, 1));
    std::cout << "test 3 done!";
    return 0;
}
