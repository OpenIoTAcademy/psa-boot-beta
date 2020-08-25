using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace PSABootPackageCreator.Crypto
{
    public class AES
    {
        Aes aesAlg;
        byte[] key;

        public AES(byte[] key)
        {
            aesAlg = Aes.Create();
            aesAlg.GenerateIV();
            aesAlg.Mode = CipherMode.CBC;
            this.key = key;
            aesAlg.Key = this.key;
        }

        public byte[] IV
        {
            get
            {
                return aesAlg.IV;
            }
        }

        public byte[] Encrypt(byte[] plainData)
        {
            byte[] encrypted;

            var encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);

            // Create the streams used for encryption. 
            using (var msEncrypt = new MemoryStream())
            {
                using (var csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                {
                    using (var swEncrypt = new BinaryWriter(csEncrypt))
                    {
                        //Write all data to the stream.
                        swEncrypt.Write(plainData);
                    }
                    encrypted = msEncrypt.ToArray();
                }
            }

            return encrypted;
        }
    }

    public class RSA
    {

        public enum KeySize { None = 0, Key1024 = 128, Key2048 = 256, Key4096 = 512 };

        KeySize keySize = KeySize.None;

        public RSA(KeySize keySize, byte[] privateKey)
        {
            if (privateKey.Length != (int)keySize)
            {
                throw new Exception("Invalid Private Key");
            }
            this.keySize = keySize;
        }

        public byte[] Sign(byte[] data)
        {
            byte[] SignedHash = null;
            try
            {
                
                //Create a new instance of RSACryptoServiceProvider.
                using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
                {
                    //The hash to sign.
                    byte[] hash;
                    using (SHA256 sha256 = SHA256.Create())
                    {

                        hash = sha256.ComputeHash(data);
                    }

                    //Create an RSASignatureFormatter object and pass it the 
                    //RSACryptoServiceProvider to transfer the key information.
                    RSAPKCS1SignatureFormatter RSAFormatter = new RSAPKCS1SignatureFormatter(rsa);

                    //Set the hash algorithm to SHA256.
                    RSAFormatter.SetHashAlgorithm("SHA256");

                    //Create a signature for HashValue and return it.
                    SignedHash = RSAFormatter.CreateSignature(hash);

                    return SignedHash;
                }
            }

            catch (CryptographicException e)
            {
                Console.WriteLine(e.Message);
            }
            			
			/* Remove the below line once you return a proper signature */
			return  SignedHash;

        }
    }
}

    

   
