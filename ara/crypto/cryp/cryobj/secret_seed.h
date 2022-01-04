#ifndef ARA_CRYPTO_CRYP_SECRET_SEED_H
#define ARA_CRYPTO_CRYP_SECRET_SEED_H

#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23000]
             * Secret Seed object interface. This object contains a raw bit sequence of specific length (without
             * any filtering of allowed/disallowed values)! The secret seed value can be loaded only to a
             * non-key input of a cryptographic transformation context (like IV/salt/nonce)! Bit length of the
             * secret seed is specific to concret crypto algorithm and corresponds to maximum of its input/
             * output/salt block-length.
             */
            class SecretSeed : public RestrictedUseObject
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23001]
                 * Unique smart pointer of a constant interface instance.
                 */
                using Uptrc = std::unique_ptr<const SecretSeed>;

                /**
                 * @brief [SWS_CRYPT_23002]
                 * Unique smart pointer of a volatile interface instance.
                 */
                using Uptr = std::unique_ptr<SecretSeed>;

                /**
                 * @brief [SWS_CRYPT_23003]
                 * Static mapping of this interface to specific value of CryptoObjectType enumeration.
                 */
                static const CryptoObjectType kObjectType = CryptoObjectType::kSecretSeed;

                /**
                 * @brief [SWS_CRYPT_23011]
                 * Clone this Secret Seed object to new session object. Created object instance is session and
                 * non-exportable, AllowedUsageFlags attribute of the "cloned" object is identical to this attribute
                 * of the source object! If size of the xorDelta argument is less than the value size of this seed
                 * then only correspondent number of leading bytes of the original seed should be XOR-ed, but
                 * the rest should be copied without change. If size of the xorDelta argument is larger than the
                 * value size of this seed then extra bytes of the xorDelta should be ignored.
                 * @param[in] xorDelta optional "delta" value that must be XOR-ed with the "cloned" copy of the original seed
                 * @return ara::core::Result<SecretSeed::Uptr> unique smart pointer to "cloned" session Secret Seed object
                 */
                virtual ara::core::Result<SecretSeed::Uptr> Clone (ReadOnlyMemRegion xorDelta=ReadOnlyMemRegion()) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23012]
                 * Set value of this seed object as a "jump" from an initial state to specified number of steps,
                 * according to "counting" expression defined by a cryptographic algorithm associated with this
                 * object. steps may have positive and negative values that correspond to forward and backward
                 * direction of the "jump" respectively, but 0 value means only copy from value to this seed object.
                 * Seed size of the from argument always must be greater or equal of this seed size.
                 * @param[in] from source object that keeps the initial value for jumping from
                 * @param[in] steps number of steps for the "jump"
                 * @return ara::core::Result<void> reference to this updated object
                 * @exception CryptoErrorDomain::kIncompatibleObject if this object and the from argument are associated with incompatible cryptographic algorithms
                 * @exception CryptoErrorDomain::kInvalidInputSize if value size of the from seed is less then value size of this one
                 */
                virtual ara::core::Result<void> JumpFrom (const SecretSeed &from, std::int64_t steps) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23014]
                 * Set value of this seed object as a "jump" from it’s current state to specified number of steps,
                 * according to "counting" expression defined by a cryptographic algorithm associated with this
                 * object. steps may have positive and negative values that correspond to forward and backward
                 * direction of the "jump" respectively, but 0 value means no changes of the current seed value.
                 * @param steps number of "steps" for jumping (forward or backward) from the current state
                 * @return SecretSeed& reference to this updated object
                 */
                virtual SecretSeed& Jump (std::int64_t steps) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23013]
                 * Set next value of the secret seed according to "counting" expression defined by a cryptographic
                 * algorithm associated with this object. If the associated cryptographic algorithm doesn’t specify
                 * a "counting" expression then generic increment operation must be implemented as default
                 * (little-endian notation, i.e. first byte is least significant).
                 * @return SecretSeed& 
                 */
                virtual SecretSeed& Next () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23015]
                 * XOR value of this seed object with another one and save result to this object. If seed sizes in
                 * this object and in the source argument are different then only correspondent number of leading
                 * bytes in this seed object should be updated.
                 * @param[in] source right argument for the XOR operation
                 * @return SecretSeed & reference to this updated object
                 */
                virtual SecretSeed& operator^= (const SecretSeed &source) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23016]
                 * XOR value of this seed object with provided memory region and save result to this object. If
                 * seed sizes in this object and in the source argument are different then only correspondent
                 * number of leading bytes of this seed object should be updated.
                 * @param source right argument for the XOR operation
                 * @return SecretSeed& reference to this updated object
                 */
                virtual SecretSeed& operator^= (ReadOnlyMemRegion source) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SECRET_SEED_H