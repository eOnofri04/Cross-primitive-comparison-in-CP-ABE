
#include "abecontext.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace lbcrypto;
using namespace std;
using namespace chrono;
int main(int argc, char* argv[]) {
  // Create context under security level and number of attributes
  //cout << "This is a demo file of the CPABE scheme" << endl << endl;

  //usint ringsize = 1024;
  //usint base = 64;
  //cout << "Used parameters:" << endl;
  //cout << "Ring size: " << ringsize << endl;
  //cout << "Base: " << base << endl << endl;

  string prova;
  prova = "aaa";
  ABEContext<NativePoly> context;
  //cout << "Generating a context under these parameters" << endl << endl;
  string arg1(argv[1]);
  context.GenerateCPABEContext(HEStd_128_classic, arg1.length());

  //cout << "Generating master secret key and master public key" << endl;





  // Generate master keys
  auto start_Setup = high_resolution_clock::now();
  CPABEMasterPublicKey<NativePoly> mpk;
  CPABEMasterSecretKey<NativePoly> msk;
  context.Setup(&mpk, &msk);
  auto end_Setup = high_resolution_clock::now();
  auto execTime_Setup = duration_cast<milliseconds>(end_Setup - start_Setup);

  //cout << "Setup: " << execTime_Setup.count() << " ms" << endl << endl;


  // Create a random access policy and user attribute set
  //cout << " Creating access policy and user attribute sets" << endl;
  vector<usint> s;
  vector<int> w;

  string s_str, w_str;
  s_str = argv[1];
  w_str = argv[1];

  //Creating le lists from the binary strings
  for (char c : s_str) {
	s.push_back(c - '0');
  }

  for (char c : w_str) {
	w.push_back(c - '0');
  }

  //cout << "User attribute set: " << s << endl;
  //cout << "Access policy defined:" << w << endl << endl;
  CPABEUserAccess<NativePoly> ua(s);
  CPABEAccessPolicy<NativePoly> ap(w);







  // Create the key corresponding to the access policy
  CPABESecretKey<NativePoly> sk;
  //cout << "Creating secret key for the attribute set" << endl;
  auto start_Keygen = high_resolution_clock::now();
  context.KeyGen(msk, mpk, ua, &sk);
  auto end_Keygen = high_resolution_clock::now();
  auto execTime_Keygen = duration_cast<milliseconds>(end_Keygen - start_Keygen);

  //cout << "KeyGen: " << execTime_Keygen.count() << " ms" << endl << endl;





  // Create a plaintext
  vector<int64_t> plaintextVector;
  string p_str;
  p_str = argv[2];

  for (char c : p_str) {
	plaintextVector.push_back(c - '0');
  }
  Plaintext pt = context.MakeCoefPackedPlaintext(plaintextVector);
  //cout << "Plaintext vector of bits: " << plaintextVector << endl << endl;






  // Encrypt the plaintext
  //cout << "Encrypting the plaintext under the access policy" << endl;
  auto start_Encrypt = high_resolution_clock::now();
  CPABECiphertext<NativePoly> ct;
  context.Encrypt(mpk, ap, pt, &ct);
  auto end_Encrypt = high_resolution_clock::now();
  auto execTime_Encrypt = duration_cast<milliseconds>(end_Encrypt - start_Encrypt);

  //cout << "Encryption: " << execTime_Encrypt.count() << " ms" << endl << endl;





  // Decrypt the ciphertext
  //cout << "Decrpyting the ciphertext" << endl;
  auto start_Decrypt = high_resolution_clock::now();
  Plaintext dt = context.Decrypt(ap, ua, sk, ct);
  auto end_Decrypt = high_resolution_clock::now();
  auto execTime_Decrypt = duration_cast<milliseconds>(end_Decrypt - start_Decrypt);

  //cout << "Decryption: " << execTime_Decrypt.count() << " ms" << endl << endl;


  //Outputs in order to let the bash file read the execution times of the functions

  cout << execTime_Setup.count() << " " << execTime_Keygen.count() << " " << execTime_Encrypt.count() << " " << execTime_Decrypt.count() << endl;






  //cout << "Checking if the plaintext & decrypted text match" << endl;
  // Check if original plaintext and decrypted plaintext match
  //if (pt->GetElement<NativePoly>() == dt->GetElement<NativePoly>()) {
	//cout << "Encryption & decryption successful" << endl;
  //} else {
	//cout << "Encryption & decryption failed" << endl;
  //}
}

