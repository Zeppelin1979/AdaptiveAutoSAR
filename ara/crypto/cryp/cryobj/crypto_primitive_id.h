#ifndef ARA_CRYPTO_CRYP_CRYOBJ_CRYPTO_PRIMITIVE_ID_H
#define ARA_CRYPTO_CRYP_CRYOBJ_CRYPTO_PRIMITIVE_ID_H

#include "ara/crypto/cryp/cryobj/crypto_primitive_id.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_20600]
             * Common interface for identification of all Crypto Primitives and their keys & parameters.
             */
            class CryptoPrimitiveId
            {
            public:

                /**
                 * @brief [SWS_CRYPT_20641]
                 * Type definition of vendor specific binary Crypto Primitive ID.
                 */
                using AlgId = CryptoAlgId;
                
                /**
                 * @brief [SWS_CRYPT_20644]
                 * type definition pointer
                 */
                using Uptrc = std::unique_ptr<const CryptoPrimitiveId>;

                /**
                 * @brief [SWS_CRYPT_20643]
                 * type definition pointer to const
                 */
                using Uptr = std::unique_ptr<CryptoPrimitiveId>;

                /**
                 * @brief [SWS_CRYPT_10808]
                 * Destroy the Crypto Primitive Id object
                 * 
                 */
                virtual ~CryptoPrimitiveId () noexcept=default;

                /**
                 * @brief [SWS_CRYPT_20652]
                 * Get vendor specific ID of the primitive.
                 * @return AlgId the binary Crypto Primitive ID
                 */
                virtual AlgId GetPrimitiveId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20651]
                 * Get a unified name of the primitive. The crypto primitive name can be fully or partially specified
                 * (see "Crypto Primitives Naming Convention" for more details). The life-time of the returned
                 * StringView instance should not exceed the life-time of this CryptoPrimitiveId instance!
                 * @return const ara::core::StringView the unified name of the crypto primitive
                 */
                virtual const ara::core::StringView GetPrimitiveName () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30212]
                 * Copy-assign another CryptoPrimitiveId to this instance.
                 * @param other the other instance
                 * @return CryptoPrimitiveId& *this, containing the contents of other
                 */
                CryptoPrimitiveId& operator= (const CryptoPrimitiveId &other)=default;

                /**
                 * @brief [SWS_CRYPT_30213]
                 * Move-assign another CryptoPrimitiveId to this instance.
                 * @param other the other instance
                 * @return CryptoPrimitiveId& *this, containing the contents of other
                 */
                CryptoPrimitiveId& operator= (const CryptoPrimitiveId &&other)=default;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_CRYOBJ_CRYPTO_PRIMITIVE_ID_H