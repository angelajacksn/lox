#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include <cmath>
#include <concepts>
#include <fmt/format.h>
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
            String,
            Boolean
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
        operator bool() const { return is_truthy(); }
        bool operator==(const Object& other) const { return is_equal(other); }

    protected:
        static Object::Ptr unsupported_operation() { return nullptr; }
        virtual Object::Ptr add(const Object& other) const { return unsupported_operation(); }
        virtual Object::Ptr subtract(const Object& other) const { return unsupported_operation(); }
        virtual Object::Ptr negate() const { return unsupported_operation(); }
        virtual Object::Ptr multiply(const Object& other) const { return unsupported_operation(); }
        virtual Object::Ptr divide(const Object& other) const { return unsupported_operation(); }
        virtual Object::Ptr modulus(const Object& other) const { return unsupported_operation(); }
        virtual bool is_truthy() const = 0;
        virtual bool is_equal(const Object& other) const = 0;
    };

    class Nil : public Object
    {
    public:
        static constexpr std::string_view kString = "Nil";
        static const Object::Ptr kNilRef;

        std::string_view to_string() const override { return kString; }
        Type type() const override { return Type::Nil; }

    protected:
        bool is_truthy() const override { return false; }
        bool is_equal(const Object& other) const { return other.type() == Object::Type::Nil; }
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
        bool is_truthy() const override { return value_ != 0.0; }
        bool is_equal(const Object& other) const;

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
        Object::Ptr multiply(const Object& other) const override;
        bool is_truthy() const override { return !string_.empty(); }
        bool is_equal(const Object& other) const;

    private:
        std::string string_;
    };

    class Boolean : public Object
    {
    public:
        static const Object::Ptr kTrueRef;
        static const Object::Ptr kFalseRef;

        Boolean(bool value);
        Boolean(std::string_view value);

        std::string_view to_string() const override;
        Type type() const override { return Object::Type::Boolean; }

    protected:
        bool is_truthy() const override { return value_; }
        bool is_equal(const Object& other) const override;

    private:
        bool value_;
        std::string string_;
    };

    constexpr const char* to_string(Object::Type object_type)
    {
        using enum Object::Type;
        switch (object_type) {
            case Nil:
                return "Nil";
            case Number:
                return "Number";
            case String:
                return "String";
            case Boolean:
                return "Boolean";
        }
        return "UNKNOWN";
    }
} // namespace Lox

template<>
struct fmt::formatter<Lox::Object::Type> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(Lox::Object::Type type, FormatContext& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}", Lox::to_string(type));
    }
};

#endif // LOX_OBJECT_H
