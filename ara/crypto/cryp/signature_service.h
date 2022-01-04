#ifndef ARA_CRYPTO_CRYP_SIGNATURE_SERVICE_H
#define ARA_CRYPTO_CRYP_SIGNATURE_SERVICE_H

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_29000]
             * Extension meta-information service for signature contexts.
             */
            class SignatureService : public ExtensionService
            {
            public:

                /**
                 * @brief [SWS_CRYPT_29001]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SignatureService>;

                /**
                 * @brief [SWS_CRYPT_29003]
                 * Get an ID of hash algorithm required by current signature algorithm.
                 * @return CryptoPrimitiveId::AlgId required hash algorithm ID or kAlgIdAny if the
                 * signature algorithm specification does not include a
                 * concrete hash function
                 */
                virtual CryptoPrimitiveId::AlgId GetRequiredHashAlgId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29002]
                 * Get the hash size required by current signature algorithm.
                 * @return std::size_t required hash size in bytes
                 */
                virtual std::size_t GetRequiredHashSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29004]
                 * Get size of the signature value produced and required by the current algorithm.
                 * @return std::size_t size of the signature value in bytes
                 */
                virtual std::size_t GetSignatureSize () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SIGNATURE_SERVICE_H