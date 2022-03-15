#!/bin/bash

usage() {
  echo "Usage: ./decodebase64 [FILE]"
  echo "Formats: APNG BMP GIF JPEG PNG WEBP"
}

# Print usage and exit if the file was not provided
[ $# -eq 0 ] && usage && exit 1

# Grab the image format
fmt=$(file "$1" | grep -iEo 'apng|bmp|gif|jpeg|png|webp' | head -n1 | tr '[:upper:]' '[:lower:]')

# Check if the image format is supported
[ -z "$fmt" ] && usage && exit 1

# Create an IMG template
img="$(base64 --decode base64.txt > "$1")'"



#echo "$img"
echo "Base64 to Image Decoded!"