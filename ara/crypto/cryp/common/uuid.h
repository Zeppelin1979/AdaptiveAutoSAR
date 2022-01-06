#ifndef ARA_CRYPTO_CRYP_COMMON_UUID_H
#define ARA_CRYPTO_CRYP_COMMON_UUID_H

#include <cinttypes>

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_10400]
         * Definition of Universally Unique Identifier (UUID) type. Independently from internal definition
         * details of this structure, it’s size must be 16 bytes and entropy of this ID should be close to 128
         * bit!
         */
        struct Uuid
        {
            /**
             * @brief [SWS_CRYPT_10412]
             * Less significant QWORD.
             */
            std::uint64_t mQwordLs = 0u;

            /**
             * @brief [SWS_CRYPT_10413]
             * Most significant QWORD.
             */
            std::uint64_t mQwordMs = 0u;

            /**
             * @brief [SWS_CRYPT_10411]
             * Check whether this identifier is the "Nil UUID" (according to RFC4122).
             * @return true if this identifier is "Nil"
             * @return false otherwise
             */
            bool IsNil () const noexcept
            {
                return ((mQwordLs == 0u)&&(mQwordMs == 0u));
            }
        } ;

        /**
         * @brief [SWS_CRYPT_10451]
         * Comparison operator "equal" for Uuid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is equal to rhs
         * @return false otherwise
         */
        constexpr bool operator== (const Uuid &lhs, const Uuid &rhs) noexcept
        {
            return ((lhs.mQwordLs == rhs.mQwordLs) && (lhs.mQwordMs == rhs.mQwordMs));
        }

        /**
         * @brief [SWS_CRYPT_10452]
         * Comparison operator "less than" for Uuid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is less than rhs
         * @return false otherwise
         */
        constexpr bool operator< (const Uuid &lhs, const Uuid &rhs) noexcept
        {
            if (lhs.mQwordMs < rhs.mQwordMs)
            {
                return true;
            }
            else if (lhs.mQwordMs > rhs.mQwordMs)
            {
                return false;
            }
            else /* Most significant QWord is equal */
            {
                return lhs.mQwordLs < rhs.mQwordLs;
            }
        }

        /**
         * @brief [SWS_CRYPT_10453]
         * Comparison operator "greater than" for Uuid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is greater than rhs
         * @return false otherwise
         */
        constexpr bool operator> (const Uuid &lhs, const Uuid &rhs) noexcept
        {
            if (lhs.mQwordMs > rhs.mQwordMs)
            {
                return true;
            }
            else if (lhs.mQwordMs < rhs.mQwordMs)
            {
                return false;
            }
            else /* Most significant QWord is equal */
            {
                return lhs.mQwordLs > rhs.mQwordLs;
            }
        }

        /**
         * @brief [SWS_CRYPT_10454]
         * Comparison operator "not equal" for Uuid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true  if a binary representation of lhs is not equal to rhs
         * @return false otherwise
         */
        constexpr bool operator!= (const Uuid &lhs, const Uuid &rhs) noexcept
        {
            return !(lhs == rhs);
        };

        /**
         * @brief [SWS_CRYPT_10455]
         * Comparison operator "less than or equal" for Uuid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is less than or equal to rhs
         * @return false otherwise
         */
        constexpr bool operator<= (const Uuid &lhs, const Uuid &rhs) noexcept
        {
            return !(lhs > rhs);
        }

        /**
         * @brief [SWS_CRYPT_10456]
         * Comparison operator "greater than or equal" for Uuid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is greater than or equal to rhs
         * @return false otherwise
         */
        constexpr bool operator>= (const Uuid &lhs, const Uuid &rhs) noexcept
        {
            return !(lhs < rhs);
        }
    }
}

#endif // ARA_CRYPTO_CRYP_COMMON_UUID_H
