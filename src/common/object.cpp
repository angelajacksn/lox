#include "object.h"

namespace Lox
{
    const Object::Ptr Nil::kNilRef = Object::create<Nil>();
    const Object::Ptr Boolean::kTrueRef = Object::create<Boolean>(true);
    const Object::Ptr Boolean::kFalseRef = Object::create<Boolean>(false);

    Number::Number(double value)
        : value_(value)
        , string_(std::to_string(value))
    {
    }

    Number::Number(std::string_view value)
        : value_(std::stod(value.data()))
        , string_(value)
    {
    }

    Object::Ptr Number::add(const Object& other) const
    {
        if (auto number = dynamic_cast<const Number*>(&other))
            return Object::create<Number>(value_ + number->value_);

        return unsupported_operation();
    }

    Object::Ptr Number::subtract(const Object& other) const
    {
        if (auto number = dynamic_cast<const Number*>(&other))
            return Object::create<Number>(value_ - number->value_);

        return unsupported_operation();
    }

    Object::Ptr Number::negate() const
    {
        return Object::create<Number>(-value_);
    }

    Object::Ptr Number::multiply(const Object& other) const
    {
        return unsupported_operation();
    }
    Object::Ptr Number::divide(const Object& other) const
    {
        if (auto number = dynamic_cast<const Number*>(&other))
            return Object::create<Number>(value_ * number->value_);

        return unsupported_operation();
    }
    Object::Ptr Number::modulus(const Object& other) const
    {
        if (auto number = dynamic_cast<const Number*>(&other))
            return Object::create<Number>(std::fmod(value_, number->value_));

        return unsupported_operation();
    }

    String::String(std::string value)
        : string_(std::move(value))
    {
    }

    String::String(std::string_view value)
        : string_(value)
    {
    }

    Object::Ptr String::add(const Object& other) const
    {
        if (auto string = dynamic_cast<const String*>(&other))
            return Object::create<String>(string_ + string->string_);

        return unsupported_operation();
    }

    Object::Ptr String::multiply(const Object& other) const
    {
        if (auto number = dynamic_cast<const Number*>(&other)) {
            auto multiplied_string = string_;
            for (size_t i = 1; i < number->value(); ++i)
                multiplied_string += string_;
            return Object::create<String>(multiplied_string);
        }
        return unsupported_operation();
    }

    Boolean::Boolean(bool value)
        : value_(value)
        , string_(value ? "true" : "false")
    {
    }

    Boolean::Boolean(std::string_view value)
        : value_(value == "true" ? true : false)
        , string_(value)
    {
    }

    std::string_view Boolean::to_string() const
    {
        return string_;
    }
} // namespace Lox