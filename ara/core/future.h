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

/**
 * @file
 * @brief Interface to class ara::core::Future
 *
 * ara::core::Future is a composition of basic features of std::future
 * and methods borrowed from the C++ proposal N3857.
 */

#ifndef ARA_CORE_FUTURE_H
#define ARA_CORE_FUTURE_H

#include <chrono>
#include <future>
#include <system_error>
#include <cassert>

#include "ara/core/future_error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/result.h"
#include "ara/core/posix_error_domain.h"
#include "ara/core/exception.h"
#include "internal/state.h"

#if !defined(ATTR_NODISCARD)
#if __cplusplus >= 201703L
#define ar_attribute_nodiscard [[nodiscard]]
#else
#if defined(__GNUC__) || defined(__clang__)
#define ar_attribute_nodiscard __attribute__((warn_unused_result))
#else
#define ar_attribute_nodiscard /* nothing */
#endif
#endif
#define ATTR_NODISCARD ar_attribute_nodiscard
#endif

namespace ara
{
    namespace core
    {

        /* Forward declaration */
        template <typename, typename>
        class Promise;

        /**
         * @brief Specifies the state of a Future as returned by wait_for() and wait_until().
         *
         * These definitions are equivalent to the ones from std::future_status. However, the
         * item std::future_status::deferred is not supported here.
         *
         * @uptrace{SWS_CORE_00320}
         */
        enum class FutureStatus : uint8_t
        {
            kReady = 1, ///< the shared state is ready
            kTimeout,   ///< the shared state did not become ready before the specified timeout has passed
        };

        inline std::ostream &operator<<(std::ostream &out, FutureException const &ex)
        {
            return (out << "FutureException: " << ex.Error() << " (" << ex.what() << ")");
        }

        /**
         * @brief Provides ara::core specific Future operations to collect the results of an asynchronous call.
         *
         * Much of its functionality is delegated to std::future and all methods that resemble std::future are guaranteed to
         * behave the same.
         *
         * If the valid() member function of an instance returns true, all other methods are guaranteed to work on that
         * instance. Otherwise, they may fail with or without an exception. A thrown exception will be of type
         * std::future_error.
         *
         * Having an invalid future will usually happen when the future was moved from using the move constructor or move
         * assignment.
         *
         * @uptrace{SWS_CORE_00321}
         */
        template <typename T, typename E = ErrorCode>
        class Future final
        {
            using R = Result<T, E>;

            using Lock = std::unique_lock<std::mutex>;

        public:
            /// Alias type for T
            using ValueType = T;
            /// Alias type for the Promise type collaborating with this Future type
            using PromiseType = Promise<T, E>;
            /// Alias type for the FutureStatus type
            using Status = FutureStatus;

            /**
             * @brief Default constructor
             *
             * @uptrace{SWS_CORE_00322}
             */
            Future() noexcept = default;

            /**
             * @brief Destructor for Future objects
             *
             * This will also disable any callback that has been set.
             */
            ~Future()
            {
                Lock lock(mutex_);

                if (extra_state_)
                {
                    extra_state_->SetCallback(nullptr);
                }
            }

            Future(Future const &) = delete;
            Future &operator=(Future const &) = delete;

            /**
             * @uptrace{SWS_CORE_00323}
             */
            Future(Future &&other) noexcept
                : lock_(other.mutex_), delegate_future_(std::move(other.delegate_future_)), extra_state_(std::move(other.extra_state_))
            {
                lock_.unlock();
            }

            /**
             * @uptrace{SWS_CORE_00325}
             */
            Future &operator=(Future &&other) noexcept
            {
                if (this != &other)
                {
                    Lock lhsLock(mutex_, std::defer_lock);
                    Lock rhsLock(other.mutex_, std::defer_lock);
                    std::lock(lhsLock, rhsLock);

                    delegate_future_ = std::move(other.delegate_future_);
                    extra_state_ = std::move(other.extra_state_);
                }
                return *this;
            }

            // Stop defining noexcept in order to let other exception be propageted to upper levels and fix some crashes
            ATTR_NODISCARD R GetResult()
            {
#ifndef ARA_NO_EXCEPTIONS
                try
                {
                    return delegate_future_.get();
                }
                catch (std::future_error const &ex)
                {
                    std::error_code const &ec = ex.code();
                    future_errc err;
                    if (ec == std::future_errc::broken_promise)
                    {
                        err = future_errc::broken_promise;
                    }
                    else if (ec == std::future_errc::future_already_retrieved)
                    {
                        err = future_errc::future_already_retrieved;
                    }
                    else if (ec == std::future_errc::promise_already_satisfied)
                    {
                        err = future_errc::promise_already_satisfied;
                    }
                    else if (ec == std::future_errc::no_state)
                    {
                        err = future_errc::no_state;
                    }
                    else
                    {
                        // Should rather use a vendor/demonstrator-specific ErrorDomain here?
                        return R::FromError(PosixErrc::invalid_argument);
                    }
                    R r = R::FromError(err);
                    return r;
                }
#else
                // TODO: Somehow query the future object whether it contains an exception,
                // and if so, translate it into a Result<...>
                // This does not seem possible with C++14's std::future, because it lacks boost::future's
                // has_exception() method. Unfortunately, boost::future cannot be compiled with
                // -fno-exceptions, so that one is out as well.
                return delegate_future_.get();
#endif
            }

#ifndef ARA_NO_EXCEPTIONS
            /**
             * @brief Get the value.
             *
             * This call blocks until the result or an exception is available.
             *
             * @returns value of type T
             *
             * @uptrace{SWS_CORE_00326}
             */
            T get()
            {
                return GetResult().ValueOrThrow();
            }
#endif

            /**
             * @brief Checks if the future is valid, i.e. if it has a shared state.
             *
             * @returns true if the future is usable, false otherwise
             *
             * @uptrace{SWS_CORE_00327}
             */
            bool valid() const noexcept
            {
                return delegate_future_.valid();
            }

            /**
             * @brief Waits for a value or an exception to be available.
             *
             * After this method returns, get() is guaranteed to not block and is_ready() will return true.
             *
             * @uptrace{SWS_CORE_00328}
             */
            void wait() const
            {
                delegate_future_.wait();
            }

            /**
             * @brief Wait for the given period.
             *
             * If the Future becomes ready or the timeout is reached, the method returns.
             *
             * @param timeout_duration maximal duration to wait for
             * @returns status that indicates whether the timeout hit or if a value is available
             *
             * @uptrace{SWS_CORE_00329}
             */
            template <typename Rep, typename Period>
            Status wait_for(std::chrono::duration<Rep, Period> const &timeout_duration) const
            {
                switch (delegate_future_.wait_for(timeout_duration))
                {
                case std::future_status::ready:
                    return Status::kReady;
                case std::future_status::timeout:
                    return Status::kTimeout;
                default:
                    assert(!"this std::future_status should not occur in our setup");
                }
            }

            /**
             * @brief Wait until the given time.
             *
             * If the Future becomes ready or the time is reached, the method returns.
             *
             * @param deadline latest point in time to wait
             * @returns status that indicates whether the time was reached or if a value is available
             *
             * @uptrace{SWS_CORE_00330}
             */
            template <typename Clock, typename Duration>
            Status wait_until(std::chrono::time_point<Clock, Duration> const &deadline) const
            {
                switch (delegate_future_.wait_until(deadline))
                {
                case std::future_status::ready:
                    return Status::kReady;
                case std::future_status::timeout:
                    return Status::kTimeout;
                default:
                    assert(!"this std::future_status should not occur in our setup");
                }
            }

            /**
             * @brief Register a function that gets called when the future becomes ready.
             *
             * When @a func is called, it is guaranteed that get() will not block.
             *
             * @a func may be called in the context of this call or in the context of Promise::set_value()
             * or Promise::set_exception() or somewhere else.
             *
             * @param func a Callable to register to get the Future result or an exception
             *
             * @uptrace{SWS_CORE_00331}
             */
            template <typename F>
            void then(F &&func)
            {
                Lock lock(mutex_);

                extra_state_->SetCallback_NoLock(std::forward<F>(func));
                if (is_ready())
                {
                    extra_state_->FireCallback_NoLock();
                }
            }

            /**
             * True when the future contains either a result or an exception.
             *
             * If is_ready() returns true, get() and the wait calls are guaranteed to not block.
             *
             * @returns true if the Future contains data, false otherwise
             *
             * @uptrace{SWS_CORE_00332}
             */
            bool is_ready() const
            {
                return std::future_status::ready == delegate_future_.wait_for(std::chrono::seconds::zero());
            }

        private:
            /**
             * @brief Constructs a Future from a given std::future and a pointer to the extra state.
             *
             * @param delegate_future std::future instance
             * @param extra_state state that is shared with the Promise
             */
            Future(std::future<R> &&delegate_future, internal::State::Ptr extra_state)
                : delegate_future_(std::move(delegate_future)), extra_state_(extra_state)
            {
            }

            std::mutex mutex_;
            Lock lock_; // this Lock is only necessary for the move constructor

            std::future<R> delegate_future_;
            internal::State::Ptr extra_state_;

            template <typename, typename>
            friend class Promise;
        };

    } // namespace core
} // namespace ara

#endif // ARA_CORE_FUTURE_H
