#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include <concepts>
#include <memory>
#include <string>
#include <string_view>

namespace Lox
{
    class Object
    {
    public:
        enum class Type {
            Nil,
            Number
        };

        using Ptr = std::shared_ptr<Object>;
        template<typename ObjectType, typename... Args>
            requires std::derived_from<ObjectType, Object>
        static auto create(Args&&... args)
        {
            return std::make_shared<ObjectType>(std::forward<Args>(args)...);
        }

        virtual ~Object() = default;
        virtual std::string_view to_string() const = 0;
        virtual Object::Type type() const = 0;
    };

    class Number : public Object
    {
    public:
        Number() = default;
        Number(double value);
        Number(std::string_view value);
        std::string_view to_string() const override { return string_; }
        Type type() const override;

    private:
        double value_ = 0.0;
        std::string string_ = "";
    };

    class Nil : public Object
    {
    public:
        static constexpr std::string_view kString = "Nil";

        std::string_view to_string() const override { return kString; }
        Type type() const override { return Type::Nil; }
    };

} // namespace Lox

#endif // LOX_OBJECT_H
