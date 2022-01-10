#include "ara/crypto/x509/x509_dn.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            ara::core::Result<ara::core::String> X509DN::GetAttribute (AttributeId id) const noexcept
            {
                switch (id)
                {
                    case AttributeId::kCommonName:
                        return ara::core::Result<ara::core::String>::FromValue(mCommonName);
                        break;
                    case AttributeId::kCountry:
                        return ara::core::Result<ara::core::String>::FromValue(mCountry);
                        break;
                    case AttributeId::kState:
                        return ara::core::Result<ara::core::String>::FromValue(mState);
                        break;
                    case AttributeId::kLocality:
                        return ara::core::Result<ara::core::String>::FromValue(mLocality);
                        break;
                    case AttributeId::kOrganization:
                        return ara::core::Result<ara::core::String>::FromValue(mOrganization);
                        break;
                    case AttributeId::kStreet:
                        return ara::core::Result<ara::core::String>::FromValue(mStreet);
                        break;
                    case AttributeId::kPostalCode:
                        return ara::core::Result<ara::core::String>::FromValue(mPostalCode);
                        break;
                    case AttributeId::kTitle:
                        return ara::core::Result<ara::core::String>::FromValue(mTitle);
                        break;
                    case AttributeId::kSurname:
                        return ara::core::Result<ara::core::String>::FromValue(mSurname);
                        break;
                    case AttributeId::kGivenName:
                        return ara::core::Result<ara::core::String>::FromValue(mGivenName);
                        break;
                    case AttributeId::kInitials:
                        return ara::core::Result<ara::core::String>::FromValue(mInitials);
                        break;
                    case AttributeId::kPseudonym:
                        return ara::core::Result<ara::core::String>::FromValue(mPseudonym);
                        break;
                    case AttributeId::kGenerationQualifier:
                        return ara::core::Result<ara::core::String>::FromValue(mGenerationQualifier);
                        break;
                    case AttributeId::kDnQualifier:
                        return ara::core::Result<ara::core::String>::FromValue(mDnQualifier);
                        break;
                        case AttributeId::kEmail:
                        return ara::core::Result<ara::core::String>::FromValue(mEmail);
                        break;
                        case AttributeId::kUri:
                        return ara::core::Result<ara::core::String>::FromValue(mUri);
                        break;
                        case AttributeId::kDns:
                        return ara::core::Result<ara::core::String>::FromValue(mDns);
                        break;
                        case AttributeId::kHostName:
                        return ara::core::Result<ara::core::String>::FromValue(mHostName);
                        break;
                        case AttributeId::kIpAddress:
                        return ara::core::Result<ara::core::String>::FromValue(mIpAddress);
                        break;
                        case AttributeId::kSerialNumbers:
                        return ara::core::Result<ara::core::String>::FromValue(mSerialNumbers);
                        break;
                        case AttributeId::kUserId:
                        return ara::core::Result<ara::core::String>::FromValue(mUserId);
                        break;
                    default:
                        return ara::core::Result<ara::core::String>::FromError(CryptoErrorDomain::Errc::kUnknownIdentifier);
                        break;
                }
            }

            ara::core::Result<ara::core::String> X509DN::GetAttribute (AttributeId id, unsigned index) const noexcept
            {
                switch (id)
                {
                    case AttributeId::kOrgUnit:
                        if (mOrgUnit.size() > index)
                        {
                            return ara::core::Result<ara::core::String>::FromValue(mOrgUnit.at(index));
                        }
                        else
                        {
                            return ara::core::Result<ara::core::String>::FromError(CryptoErrorDomain::Errc::kAboveBoundary);
                        }
                        break;
                    case AttributeId::kDomainComponent:
                            if (mDomainComponent.size() > index)
                        {
                            return ara::core::Result<ara::core::String>::FromValue(mDomainComponent.at(index));
                        }
                        else
                        {
                            return ara::core::Result<ara::core::String>::FromError(CryptoErrorDomain::Errc::kAboveBoundary);
                        }
                        break;
                    default:
                        if (index == 0)
                        {
                            return GetAttribute(id);
                        }
                        else
                        {
                            return ara::core::Result<ara::core::String>::FromError(CryptoErrorDomain::Errc::kInvalidArgument);
                        }
                        break;
                }
            }

            ara::core::Result<ara::core::String> X509DN::GetDnString () const noexcept
            {
                ara::core::String result;
                for (ara::core::String str : mDomainComponent)
                {
                    result += str;
                }
                return ara::core::Result<ara::core::String>::FromValue(result);
            }
        }
    }
}