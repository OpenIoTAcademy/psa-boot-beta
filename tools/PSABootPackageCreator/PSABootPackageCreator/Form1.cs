using PSABootPackageCreator.Crypto;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PSABootPackageCreator
{
    public partial class Form1 : Form
    {
        /*
         * Encryption Key
         */
        static byte[] encKey = new byte[32]
        {
                0xA5, 0xD3, 0x7, 0xF1, 0x11, 0x23, 0x37, 0xA3, 0xA8, 0xD1, 0x3, 0xDD, 0x24, 0x93, 0x22, 0xF1,
                0x34, 0xF9, 0xC4, 0xA5, 0x75, 0x97, 0x98, 0xA7, 0x17, 0xE3, 0xA1, 0x36, 0xC3, 0xBA, 0xC3, 0x13
        };

        /* TODO Fill here */
        static byte[] signingKey = new byte[128];



        public Form1()
        {
            InitializeComponent();
        }

        private void btnCreate_Click(object sender, EventArgs e)
        {
            //if (!File.Exists(txtImagePath.Text))
            //{
            //    MessageBox.Show("The Image does not exists");
            //}

            preparePackage(1, txtImagePath.Text);
        }

        private void preparePackage(UInt32 version, string applicationPath)
        {
            AES aes = new AES(encKey);
            RSA rsa = new RSA(RSA.KeySize.Key1024, signingKey);

            /*
             * How to prepare a package
             * 1. Read the application image first
             * 2. Encrypt it
             * 3. Sign the encrypted image
             * 4. Create the metadata for the encrypted and signed application image
             * 5. Write the metadata and the encrypted image into a file. (The bootloader will be using this file)
             */

            /* Read the Application Image */
            byte[] applicationImage = getApplicationImage(applicationPath);

            /* Encrypt the Application Image */
            byte[] encryptedApplicationImage = aes.Encrypt(applicationImage);

            /* Sign the encrypted image */
            byte[] signature = rsa.Sign(encryptedApplicationImage);

            /* Create a metadata  */
            byte[] metaData = getMetaData(version, (UInt32)encryptedApplicationImage.Length, aes.IV, signature);

            /* Write Metadata and the encrypted image into the upgrade package */
            {
                string packagePath = applicationPath + ".package.bin";
                
                if (File.Exists(packagePath))
                {
                    File.Delete(packagePath);
                }

                using (FileStream fs = new FileStream(packagePath, FileMode.CreateNew))
                {
                    using (BinaryWriter bS = new BinaryWriter(fs))
                    {
                        bS.Write(metaData);
                        bS.Write(encryptedApplicationImage);
                        bS.Close();
                    }
                    fs.Close();
                }
            }
        }

        private byte[] getMetaData(UInt32 version, UInt32 size, byte[] IV, byte[] signature)
        {
            /*
             * The package structure must be as below
             * 
             * typedef struct
             * {
             *     uint8_t prefix[4];
             *     uint32_t version;
             *     uint32_t size;
             *     uint8_t reserved[4];
             *     uint8_t iv[16];
             *     uint8_t signature[128];
             * }
             * boot_image_metadata_t;
             */

            List<byte> metaData = new List<byte>();
            metaData.AddRange(new byte[4] { (byte)'Z', (byte)'A', (byte)'Y', (byte)'A' });
            metaData.AddRange(BitConverter.GetBytes(version));
            metaData.AddRange(BitConverter.GetBytes(size));
            metaData.AddRange(new byte[4] { 0, 0, 0, 0} );
            metaData.AddRange(IV);
            metaData.AddRange(signature);

            return metaData.ToArray();
        }

        private byte[] getApplicationImage(string applicationPath)
        {
            /* TODO : Read the image from file */

            /* Return test bytes */
            {
                string test = "Application Image is success!";
                return Encoding.ASCII.GetBytes(test);
            }
        }
    }
}
