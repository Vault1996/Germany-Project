/* includes */
#include <cstring>
#include <aConvolution.h>
#include <aInputOutput.h>
#include <limits.h>

/******************************************************************************

   Author:          Oleg Krivonos (C) 9/10/1998

   Project name:    vgl-extension classes test

   Date:            9/21/1999

   Name:            runConvolution

   Description:     
   algorithm:  Create skeleton image by using thinning algorithm 


   called by: 
              

   calls: 


   tested:    not yet

   preconditions: 
              Volume dataset have to be initialized

   postconditions: 


   possible problems: 
	      
   Parameters:     

********************************************************************************/

void runConvolution(char *inVolume1, int x1, int y1, int z1, int depth, 
		    char *inVolume2, int x2, int y2, int z2, int method_id, int norm, 
		    int vmax, int vmin, 
		    char *outVolume) {

 const char program[]="runConvolution";
 std::cout<<program<<" is running"<<std::endl;

  switch(depth){
    case 8:{ 
      std::cout<<"depth = 8"<<std::endl;
      aConv<char,double> *pConv = aConv<char,double>::make_conv(method_id);
      if ( pConv == 0 ) {
          std::cout<<"Cannot create a convolution object for the specified method id: "<<(int)method_id<<std::endl;
          return;
      }
      pConv->setNormValue(norm);
    
      pConv->setMaxLimit((char)vmax);
      pConv->setMinLimit((char)vmin);
      // allow the limits
      pConv->setLimitsOn(true);

      aImage<char> volume1( x1, y1, z1 );
      aImage<char> volume2( x2, y2, z2 );
      aImage<char> volume3; 

      aInputOutput<char> ioObj;
      ioObj.readRaw( inVolume1, volume1 );
      ioObj.readRaw( inVolume2, volume2 );

      std::cout<<"Make convolution volume"<<std::endl;
      pConv->make( volume1, volume2, volume3 );
      if ( !pConv->isOK() ) {
         std::cout<<pConv->getLastError()<<std::endl;
         return;
      }

      std::cout<<"Write to file ..."<<std::endl;
      ioObj.writeRaw( outVolume, volume3 );

      // Clean memory
      delete pConv;

      std::cout<<"Done ... "<<std::endl;

    } break;

    case 16:{ 
      std::cout<<"depth = 16"<<std::endl;

      aConv<short,double> *pConv = aConv<short,double>::make_conv(method_id);
      if ( pConv == 0 ) {
          std::cout<<"Cannot create a convolution object for the specified method id: "<<(int)method_id<<std::endl;
          return;
      }
      pConv->setNormValue(norm);

      pConv->setMaxLimit((short)vmax);
      pConv->setMinLimit((short)vmin);
      // allow the limits
      pConv->setLimitsOn(true);

      aImage<short> volume1( x1, y1, z1 );
      aImage<short> volume2( x2, y2, z2 );
      aImage<short> volume3; 

      aInputOutput<short> ioObj;
      ioObj.readRaw( inVolume1, volume1 );

      ioObj.readRaw( inVolume2, volume2 );

      std::cout<<"Make convolution volume"<<std::endl;
      pConv->make( volume1, volume2, volume3 );
      if ( !pConv->isOK() ) {
         std::cout<<pConv->getLastError()<<std::endl;
         return;
      }

      std::cout<<"Write to file ..."<<std::endl;
      ioObj.writeRaw( outVolume, volume3 );

      // Clean memory
      delete pConv;

      std::cout<<"Done ... "<<std::endl;

    } break;

    default: std::cout<<"ERROR: wrong data type"<<std::endl;

  }// end switch

}// End runConvolution
