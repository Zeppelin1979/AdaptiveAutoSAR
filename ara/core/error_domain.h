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

#ifndef ARA_CORE_ERROR_DOMAIN_H
#define ARA_CORE_ERROR_DOMAIN_H

#include <cstdint>
#include <exception>

namespace ara
{
    namespace core
    {

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

        // forward declaration
        class ErrorCode;

        /// @uptrace{SWS_CORE_00110}
        class ErrorDomain
        {
        public:
            /// @uptrace{SWS_CORE_00121}
            using IdType = std::uint64_t;
            /// @uptrace{SWS_CORE_00122}
            using CodeType = std::int32_t;
            /// @uptrace{SWS_CORE_00123}
            using SupportDataType = std::int32_t;

            /// @uptrace{SWS_CORE_00131}
            ErrorDomain(ErrorDomain const &) = delete;
            /// @uptrace{SWS_CORE_00132}
            ErrorDomain(ErrorDomain &&) = delete;
            /// @uptrace{SWS_CORE_00133}
            ErrorDomain &operator=(ErrorDomain const &) = delete;
            /// @uptrace{SWS_CORE_00134}
            ErrorDomain &operator=(ErrorDomain &&) = delete;

            /// @uptrace{SWS_CORE_00152}
            virtual char const *Name() const noexcept = 0;

            /// @uptrace{SWS_CORE_00153}
            virtual char const *Message(CodeType errorCode) const noexcept = 0;

            /**
             * @brief Throws the given errorCode as Exception
             * @param errorCode error code to be thrown
             * @remark if ARA_NO_EXCEPTIONS is defined, this function call will terminate.
             * @uptrace{SWS_CORE_00154}
             */
            [[noreturn]] virtual void ThrowAsException(ErrorCode const &errorCode) const noexcept(false) = 0;

            /// @uptrace{SWS_CORE_00151}
            constexpr IdType Id() const noexcept
            {
                return mId;
            }

            /// @uptrace{SWS_CORE_00137}
            constexpr bool operator==(ErrorDomain const &other) const noexcept
            {
                return mId == other.mId;
            }

            /// @uptrace{SWS_CORE_00138}
            constexpr bool operator!=(ErrorDomain const &other) const noexcept
            {
                return mId != other.mId;
            }

        protected:
            /// @uptrace{SWS_CORE_00135}
            constexpr explicit ErrorDomain(IdType id) noexcept
                : mId(id)
            {
            }

            /// @brief Destructor
            ///
            /// This dtor is non-virtual (and trivial) so that this class is a literal type.
            /// While we do have virtual functions, we never need polymorphic destruction.
            ///
            /// @uptrace{SWS_CORE_00136}
            ~ErrorDomain() = default;

        private:
            IdType const mId;
        };

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

    } // namespace core
} // namespace ara

#endif // ARA_CORE_ERROR_DOMAIN_H
