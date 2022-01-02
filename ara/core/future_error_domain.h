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

#ifndef APD_ARA_CORE_FUTURE_ERROR_DOMAIN_H_
#define APD_ARA_CORE_FUTURE_ERROR_DOMAIN_H_

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

#include <cstdint>

namespace ara
{
    namespace core
    {

        /**
         * @brief Specifies the types of internal errors that can occur upon calling Future::get or Future::GetResult.
         *
         * These definitions are equivalent to the ones from std::future_errc.
         *
         * @uptrace{SWS_CORE_00400}
         */
        enum class FutureErrc : int32_t
        {
            kBrokenPromise = 101,            ///< the asynchronous task abandoned its shared state
            kFutureAlreadyRetrieved = 102,  ///< the contents of the shared state were already accessed
            kPromiseAlreadySatisfied = 103, ///< attempt to store a value into the shared state twice
            kNoState = 104,                  ///< attempt to access Promise or Future without an associated state
        };

        /**
         * @brief Exception type thrown by Future and Promise classes.
         *
         * @uptrace{SWS_CORE_00411}
         */
        class FutureException : public Exception
        {
        public:
            /**
             * @brief Construct a new FutureException from an ErrorCode.
             * @param err  the ErrorCode
             *
             * @uptrace{SWS_CORE_00412}
             */
            explicit FutureException(ErrorCode err) noexcept
                : Exception(std::move(err))
            {
            }
        };

        /**
         * @brief Error domain for errors originating from classes Future and Promise.
         *
         * @uptrace{SWS_CORE_00421}
         */
        class FutureErrorDomain final : public ErrorDomain
        {
            constexpr static ErrorDomain::IdType kId = 0x8000'0000'0000'0013;

        public:
            /// @brief Alias for the error code value enumeration
            ///
            /// @uptrace{SWS_CORE_00431}
            using Errc = FutureErrc;

            /// @brief Alias for the exception base class
            ///
            /// @uptrace{SWS_CORE_00432}
            using Exception = FutureException;

            /// @brief Default constructor
            ///
            /// @uptrace{SWS_CORE_00441}
            /// @uptrace{SWS_CORE_00013}
            constexpr FutureErrorDomain() noexcept
                : ErrorDomain(kId)
            {
            }

            /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
            /// @returns "Future"
            ///
            /// @uptrace{SWS_CORE_00442}
            /// @uptrace{SWS_CORE_00013}
            char const *Name() const noexcept override
            {
                return "Future";
            }

            /// @brief Translate an error code value into a text message.
            /// @param errorCode  the error code value
            /// @returns the text message, never nullptr
            ///
            /// @uptrace{SWS_CORE_00443}
            char const *Message(ErrorDomain::CodeType errorCode) const noexcept override
            {
                Errc const code = static_cast<Errc>(errorCode);
                switch (code)
                {
                case Errc::kBrokenPromise:
                    return "broken promise";
                case Errc::kFutureAlreadyRetrieved:
                    return "future already retrieved";
                case Errc::kPromiseAlreadySatisfied:
                    return "promise already satisfied";
                case Errc::kNoState:
                    return "no state associated with this future";
                default:
                    return "unknown future error";
                }
            }

            /// @brief Throw the exception type corresponding to the given ErrorCode.
            /// @param errorCode  the ErrorCode instance
            ///
            /// @uptrace{SWS_CORE_00444}
            void ThrowAsException(ErrorCode const &errorCode) const noexcept(false) override
            {
                ThrowOrTerminate<Exception>(errorCode);
            }
        };

        namespace internal
        {
            constexpr FutureErrorDomain g_futureErrorDomain;
        }

        /**
         * @brief Obtain the reference to the single global FutureErrorDomain instance.
         * @returns reference to the FutureErrorDomain instance
         *
         * @uptrace{SWS_CORE_00480}
         */
        inline constexpr ErrorDomain const &GetFutureDomain() noexcept
        {
            return internal::g_futureErrorDomain;
        }

        /**
         * @brief Create a new ErrorCode for FutureErrorDomain with the given support data type and message.
         *
         * The lifetime of the text pointed to by @a message must exceed that
         * of all uses of ErrorCode::UserMessage() on the new instance.
         *
         * @param code  an enumeration value from future_errc
         * @param data  a vendor-defined supplementary value
         * @param message  a user-defined context message (can be nullptr)
         * @returns the new ErrorCode instance
         *
         * @uptrace{SWS_CORE_00490}
         */
        inline constexpr ErrorCode MakeErrorCode(FutureErrc code,
                                                 ErrorDomain::SupportDataType data,
                                                 char const *message) noexcept
        {
            return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetFutureDomain(), data, message);
        }

    } // namespace core
} // namespace ara

#endif // APD_ARA_CORE_FUTURE_ERROR_DOMAIN_H_
