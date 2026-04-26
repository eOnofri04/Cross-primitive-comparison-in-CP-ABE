#!/bin/bash

NUM_RUNS=1000


OUTPUT_FILE="execution_results128.csv"
attribute_choice="6 8 16 20 32"


echo "Number of attributes,Iteration,Setup Time,Key Generation Time,Encryption Time,Decryption Time" > "$OUTPUT_FILE"



plaintext=""
for ((l=1; l<=128; l++)); do

	if [ $((RANDOM % 2)) -eq 0 ]; then
		plaintext+="0"
	else
		plaintext+="1"
	fi

done

for n in $attribute_choice
do

	user_attr=""
	policy=""

	for ((i=1; i<=n; i++)); do
	
			user_attr+="1"
			policy+="1"

	done

	for ((k=1; k<=NUM_RUNS; k++)); do

		echo "Running iteration $k with..."
		echo "plaintext = $plaintext"
		echo "policy = $policy"
		echo "user's attributes = $user_attr"

		IFS=' ' read -r setup_time keygen_time encrypt_time decrypt_time <<< $(./bench128 "$policy" "$plaintext")

		echo "$n,$k,$setup_time,$keygen_time,$encrypt_time,$decrypt_time" >> "$OUTPUT_FILE"
	done

done



