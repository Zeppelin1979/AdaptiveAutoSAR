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
 * @brief Interface to class ara::core::Vector
 */

#ifndef APD_ARA_CORE_VECTOR_H_
#define APD_ARA_CORE_VECTOR_H_

#include <vector>
#include <memory>
#include <type_traits>

namespace ara
{
    namespace core
    {

        /**
         * @brief A sequence container that encapsulates dynamically sized arrays
         *
         * @tparam T  the type of contained values
         * @tparam Allocator  the type of Allocator to use for this container
         *
         * @uptrace{SWS_CORE_01301}
         */
        template <typename T, typename Allocator = std::allocator<T>>
        using Vector = std::vector<T, Allocator>;

        // Transitional compatibility name; should remove this before R18-10.
        template <typename T>
        using vector = std::vector<T>;

        /**
         * @brief Global operator== for Vector instances
         *
         * @uptrace{SWS_CORE_01390}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        inline bool operator==(Vector<T, Allocator> const &lhs, Vector<T, Allocator> const &rhs)
        {
            return std::operator==(lhs, rhs);
        }

        /**
         * @brief Global operator!= for Vector instances
         *
         * @uptrace{SWS_CORE_01391}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        inline bool operator!=(Vector<T, Allocator> const &lhs, Vector<T, Allocator> const &rhs)
        {
            return std::operator!=(lhs, rhs);
        }

        /**
         * @brief Global operator< for Vector instances
         *
         * @uptrace{SWS_CORE_01392}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        inline bool operator<(Vector<T, Allocator> const &lhs, Vector<T, Allocator> const &rhs)
        {
            return std::operator<(lhs, rhs);
        }

        /**
         * @brief Global operator<= for Vector instances
         *
         * @uptrace{SWS_CORE_01393}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        inline bool operator<=(Vector<T, Allocator> const &lhs, Vector<T, Allocator> const &rhs)
        {
            return std::operator<=(lhs, rhs);
        }

        /**
         * @brief Global operator> for Vector instances
         *
         * @uptrace{SWS_CORE_01394}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        inline bool operator>(Vector<T, Allocator> const &lhs, Vector<T, Allocator> const &rhs)
        {
            return std::operator>(lhs, rhs);
        }

        /**
         * @brief Global operator>= for Vector instances
         *
         * @uptrace{SWS_CORE_01395}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        inline bool operator>=(Vector<T, Allocator> const &lhs, Vector<T, Allocator> const &rhs)
        {
            return std::operator>=(lhs, rhs);
        }

        /**
         * @brief Add overload of swap for ara::core::Vector
         *
         * We actually don't need this overload at all, because our implementation is just
         * a type alias and thus can simply use the overload for the std:: type.
         * However, we need this symbol in order to provide uptracing.
         *
         * @tparam T  the type of values in the Vectors
         * @tparam Allocator  the Allocator used by the Vectors
         * @param lhs  the first argument of the swap invocation
         * @param rhs  the second argument of the swap invocation
         *
         * @uptrace{SWS_CORE_01396}
         */
        template <typename T,
                  typename Allocator,
                  typename = typename std::enable_if<!std::is_same<Vector<T, Allocator>, std::vector<T, Allocator>>::value>::type>
        void swap(Vector<T, Allocator> &lhs, Vector<T, Allocator> &rhs)
        {
            lhs.swap(rhs);
        }

    } // namespace core
} // namespace ara

#endif // APD_ARA_CORE_VECTOR_H_
