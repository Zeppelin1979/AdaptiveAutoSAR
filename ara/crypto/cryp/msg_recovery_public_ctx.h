/**
 * @brief [SWS_CRYPT_22200]
 * A public key context for asymmetric recovery of a short message and its signature verification
 * (RSA-like). Restricted groups of trusted subscribers can use this primitive for simultaneous
 * provisioning of confidentiality, authenticity and non-repudiation of short messages, if the public
 * key is generated appropriately and kept in secret. If (0 == BlockCryptor::ProcessBlock(...)) then
 * the input message-block is violated.
 */
class MsgRecoveryPublicCtx : public CryptoContext {...};