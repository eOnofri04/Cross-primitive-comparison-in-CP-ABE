#!/bin/bash
set -e

IMAGE_NAME="openabe-bench"
CSV_PATH="/scripts/execution_resultsBN382.csv"   # <-- cambia con il path reale del CSV
OUTPUT_DIR="./output"

# Build
docker build -f Docker/Dockerfile . -t $IMAGE_NAME

# Estrai il CSV
mkdir -p $OUTPUT_DIR
CONTAINER_ID=$(docker create $IMAGE_NAME)
docker cp $CONTAINER_ID:$CSV_PATH $OUTPUT_DIR/
docker rm $CONTAINER_ID

echo "CSV estratto in $OUTPUT_DIR/"