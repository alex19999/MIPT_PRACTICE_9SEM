#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

namespace matrix
{
    enum class FILL_TYPE : short
    {
        NO_FILL,
        ZEROS,
        ONES,
        SEQUENTIAL
    };

    template <typename T>
    class Matrix
    {
    
    public:
        struct row
        {   
            T* elems;
            void allocateRow(size_t cols) { elems = new T[cols]; }
            void deallocateRow() { delete [] elems; }
            T& operator[](size_t idx) 
            {
                return elems[idx]; 
            }
            const T& operator[](size_t idx) const 
            {
                return elems[idx]; 
            }
        };

        // C-tors
        Matrix(size_t cols, size_t rows, enum FILL_TYPE fillType = FILL_TYPE::NO_FILL);

        Matrix(size_t cols, size_t rows, T val);

        template <typename It>
        Matrix(size_t cols, size_t rows, It start, It fin);

        // Copy c-tor
        Matrix(const Matrix& rhs);
        
        // Copy assignment
        Matrix& operator=(const Matrix& rhs);

        // Move c-tor
        //Matrix(Matrix&& rhs);
        //Matrix& operator=(Matrix&& rhs);
        
        // Destructor
        ~Matrix();

        // Filling with 1
        static Matrix eye(size_t n, size_t m);

        // Access
        row& operator[](size_t idx) 
        { 
            if (idx >= iRows)
            {
                throw std::runtime_error("Row out of the range");
            }
            return iData[idx]; 
        }

        const row& operator[](size_t idx) const  
        {
            if (idx >= iRows)
            {
                throw std::runtime_error("Row out of the range");
            }
            return iData[idx];
        }

        // Getters
        row* getData() const { return iData; }
        size_t getColsNum() const { return iCols; }
        size_t getRowsNum() const { return iRows; }

        // Setter
        void setDataPtr(row* newData) { iData = newData; }

        // Arithmetic operations
        Matrix& operator+=(const Matrix& rhs) &;
        Matrix& operator-=(const Matrix& rhs) &;
        Matrix& operator*=(const Matrix& rhs) &;
        Matrix& operator/=(const Matrix& rhs) &;
        Matrix& operator*=(T val) &;
        Matrix& matMul(const Matrix& rhs) &;

        // Equality
        bool haveEqualSize(const Matrix& other) const;
        bool identical(const Matrix& other) const;

        // Negative matrix
        Matrix& negate() &;
        Matrix operator-() const;

        // Trace
        T trace() const;
    
        Matrix& transpose() &;

        void print(std::ostream& out);
    
    protected:
        void _fillSameValue(T val);
        void _fillSequential();
        void _elementWiseOp(const Matrix& actor, std::function<T(const T, const T)> op);

    private:
        size_t iCols;
        size_t iRows;
        row* iData;
    };

    // Helper
    template <typename T>
    void Matrix<T>::_fillSameValue(T val)
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                iData[i][j] = val;
            }
        }
    }

    template <typename T>
    void Matrix<T>::_fillSequential()
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                iData[i][j] = static_cast<T>(i * iCols + j);
            }
        }
    }

    template <typename T>
    void Matrix<T>::_elementWiseOp(const Matrix& actor, std::function<T(const T, const T)> op)
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                iData[i][j] = op(iData[i][j], actor.getData()[i][j]);
            }
        }
    }

    template <typename T>
    void Matrix<T>::print(std::ostream& out)
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                out << "row = " << i << ", column = " << j << ", value = " << iData[i][j] << std::endl;
            }
        }
    }
    
    template <typename T>
    Matrix<T>::Matrix(size_t cols, size_t rows, enum FILL_TYPE fillType)
    : iCols(cols)
    , iRows(rows)
    {
        iData = new row[iRows];
        for (size_t i = 0; i < iRows; ++i)
        {
            iData[i].allocateRow(iCols);
        }

        switch (fillType)
        {
            case FILL_TYPE::ZEROS:
                _fillSameValue(static_cast<T>(0));
                break;
            case FILL_TYPE::ONES:
                _fillSameValue(static_cast<T>(1));
                break;
            case FILL_TYPE::SEQUENTIAL:
                _fillSequential();
                break;
            default:
                break;
        }
    }

    template <typename T>
    Matrix<T>::Matrix(size_t cols, size_t rows, T val)
    : Matrix(cols, rows)
    {
        // Fill
       _fillSameValue(val);
    }
    
    template <typename T>
    template <typename It>
    Matrix<T>::Matrix(size_t cols, size_t rows, It start, It fin)
    : Matrix(cols, rows)
    {
        auto begin = start;
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                iData[i][j] = T(*start);
                start++;
                if (start == fin)
                {
                    return;
                }
            }
        }
    }

    template <typename T>
    Matrix<T> Matrix<T>::eye(size_t cols, size_t rows)
    {
        Matrix eye(cols, rows);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                if (i == j)
                {
                    eye.getData()[i][j] = static_cast<T>(1);
                }
                else
                {
                    eye.getData()[i][j] = static_cast<T>(0);
                }
            }
        }
        return eye;
    }
    
    template <typename T>
    Matrix<T>::Matrix(const Matrix& rhs)
    : Matrix(rhs.getColsNum(), rhs.getRowsNum())
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                iData[i][j] = rhs.getData()[i][j];
            }
        }
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)
    {
        this->~Matrix();
        new (this) Matrix(rhs);
        return *this;
    }

    /*
    template <typename T>
    Matrix<T>::Matrix(Matrix&& rhs)
    {
        iRows = std::move(rhs.getRowsNum());
        iCols = std::move(rhs.getColsNum());
        iData = std::move(rhs.getData());
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& rhs)
        : Matrix(rhs)
    {
    }*/

    template <typename T>
    Matrix<T>::~Matrix()
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            iData[i].deallocateRow();
        }
        delete [] iData;
    }

    template <typename T>
    bool Matrix<T>::haveEqualSize(const Matrix& other) const
    {
        return getColsNum() == other.getColsNum() && getRowsNum() == other.getRowsNum();
    }

    template <typename T>
    bool Matrix<T>::identical(const Matrix& other) const
    {
        if (!haveEqualSize(other))
        {
            return false;
        }
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                if (iData[i][j] != other.getData()[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs) &
    {
        if (!haveEqualSize(rhs))
        {
            throw std::runtime_error("Operator +: Matrices should have the same size");
        }
        _elementWiseOp(rhs, [](const T x, const T y) { return x + y; });
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator-=(const Matrix& rhs) &
    {
        if (!haveEqualSize(rhs))
        {
            throw std::runtime_error("Operator +: Matrices should have the same size");
        }

        _elementWiseOp(rhs, [](const T x, const T y) { return x - y; });
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator*=(const Matrix& rhs) &
    {
        if (!haveEqualSize(rhs))
        {
            throw std::runtime_error("Operator +: Matrices should have the same size");
        }
        
        _elementWiseOp(rhs, [](const T x, const T y) { return x * y; });
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator/=(const Matrix& rhs) &
    {
        if (!haveEqualSize(rhs))
        {
            throw std::runtime_error("Operator +: Matrices should have the same size");
        }
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                if (rhs.getData()[i][j] == static_cast<T>(0))
                {
                    throw std::runtime_error("Division by zero");
                }
                iData[i][j] /= rhs.getData()[i][j];
            }
        }
        return *this;
    }

    template <typename T>
    bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        return lhs.identical(rhs);
    }

    template <typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        Matrix tmp{ lhs };
        tmp += rhs;
        return tmp;
    }

    template <typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        Matrix tmp{ lhs };
        tmp -= rhs;
        return tmp;
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        Matrix tmp{ lhs };
        tmp *= rhs;
        return tmp;
    }

    template <typename T>
    Matrix<T> operator/(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        Matrix tmp{ lhs };
        tmp /= rhs;
        return tmp;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator*=(T val) &
    {
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                iData[i][j] *= val;
            }
        }
        return *this;
    }

    template <typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, T n)
    {
        Matrix tmp {lhs};
        tmp *= n;
        return tmp; 
    }

    template <typename T>
    Matrix<T>& Matrix<T>::negate() &
    {
        *this *= static_cast<T>(-1);
        return *this;
    }
    
    template <typename T>
    Matrix<T> Matrix<T>::operator-() const
    { 
        Matrix tmp{*this}; 
        return tmp.negate(); 
    }
    
    template <typename T>
    T Matrix<T>::trace() const
    {
        T trace = static_cast<T>(0);
        for (size_t i = 0; i < iRows; ++i)
        {
            trace += iData[i][i];
        }
        return trace;
    }
    
    template <typename T>
    Matrix<T>& Matrix<T>::matMul(const Matrix<T>& rhs) &
    {
        if (iCols != rhs.getRowsNum())
        {
            throw std::runtime_error("Matmul: incorrect matrices sizes");
        }

        Matrix tmp{ rhs.getColsNum(), iRows, FILL_TYPE::ZEROS};
        for(size_t i = 0; i < iRows; ++i)
        {
            for(size_t j = 0; j < rhs.getColsNum(); ++j)
            {
                for(size_t k = 0; k < iCols; ++k)
                {
                    tmp[i][j] += iData[i][k] * rhs.getData()[k][j];
                }
            }
        }
        *this = std::move(tmp);
        return *this;
    }
    
    template <typename T>
    Matrix<T>& Matrix<T>::transpose() &
    {
        Matrix tmp { iRows, iCols };
        for (size_t i = 0; i < iRows; ++i)
        {
            for (size_t j = 0; j < iCols; ++j)
            {
                tmp.getData()[j][i] = iData[i][j];
            }
        }
        *this = std::move(tmp);
        return *this;
    }
}

#endif 