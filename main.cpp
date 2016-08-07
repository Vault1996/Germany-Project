#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bool.h> 

void runConvolution(char *inVolume1, int x1, int y1, int z1, int depth, 
		    char *inVolume2, int x2, int y2, int z2, int method_id, int norm, 
		    int vmax, int vmin, 
		    char *outVolume);

int main(int argc, char **argv) {
 bool flag = false;

 if ( argc ==29 ) {
   if ( (argv[1][0] == '-' && argv[1][1] == 'i' ) &&
	(argv[3][0]  == '-' && argv[3][1] == 'x' ) &&
	(argv[5][0]  == '-' && argv[5][1] == 'y' ) &&
	(argv[7][0]  == '-' && argv[7][1] == 'z' ) &&
	(argv[9][0]  == '-' && argv[9][1] == 'd' ) && 
	(argv[11][0] == '-' && argv[11][1] == 'k' ) &&
	(argv[13][0]  == '-' && argv[13][1] == 'a' ) &&
	(argv[15][0]  == '-' && argv[15][1] == 'b' ) &&
	(argv[17][0]  == '-' && argv[17][1] == 'c' ) &&
    (argv[19][0] == '-' && argv[19][1] == 'm' ) &&
	(argv[21][0] == '-' && argv[21][1] == 'n' ) &&
	(argv[23][0] == '-' && argv[23][1] == 'p' ) &&
	(argv[25][0] == '-' && argv[25][1] == 'r' ) &&
    (argv[27][0] == '-' && argv[27][1] == 'o' )) {
	
    runConvolution( argv[2], atoi(argv[4]), atoi(argv[6]), atoi(argv[8]), atoi(argv[10]), 
		    argv[12], atoi(argv[14]), atoi(argv[16]), atoi(argv[18]), atoi(argv[20]),
		    atoi(argv[22]), atoi(argv[24]), atoi(argv[26]), argv[28] );
	flag = true;
   }
 }

 if ( flag==false ){
   std::cout<<"myfilter require "<<std::endl;
   std::cout<<"\n-i    input image"<<std::endl;
   std::cout<<"\n-x    size of x"<<std::endl;
   std::cout<<"\n-y    size of y"<<std::endl;
   std::cout<<"\n-z    size of z"<<std::endl;
   std::cout<<"\n-d    depth"<<std::endl;   
   std::cout<<"\n-k    input kernel"<<std::endl;
   std::cout<<"\n-a    size of x"<<std::endl;
   std::cout<<"\n-b    size of y"<<std::endl;
   std::cout<<"\n-c    size of z"<<std::endl;
   std::cout<<"\n-m    convolution method [0 padded same, ...]"<<std::endl;
   std::cout<<"\n-n    norm flag[0,norm_value]"<<std::endl;
   std::cout<<"\n-p    max limit value of convolution"<<std::endl;
   std::cout<<"\n-r    min limit value of convolution"<<std::endl;
   std::cout<<"\n-o    output image"<<std::endl;
   std::cout<<"\nExample: myfilter -i man.raw -x 256 -y 256 -z 100 -d 16 -k gauss3x3x3.raw -a 3 -b 3 -c 3 -m 0 -n 0 -p 32000 -r 0 -o blur.raw"<<std::endl;
 }

 system("pause");

}// End main()
