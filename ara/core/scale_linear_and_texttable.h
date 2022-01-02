#ifndef ADP_ARA_CORE_SCALE_LINEAR_AND_TEXTTABLE_H_
#define ADP_ARA_CORE_SCALE_LINEAR_AND_TEXTTABLE_H_

namespace ara
{
    namespace core
    {
        /**
         * @brief [SWS_CORE_08101]
         * A wrapper type extending the capabilities of an enum.
         * The definitions of this class have been carefully set up so that the behavior of this class is the
         * same as that of a regular enum type in C++17.
         * The type T is required to be an enum type.
         * @tparam T the type of the enum
         */
        template <typename T>
        class ScaleLinearAndTexttable final
        {
        private:
            UnderlyingType gValue;


        public:
            /// @uptrace{SWS_CORE_08111} The enum’s underlying type.
            using UnderlyingType = typename std::underlying_type<T>::type;

            /// @uptrace{SWS_CORE_08121} Default constructor. As with built-in enum types, this constructor leaves the value in an indeterminate state.
            constexpr ScaleLinearAndTexttable () noexcept=default;

            /// @uptrace{SWS_CORE_08123} Copy constructor.
            constexpr ScaleLinearAndTexttable (const ScaleLinearAndTexttable &other) noexcept=default
            {
                gValue = other.gValue;
            }

            /// @uptrace{SWS_CORE_08124} Move constructor.
            constexpr ScaleLinearAndTexttable (ScaleLinearAndTexttable &&other) noexcept=default;

            /// @uptrace{SWS_CORE_08127} Create an instance from a value of the enum.
            constexpr ScaleLinearAndTexttable (const T &v) noexcept
            {
                gValue = v;
            }

            /// @uptrace{SWS_CORE_08128} Create an instance from a value of the enum’s underlying type.
            explicit constexpr ScaleLinearAndTexttable (const UnderlyingType &v) noexcept
            {
                gValue = v;
            }

            /// @uptrace{SWS_CORE_08125} Copy assignment operator.
            constexpr ScaleLinearAndTexttable& operator= (const ScaleLinearAndTexttable &other) noexcept=default
            {
                gValue = other.gValue;
                return *this;
            }

            /// @uptrace{SWS_CORE_08126} Move assignment operator.
            constexpr ScaleLinearAndTexttable& operator= (const ScaleLinearAndTexttable &&other) noexcept=default
            {
                gValue = other.gValue;
                return *this;
            }

            /// @uptrace{SWS_CORE_08129} Assign the given enum value to this instance.
            constexpr ScaleLinearAndTexttable& operator= (const T &v) noexcept
            {
                gValue = v;
                return *this;
            }

            /// @uptrace{SWS_CORE_08122} Destructor.
            ~ScaleLinearAndTexttable () noexcept=default;

            /// @uptrace{SWS_CORE_08141} Conversion operator to the enum’s underlying type.
            explicit constexpr operator UnderlyingType () const noexcept
            {
                return UnderlyingType;
            }
        };

        /// @uptrace{SWS_CORE_08180} Return true if the numerical value of lhs is equal to the numerical value of rhs.
        template <typename T>
        constexpr bool operator== (const ScaleLinearAndTexttable< T > &lhs, const ScaleLinearAndTexttable< T > &rhs) noexcept
        {
            return lhs == rhs;
        }

    }
}

#endif // ADP_ARA_CORE_SCALE_LINEAR_AND_TEXTTABLE_H_