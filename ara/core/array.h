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

/// @file
/// @brief Interface to class ara::core::array

#ifndef ARA_CORE_ARRAY_H
#define ARA_CORE_ARRAY_H

#include <array>
#include <type_traits>

namespace ara
{
    namespace core
    {

        /// @brief A sequence container that encapsulates fixed sized arrays
        ///
        /// @tparam T  the type of contained values
        /// @tparam N  the number of elements in this Array
        ///
        /// @uptrace{SWS_CORE_01201}
        template <typename T, std::size_t N>
        using Array = std::array<T, N>;

        /// @brief Add overload of swap for ara::core::Array
        ///
        /// We actually don't need this overload at all, because our implementation is just
        /// a type alias and thus can simply use the overload for the std:: type.
        /// However, we need this symbol in order to provide uptracing.
        ///
        /// @tparam T  the type of values in the Arrays
        /// @tparam N  the size of the Arrays
        /// @param lhs  the first argument of the swap invocation
        /// @param rhs  the second argument of the swap invocation
        ///
        /// @uptrace{SWS_CORE_01296}
        template <typename T,
                  std::size_t N,
                  typename = typename std::enable_if<!std::is_same<Array<T, N>, std::array<T, N>>::value>::type>
        void swap(Array<T, N> &lhs, Array<T, N> &rhs)
        {
            lhs.swap(rhs);
        }

    } // namespace core
} // namespace ara

#endif // ARA_CORE_ARRAY_H
