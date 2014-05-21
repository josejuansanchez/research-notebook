#!/bin/bash

#set -x

# Tools
WOISTOCACHE=/home/josejuan/experimentos/experimentos_cr/conditional_replenishment/Code/CR/woistocache
DECODEFROMCACHE=/home/josejuan/experimentos/experimentos_cr/conditional_replenishment/Code/CR/decodefromcache
SNR=/home/josejuan/experimentos/experimentos_cr/conditional_replenishment/tools/snr

#################################################

# Precinct size at the maximum resolution level
W_PRECINT_SIZE=128
H_PRECINT_SIZE=128

# Compression parameters used in Kakadu
CLEVELS=2
CLAYERS=8

# Original image dimension
WIDTH_RECONS=1280
HEIGHT_RECONS=768

#################################################

# Functions
function CheckExitStatusCode()
{
	if [ $? -ne 0 ]; then
		echo "Error"
		exit
	fi
}

function check_psnr_mode {

	MODE=$1
	IMAGE_J2C=$2
	IMAGE_J2C_CACHE=${2}.cache

	for ((LAYER=1; LAYER <= CLAYERS ; LAYER++))
	do
		# Cleaning a bit
		rm *.cache > /dev/null 2>&1
		rm *.lrcp  > /dev/null 2>&1
		rm *.sort  > /dev/null 2>&1
		rm *.woi   > /dev/null 2>&1
		rm *.pgm   > /dev/null 2>&1
		rm bytes.readed > /dev/null 2>&1

		$WOISTOCACHE $IMAGE_J2C wois.txt $W_PRECINT_SIZE $H_PRECINT_SIZE $(($CLEVELS+1)) $LAYER 999999999 $MODE > /dev/null 2>&1
		CheckExitStatusCode
		BYTES_READED=`cat bytes.readed`

		$DECODEFROMCACHE $IMAGE_J2C_CACHE out.pgm $WIDTH_RECONS $HEIGHT_RECONS $IMAGE_J2C > /dev/null 2>&1
		CheckExitStatusCode

		#display out.pgm
		pamcut -left 0 -top 0 -width $W_PRECINT_SIZE -height $H_PRECINT_SIZE out.pgm > out_cut.pgm
		CheckExitStatusCode
		
		#display out_cut.pgm 
		kdu_expand -i $IMAGE_J2C -o 1ql.pgm -layers $LAYER > /dev/null 2>&1
		CheckExitStatusCode
		
		pamcut -left 0 -top 0 -width $W_PRECINT_SIZE -height $H_PRECINT_SIZE 1ql.pgm > 1ql_cut.pgm
		CheckExitStatusCode
		
		#cmp out_cut.pgm 1ql_cut.pgm

		PSNR_VS_SAME_QL=`$SNR --type=uchar --peak=255 --file_A=1ql_cut.pgm --file_B=out_cut.pgm 2> /dev/null | \
		grep "PSNR\[dB\]" | awk '{print $3}'`
		CheckExitStatusCode

		# Compare with the original image
		IMAGE_ALL_QL=all_ql.pgm
		IMAGE_ALL_QL_CUT=all_ql_cut.pgm

		kdu_expand -i $IMAGE_J2C -o $IMAGE_ALL_QL > /dev/null 2>&1
		CheckExitStatusCode
		
		pamcut -left 0 -top 0 -width $W_PRECINT_SIZE -height $H_PRECINT_SIZE $IMAGE_ALL_QL > $IMAGE_ALL_QL_CUT
		CheckExitStatusCode

		PSNR_VS_ALL_QL=`$SNR --type=uchar --peak=255 --file_A=$IMAGE_ALL_QL_CUT --file_B=out_cut.pgm 2> /dev/null | \
		grep "PSNR\[dB\]" | awk '{print $3}'`
		CheckExitStatusCode

		echo -e "Layer: $LAYER \t PSNR_VS_SAME_QL: $PSNR_VS_SAME_QL \t PSNR_VS_ALL_QL: $PSNR_VS_ALL_QL \t BYTES_READED: $BYTES_READED"
	done
}  

#################################################

# Tests
#
# 1) Mode 0 (Kakadu Mode)
echo -e "\nTest Mode 0 (Kakadu Mode)"
check_psnr_mode 0 image.j2c wois.txt

# 2) Mode 1 (Exact WOI)
echo -e "\nTest Mode 1 (Exact WOI)"
check_psnr_mode 1 image.j2c wois.txt