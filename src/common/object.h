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

        Object::Ptr operator+(const Object& other) { return add(other); }
        Object::Ptr operator-(const Object& other) { return subtract(other); }
        Object::Ptr operator-() const { return negate(); }
        Object::Ptr operator*(const Object& other) const { return multiply(other); }
        Object::Ptr operator/(const Object& other) const { return divide(other); }
        Object::Ptr operator%(const Object& other) const { return modulus(other); }

    protected:
        virtual Object::Ptr add(const Object& other) const = 0;
        virtual Object::Ptr subtract(const Object& other) const = 0;
        virtual Object::Ptr negate() const = 0;
        virtual Object::Ptr multiply(const Object& other) const = 0;
        virtual Object::Ptr divide(const Object& other) const = 0;
        virtual Object::Ptr modulus(const Object& other) const = 0;
    };

    class Nil : public Object
    {
    public:
        static constexpr std::string_view kString = "Nil";
        static const Object::Ptr kNilRef;

        std::string_view to_string() const override { return kString; }
        Type type() const override { return Type::Nil; }
        Object::Ptr add(const Object& other) const override { return kNilRef; }

    protected:
        Object::Ptr subtract(const Object& other) const override { return kNilRef; }
        Object::Ptr negate() const override { return kNilRef; }
        Object::Ptr multiply(const Object& other) const override { return kNilRef; }
        Object::Ptr divide(const Object& other) const override { return kNilRef; }
        Object::Ptr modulus(const Object& other) const override { return kNilRef; }
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

    protected:
        Object::Ptr add(const Object& other) const override;
        Object::Ptr subtract(const Object& other) const override;
        Object::Ptr negate() const override;
        Object::Ptr multiply(const Object& other) const override;
        Object::Ptr divide(const Object& other) const override;
        Object::Ptr modulus(const Object& other) const override;

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

    protected:
        Object::Ptr add(const Object& other) const override;
        Object::Ptr subtract(const Object& other) const override;
        Object::Ptr negate() const override;
        Object::Ptr multiply(const Object& other) const override;
        Object::Ptr divide(const Object& other) const override;
        Object::Ptr modulus(const Object& other) const override;

    private:
        std::string string_;
    };
} // namespace Lox

#endif // LOX_OBJECT_H
