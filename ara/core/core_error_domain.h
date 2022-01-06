#ifndef ARA_CORE_ERROR_DOMAIN_H
#define ARA_CORE_ERROR_DOMAIN_H

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

#include <cstdint>

namespace ara
{
    namespace core
    {
        /// @uptrace{SWS_CORE_05200}
        enum class CoreErrc : ErrorDomain::CodeType
        {
            kInvalidArgument = 22,            ///< an invalid argument was passed to a function
            kInvalidMetaModelShortname = 137, ///< given string is not a valid model element shortname
            kInvalidMetaModelPath = 138,      ///< missing or invalid path to model element
        };

        class CoreException : public Exception
        {
        public:
            /// @uptrace{SWS_CORE_05212}
            explicit CoreException(ErrorCode err) noexcept : Exception(err)
            {
            }
        };

        class CoreErrorDomain final : public ErrorDomain
        {
            constexpr static ErrorDomain::IdType kId = 0x8000'0000'0000'0014;

        public:
            /// @brief Alias for the error code value enumeration
            ///
            /// @uptrace{SWS_CORE_05231}
            using Errc = CoreErrc;

            /// @brief Alias for the exception base class
            ///
            /// @uptrace{SWS_CORE_05232}
            using Exception = CoreException;

            /// @brief Default constructor
            ///
            /// @uptrace{SWS_CORE_05241}
            constexpr CoreErrorDomain() noexcept
                : ErrorDomain(kId)
            {
            }

            /// @brief Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
            /// @returns "Core"
            ///
            /// @uptrace{SWS_CORE_05242}
            char const *Name() const noexcept override
            {
                return "Core";
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
                case Errc::kInvalidArgument:
                    return "an invalid argument was passed to a function";
                case Errc::kInvalidMetaModelShortname:
                    return "given string is not a valid model element shortname";
                case Errc::kInvalidMetaModelPath:
                    return "missing or invalid path to model element";
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
            constexpr CoreErrorDomain g_coreErrorDomain;
        }

        /**
        * @brief Obtain the reference to the single global CoreErrorDomain instance.
        * @returns reference to the CoreErrorDomain instance
        *
        * @uptrace{SWS_CORE_05280}
        */
        inline constexpr ErrorDomain const &GetCoreErrorDomain() noexcept
        {
            return internal::g_coreErrorDomain;
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
        inline constexpr ErrorCode MakeErrorCode(CoreErrc code,
                                                 ErrorDomain::SupportDataType data,
                                                 char const *message) noexcept
        {
            return ErrorCode(static_cast<ErrorDomain::CodeType>(code), GetCoreErrorDomain(), data, message);
        }

    }
}

#endif // ARA_CORE_ERROR_DOMAIN_H