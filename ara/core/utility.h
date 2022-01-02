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

#ifndef APD_ARA_CORE_UTILITY_H_
#define APD_ARA_CORE_UTILITY_H_

#include <initializer_list>
#include <iterator>
#include <cstddef>

namespace ara
{
    namespace core
    {

#if (__cpp_lib_nonmember_container_access - 0) >= 201411
        using std::data;
        using std::size;
#else
        // pre C++17

        /// @brief Return a pointer to the block of memory that contains the elements of a container.
        /// @tparam Container  a type with a data() method
        /// @param c  an instance of Container
        /// @returns a pointer to the first element of the container
        ///
        /// @uptrace{SWS_CORE_04110}
        template <typename Container>
        constexpr auto data(Container &c) -> decltype(c.data())
        {
            return c.data();
        }

        /// @brief Return a const_pointer to the block of memory that contains the elements of a container.
        /// @tparam Container  a type with a data() method
        /// @param c  an instance of Container
        /// @returns a pointer to the first element of the container
        ///
        /// @uptrace{SWS_CORE_04111}
        template <typename Container>
        constexpr auto data(Container const &c) -> decltype(c.data())
        {
            return c.data();
        }

        /// @uptrace{SWS_CORE_04130}
        template <typename Container>
        constexpr auto empty (const Container &c) -> decltype(c.empty())
        {
            return c.empty();
        }

        /// @brief Return a pointer to the block of memory that contains the elements of a raw array.
        /// @tparam T  the type of array elements
        /// @tparam N  the number of elements in the array
        /// @param array  reference to a raw array
        /// @returns a pointer to the first element of the array
        ///
        /// @uptrace{SWS_CORE_04112}
        template <typename T, std::size_t N>
        constexpr T *data(T (&array)[N]) noexcept
        {
            return array;
        }

        /// @uptrace{SWS_CORE_04131}
        template <typename T, std::size_t N>
        constexpr bool empty (const T(&array)[N]) noexcept
        {
            return false;
        }

        /// @brief Return a pointer to the block of memory that contains the elements of a std::initializer_list.
        /// @tparam E  the type of elements in the std::initializer_list
        /// @param il  the std::initializer_list
        /// @returns a pointer to the first element of the std::initializer_list
        ///
        /// @uptrace{SWS_CORE_04113}
        template <typename E>
        constexpr E const *data(std::initializer_list<E> il) noexcept
        {
            return il.begin();
        }

         /// @uptrace{SWS_CORE_04132}
        template <typename E>
        constexpr bool empty (std::initializer_list< E > il) noexcept
        {
            return il.empty();
        }

       /// @brief Return the size of a container.
        /// @tparam Container  a type with a data() method
        /// @param c  an instance of Container
        /// @returns the size of the container
        ///
        /// @uptrace{SWS_CORE_04120}
        template <typename Container>
        constexpr auto size(Container const &c) -> decltype(c.size())
        {
            return c.size();
        }

        /// @brief Return the size of a raw array.
        /// @tparam T  the type of array elements
        /// @tparam N  the number of elements in the array
        /// @param array  reference to a raw array
        /// @returns the size of the array, i.e. N
        ///
        /// @uptrace{SWS_CORE_04121}
        template <typename T, std::size_t N>
        constexpr std::size_t size(T const (&array)[N]) noexcept
        {
            return N;
        }
#endif
        /// @uptrace{SWS_CORE_04011}
        struct in_place_t
        {
            explicit in_place_t ()=default;
        };

        /// @uptrace{SWS_CORE_04013} The singleton instance of in_place_t.
        constexpr in_place_t in_place;

        /// @uptrace{SWS_CORE_04021}
        template <typename T>
        struct in_place_type_t
        {
            explicit in_place_type_t ()=default;
        };

        /// @uptrace{SWS_CORE_04023} The singleton instances (one for each T) of in_place_type_t.
        template <typename T>
        constexpr in_place_type_t<T> in_place_type;

        /// @uptrace{SWS_CORE_04031}
        template <std::size_t I>
        struct in_place_index_t
        {
            explicit in_place_index_t ()=default;
        };

        /// @uptrace{SWS_CORE_04033} The singleton instances (one for each I) of in_place_index_t.
        template <std::size_t I>
        constexpr in_place_index_t<I> in_place_index {};

    } // namespace core
} // namespace ara

#endif // APD_ARA_CORE_UTILITY_H_
