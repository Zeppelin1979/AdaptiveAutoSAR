#ifndef ARA_CRYPTO_CRYP_COMMON_CRYPTO_OBJECT_UID_H
#define ARA_CRYPTO_CRYP_COMMON_CRYPTO_OBJECT_UID_H

#include "ara/crypto/cryp/common/uuid.h"

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_10100]
         * Definition of Crypto Object Unique Identifier (COUID) type.
         */
        struct CryptoObjectUid
        {
            /**
             * @brief [SWS_CRYPT_10102]
             * Sequential value of a steady timer or simple counter, representing version of correspondent
             * Crypto Object.
             */
            std::uint64_t mVersionStamp = 0u;

            /**
             * @brief [SWS_CRYPT_10101]
             * UUID of a generator that has produced this COUID. This UUID can be associated with HSM,
             * physical host/ECU or VM.
             */
            Uuid mGeneratorUid;
            
            /**
             * @brief [SWS_CRYPT_10112]
             * Check whether this identifier was generated earlier than the one provided by the argument.
             * @param[in] anotherId another identifier for the comparison
             * @return true  if this identifier was generated earlier than the anotherId
             * @return false otherwise
             */
            constexpr bool HasEarlierVersionThan (const CryptoObjectUid &anotherId) const noexcept;

            /**
             * @brief [SWS_CRYPT_10113]
             * Check whether this identifier was generated later than the one provided by the argument.
             * @param[in] anotherId another identifier for the comparison
             * @return true if this identifier was generated later than the anotherId
             * @return false otherwise
             */
            constexpr bool HasLaterVersionThan (const CryptoObjectUid &anotherId) const noexcept;

            /**
             * @brief [SWS_CRYPT_10111]
             * Check whether this identifier has a common source with the one provided by the argument.
             * @param[in] anotherId another identifier for the comparison
             * @return true if both identifiers has common source (identical value of the mGeneratorUid field)
             * @return false otherwise
             */
            constexpr bool HasSameSourceAs (const CryptoObjectUid &anotherId) const noexcept;

            /**
             * @brief [SWS_CRYPT_10114]
             * Check whether this identifier is "Nil".
             * @return true if this identifier is "Nil"
             * @return false otherwise
             */
            bool IsNil () const noexcept;

            /**
             * @brief [SWS_CRYPT_10115]
             * Check whether this object’s generator identifier is "Nil".
             * @return true if this identifier is "Nil"
             * @return false otherwise
             */
            bool SourceIsNil () const noexcept;
        };

        /**
         * @brief [SWS_CRYPT_10150]
         * Comparison operator "equal" for CryptoObjectUid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return bool true if all members’ values of lhs is equal to rhs, and false otherwise
         */
        constexpr bool operator== (const CryptoObjectUid &lhs, const CryptoObjectUid &rhs) noexcept;

        /**
         * @brief [SWS_CRYPT_10151]
         * Comparison operator "less than" for CryptoObjectUid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is less than rhs
         * @return false otherwise
         */
        constexpr bool operator< (const CryptoObjectUid &lhs, const CryptoObjectUid &rhs) noexcept;

        /**
         * @brief [SWS_CRYPT_10152]
         * Comparison operator "greater than" for CryptoObjectUid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is greater than rhs
         * @return false otherwise
         */
        constexpr bool operator> (const CryptoObjectUid &lhs, const CryptoObjectUid &rhs) noexcept;

        /**
         * @brief [SWS_CRYPT_10153]
         * Comparison operator "not equal" for CryptoObjectUid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if at least one member of lhs has a value not equal to correspondent member of rhs
         * @return false otherwise
         */
        constexpr bool operator!= (const CryptoObjectUid &lhs, const CryptoObjectUid &rhs) noexcept
        {
            return !(lhs==rhs);
        };

        /**
         * @brief [SWS_CRYPT_10154]
         * Comparison operator "less than or equal" for CryptoObjectUid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is less than or equal to rhs
         * @return false otherwise 
         */
        constexpr bool operator<= (const CryptoObjectUid &lhs, const CryptoObjectUid &rhs) noexcept;

        /**
         * @brief [SWS_CRYPT_10155]
         * Comparison operator "greater than or equal" for CryptoObjectUid operands.
         * @param lhs left-hand side operand
         * @param rhs right-hand side operand
         * @return true if a binary representation of lhs is greater than or equal to rhs
         * @return false otherwise 
         */
        constexpr bool operator>= (const CryptoObjectUid &lhs, const CryptoObjectUid &rhs) noexcept;
    }
}

#endif // ARA_CRYPTO_CRYP_COMMON_CRYPTO_OBJECT_UID_H
