#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include <cmath>
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
            Number,
            String
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

    class Nil : public Object
    {
    public:
        static constexpr std::string_view kString = "Nil";

        std::string_view to_string() const override { return kString; }
        Type type() const override { return Type::Nil; }
    };

    class Number : public Object
    {
    public:
        Number() = default;
        Number(double value);
        Number(std::string_view value);

        std::string_view to_string() const override { return string_; }
        Type type() const override { return Type::Number; }

        double value() const { return value_; }
        double operator+(const Number& other) const { return value_ + other.value_; }
        double operator-(const Number& other) const { return value_ - other.value_; }
        double operator-() const { return -value_; }
        double operator*(const Number& other) const { return value_ * other.value_; }
        double operator/(const Number& other) const { return value_ / other.value_; }
        double operator%(const Number& other) const { return std::fmod(value_, other.value_); }

    private:
        double value_ = 0.0;
        std::string string_ = "";
    };

    class String : public Object
    {
    public:
        String(std::string value);
        String(std::string_view value);

        std::string_view to_string() const override { return string_; }
        Type type() const override { return Object::Type::String; }

        const std::string& value() const { return string_; }

    private:
        std::string string_;
    };
} // namespace Lox

#endif // LOX_OBJECT_H
