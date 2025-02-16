#ifndef CSLIBS_MATH_MEAN_HPP
#define CSLIBS_MATH_MEAN_HPP

#include <eigen3/Eigen/Core>

namespace cslibs_math {
namespace statistics {
template<typename T, std::size_t Dim>
class EIGEN_ALIGN16 Mean
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    using allocator_t = Eigen::aligned_allocator<Mean<T,Dim>>;

    using Ptr         = std::shared_ptr<Mean<T,Dim>>;
    using sample_t    = Eigen::Matrix<T, Dim, 1>;

    inline Mean() :
        mean_(Eigen::Matrix<T, Dim, 1>::Zero()),
        n_(1),
        n_1(0)
    {
    }

    inline Mean(const Mean &other) :
        mean_(other.mean_),
        n_(other.n_),
        n_1(other.n_1)
    {
    }

    inline Mean(Mean &&other) :
        mean_(std::move(other.mean_)),
        n_(other.n_),
        n_1(other.n_1)
    {
    }

    inline void add(const sample_t &sample)
    {
        mean_ = (mean_ * static_cast<T>(n_1) + sample) / static_cast<T>(n_);
        ++n_;
        ++n_1;
    }

    inline sample_t get() const
    {
        return mean_;
    }

private:
    sample_t    mean_;
    std::size_t n_;
    std::size_t n_1;
};

template<typename T>
class EIGEN_ALIGN16 Mean<T, 1>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    using allocator_t = Eigen::aligned_allocator<Mean<T,1>>;

    Mean() :
        mean_(T()),
        n_(1),
        n_1(0)
    {
    }

    inline void add(const T &sample)
    {
        mean_ = (mean_ * static_cast<T>(n_1) + sample) / static_cast<T>(n_);
        ++n_;
        ++n_1;
    }

    inline T get() const
    {
        return mean_;
    }

private:
    T mean_;
    std::size_t n_;
    std::size_t n_1;
};
}
}

#endif // CSLIBS_MATH_MEAN_HPP
