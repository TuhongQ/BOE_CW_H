[version 2.1.1.1]

[List]
Enclave.signed.dll size: 1,480,720 byte     
EnclaveBridge.dll size: 31,760 byte    
libgcc_s_sjlj-1.dll size: 1,002,901 byte
libSafePublic.dll size: 6,612,992 byte
libSafePublic.h size: 7,736 byte
libSafePublic.lib size: 11,192 byte
mfc140.dll size: 4,378,776 byte
readme size: 2,333 byte
sec2.dll size: 9,028,112 byte
securec.dll size: 15,376 byte
sgx_capable.dll size: 92,432 byte
sgx_white_list_cert.bin size: 1,720 byte
SGXSupport.dll size: 15,888 byte
table1 size: 163,849 byte

[Update]
v1.0.4.1
1. The openSSL linked by Enclave.signed.dll was updated to version 1.0.2p 

v1.0.4.2
1. Add print log information 
2. Eliminate coverity and fortify warnings 
3. Solved ASC rework tools crash issue

v1.0.5.1
1. Add log information control 
2. Add application identity authentication

v1.0.6.1
1. The openSSL linked by Enclave.signed.dll was updated to version 1.0.2r
2. The openSSL linked by sec2.dll and libSafePublic.dll was updated to version 1.1.1a
3. Modified sec2.dll to meet the requirements of Cyber Security Evaluation Centre
4. fixed the issue of getting sec2.dll path by GetModuleHandle function.

v2.0.0.1907
1. Modified identity authentication to only verify the module that directly calls the public library
2. Added API GetDongleLibInfo to support returning encrypted public library information
3. Public library internal security hardening
4. Modify the public library initialization mode(Fix individual sgx environment tool stuck problem)
5. Added libSafePublic.lib for prisetting tool
6. Added file mfc140.dll, if this version of mfc140.dll does not match your environment, please get and run vc_redist.x86.exe from the vc_redist.x86.rar path
7. vc_redist.x86.rar path: \\peknas10av3-rd\IT_VMP_PEK_255_F\BL250617129_CBG_PKI 2.0.0.1907\Test\TestSoftware

v2.0.0.1908
1. Compatible with the signature of the new and old version of the certificate on vmp
2. Added sgxstatus tag in xml file
3. Fixed ATE verify

v2.0.1.1908
1. Delete author information in the header comment

v2.1.1.1
1. fixed probabilistic delay
2. The openSSL linked by sec2.dll and libSafePublic.dll was updated to version 1.1.1d
3. The openSSL linked by Enclave.signed.dll,EnclaveBridge.dll,SGXSupport.dll was updated to version 1.1.1d
4. The dll build by minGW

v2.1.2.001
1. getmac function optimization: increase wireless network card support, eliminate virtual network card.

v3.0.0.001
1. first release version for honor product.