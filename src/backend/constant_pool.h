#ifndef LOX_CONSTANT_POOL_H
#define LOX_CONSTANT_POOL_H

#include "common/object.h"
#include "errors/out_of_memory_error.h"
#include <array>

namespace Lox
{
    template<typename IndexType = size_t, IndexType PoolSize = std::numeric_limits<IndexType>::max()>
    class ConstantPool
    {
    public:
        ConstantPool()
        {
            constants_.fill(nullptr);
        }

        IndexType push(Object::Ptr object)
        {
            if (next_index_ >= PoolSize - 1)
                throw OutOfMemoryError();
            auto index = next_index_++;
            constants_[index] = std::move(object);
            return index;
        }

        Object::Ptr get(IndexType index) const
        {
            // We need to check since std::array::operator[] does
            // no bounds checking
            if (index >= PoolSize)
                throw std::range_error("Constant index larger than kMaxConstants");
            return constants_[index];
        }

    private:
        std::array<Object::Ptr, PoolSize> constants_;
        IndexType next_index_ = 0;
    };

} // namespace Lox

#endif // LOX_CONSTANT_POOL_H
