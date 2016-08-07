ECHO OFF
 ..\..\..\bin\Debug\tconvolution -i c11man_16bits.raw -x 256 -y 256 -z 1 -d 16 -k gradW_3x3_16bits.raw -a 3 -b 3 -c 1 -m 2 -n 0 -p 32000 -r -32000 -o result_256_256_16bits.raw
PAUSE