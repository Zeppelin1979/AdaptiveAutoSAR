#ifndef ARA_CRYPTO_X509_X509DN_H
#define ARA_CRYPTO_X509_X509DN_H

#include <memory>
#include <cinttypes>

#include "ara/core/result.h"
#include "ara/core/string.h"

#include "ara/crypto/cryp/common/crypto_error_domain.h"

#include "ara/crypto/x509/x509_object.h"
#include "ara/crypto/x509/x509_provider.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40400]
             * Interface of X.509 Distinguished Name (DN).
             */
            class X509DN : public X509Object
            {
            private:
                ara::core::String mCommonName = nullptr;
                ara::core::String mCountry;            // Country
                ara::core::String mState;              // State
                ara::core::String mLocality;           // Locality
                ara::core::String mOrganization;       // Organization
                ara::core::vector<ara::core::String> mOrgUnit;            // Organization Unit
                ara::core::String mStreet;             // Street
                ara::core::String mPostalCode;         // Postal Code
                ara::core::String mTitle;              // Title
                ara::core::String mSurname;            // Surname
                ara::core::String mGivenName;         // Given Name
                ara::core::String mInitials;          // Initials
                ara::core::String mPseudonym;         // Pseudonym
                ara::core::String mGenerationQualifier;   // Generation Qualifier
                ara::core::vector<ara::core::String> mDomainComponent;   // Domain Component
                ara::core::String mDnQualifier;       // Distinguished Name Qualifier
                ara::core::String mEmail;             // E-mail
                ara::core::String mUri;               // URI
                ara::core::String mDns;               // DNS
                ara::core::String mHostName;          // Host Name (UNSTRUCTUREDNAME)
                ara::core::String mIpAddress;         // IP Address (UNSTRUCTUREDADDRESS)
                ara::core::String mSerialNumbers;     // Serial Numbers
                ara::core::String mUserId;             // User ID

            public:

                X509DN (X509Provider &provider, std::size_t capacity=0)
                : X509Object(provider),
                  mCommonName(),
                  mCountry(),
                  mState(),
                  mLocality(),
                  mOrganization(),
                  mOrgUnit(),
                  mStreet(),
                  mPostalCode(),
                  mTitle(),
                  mSurname(),
                  mGivenName(),
                  mInitials(),
                  mPseudonym(),
                  mGenerationQualifier(),
                  mDomainComponent(),
                  mDnQualifier(),
                  mEmail(),
                  mUri(),
                  mDns(),
                  mHostName(),
                  mIpAddress(),
                  mSerialNumbers(),
                  mUserId()
                {
                }

                ~X509DN ()
                {
                }

                /**
                 * @brief [SWS_CRYPT_40402]
                 * Unique smart pointer of the constant interface.
                 */
                using Uptrc = std::unique_ptr<const X509DN>;

                /**
                 * @brief [SWS_CRYPT_40401]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<X509DN>;
                
                /**
                 * @brief [SWS_CRYPT_40403]
                 * Enumeration of DN attributes’ identifiers.
                 */
                enum class AttributeId : std::uint32_t
                {
                    kCommonName= 0,         // Common Name
                    kCountry= 1,            // Country
                    kState= 2,              // State
                    kLocality= 3,           // Locality
                    kOrganization= 4,       // Organization
                    kOrgUnit= 5,            // Organization Unit
                    kStreet= 6,             // Street
                    kPostalCode= 7,         // Postal Code
                    kTitle= 8,              // Title
                    kSurname= 9,            // Surname
                    kGivenName= 10,         // Given Name
                    kInitials= 11,          // Initials
                    kPseudonym= 12,         // Pseudonym
                    kGenerationQualifier= 13,   // Generation Qualifier
                    kDomainComponent= 14,   // Domain Component
                    kDnQualifier= 15,       // Distinguished Name Qualifier
                    kEmail= 16,             // E-mail
                    kUri= 17,               // URI
                    kDns= 18,               // DNS
                    kHostName= 19,          // Host Name (UNSTRUCTUREDNAME)
                    kIpAddress= 20,         // IP Address (UNSTRUCTUREDADDRESS)
                    kSerialNumbers= 21,     // Serial Numbers
                    kUserId= 22             // User ID
                };

                /**
                 * @brief [SWS_CRYPT_40413]
                 * Get DN attribute by its ID (this method is applicale to all attributes except kOrgUnit and k
                 * DomainComponent). Capacity of the output string must be enough for storing the output value!
                 * If (attribute == nullptr) then method only returns required buffer capacity.
                 * @param[in] id the identifier of required attribute
                 * @return ara::core::Result<ara::core::String> String of the attribute
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the id argument has unsupported value
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (attribute != nullptr), but attribute->capacity() is less than required for storing of the output
                 */
                virtual ara::core::Result<ara::core::String> GetAttribute (AttributeId id) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40415]
                 * Return DN attribute by its ID and sequential index (this method is applicale to attributes kOrg
                 * Unit and kDomainComponent). Capacity of the output string must be enough for storing the
                 * output value! If (attribute == nullptr) then method only returns required buffer capacity.
                 * @param[in] id the identifier of required attribute
                 * @param[in] index the zero-based index of required component of the attribute
                 * @return ara::core::Result<ara::core::String> String of the attribute
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the id argument has unsupported value
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (attribute != nullptr), but attribute->capacity() is less than required for storing of the output
                 * @exception CryptoErrorDomain::kInvalidArgument if (id != kOrgUnit) && (id != kDomainComponent) && (index > 0)
                 * @exception CryptoErrorDomain::kAboveBoundary if ((id == kOrgUnit) || (id == kDomainComponent)) and the index value is greater than or equal to the
                 * actual number of components in the specified attribute
                 */
                virtual ara::core::Result<ara::core::String> GetAttribute (AttributeId id, unsigned index) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40411]
                 * Get the whole Distinguished Name (DN) as a single string. Capacity of the output string must
                 * be enough for storing the output value! If (dn == nullptr) then method only returns required
                 * buffer capacity.
                 * @return ara::core::Result<ara::core::String> String of the whole DN string
                 * @exception CryptoErrorDomain::kInsufficientCapacity if (dn != nullptr), but dn->capacity() is less than required for the output value storing
                 */
                virtual ara::core::Result<ara::core::String> GetDnString () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40417]
                 * Check for equality of this and another Distinguished Name (DN) objects.
                 * @param other another instance of DN for comparison
                 * @return true if the provided DN is identical to this one
                 * @return false otherwise
                 */
                virtual bool operator== (const X509DN &other) const noexcept=0;
 
                /**
                 * @brief [SWS_CRYPT_40418]
                 * Check for inequality of this and another Distinguished Name (DN) objects.
                 * @param other another instance of DN for comparison
                 * @return true if the provided DN is not identical to this one
                 * @return false otherwise
                 */
                bool operator!= (const X509DN &other) const noexcept;

                /**
                 * @brief [SWS_CRYPT_40414]
                 * Set DN attribute by its ID (this method is applicale to all attributes except kOrgUnit and k
                 * DomainComponent).
                 * @param[in] id the identifier of required attributet
                 * @param[in] attribute the attribute value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the id argument has unsupported value
                 * @exception CryptoErrorDomain::kUnexpectedValue if the attribute string contains incorrect characters or it has unsupported length
                 */
                virtual ara::core::Result<void> SetAttribute (AttributeId id, ara::core::StringView attribute) noexcept/*=0;*/
                {
                    switch(id)
                    {
                        case AttributeId::kCommonName:
                            mCommonName = attribute;
                            break;
                    }
                }

                /**
                 * @brief [SWS_CRYPT_40416]
                 * Set DN attribute by its ID and sequential index (this method is applicale to attributes kOrgUnit
                 * and kDomainComponent).
                 * @param[in] id the identifier of required attribute
                 * @param[in] index the zero-based index of required component of the attribute
                 * @param[in] attribute the attribute value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUnknownIdentifier if the id argument has unsupported value
                 * @exception CryptoErrorDomain::kUnexpectedValue if the attribute string contains incorrect characters or it has unsupported length
                 * @exception CryptoErrorDomain::kInvalidArgument if (id != kOrgUnit) && (id != kDomainComponent) && (index > 0)
                 * @exception CryptoErrorDomain::kAboveBoundary if ((id == kOrgUnit) || (id == kDomainComponent))
                 * and the index value is greater than the current number of components in the specified attribute
                 */
                virtual ara::core::Result<void> SetAttribute (AttributeId id, unsigned index, ara::core::StringView attribute) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40412]
                 * Set whole Distinguished Name (DN) from a single string.
                 * @param[in] dn the single string containing the whole DN value in text format
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUnexpectedValue if the dn string has incorrect syntax.
                 */
                virtual ara::core::Result<void> SetDn (ara::core::StringView dn) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_X509DN_H