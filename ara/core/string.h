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
 * @brief Interface to class ara::core::String
 */

#ifndef APD_ARA_CORE_STRING_H_
#define APD_ARA_CORE_STRING_H_

#include "ara/core/string_view.h"

#include <string>
#include <type_traits>
#include <functional>

namespace ara
{
    namespace core
    {

        namespace internal
        {

            template <typename CharT, typename Traits = std::char_traits<CharT>, typename Allocator = std::allocator<CharT>>
            class basic_string : public std::basic_string<CharT, Traits, Allocator>
            {
                using Base = std::basic_string<CharT, Traits, Allocator>;

                // Inherit most constructors of std::string
                // (except for copy/move and default ctor, see C++11, 12.9.3)
                using Base::Base;

            public:
                // Default constructors are not inherited by a using declaration, and since we are
                // also adding other constructors, no default one is being generated by the compiler.
                // Thus, we must define this explicitly.
                basic_string() noexcept(noexcept(Allocator()))
                    : Base(Allocator())
                {
                }

                // Single-argument copy/move constructors are not inherited by a using declaration,
                // but we want them for interoperability with std::string, so that we can support
                // assignment from std::string.

                basic_string(Base const &s)
                    : Base(s)
                {
                }

                basic_string(Base &&s) noexcept
                    : Base(std::move(s))
                {
                }

                // Standard copy and move constructors.

                basic_string(basic_string const &s)
                    : Base(s)
                {
                }

                basic_string(basic_string &&s) noexcept
                    : Base(std::move(s))
                {
                }

                // Inherit assignment operators from std::string. As this subclass does not add any additional
                // data member, there is no danger of slicing.
                using Base::operator=;

                // Standard copy and move assignment operators.

                basic_string &operator=(basic_string const &other)
                {
                    assign(other);
                    return *this;
                }

                basic_string &operator=(basic_string &&other)
                {
                    assign(std::move(other));
                    return *this;
                }

                //
                // Interoperability with StringView (taken from C++17)
                //

                using size_type = typename Base::size_type;
                using const_iterator = typename Base::const_iterator;
                using Base::npos;

                /// @uptrace{SWS_CORE_03302}
                explicit basic_string(basic_string_view<CharT, Traits> sv, Allocator const &a = Allocator())
                    : Base(sv.data(), sv.size(), a)
                {
                }

                /// @uptrace{SWS_CORE_03303}
                template <typename T>
                basic_string(T const &t, size_type pos, size_type n, Allocator const &a = Allocator())
                    : basic_string(StringView(t).substr(pos, n), a)
                {
                }

                /// @uptrace{SWS_CORE_03304}
                basic_string &operator=(basic_string_view<CharT, Traits> sv)
                {
                    return assign(sv);
                }

                /// @uptrace{SWS_CORE_03307}
                basic_string &operator+=(basic_string_view<CharT, Traits> sv)
                {
                    return append(sv);
                }

                using Base::append;

                /// @uptrace{SWS_CORE_03308}
                basic_string &append(basic_string_view<CharT, Traits> sv)
                {
                    Base::append(sv.data(), sv.size());
                    return *this;
                }

                /// @uptrace{SWS_CORE_03309}
                template <typename T,
                          typename = typename std::enable_if<std::is_convertible<T const &, basic_string_view<CharT, Traits>>::value && !std::is_convertible<T const &, CharT const *>::value>::type>
                basic_string &append(T const &t, size_type pos, size_type n = npos)
                {
                    // TODO: out_of_range if pos > sv.size()
                    basic_string_view<CharT, Traits> const sv = t;
                    size_type const rlen = std::min(n, size_type(sv.size() - pos));
                    Base::append(sv.data() + pos, rlen);
                    return *this;
                }

                using Base::assign;

                /// @uptrace{SWS_CORE_03305}
                basic_string &assign(basic_string_view<CharT, Traits> sv)
                {
                    Base::assign(sv.data(), sv.size());
                    return *this;
                }

                /// @uptrace{SWS_CORE_03306}
                template <typename T,
                          typename = typename std::enable_if<std::is_convertible<T const &, basic_string_view<CharT, Traits>>::value && !std::is_convertible<T const &, CharT const *>::value>::type>
                basic_string &assign(T const &t, size_type pos, size_type n = npos)
                {
                    // TODO: out_of_range if pos > sv.size()
                    basic_string_view<CharT, Traits> const sv = t;
                    size_type const rlen = std::min(n, size_type(Base::size() - pos));
                    Base::assign(sv.data() + pos, rlen);
                    return *this;
                }

                using Base::insert;

                /// @uptrace{SWS_CORE_03310}
                basic_string &insert(size_type pos, basic_string_view<CharT, Traits> sv)
                {
                    Base::insert(pos, sv.data(), sv.size());
                    return *this;
                }

                /// @uptrace{SWS_CORE_03311}
                template <typename T,
                          typename = typename std::enable_if<std::is_convertible<T const &, basic_string_view<CharT, Traits>>::value && !std::is_convertible<T const &, CharT const *>::value>::type>
                basic_string &insert(size_type pos1, T const &t, size_type pos2, size_type n = npos)
                {
                    // TODO: out_of_range if pos1 > size() or pos2 > sv.size()
                    basic_string_view<CharT, Traits> sv = t;
                    size_type const rlen = std::min(n, size_type(Base::size() - pos2));
                    Base::insert(pos1, sv.data() + pos2, rlen);
                    return *this;
                }

                using Base::replace;

                /// @uptrace{SWS_CORE_03312}
                basic_string &replace(size_type pos1, size_type n1, basic_string_view<CharT, Traits> sv)
                {
                    Base::replace(pos1, n1, sv.data(), sv.size());
                    return *this;
                }

                /// @uptrace{SWS_CORE_03313}
                template <typename T,
                          typename = typename std::enable_if<std::is_convertible<T const &, basic_string_view<CharT, Traits>>::value && !std::is_convertible<T const &, CharT const *>::value>::type>
                basic_string &replace(size_type pos1, size_type n1, T const &t, size_type pos2, size_type n2 = npos)
                {
                    // TODO: out_of_range if pos1 > size() or pos2 > sv.size()
                    basic_string_view<CharT, Traits> sv = t;
                    size_type const rlen = std::min(n2, size_type(sv.size() - pos2));
                    Base::replace(pos1, n1, sv.data() + pos2, rlen);
                    return *this;
                }

                /// @uptrace{SWS_CORE_03314}
                basic_string &replace(const_iterator i1, const_iterator i2, basic_string_view<CharT, Traits> sv)
                {
                    return replace(i1 - Base::begin(), i2 - i1, sv);
                }

                /// @uptrace{SWS_CORE_03301}
                operator basic_string_view<CharT, Traits>() const noexcept
                {
                    return StringView(Base::data(), Base::size());
                }

                using Base::find;
                using Base::find_first_not_of;
                using Base::find_first_of;
                using Base::find_last_not_of;
                using Base::find_last_of;
                using Base::rfind;

                /// @uptrace{SWS_CORE_03315}
                size_type find(basic_string_view<CharT, Traits> sv, size_type pos = 0) const noexcept
                {
                    return Base::find(sv.data(), pos, sv.size());
                }

                /// @uptrace{SWS_CORE_03316}
                size_type rfind(basic_string_view<CharT, Traits> sv, size_type pos = npos) const noexcept
                {
                    return Base::rfind(sv.data(), pos, sv.size());
                }

                /// @uptrace{SWS_CORE_03317}
                size_type find_first_of(basic_string_view<CharT, Traits> sv, size_type pos = 0) const noexcept
                {
                    return Base::find_first_of(sv.data(), pos, sv.size());
                }

                /// @uptrace{SWS_CORE_03318}
                size_type find_last_of(basic_string_view<CharT, Traits> sv, size_type pos = npos) const noexcept
                {
                    return Base::find_last_of(sv.data(), pos, sv.size());
                }

                /// @uptrace{SWS_CORE_03319}
                size_type find_first_not_of(basic_string_view<CharT, Traits> sv, size_type pos = 0) const noexcept
                {
                    return Base::find_first_not_of(sv.data(), pos, sv.size());
                }

                /// @uptrace{SWS_CORE_03320}
                size_type find_last_not_of(basic_string_view<CharT, Traits> sv, size_type pos = npos) const noexcept
                {
                    return Base::find_last_not_of(sv.data(), pos, sv.size());
                }

                using Base::compare;

                /// @uptrace{SWS_CORE_03321}
                int compare(basic_string_view<CharT, Traits> sv) const noexcept
                {
                    size_type const rlen = std::min(Base::size(), sv.size());
                    int const ret = Traits::compare(Base::data(), sv.data(), rlen);
                    if (ret == 0)
                    {
                        return (Base::size() < sv.size()) ? -1 : Base::size() > sv.size();
                    }
                    return ret;
                }

                /// @uptrace{SWS_CORE_03322}
                int compare(size_type pos1, size_type n1, basic_string_view<CharT, Traits> sv) const
                {
                    return basic_string_view<CharT, Traits>(Base::data(), Base::size()).substr(pos1, n1).compare(sv);
                }

                /// @uptrace{SWS_CORE_03323}
                template <typename T,
                          typename = typename std::enable_if<std::is_convertible<T const &, basic_string_view<CharT, Traits>>::value && !std::is_convertible<T const &, CharT const *>::value>::type>
                int compare(size_type pos1, size_type n1, T const &t, size_type pos2, size_type n2 = npos) const
                {
                    basic_string_view<CharT, Traits> const sv = t;
                    return basic_string_view<CharT, Traits>(Base::data(), Base::size())
                        .substr(pos1, n1)
                        .compare(sv.substr(pos2, n2));
                }
            };

        } // namespace internal

        /**
 * @brief Representation of a contiguous sequence of narrow characters
 *
 * @uptrace{SWS_CORE_03001}
 */
        using BasicString = internal::basic_string<char>;
        using String = internal::basic_string<char>;

        // Transitional compatibility name; should remove this before R18-10.
        using string = std::basic_string<char>;

        /// @brief Add overload of std::swap for String.
        ///
        /// We actually don't need this overload at all, because our implementation inherits
        /// from std::string and thus can simply use the overload for that.
        /// However, we need this symbol in order to provide uptracing.
        ///
        /// @param lhs  the first argument of the swap invocation
        /// @param rhs  the second argument of the swap invocation
        ///
        /// @uptrace{SWS_CORE_03296}
        template <typename Dummy = void,
                  typename = typename std::enable_if<!std::is_same<String, std::string>::value, Dummy>::type>
        void swap(String &lhs, String &rhs)
        {
            lhs.swap(rhs);
        }

    } // namespace core
} // namespace ara

namespace std
{

    /// @brief Specialization of std::hash for ara::core::String
    template <>
    struct hash<ara::core::String>
    {
        using result_type = std::size_t;

        /// @brief Function call operator to retrieve the hash value of ara::core::String.
        ///
        /// By providing this, ara::core::String can be used in std::unordered_map and std::unordered_set.
        ///
        /// @param k  the ara::core::String to be hashed.
        /// @returns the hash value
        result_type operator()(ara::core::String const &s) const noexcept
        {
            using std::hash;
            result_type ret = 0;
            for (result_type i = 0; i < s.length(); ++i)
            {
                ret += hash<char>()(s[i]);
            }
            return ret;
        }
    };

} // namespace std

#endif // APD_ARA_CORE_STRING_H_
