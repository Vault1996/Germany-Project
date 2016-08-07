#include<aConvolution.h>
#include<aDebug.h>

template<class T, class U>
void aNConvolution<T,U>::make(aImage<T> &img1, aImage<T> &img2, aImage<T> &out) {
  m_isOK = true;
  int nCol1, nRow1, nBand1;
  int nCol2, nRow2, nBand2;
  // Initialization
  nCol1  = img1.getSizeX();
  nRow1  = img1.getSizeY();
  nBand1 = img1.getSizeZ();

  nCol2  = img2.getSizeX();
  nRow2  = img2.getSizeY();
  nBand2 = img2.getSizeZ();

  intPOINT P; // current point

  // creating map of input image
  aImage<T> mapImage ( nCol1, nRow1, nBand1 );
  for ( int k=0; k<nBand1; k++ ) {
      P.z = k;
      for ( int j=0; j<nRow1; j++ ) {
          P.y = j;
          for ( int i=0; i<nCol1; i++ ) { 
              P.x = i;
			  if ( img1.elem( P.x, P.y, P.z ) != 0 ) {
				  mapImage.elem( P.x, P.y, P.z ) = 1;
			  } else {
				  mapImage.elem( P.x, P.y, P.z ) = 0;
			  }
		  }
	  }
  }	// map created

  aImage<T> normalizedMap;
  
  aConv<T, U> *simpleConvolution = aConv<T, U>::make_conv(A_CONVOLUTION);

  simpleConvolution->make(mapImage, img2, normalizedMap);

  simpleConvolution->make(img1, img2, out);

  // normolizing output image
  for ( int k=0; k<nBand1; k++ ) {  
      P.z = k;
      for ( int j=0; j<nRow1; j++ ) {
          P.y = j;
          for ( int i=0; i<nCol1; i++ ) { 
              P.x = i;
			  if(normalizedMap.elem( P.x, P.y, P.z ) != 0)
			      out.elem( P.x, P.y, P.z ) /= normalizedMap.elem( P.x, P.y, P.z );
		  }
	  }
  }

}//end aNConvolution<T,U>::makeConvolution() 

 
template class aNConvolution<char,float>;
template class aNConvolution<unsigned char,float>;
template class aNConvolution<short,float>;
template class aNConvolution<unsigned short,float>;
template class aNConvolution<int,float>;
template class aNConvolution<unsigned int,float>;
template class aNConvolution<float,float>; 

template class aNConvolution<char,double>;
template class aNConvolution<unsigned char,double>;
template class aNConvolution<short,double>;
template class aNConvolution<unsigned short,double>;
template class aNConvolution<int,double>;
template class aNConvolution<unsigned int,double>;
template class aNConvolution<double,double>; 
