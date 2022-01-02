/**
 * @brief [SWS_CRYPT_20700]
 * Crypto Provider is a "factory" interface of all supported Crypto Primitives and a "trusted
 * environmet" for internal communications between them. All Crypto Primitives should have an
 * actual reference to their parent Crypto Provider. A Crypto Provider can be destroyed only after
 * destroying of all its daughterly Crypto Primitives. Each method of this interface that creates a
 * Crypto Primitive instance is non-constant, because any such creation increases a references
 * counter of the Crypto Primitive.
 */
class CryptoProvider {...};