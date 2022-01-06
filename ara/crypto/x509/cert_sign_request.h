#ifndef ARA_CRYPTO_X509_CERT_SIGN_REQUEST_H
#define ARA_CRYPTO_X509_CERT_SIGN_REQUEST_H

#include "ara/core/utility.h"

#include "ara/crypto/cryp/cryobj/signature.h"

#include "ara/crypto/x509/basic_cert_info.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40300]
             * Certificate Signing Request (CSR) object interface This interface is dedicated for complete
             * parsing of the request content.
             */
            class CertSignRequest : public BasicCertInfo
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40301]
                 * Unique smart pointer of the constant interface.
                 */
                using Uptrc = std::unique_ptr<const CertSignRequest>;

                /**
                 * @brief [SWS_CRYPT_40302]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<CertSignRequest>;

                /**
                 * @brief [SWS_CRYPT_40311]
                 * Verifies self-signed signature of the certificate request.
                 * @return true if the signature is correct
                 * @return false otherwise
                 */
                virtual bool Verify () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40313]
                 * Export this certificate signing request in DER encoded ASN1 format. Note: this is the CSR that
                 * can be sent to the CA for obtaining the certificate.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > a buffer with the formatted CSR
                 * @exception CryptoErrorDomain::kInvalidUsageOrder this error will be returned in case not all required information has been provided
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ExportASN1CertSignRequest () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40315]
                 * Return signature object of the request.
                 * @return const ara::crypto::cryp::Signature& signature object of the request
                 */
                virtual const ara::crypto::cryp::Signature& GetSignature () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40314]
                 * Return format version of the certificate request.
                 * @return unsigned format version of the certificate request
                 */
                virtual unsigned Version () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_CERT_SIGN_REQUEST_H