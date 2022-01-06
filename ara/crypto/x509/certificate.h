#ifndef ARA_CRYPTO_X509_CERTIFICATE_H
#define ARA_CRYPTO_X509_CERTIFICATE_H

#include "ara/core/optional.h"
#include "ara/core/utility.h"

#include "ara/crypto/x509/basic_cert_info.h"

#include "ara/crypto/cryp/hash_function_ctx.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40200]
             * X.509 Certificate interface.
             */
            class Certificate : public BasicCertInfo
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40203]
                 * Certificate verification status.
                 */
                enum class Status : std::uint32_t
                {
                    kValid= 0,      // The certificate is valid.
                    kInvalid= 1,    // The certificate is invalid.
                    kUnknown= 2,    // Status of the certificate is unknown yet.
                    kNoTrust= 3,    // The certificate has correct signature, but the ECU has no a root of trust for this certificate.
                    kExpired= 4,    // The certificate has correct signature, but it is already expired (its validity period has ended)
                    kFuture= 5      // The certificate has correct signature, but its validity period is not started yet.
                };

                /**
                 * @brief [SWS_CRYPT_40202]
                 * Unique smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const Certificate>;

                /**
                 * @brief [SWS_CRYPT_40201]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<Certificate>;

                /**
                 * @brief [SWS_CRYPT_40217]
                 * Get the DER encoded AuthorityKeyIdentifier of this certificate. If (id.empty() == true) then this
                 * method only returns required size of the output buffer.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > size of the DER encoded AuthorityKeyIdentifier in bytes
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (id.empty() == false), but its size is not enough for storing the output value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > AuthorityKeyId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40215]
                 * Get the "Not After" of the certificate.
                 * @return time_t "Not After" of the certificate
                 */
                virtual time_t EndTime () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40220]
                 * Calculate a fingerprint from the whole certificate. The produced fingerprint value saved to the
                 * output buffer starting from leading bytes of the hash value. If the capacity of the output buffer is
                 * less than the digest size then the digest will be truncated and only leading bytes will be saved.
                 * If the capacity of the output buffer is higher than the digest size then only leading bytes of the
                 * buffer will be updated.
                 * @param[out] fingerprint output buffer for the fingerprint storage
                 * @param[in] hashCtx an initialized hash function context
                 * @return ara::core::Result<std::size_t> number of bytes actually saved to the output buffer
                 * @exception CryptoErrorDomain::kIncompleteArgState if the hashCtx context is not initialized
                 */
                virtual ara::core::Result<std::size_t> GetFingerprint (ReadWriteMemRegion fingerprint, cryp::HashFunctionCtx &hashCtx) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40221]
                 * Return last verification status of the certificate.
                 * @return Status the certificate verification status
                 */
                virtual Status GetStatus () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40212]
                 * Check whether this certificate belongs to a root CA.
                 * @return true if the TrustMaster has set this certificate as root
                 * @return false otherwise
                 */
                virtual bool IsRoot () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40213]
                 * Get the issuer certificate DN.
                 * @return const X509DN& Issuer DN of this certificate
                 */
                virtual const X509DN& IssuerDn () const =0;

                /**
                 * @brief [SWS_CRYPT_40216]
                 * Get the serial number of this certificate. If (sn.empty() == true) then this method only returns
                 * required size of the output buffer.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > size of the certificate serial number in bytes
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (sn.empty() == false), but its size is not enough for storing the output value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > SerialNumber () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40214]
                 * Get the "Not Before" of the certificate.
                 * @return time_t "Not Before" of the certificate
                 */
                virtual time_t StartTime () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40218]
                 * Get the DER encoded SubjectKeyIdentifier of this certificate. If (id.empty() == true) then this
                 * method only returns required size of the output buffer.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > size of the DER encoded SubjectKeyIdentifier in bytes
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (id.empty() == false), but its size is not enough for storing the output value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > SubjectKeyId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40219]
                 * Verify signature of the certificate. Call with (caCert == nullptr) is applicable only if this is a
                 * certificate of a root CA.
                 * @param caCert[in] the optional pointer to a Certification Authority certificate used for signature of the current one
                 * @return true if this certificate was verified successfully
                 * @return false otherwise
                 */
                virtual bool VerifyMe (ara::core::Optional< const Certificate::Uptr > caCert) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40211]
                 * Get the X.509 version of this certificate object.
                 * @return std::uint32_t X.509 version
                 */
                virtual std::uint32_t X509Version () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_CERTIFICATE_H