#ifndef MATRIX_H
#define MATRIX_H

namespace matrix
{
    
    template <typename T>
    class Matrix
    {
    
    public:
        struct row
        {
            T* elems;
            T& operator[](size_t idx) { return elems[idx]; }
            const T& operator[](size_t idx) const { return elems[idx]; }
        };

        // C-tors
        Matrix(int cols, int rows, T val = T{});

        template <typename It>
        Matrix(int cols, int rows, It start, It fin);

        // Filling with 1
        static Matrix eye(int n, int m);

    private:
        row* data;

    };

}

#endif 