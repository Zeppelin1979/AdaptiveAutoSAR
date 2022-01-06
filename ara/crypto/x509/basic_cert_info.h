#ifndef ARA_CRYPTO_X509_BASIC_CERT_INFO_H
#define ARA_CRYPTO_X509_BASIC_CERT_INFO_H

#include "ara/crypto/cryp/crypto_provider.h"

#include "ara/crypto/x509/x509_object.h"
#include "ara/crypto/x509/x509_dn.h"
#include "ara/crypto/x509/x509_public_key_info.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40100]
             * Basic Certificate Information interface.
             */
            class BasicCertInfo : public X509Object
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40101]
                 * X.509 v3 Key Constraints type definition.
                 */
                using KeyConstraints = std::uint32_t;

                /**
                 * @brief [SWS_CRYPT_40157]
                 * The key can be used for Certificates Revokation Lists (CRL) signing.
                 */
                static const KeyConstraints kConstrCrlSign = 0x0200;

                /**
                 * @brief [SWS_CRYPT_40154]
                 * The key can be used for data encipherment.
                 */
                static const KeyConstraints kConstrDataEncipherment = 0x1000;

                /**
                 * @brief [SWS_CRYPT_40159]
                 * The enciphermet key can be used for deciphering only.
                 */
                static const KeyConstraints kConstrDecipherOnly = 0x0080;

                /**
                 * @brief [SWS_CRYPT_40151]
                 * The key can be used for digital signature production.
                 */
                static const KeyConstraints kConstrDigitalSignature = 0x8000;

                /**
                 * @brief [SWS_CRYPT_40158]
                 * The enciphermet key can be used for enciphering only.
                 */
                static const KeyConstraints kConstrEncipherOnly = 0x0100;

                /**
                 * @brief [SWS_CRYPT_40155]
                 * The key can be used for a key agreement protocol execution.
                 */
                static const KeyConstraints kConstrKeyAgreement = 0x0800;

                /**
                 * @brief [SWS_CRYPT_40156]
                 * The key can be used for certificates signing.
                 */
                static const KeyConstraints kConstrKeyCertSign = 0x0400;

                /**
                 * @brief [SWS_CRYPT_40153]
                 * The key can be used for key encipherment.
                 */
                static const KeyConstraints kConstrKeyEncipherment = 0x2000;

                /**
                 * @brief [SWS_CRYPT_40152]
                 * The key can be used in cases requiring the "non-repudiation" guarantee.
                 */
                static const KeyConstraints kConstrNonRepudiation = 0x4000;

                /**
                 * @brief [SWS_CRYPT_40150]
                 * No key constraints.
                 */
                static const KeyConstraints kConstrNone = 0;

                /**
                 * @brief [SWS_CRYPT_40115]
                 * Get the key constraints for the key associated with this PKCS#10 object.
                 * @return KeyConstraints key constraints
                 */
                virtual KeyConstraints GetConstraints () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40114]
                 * Get the constraint on the path length defined in the Basic Constraints extension.
                 * @return std::uint32_t certification path length limit
                 */
                virtual std::uint32_t GetPathLimit () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40113]
                 * Check whether the CA attribute of X509v3 Basic Constraints is true (i.e. pathlen=0).
                 * @return true if it is a CA request
                 * @return false otherwise
                 */
                virtual bool IsCa () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40112]
                 * Get the subject DN.
                 * @return const X509DN& subject DN
                 */
                virtual const X509DN& SubjectDn () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40111]
                 * Load the subject public key information object to realm of specified crypto provider. If (crypto
                 * Provider == nullptr) then X509PublicKeyInfo object will be loaded in realm of the Stack-default
                 * Crypto Provider.
                 * @param[in] cryptoProvider unique pointer of a target Crypto Provider, where the public key will be used
                 * @return const X509PublicKeyInfo& constant reference of the subject public key interface
                 */
                virtual const X509PublicKeyInfo& SubjectPubKey (cryp::CryptoProvider::Uptr cryptoProvider=nullptr) const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_BASIC_CERT_INFO_H