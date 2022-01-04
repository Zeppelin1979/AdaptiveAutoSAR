#ifndef ARA_CRYPTO_CRYP_DIGSET_SERVICE_H
#define ARA_CRYPTO_CRYP_DIGSET_SERVICE_H

#include "ara/crypto/cryp/block_service.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_29010]
             * Extension meta-information service for digest producing contexts.
             */
            class DigestService : public BlockService
            {
            public:

                /**
                 * @brief [SWS_CRYPT_29011]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<DigestService>;

                /**
                 * @brief [SWS_CRYPT_29013]
                 * Compare the calculated digest against an expected value. Entire digest value is kept in the
                 * context up to next call Start(), therefore any its part can be verified again or extracted. If (full_
                 * digest_size <= offset) || (expected.size() == 0) then return false; else comparison_size =
                 * min(expected.size(), (full_digest_size - offset)) bytes. This method can be implemented as
                 * "inline" after standartization of function ara::core::memcmp().
                 * @param[in] expected the memory region containing an expected digest value
                 * @param[in] offset position of the first byte in calculated digest for the comparison starting
                 * @return ara::core::Result<bool> true if the expected bytes sequence is identical to first bytes of calculated digest
                 * @exception CryptoErrorDomain::kProcessingNotFinished if the digest calculation was not finished by a call of the Finish() method
                 * @exception CryptoErrorDomain::kBruteForceRisk if the buffered digest belongs to a MAC/HMAC/AE/AEAD context, which was initialized by a key without kAllowSignature permission, but actual size of requested digest is less than 8 bytes (it is a protection from the brute-force attack)
                 */
                virtual ara::core::Result<bool> Compare (ReadOnlyMemRegion expected, std::size_t offset=0) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29012]
                 * Get the output digest size.
                 * @return std::size_t 
                 */
                virtual std::size_t GetDigestSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29015]
                 * Check current status of the stream processing: finished or no.
                 * @return true if a previously started stream processing was finished by a call of the Finish() or FinishBytes() methods
                 * @return false otherwise
                 */
                virtual bool IsFinished () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_29014]
                 * Check current status of the stream processing: started or no.
                 * @return true if the processing was start by a call of the Start() methods and was not finished yet
                 * @return false otherwise
                 */
                virtual bool IsStarted () const noexcept=0;
            };
        }
    }
}
#endif // ARA_CRYPTO_CRYP_DIGSET_SERVICE_H