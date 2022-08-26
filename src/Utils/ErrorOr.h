//
// Created by mythi on 26/08/22.
//

#ifndef HASHA_ERROROR_H
#define HASHA_ERROROR_H

#include <variant>
#include <string>
#include <optional>

namespace hasha {

#define TRY(expression)                                                        \
  ({                                                                           \
    auto _temporary_result = (expression);                                     \
    if (_temporary_result.is_error()) [[unlikely]]                             \
      return _temporary_result.release_error();                                \
    _temporary_result.release_value();                                         \
  })

    using ErrorType = std::string;

    template<typename T>
    class [[nodiscard]] ErrorOr final : public std::variant<T, ErrorType> {
        using std::variant<T, ErrorType>::variant;

    public:
        template<typename U>
        explicit ErrorOr(U &&value)requires (!std::is_same<std::remove_reference<U>, ErrorOr<T>>::value)
                : std::variant<T, ErrorType>(std::forward<U>(value)) {}

        T &value() { return std::get<T>(*this); }

        T const &value() const { return std::get<T>(*this); }

        ErrorType &error() { return std::get<ErrorType>(*this); }

        [[nodiscard]] ErrorType const &error() const {

            return std::get<ErrorType>(*this);
        }

        [[nodiscard]] bool is_error() const {

            return std::holds_alternative<ErrorType>(*this);
        }

        T release_value() { return std::move(value()); }

        ErrorType release_error() { return std::move(error()); }
    };

    template<>
    class [[nodiscard]] ErrorOr<void> {
    public:
        ErrorOr(ErrorType error) : m_error(move(error)) {}

        ErrorOr() = default;

        ErrorOr(ErrorOr &&other) noexcept = default;

        ErrorOr(ErrorOr const &other) = default;

        ~ErrorOr() = default;

        ErrorOr &operator=(ErrorOr &&other) = default;

        ErrorOr &operator=(ErrorOr const &other) = default;

        ErrorType &error() { return m_error.value(); }

        [[nodiscard]] bool is_error() const { return m_error.has_value(); }

        ErrorType release_error() { return std::move(m_error.value()); }

        void release_value() {}

    private:
        std::optional<ErrorType> m_error;
    };
} // hasha

#endif //HASHA_ERROROR_H
