
#include <iostream>
#include <string>
#include <cassert>
#include <openabe/openabe.h>
#include <openabe/zsymcrypto.h>
#include <chrono>
#include <fstream>

using namespace std;
using namespace oabe;
using namespace oabe::crypto;
using namespace chrono;

int main(int argc, char **argv) {

  InitializeOpenABE();


  unique_ptr<OpenABEContextSchemeCCA> ccaCpAbeContext = nullptr;

  ccaCpAbeContext = OpenABE_createContextABESchemeCCA(OpenABE_SCHEME_CP_WATERS);

  string ciphertext, plaintext, recovered_plaintext, policy, user_attributes_list;

  plaintext = argv[1];

  policy = argv[2];

  user_attributes_list = argv[3];





  auto start_generateParams = high_resolution_clock::now();

  ccaCpAbeContext->generateParams("BN_P382", "mpk", "msk");

  auto end_generateParams = high_resolution_clock::now();




  auto start_keygen = high_resolution_clock::now();

  unique_ptr<OpenABEFunctionInput> keyInput = createAttributeList(user_attributes_list);

  ccaCpAbeContext->keygen(keyInput.get(), "deckey", "mpk", "msk");

  auto end_keygen = high_resolution_clock::now();
  

  
  auto start_encrypt = high_resolution_clock::now();

  OpenABECiphertext ct1, ct2;

  unique_ptr<OpenABEFunctionInput> encInput = createPolicyTree(policy);

  ccaCpAbeContext->encrypt("mpk", encInput.get(), plaintext, &ct1, &ct2);

  auto end_encrypt = high_resolution_clock::now();


  

  auto start_decrypt = high_resolution_clock::now();
  
  ccaCpAbeContext->decrypt("mpk", "deckey", recovered_plaintext, &ct1, &ct2);

  auto end_decrypt = high_resolution_clock::now();


  auto execTime_generateParams = duration_cast<milliseconds>(end_generateParams - start_generateParams);

  auto execTime_keygen = duration_cast<milliseconds>(end_keygen - start_keygen);

  auto execTime_encrypt = duration_cast<milliseconds>(end_encrypt - start_encrypt);

  auto execTime_decrypt = duration_cast<milliseconds>(end_decrypt - start_decrypt);




  cout << execTime_generateParams.count() << " " << execTime_keygen.count() << " " << execTime_encrypt.count() << " " << execTime_decrypt.count() << endl;

  ShutdownOpenABE();

  return 0;
}
