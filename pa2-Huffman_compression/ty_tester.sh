#!/usr/bin/env bash
#### Description: UCSD CSE100 Spring 2016 PA2 Self-Tester for Students.
#### Usage: 
#### 1. In the directory that contains the script, run `chmod u+x ty_tester.sh` so that it is executable. 
####   * See [chmod](https://en.wikipedia.org/wiki/Chmod) on Wikipedia. 
#### 2. Run `./ty_tester.sh`

set -o nounset

# Text
# These are used for colored command line output
# See https://en.wikipedia.org/wiki/Tput
TXT_RESET="$(tput sgr 0 2> /dev/null)"
TXT_RED="$(tput setaf 1 2> /dev/null)"
TXT_GREEN="$(tput setaf 2 2> /dev/null)"
TXT_YELLOW="$(tput setaf 3 2> /dev/null)"
TXT_CYAN="$(tput setaf 6 2> /dev/null)"

# Variables
INPUT_DIR="pa2_input_files"
REF_CMP="ty_test_ref_cmp.tmp"
YOUR_CMP="ty_test_your_cmp.tmp"
REF_UNCMP="ty_test_ref_uncmp.tmp"
YOUR_UNCMP="ty_test_your_uncmp.tmp"
RAND_TXT="ty_large_random_input.txt"
RAND_BIN="ty_large_random_input.bin"

# This creates a temporary directory to store the generated test files
TMP_DIR="$(mktemp -d)"

# I am using `hostname` to determine if the script is running on ieng6, not robust, but works
[[ $(hostname -s) = ieng6* ]]; ON_IENG6=$?

# This function takes a size argument (byte) to generate random text & binary files using `openssl rand`
# `openssl rand` is faster than using `/dev/urandom`
# See https://en.wikipedia.org/wiki/OpenSSL https://en.wikipedia.org/wiki//dev/random
generate_random_input_files() {
  local input_file_size="$1" # the size argument
  if [[ -z ${input_file_size} ]]; then
    echo "generate_random_input_files: No size was specified. Exiting. ";
    exit 1
  fi
  echo -ne "Generating random input text & binary files of size ${input_file_size}... "
  # Base64 is used to produce text file, see: https://en.wikipedia.org/wiki/Base64
  # The * 3/4 part accounts for Base64 overhead so that the output is of the correct size
  openssl rand -out "${INPUT_DIR}/${RAND_TXT}" -base64 $(( ${input_file_size} * 3/4 ))
  openssl rand -out "${INPUT_DIR}/${RAND_BIN}" ${input_file_size}
  echo -e "[${TXT_GREEN}DONE${TXT_RESET}]"
}

# This function uses stat to get the file sizes of your compressed version and the reference compressed version
compression_ratio_test() {
  # This if statement is to test whether the machine has GNU `stat` or BSD `stat` since the flags are different
  # ieng6 has GNU `stat`, OS X has BSD `stat`. 
  # Actually, `compression_ratio_test` is run only when on ieng6, see below. But it is nice to have portable code. 
  # The if condition works because BSD `stat` does not have the `--version` flag so the return code will tell
  # See https://en.wikipedia.org/wiki/GNU_toolchain & https://wiki.freebsd.org/BSDToolchain
  if stat --version &>/dev/null; then
    # GNU `stat`
    local ref_cmp_filesize="$(stat -c%s "${TMP_DIR}/${REF_CMP}")"
    local your_cmp_filesize="$(stat -c%s "${TMP_DIR}/${YOUR_CMP}")"
  else
    # BSD `stat`
    local ref_cmp_filesize="$(stat -f%z "${TMP_DIR}/${REF_CMP}")"
    local your_cmp_filesize="$(stat -f%z "${TMP_DIR}/${YOUR_CMP}")"
  fi
  # The actual comparison, `-gt` means greater than
  if [[ ${ref_cmp_filesize} -gt ${your_cmp_filesize} ]]; then
    echo -e "[${TXT_GREEN}PASSED${TXT_RESET}]"
  else
    echo -e "[${TXT_YELLOW}ACCURATE${TXT_RESET}]"
    echo -e "${TXT_YELLOW}Reference compressed size: ${ref_cmp_filesize}. Your compressed size is ${your_cmp_filesize}. ${TXT_RESET}"
  fi
}

is_on_ieng6() {
  return ${ON_IENG6}
}

# This function removes the generated files
cleanup () {
  rm "${INPUT_DIR}/${RAND_TXT}" "${INPUT_DIR}/${RAND_BIN}"
  rm -rf "${TMP_DIR}"
  # ehco -e "${TMP_DIR}"
  echo "Temporary files generated by the tests deleted. "
  echo -e "${TXT_YELLOW}WARNING: THIS SCRIPT IS PROVIDED FOR YOUR REFERENCE ONLY. ${TXT_RESET}"
  echo -e "${TXT_YELLOW}IT DOES NOT COME WITH ANY GUARANTEE. ${TXT_RESET}"
  echo -e "${TXT_YELLOW}IT IS YOUR RESPONSIBILITY TO MAKE SURE YOUR CODE WORKS CORRECTLY. ${TXT_RESET}"
}
trap cleanup EXIT # trap is a nice feature. Upon EXIT, cleanup function is run

# use `make` to compile your code, check return code for failure
if ! make; then
    echo -e "${TXT_RED}Failed to compile using make. ${TXT_RESET} No test was run. "
    exit 1 # unsuccessful
fi
echo -e "${TXT_GREEN}Compiled successfully using make. ${TXT_RESET}"

# generates a random binary input file and a random text input file for testing 
if is_on_ieng6; then
  echo -e "${TXT_CYAN}NOTE: On ieng6, the random files generated are of smaller size for performance reason. ${TXT_RESET}"
  generate_random_input_files 5242880 # since ieng6 is slow
else
  generate_random_input_files 10485760
  echo -e "${TXT_CYAN}NOTE: Compression ratio tests will not be run since you are not on ieng6. ${TXT_RESET}"
fi

# loop through all the input files found in in the input file directory
for input_file in "${INPUT_DIR}"/*; do
  echo -ne "Testing \"${input_file}\"... \t "
  # perform `compress` and `uncompress`, suppress output
  ./compress "${input_file}" "${TMP_DIR}/${YOUR_CMP}" &> /dev/null
  ./uncompress "${TMP_DIR}/${YOUR_CMP}" "${TMP_DIR}/${YOUR_UNCMP}" &> /dev/null
  # since `refcompress` is compiled and run on ieng6
  if is_on_ieng6; then
    # perform `refcompress`, suppress output
    ./refcompress "${input_file}" "${TMP_DIR}/${REF_CMP}" &> /dev/null
    # ./refuncompress "${TMP_DIR}/${REF_CMP}" "${TMP_DIR}/${REF_UNCMP}" &> /dev/null
  fi
  # `cmp`'s return code indicates if the files are identical
  if cmp -s "${input_file}" "${TMP_DIR}/${YOUR_UNCMP}"; then
    # since `refcompress` is compiled and run on ieng6
    if is_on_ieng6; then
      compression_ratio_test
    else
      echo -e "[${TXT_YELLOW}ACCURATE${TXT_RESET}]"
    fi
  else
    echo -e "[${TXT_RED}FAILED${TXT_RESET}]"
    echo -e "${TXT_RED}Not all tests were run. ${TXT_RESET}"
    exit 1 # unsuccessful
  fi
done

echo "All tests finished. "
exit 0 # successful


