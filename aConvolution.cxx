#include<aConvolution.h>
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
void aConvolution<T,U>::make(aImage<T> &img1, aImage<T> &img2, aImage<T> &out) {
  m_isOK = true;
  int nCol1, nRow1, nBand1;
  int nCol2, nRow2, nBand2;
  U Sum;
  T res;

  // create neighbour coordinates map
  aGrid *pGrid = aGrid::make_grid(A_GRID_CUSTOM);
  if ( pGrid==0 ) {
     m_isOK      = false;
     m_lastError = "Cannot create a custom grid.";
     return;
  }

  std::cout<<"Grid created"<<std::endl;
  // Initialization
  nCol1  = img1.getSizeX();
  nRow1  = img1.getSizeY();
  nBand1 = img1.getSizeZ();

  nCol2  = img2.getSizeX();
  nRow2  = img2.getSizeY();
  nBand2 = img2.getSizeZ();

  // resize out if necessary
  if ( nCol1  != out.getSizeX() || nRow1  != out.getSizeY() || nBand1 != out.getSizeZ() ) {
     out.resize(nCol1, nRow1, nBand1);
  }

  pGrid->setGridSize(nCol2, nRow2, nBand2);

  // 0 means to use the weight of kernel as the norm value
  if ( m_normValue == 0.0 ){
      T nS = 0;
      T *p2 = img2.getPtr();
      for ( int i=0; i<img2.getSize(); i++ ) {
          nS += *(p2+i);
      }
      if ( nS == (T)0 ) m_normValue = (U)1.0;
      else m_normValue = (U)1/(U)nS;
  }  

  // calculate convolution
  // convj = Sum fi*gi  
  // 
  intPOINT P; // current point
  intPOINT p; // neighbour point
  // Iterate though all image points and calculate neighbour coordinates p_i, i \in N. The neibourhood N is defined by the
  // convolution kernel img2, centered into point P.
  // Calculate a sum_N img1(p_i)*img2(-i) for every p and normaise it, if necessary. 
  // out(P) = sum_N * m_normValue;
  // Note: this version of the image convolution is mathematically correct, while the input kernel is rotated.
  for ( int k=0; k<nBand1; k++ ) {  
      P.z = k;
      for ( int j=0; j<nRow1; j++ ) {
          P.y = j;
          for ( int i=0; i<nCol1; i++ ) { 
              P.x = i;
              pGrid->calculateNeighbours(P);

              // calculate sum for (i,j,k) point
              Sum       = 0.0;
              int count = 0;
              // Version for non-rotated kernel (mathematically not correct)
              /*for ( int kk=0; kk<nBand2; kk++ ) {
                  for ( int jj=0; jj<nRow2; jj++ ){
                      for ( int ii=0; ii<nCol2; ii++ ){*/
              // Version for rotated kernel (mathematically correct)
              for ( int kk=nBand2-1; kk>=0; kk-- ) {
                  for ( int jj=nRow2-1; jj>=0; jj-- ){
                      for ( int ii=nCol2-1; ii>=0; ii-- ){
                          // find a corresponding point of second image (ii,jj,kk)
                          // and check conditions
                          
                          p = pGrid->getPoint(count);
                          count++;
                          // check the point to be inside the convolved image
                          if (p.x>=0 && p.x<nCol1){
                              if (p.y>=0 && p.y<nRow1)
                                  if (p.z>=0 && p.z<nBand1 ) {
                                      // Get the convolution sum
                                      Sum += img1.elem(p.x, p.y, p.z)*img2.elem(ii,jj,kk);
                                  }

                          } // end if
                      } // end for ii
                  }
              }
              
              // Normalise the sum, depending on the image type T.
              res = normalise(Sum);
              if ( m_isLimited ) {
                  if ( res > m_maxLimit ) { 
                      //apply maximal limit
                      out.elem(i,j,k) = m_maxLimit;
                  } else { 
                      if ( res < m_minLimit ) { 
                          // apply minimal limit
                          out.elem(i,j,k) = m_minLimit;
                      }
                  }
              } 
              // Assitgn output image value (i,j,k)
              out.elem(i,j,k) = (T)res;

          } // end for i     
      } // end for j
  } // end for k

  // Clean memory
  //delete pGrid;
  //pGrid->release();

}//end aConvolution<T,U>::makeConvolution() 

// Normalisation with round value
template<class T, class U>
T aConvolution<T,U>::normalise(U sum) {
  T res;
  if ( m_normValue !=1 )
     res = (T)(sum * m_normValue) + 0.5;
  else 
     res = (T)sum;
  return res;
}
// Normalisation for float type
template<>
float aConvolution<float,float>::normalise(float sum) {
  float res;
  if ( m_normValue !=1 )
     res = (float)(sum * m_normValue);
  else 
     res = (float)sum;
  return res;
}
// Normalisation for double type
template<>
double aConvolution<double,double>::normalise(double sum) {
  double res;
  if ( m_normValue !=1 )
     res = (double)(sum * m_normValue);
  else 
     res = (double)sum;
  return res;
}
 
template class aConvolution<char,float>;
template class aConvolution<unsigned char,float>;
template class aConvolution<short,float>;
template class aConvolution<unsigned short,float>;
template class aConvolution<int,float>;
template class aConvolution<unsigned int,float>;
template class aConvolution<float,float>; 

template class aConvolution<char,double>;
template class aConvolution<unsigned char,double>;
template class aConvolution<short,double>;
template class aConvolution<unsigned short,double>;
template class aConvolution<int,double>;
template class aConvolution<unsigned int,double>;
template class aConvolution<double,double>; 
