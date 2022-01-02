// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------

#ifndef APD_ARA_CORE_RESULT_H_
#define APD_ARA_CORE_RESULT_H_

#include "ara/core/error_code.h"

#include <boost/variant.hpp>
#include <system_error>
#include <type_traits>
#include <memory>
#include <utility>
#include <iostream>

namespace ara
{
    namespace core
    {

        /// @uptrace{SWS_CORE_00701}
        template <typename T, typename E = ErrorCode>
        class Result
        {
            boost::variant<T, E> mData;

            template <typename U, typename... Args>
            struct has_as_first_checker;

            template <typename U>
            struct has_as_first_checker<U> : std::false_type
            {
            };

            template <typename U, typename... Args>
            struct has_as_first_checker<U, U, Args...> : std::true_type
            {
            };

            template <typename U, typename A, typename... Args>
            struct has_as_first_checker<U, A, Args...> : std::false_type
            {
            };

            template <typename U, typename... Args>
            struct has_as_first
                : public has_as_first_checker<typename std::remove_reference<U>::type,
                                              typename std::remove_reference<Args>::type...>
            {
            };

        public:
            /// @uptrace{SWS_CORE_00711}
            using value_type = T;

            /// @uptrace{SWS_CORE_00712}
            using error_type = E;

            /// @uptrace{SWS_CORE_00731}
            static Result FromValue(T const &t)
            {
                return Result(t);
            }

            /// @uptrace{SWS_CORE_00732}
            static Result FromValue(T &&t)
            {
                return Result(std::move(t));
            }

            /// @uptrace{SWS_CORE_00733}
            template <typename... Args,
                      typename = typename std::enable_if<true                                           //
                                                         && std::is_constructible<T, Args &&...>::value //
                                                         && !has_as_first<T, Args...>::value            //
                                                         && !has_as_first<Result, Args...>::value       //
                                                         >::type                                        //
                      >
            static Result FromValue(Args &&...args)
            {
                return Result(T{std::forward<Args>(args)...});
            }

            // ----------------------------------------

            /// @uptrace{SWS_CORE_00734}
            static Result FromError(E const &e)
            {
                return Result(e);
            }

            /// @uptrace{SWS_CORE_00735}
            static Result FromError(E &&e)
            {
                return Result(std::move(e));
            }

            /// @uptrace{SWS_CORE_00736}
            template <typename... Args,
                      typename = typename std::enable_if<true                                           //
                                                         && std::is_constructible<E, Args &&...>::value //
                                                         && !has_as_first<E, Args...>::value            //
                                                         && !has_as_first<Result, Args...>::value       //
                                                         >::type                                        //
                      >
            static Result FromError(Args &&...args)
            {
                return Result(E{std::forward<Args>(args)...});
            }

            // ----------------------------------------

            /// @uptrace{SWS_CORE_00725}
            Result(Result const &other) = default;

            /// @uptrace{SWS_CORE_00726}
            Result(Result &&other) = default;

            /// @uptrace{SWS_CORE_00741}
            Result &operator=(Result const &other) = default;

            /// @uptrace{SWS_CORE_00742}
            Result &operator=(Result &&other) = default;

            /// @uptrace{SWS_CORE_00721}
            Result(T const &t)
                : mData(t)
            {
            }

            /// @uptrace{SWS_CORE_00722}
            Result(T &&t)
                : mData(std::move(t))
            {
            }

            /// @uptrace{SWS_CORE_00723}
            explicit Result(E const &e)
                : mData(e)
            {
            }

            /// @uptrace{SWS_CORE_00724}
            explicit Result(E &&e)
                : mData(std::move(e))
            {
            }

            // ----------------------------------------

            /// @uptrace{SWS_CORE_00743}
            template <typename... Args>
            void EmplaceValue(Args &&...args)
            {
                // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
                mData = std::move(T(std::forward<Args>(args)...));
            }

            /// @uptrace{SWS_CORE_00744}
            template <typename... Args>
            void EmplaceError(Args &&...args)
            {
                // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
                mData = std::move(E(std::forward<Args>(args)...));
            }

            /// @uptrace{SWS_CORE_00745}
            void Swap(Result &other) noexcept(
                std::is_nothrow_move_constructible<T>::value &&std::is_nothrow_move_assignable<T>::value)
            {
                using std::swap;
                swap(mData, other.mData);
            }

            /// @uptrace{SWS_CORE_00752}
            explicit operator bool() const noexcept
            {
                return HasValue();
            }

            /// @uptrace{SWS_CORE_00751}
            bool HasValue() const noexcept
            {
                return mData.which() == 0;
            }

            /// @uptrace{SWS_CORE_00753}
            T const &operator*() const
            {
                return Value();
            }

            /// @uptrace{SWS_CORE_00754}
            T const *operator->() const
            {
                return std::addressof(Value());
            }

            /// @uptrace{SWS_CORE_00755}
            T const &Value() const &
            {
                T const *ptr = boost::get<T>(&mData);
                if (ptr)
                    return *ptr;
                std::cout << "__ value() called but NOT a value!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00756}
            T &&Value() &&
            {
                T *ptr = boost::get<T>(&mData);
                if (ptr)
                    return std::move(*ptr);
                std::cout << "__ value() called but NOT a value!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00757}
            E const &Error() const &
            {
                E const *ptr = boost::get<E>(&mData);
                if (ptr)
                    return *ptr;
                std::cout << "__ error() called but NOT an error!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00758}
            E &&Error() &&
            {
                E *ptr = boost::get<E>(&mData);
                if (ptr)
                    return std::move(*ptr);
                std::cout << "__ error() called but NOT an error!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00761}
            template <typename U>
            T ValueOr(U &&defaultValue) const &
            {
                return HasValue() ? Value() : static_cast<T>(std::forward<U>(defaultValue));
            }

            /// @uptrace{SWS_CORE_00762}
            template <typename U>
            T ValueOr(U &&defaultValue) &&
            {
                return HasValue() ? std::move(Value()) : static_cast<T>(std::forward<U>(defaultValue));
            }

            /// @uptrace{SWS_CORE_00763}
            template <typename G>
            E ErrorOr(G &&defaultError) const
            {
                return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
            }

            /// @uptrace{SWS_CORE_00765}
            template <typename G>
            bool CheckError(G &&e) const
            {
                return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(e)));
            }

#ifndef ARA_NO_EXCEPTIONS
            /// @uptrace{SWS_CORE_00766}
            T const &ValueOrThrow() noexcept(false)
            {
                T const *ptr = boost::get<T>(&mData);
                if (ptr)
                    return *ptr;

                // TODO: check if mData is uninitialized (-> monostate)
                E *e = boost::get<E>(&mData);

                e->ThrowAsException();
            }
#endif

            /// @uptrace{SWS_CORE_00767}
            template <typename F>
            T Resolve(F &&f) const
            {
                return HasValue() ? Value() : std::forward<F>(f)(Error());
            }

        private:
            // Re-implementation of C++14's std::enable_if_t
            template <bool Condition, typename U = void>
            using enable_if_t = typename std::enable_if<Condition, U>::type;

            // Re-implementation of C++14's std::result_of_t
            template <typename U>
            using result_of_t = typename std::result_of<U>::type;

            /// @brief Trait that detects whether a type is a Result<...>
            template <typename U>
            struct is_result : std::false_type
            {
            };

            template <typename U, typename G>
            struct is_result<Result<U, G>> : std::true_type
            {
            };

            template <typename F>
            using CallableReturnsResult = enable_if_t<is_result<result_of_t<F(T const &)>>::value>;

            template <typename F>
            using CallableReturnsNoResult = enable_if_t<!is_result<result_of_t<F(T const &)>>::value>;

        public:
            /// @uptrace{SWS_CORE_00768}
            template <typename F, typename = CallableReturnsResult<F>>
            auto Bind(F &&f) const -> decltype(f(Value()))
            {
                using U = decltype(f(Value()));
                return HasValue() ? std::forward<F>(f)(Value()) : U(Error());
            }

            /// @uptrace{SWS_CORE_00768}
            template <typename F, typename = CallableReturnsNoResult<F>>
            auto Bind(F &&f) const -> Result<decltype(f(Value())), E>
            {
                using U = decltype(f(Value()));
                using R = Result<U, E>;
                return HasValue() ? std::forward<F>(f)(Value()) : R(Error());
            }

            template <typename, typename>
            friend class Result;
        };

        /// @uptrace{SWS_CORE_00796}
        template <typename T, typename E>
        inline void swap(Result<T, E> &lhs, Result<T, E> &rhs) noexcept(noexcept(lhs.Swap(rhs)))
        {
            lhs.Swap(rhs);
        }

        //
        // Specialization for void
        //

        /// @uptrace{SWS_CORE_00801}
        template <typename E>
        class Result<void, E>
        {
            // Cannot use 'void' for variant, so define our own (default-constructible) dummy type instead.
            struct dummy
            {
            };
            using T = dummy;
            boost::variant<T, E> mData;

        public:
            /// @uptrace{SWS_CORE_00811}
            using value_type = void;

            /// @uptrace{SWS_CORE_00812}
            using error_type = E;

            /// @uptrace{SWS_CORE_00831}
            static Result FromValue()
            {
                return Result();
            }

            /// @uptrace{SWS_CORE_00834}
            static Result FromError(E const &e)
            {
                return Result(e);
            }

            /// @uptrace{SWS_CORE_00835}
            static Result FromError(E &&e)
            {
                return Result(std::move(e));
            }

            /// @uptrace{SWS_CORE_00836}
            template <typename... Args>
            static Result FromError(Args &&...args)
            {
                return Result(E{std::forward<Args>(args)...});
            }

            // ----------------------------------------

            /// @uptrace{SWS_CORE_00821}
            Result() noexcept
                : mData(T{})
            {
            }

            /// @uptrace{SWS_CORE_00823}
            explicit Result(E const &e)
                : mData(e)
            {
            }

            /// @uptrace{SWS_CORE_00824}
            explicit Result(E &&e)
                : mData(std::move(e))
            {
            }

            /// @uptrace{SWS_CORE_00825}
            Result(Result const &other)
                : mData(other.mData)
            {
            }

            /// @uptrace{SWS_CORE_00826}
            Result(Result &&other)
                : mData(std::move(other.mData))
            {
            }

            /// @uptrace{SWS_CORE_00827}
            ~Result()
            {
            }

            /// @uptrace{SWS_CORE_00841}
            Result &operator=(Result const &other)
            {
                mData = other.mData;
                return *this;
            }

            /// @uptrace{SWS_CORE_00842}
            Result &operator=(Result &&other)
            {
                mData = std::move(other.mData);
                return *this;
            }

            // ----------------------------------------

            /// @uptrace{SWS_CORE_00843}
            template <typename... Args>
            void EmplaceValue(Args &&...args) noexcept
            {
                mData = T(args...);
            }

            /// @uptrace{SWS_CORE_00844}
            template <typename... Args>
            void EmplaceError(Args &&...args)
            {
                // Unfortunately, Boost.Variant does not support emplace(), so we fall back to assignment here.
                mData = std::move(E(std::forward<Args>(args)...));
            }

            /// @uptrace{SWS_CORE_00845}
            void Swap(Result &other) noexcept
            {
                using std::swap;
                swap(mData, other.mData);
            }

            /// @uptrace{SWS_CORE_00852}
            explicit operator bool() const noexcept
            {
                return HasValue();
            }

            /// @uptrace{SWS_CORE_00851}
            bool HasValue() const noexcept
            {
                return mData.which() == 0;
            }

            /// @uptrace{SWS_CORE_00855}
            void Value() const
            {
                T const *ptr = boost::get<T>(&mData);
                if (ptr)
                    return;
                std::cout << "__ value() called but NOT a (void) value!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00857}
            E const &Error() const &
            {
                E const *ptr = boost::get<E>(&mData);
                if (ptr)
                    return *ptr;
                std::cout << "__ error() called but NOT an error!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00858}
            E &&Error() &&
            {
                E *ptr = boost::get<E>(&mData);
                if (ptr)
                    return std::move(*ptr);
                std::cout << "__ error() called but NOT an error!\n";
                std::terminate();
            }

            /// @uptrace{SWS_CORE_00863}
            template <typename G>
            E ErrorOr(G &&defaultError) const
            {
                return HasValue() ? static_cast<E>(std::forward<G>(defaultError)) : Error();
            }

            /// @uptrace{SWS_CORE_00865}
            template <typename G>
            bool CheckError(G &&e) const
            {
                return HasValue() ? false : (Error() == static_cast<E>(std::forward<G>(e)));
            }

#ifndef ARA_NO_EXCEPTIONS
            void ValueOrThrow() noexcept(false)
            {
                T const *ptr = boost::get<T>(&mData);
                if (ptr)
                    return;

                E *e = boost::get<E>(&mData);
                e->ThrowAsException();
            }
#endif
        };

    } // namespace core
} // namespace ara

#endif // APD_ARA_CORE_RESULT_H_
