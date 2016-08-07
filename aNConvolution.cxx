#include<aConvolution.h>
#include<aNConvolution.h>
#include<aDebug.h>

/** 
* Make padded same size convolution of two images img1 and img 2, the result is stored in the image out.
* The image out will have the same size as the image img1.
* Suits for small kernels as well as for filters with separables kernels.
* In case of overflow, intensity limits can be applied to resulted sums, if m_isLimited variable is set to true.
* In case of float and double image types, a necessary normalisation can be applied to the kernel before passing to this method, otherwise
* a proper normalisation value V has to be passed via setNormValue(V) method. Each sum will be normalised using the formula
* val = (T)(sum*1/V + 0.5). If the normValue is set to 0, then the value V is calulated as a sum of all kernel items.
*/
// An example of an implementation by default (not optimal for performance).
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

  // resize to have gaps
  img1.resize( 2*nCol1, 2*nRow1, 2*nBand1 );

  // creating map of input image
  aImage<T> mapImage ( img1 );
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
