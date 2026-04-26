#!/bin/bash
set -e

IMAGE_NAME="palisade-bench"
CSV_PATH="/scripts/execution_results128.csv"   # <-- cambia con il path reale del CSV
OUTPUT_DIR="./output"

# Build
docker build -f Docker/Dockerfile . -t $IMAGE_NAME

# Estrai il CSV
mkdir -p $OUTPUT_DIR
CONTAINER_ID=$(docker create $IMAGE_NAME)
docker cp $CONTAINER_ID:$CSV_PATH $OUTPUT_DIR/
docker rm $CONTAINER_ID

echo "CSV estratto in $OUTPUT_DIR/"