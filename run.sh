#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <argument>"
  exit 1
fi

ARGUMENT=$1
BIBLE=$(cat bible.txt)

while true; do
  ./client "$ARGUMENT" "$BIBLE"
  sleep 1
done