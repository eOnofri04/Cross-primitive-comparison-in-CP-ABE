#!/bin/bash

NUM_RUNS=1000


OUTPUT_FILE="execution_resultsBN382.csv"
attribute_choice="6 8 16 20 32"


echo "Number of attributes,Iteration,Setup Time,Key Generation Time,Encryption Time,Decryption Time" > "$OUTPUT_FILE"

characters="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

p=16

b=$(($p * 8))
plaintext=""
for ((l=1; l<=p; l++)); do

	rand_char=${characters:$((RANDOM % ${#characters})):1}
	plaintext+=$rand_char

done

for n in $attribute_choice
do

	user_attr=""
	policy=""

	for ((i=1; i<=n; i++)); do

		if [ $((RANDOM % 2)) -eq 0 ]; then
			policy+="att$i and "
		else
			policy+="att$i and "
		fi

		user_attr+="att$i|"

	done

	policy=${policy% or }
	policy=${policy% and }

	user_attr=${user_attr%|}

	for ((k=1; k<=NUM_RUNS; k++)); do

		echo "Running iteration $k with..."
		echo "plaintext = $plaintext"
		echo "policy = $policy"
		echo "user's attributes = $user_attr"

		IFS=' ' read -r setup_time keygen_time encrypt_time decrypt_time <<< $(./benchBN382 "$plaintext" "$policy" "$user_attr")

		echo "$n,$k,$setup_time,$keygen_time,$encrypt_time,$decrypt_time" >> "$OUTPUT_FILE"
	done

done

