#ifndef POINTCLOUD_HPP
#define POINTCLOUD_HPP

#include <cslibs_math/linear/vector.hpp>

#include <memory>
#include <vector>

namespace cslibs_math {
namespace linear {
template<typename point_t>
class Pointcloud
{
public:
    using Ptr              = std::shared_ptr<Pointcloud>;
    using ConstPtr         = std::shared_ptr<const Pointcloud>;

    using points_t         = std::vector<point_t, typename point_t::allocator_t>;
    using const_iterator_t = typename points_t::const_iterator;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    inline Pointcloud() :
          min_(point_t::max()),
          max_(point_t::min())
    {
    }

    inline Pointcloud(const Pointcloud &other) :
          data_(other.data_),
          min_(other.min_),
          max_(other.max_)
    {
    }

    virtual ~Pointcloud() = default;

    inline virtual void insert(const point_t &pt)
    {
        min_.min(pt);
        max_.max(pt);
        data_.emplace_back(pt);
    }

    inline virtual void insertInvalid()
    {
        data_.emplace_back(point_t::inf());
    }

    inline virtual void clear()
    {
        data_.clear();
    }

    inline const_iterator_t begin() const
    {
        return data_.begin();
    }

    inline const_iterator_t end() const
    {
        return data_.end();
    }

    inline point_t const & at(const std::size_t i) const
    {
        return data_.at(i);
    }

    inline std::vector<point_t> const & getPoints() const
    {
        return data_;
    }

    inline std::size_t size() const
    {
        return data_.size();
    }

    inline point_t min() const
    {
        return min_;
    }

    inline point_t max() const
    {
        return max_;
    }

    template<typename transform_t>
    inline void transform(const transform_t &t)
    {
        auto apply = [&t, this](point_t &p){
             p = t.apply(p);
             min_.min(p);
             max_.max(p);
        };

        min_ = point_t(std::numeric_limits<typename point_t::type_t>::max());
        max_ = point_t(std::numeric_limits<typename point_t::type_t>::min());
        std::for_each(data_.begin(), data_.end(),
                      apply);
    }


protected:
    points_t data_;
    point_t  min_;
    point_t  max_;
}__attribute__ ((aligned (16)));
}
}

#endif // POINTCLOUD_HPP
