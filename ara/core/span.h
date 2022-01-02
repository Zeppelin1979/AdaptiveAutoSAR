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

#ifndef APD_ARA_CORE_SPAN_H_
#define APD_ARA_CORE_SPAN_H_

#include "ara/core/array.h"
#include "ara/core/utility.h"

#include <iostream>
#include <type_traits>
#include <cstddef>
#include <cassert>

namespace ara
{
    namespace core
    {

        namespace
        {
            //*/
            constexpr static bool DEBUG_SPAN = false;
            /*/
            constexpr static bool DEBUG_SPAN = true;
            //*/

            template <typename... Args>
            static inline void xtrace(Args const &...args)
            {
                if (DEBUG_SPAN)
                {
                    using expander = int[];
                    expander{0, (static_cast<void>(std::cerr << args), 0)...};
                }
            }
        } // namespace

        /// @uptrace{SWS_CORE_01901}
        //constexpr std::ptrdiff_t dynamic_extent = -1;
        constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();

        template <typename T, std::size_t Extent = dynamic_extent>
        class Span;

        namespace internal
        {

            template <typename T>
            struct is_ara_core_span_checker : public std::false_type
            {
            };

            template <typename T, std::ptrdiff_t Extent>
            struct is_ara_core_span_checker<core::Span<T, Extent>> : public std::true_type
            {
            };

            template <typename T>
            struct is_ara_core_span : public is_ara_core_span_checker<typename std::remove_cv<T>::type>
            {
            };

            template <typename T>
            struct is_ara_core_array_checker : public std::false_type
            {
            };

            template <typename T, std::size_t N>
            struct is_ara_core_array_checker<core::Array<T, N>> : public std::true_type
            {
            };

            template <typename T>
            struct is_ara_core_array : public is_ara_core_array_checker<typename std::remove_cv<T>::type>
            {
            };

            template <typename, typename = size_t>
            struct is_complete : std::false_type
            {
            };

            template <typename T>
            struct is_complete<T, decltype(sizeof(T))> : std::true_type
            {
            };

        } // namespace internal

        /// @brief A view over a contiguous sequence of objects
        ///
        /// @uptrace{SWS_CORE_01900}
        template <typename T, std::size_t Extent = dynamic_extent>
        class Span
        {
            static_assert(Extent == dynamic_extent || Extent >= 0, "invalid extent for a Span");
            static_assert(std::is_object<T>::value, "Span cannot contain reference or void types");
            static_assert(!std::is_abstract<T>::value, "Span cannot contain abstract types");
            static_assert(internal::is_complete<T>::value, "Span cannot contain incomplete types");

            template <typename U>
            using type_of_data = decltype(ara::core::data(std::declval<U>()));

            template <typename U>
            using type_of_size = decltype(ara::core::size(std::declval<U>()));

        public:
            /// @uptrace{SWS_CORE_01911}
            using element_type = T;
            /// @uptrace{SWS_CORE_01912}
            using value_type = typename std::remove_cv<element_type>::type;
            /// @uptrace{SWS_CORE_01913}
            using index_type = std::size_t;
            /// @uptrace{SWS_CORE_01914}
            using difference_type = std::ptrdiff_t;
            /// @uptrace{SWS_CORE_01915}
            using pointer = element_type *;
            /// @uptrace{SWS_CORE_01916}
            using reference = element_type &;
            /// @uptrace{SWS_CORE_01917}
            using iterator = element_type *;
            /// @uptrace{SWS_CORE_01918}
            using const_iterator = element_type const *;
            /// @uptrace{SWS_CORE_01919}
            using reverse_iterator = std::reverse_iterator<iterator>;
            /// @uptrace{SWS_CORE_01920}
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;

            // Not in C++ standard, but we need it for GMock's IsSize()
            /// @uptrace{SWS_CORE_01921}
            using size_type = index_type;

            /// @uptrace{SWS_CORE_01922}
            using const_pointer = const element_type *;

            /// @uptrace{SWS_CORE_01923}
            using const_reference = const element_type &;

            /// @uptrace{SWS_CORE_01931}
            static constexpr size_type extent = Extent;

            // 21.7.3.2, constructors, copy, and assignment

            /// @uptrace{SWS_CORE_01941}
            template <typename U = void, typename = typename std::enable_if<Extent == dynamic_extent || Extent == 0, U>::type>
            constexpr Span() noexcept
                : mData(nullptr), mExtent(0)
            {
                xtrace("__ Span()\n");
            }

            /// @uptrace{SWS_CORE_01942}
            constexpr Span(pointer ptr, index_type count)
                : mData(ptr), mExtent(count)
            {
                xtrace("__ Span(T*, size_t)\n");
                xtrace("____ ptr = ", ptr, ", count = ", count, " (ex = ", Extent, ")\n");
                if (Extent != dynamic_extent && count != Extent)
                {
                    assert(!"inconsistent extent");
                }
            }

            /// @uptrace{SWS_CORE_01943}
            constexpr Span(pointer firstElem, pointer lastElem)
                : Span(firstElem, lastElem - firstElem)
            {
                xtrace("__ Span(T*, T*)\n");
                assert(std::distance(firstElem, lastElem) >= 0);
            }

            /// @uptrace{SWS_CORE_01944}
            template <std::size_t N,
                      typename = typename std::enable_if<(Extent == dynamic_extent || static_cast<std::size_t>(Extent) == N) && std::is_convertible<typename std::remove_pointer<type_of_data<element_type (&)[N]>>::type (*)[],
                                                                                                                                                    element_type (*)[]>::value>::type>
            constexpr Span(element_type (&arr)[N]) noexcept
                : Span(std::addressof(arr[0]), N)
            {
                xtrace("__ Span(raw)\n");
            }

            /// @uptrace{SWS_CORE_01945}
            template <std::size_t N,
                      typename = typename std::enable_if<(Extent == dynamic_extent || static_cast<std::size_t>(Extent) == N) && std::is_convertible<
                                                                                                                                    typename std::remove_pointer<decltype(std::declval<Array<value_type, N>>().data())>::type (*)[],
                                                                                                                                    element_type (*)[]>::value>::type>
            constexpr Span(Array<value_type, N> &arr) noexcept
                : Span(arr.data(), N)
            {
                xtrace("__ Span(Array&)\n");
            }

            /// @uptrace{SWS_CORE_01946}
            template <std::size_t N,
                      typename = typename std::enable_if<(Extent == dynamic_extent || static_cast<std::size_t>(Extent) == N) && std::is_convertible<typename std::remove_pointer<decltype(std::declval<Array<value_type, N> const>().data())>::type (*)[],
                                                                                                                                                    element_type (*)[]>::value>::type>
            constexpr Span(Array<value_type, N> const &arr) noexcept
                : Span(arr.data(), N)
            {
                xtrace("__ Span(Array const&)\n");
            }

            /// @uptrace{SWS_CORE_01947}
            template <typename Container,
                      typename = typename std::enable_if<!internal::is_ara_core_span<Container>::value && !internal::is_ara_core_array<Container>::value && !std::is_array<Container>::value>::type>
            constexpr Span(Container &cont)
                : Span(core::data(cont), static_cast<index_type>(core::size(cont)))
            {
                xtrace("__ Span(Container&)\n");
                assert(std::distance(core::data(cont), core::data(cont) + core::size(cont)) >= 0);
            }

            /// @uptrace{SWS_CORE_01948}
            template <typename Container,
                      typename = typename std::enable_if<!internal::is_ara_core_span<Container>::value && !internal::is_ara_core_array<Container>::value && !std::is_array<Container>::value>::type>
            constexpr Span(Container const &cont)
                : Span(core::data(cont), static_cast<index_type>(core::size(cont)))
            {
                xtrace("__ Span(Container const&)\n");
                assert(std::distance(core::data(cont), core::data(cont) + core::size(cont)) >= 0);
            }

            /// @uptrace{SWS_CORE_01949}
            constexpr Span(Span const &other) noexcept = default;

            /// @brief Converting constructor
            ///
            /// This ctor allows assignment of a cv-Span<> from a normal Span<>,
            /// and also of a dynamic_extent-Span<> from a static extent-one.
            ///
            /// @uptrace{SWS_CORE_01950}
            template <typename U,
                      std::ptrdiff_t N,
                      typename = typename std::enable_if<(Extent == dynamic_extent || Extent == N) && std::is_convertible<U (*)[], element_type (*)[]>::value>::type *>
            constexpr Span(Span<U, N> const &s) noexcept
                : Span(s.data(), s.size())
            {
                xtrace("__ converting ctor from N ", N, "\n");
            }

            /// @uptrace{SWS_CORE_01951}
            ~Span() noexcept = default;

            // Not "constexpr" because that would make it also "const" on C++11 compilers.
            /// @uptrace{SWS_CORE_01952}
            Span &operator=(Span const &other) noexcept = default;

            // 21.7.3.3, subviews

            /// @uptrace{SWS_CORE_01961}
            template <std::ptrdiff_t Count>
            constexpr Span<element_type, Count> first() const
            {
                static_assert(0 <= Count, "subview size cannot be negative");
                assert(Count <= size());

                return {mData, Count};
            }

            /// @uptrace{SWS_CORE_01962}
            constexpr Span<element_type, dynamic_extent> first(index_type count) const
            {
                assert(0 <= count && count <= size());

                return {mData, count};
            }

            /// @uptrace{SWS_CORE_01963}
            template <std::ptrdiff_t Count>
            constexpr Span<element_type, Count> last() const
            {
                static_assert(0 <= Count, "subview size cannot be negative");
                assert(Count <= size());

                return {mData + (size() - Count), Count};
            }

            /// @uptrace{SWS_CORE_01964}
            constexpr Span<element_type, dynamic_extent> last(index_type count) const
            {
                assert(0 <= count && count <= size());

                return {mData + (size() - count), count};
            }

            // TODO: need proper C++11 compatible return type
            /// @uptrace{SWS_CORE_01965}
            template <std::ptrdiff_t Offset, std::ptrdiff_t Count = dynamic_extent>
            constexpr auto subspan() const /*-> Span<element_type, XXX> */
            {
                assert(0 <= Offset && Offset <= size());
                assert(Count == dynamic_extent || (Count >= 0 && Offset + Count <= size()));

                constexpr index_type E = (Count != dynamic_extent) ? Count : (Extent != dynamic_extent ? Extent - Offset : dynamic_extent);

                return Span<element_type, E>(mData + Offset, Count != dynamic_extent ? Count : size() - Offset);
            }

            /// @uptrace{SWS_CORE_01966}
            constexpr Span<element_type, dynamic_extent> subspan(index_type offset, index_type count = dynamic_extent) const
            {
                assert(0 <= offset && offset <= size());
                assert(count == dynamic_extent || (count >= 0 && offset + count <= size()));

                return {mData + offset, count == dynamic_extent ? size() - offset : count};
            }

            // 21.7.3.4, observers

            /// @uptrace{SWS_CORE_01967}
            constexpr index_type size() const noexcept
            {
                return mExtent;
            }

            /// @uptrace{SWS_CORE_01968}
            constexpr index_type size_bytes() const noexcept
            {
                return mExtent * sizeof(T);
            }

            /// @uptrace{SWS_CORE_01969}
            constexpr bool empty() const noexcept
            {
                return mExtent == 0;
            }

            // 21.7.3.5, element access

            /// @uptrace{SWS_CORE_01970}
            constexpr reference operator[](index_type idx) const
            {
                return mData[idx];
            }

            /// @uptrace{SWS_CORE_01971}
            constexpr pointer data() const noexcept
            {
                return mData;
            }

            // 21.7.3.6, iterator support

            /// @uptrace{SWS_CORE_01972}
            constexpr iterator begin() const noexcept
            {
                return &mData[0];
            }

            /// @uptrace{SWS_CORE_01973}
            constexpr iterator end() const noexcept
            {
                return &mData[mExtent];
            }

            /// @uptrace{SWS_CORE_01974}
            constexpr const_iterator cbegin() const noexcept
            {
                return &mData[0];
            }

            /// @uptrace{SWS_CORE_01975}
            constexpr const_iterator cend() const noexcept
            {
                return &mData[mExtent];
            }

            /// @uptrace{SWS_CORE_01976}
            constexpr reverse_iterator rbegin() const noexcept
            {
                return reverse_iterator(end());
            }

            /// @uptrace{SWS_CORE_01977}
            constexpr reverse_iterator rend() const noexcept
            {
                return reverse_iterator(begin());
            }

            /// @uptrace{SWS_CORE_01978}
            constexpr const_reverse_iterator crbegin() const noexcept
            {
                return const_reverse_iterator(end());
            }

            /// @uptrace{SWS_CORE_01979}
            constexpr const_reverse_iterator crend() const noexcept
            {
                return const_reverse_iterator(begin());
            }

        private:
            pointer mData;
            index_type mExtent;
        };

#if (__cpp_deduction_guides - 0) >= 201703L
        template <typename T, std::size_t N>
        Span(T (&)[N]) -> Span<T, N>;

        template <typename T, std::size_t N>
        Span(Array<T, N> &) -> Span<T, N>;

        template <typename T, std::size_t N>
        Span(Array<T, N> const &) -> Span<T const, N>;

        template <typename Container>
        Span(Container &) -> Span<typename Container::value_type>;

        template <typename Container>
        Span(Container const &) -> Span<const typename Container::value_type>;
#endif // C++17 deduction guides

        /// @uptrace{SWS_CORE_01990}
        template <typename T>
        constexpr Span<T> MakeSpan(T *ptr, typename Span<T>::index_type count)
        {
            return Span<T>(ptr, count);
        }

        /// @uptrace{SWS_CORE_01991}
        template <typename T>
        constexpr Span<T> MakeSpan(T *firstElem, T *lastElem)
        {
            return Span<T>(firstElem, lastElem);
        }

        /// @uptrace{SWS_CORE_01992}
        template <typename T, std::size_t N>
        constexpr Span<T, N> MakeSpan(T (&arr)[N]) noexcept
        {
            return Span<T, N>(arr);
        }

        /// @uptrace{SWS_CORE_01993}
        template <typename Container>
        constexpr Span<typename Container::value_type> MakeSpan(Container &cont)
        {
            return Span<typename Container::value_type>(cont);
        }

        /// @uptrace{SWS_CORE_01994}
        template <typename Container>
        constexpr Span<typename Container::value_type const> MakeSpan(Container const &cont)
        {
            return Span<typename Container::value_type const>(cont);
        }

    } // namespace core
} // namespace ara

#endif // APD_ARA_CORE_SPAN_H_
