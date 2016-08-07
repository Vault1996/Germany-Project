#ifndef _A_CONVOLUTION_H
#define _A_CONVOLUTION_H

#include <iostream>
#include <aNConvolution.h>

/* includes */
#include <aImage.h>
//#include <bool.h>
#include <aGrid.h>

// STL
#include <string>
#include <vector>

/**
* Convolution methods
*/
#define A_CONVOLUTION    0 // Padded same convolution, i.e. the output image O has the same size as the input image I.
#define A_FCONVOLUTION   1 // Padded full convolution, i.e. the output image size O=I+h-1.
#define A_NCONVOLUTION   2 // Normalised convolution
#define A_FFTCONVOLUTION 3 // FFT-based convolution

template<class T, class U> class aConvolution;
//template<class T, class U> class aFConvolution;   // reserved
//template<class T, class U> class aNConvolution;   // reserved
//template<class T, class U> class aFFTConvolution; // reserved

/** \class aConv factory
* \brief A Factory for a convolution of two images. 
* 
* Input 2D or 3D images of the same type T are convolved and the result is stored into an output image. The convolved pixels
* can be normalised by multiplication on a coefficient of type U (float or double).
* \author ooo
* \date 2016
*/
template<class T,class U> class aConv {
  public:
    //! Factory Method
	static aConv<T,U>* make_conv(int id) {
		if ( id == A_CONVOLUTION){
		   return new aConvolution<T,U>();
		}
        /*if ( id == A_FCONVOLUTION){
		   return new aFConvolution<T,U>();
		}*/
        if ( id == A_NCONVOLUTION){
		   return new aNConvolution<T,U>();
		}
        /*if ( id == A_FFTCONVOLUTION){
		   return new aFFTConvolution<T,U>();
		}*/
		return 0;
	}
	//! Interface
    virtual void make(aImage<T> &imgI, aImage<T> &imgT, aImage<T> &oImg) = 0;

    //!
    virtual bool isOK() = 0;

    //!
    virtual std::string getLastError() = 0;

    //! Set a normalisation coefficient.
    virtual void setNormValue(U norm) = 0;

    //! Get the current or applied normalisation coefficient.
    virtual U getNormValue() = 0;

    //! Maximal value of the output image.
    virtual void setMaxLimit(T value) = 0;

    //! Get maximal value of the output image.
    virtual T getMaxLimit() = 0;

    //! Minimal value of the output image.
    virtual void setMinLimit(T value) = 0;

    //! Get minimal value of the output image.
    virtual T getMinLimit() = 0;

    //! Set limits on/off
    virtual void setLimitsOn(bool on) = 0;
};

/** \class aConvolution
* \brief A convolution of two images. 
* 
* Input images of the same type T are convolved and the result is stored into an output image. The convolved pixels
* can be normalised by multiplication on a coefficient of type U (float or double). The implementation suits for convolving with separable Kernels. 
* \author ooo
* \date 2016
*/
template<class T, class U> class aConvolution: public aConv<T,U> {
public:

  //! Default constructor. 
  aConvolution() {
     Init();
  };

  //! Virtual destructor.
  virtual ~aConvolution() {
  };

  //! Calculate the convolution of imgI and imgG. oImg = imgT*imgG
  void make(aImage<T> &imgI, aImage<T> &imgG, aImage<T> &oImg);

  //!
  virtual bool isOK() {
      return m_isOK;
  };

  //!
  virtual std::string getLastError() {
      return m_lastError;
  };

  //! Sets the notmalisation coefficient of the type U. Default norm = 1.0. If norm = 0, no normalisation, if norm <0 a 1/(sum of kernel elements) will be calculated as the coefficient.
  virtual void setNormValue(U norm) {
      m_normValue = norm;
  };

  //! Get the current or applied normalisation coefficient.
  virtual U getNormValue() {
      return m_normValue;
  };

  //! Maximal value of the output image.
  virtual void setMaxLimit(T value){
    m_maxLimit = value;
  };

  //! Get maximal value of the output image.
  virtual T getMaxLimit(){
    return m_maxLimit;
  };

  //! Minimal value of the output image.
  virtual void setMinLimit(T value){
    m_minLimit = value;
  };

  //! Get minimal value of the output image.
  virtual T getMinLimit(){
    return m_minLimit;
  };

  //! Set limits on/off
  virtual void setLimitsOn(bool on) {
     m_isLimited = on;
  };

protected:
  //! State.
  int m_isOK;

  //! Last message.
  std::string m_lastError;

  //! Normalisation value.
  U m_normValue;
  //! Max limit.
  T m_maxLimit;
  //! Min limit.
  T m_minLimit;
  //! Limit flag.
  bool m_isLimited;

 void Init( ) { // Init method
     m_normValue = (U)1.0;
     m_maxLimit  = (T)255;
     m_minLimit  = (T)0;
     m_isLimited = false;
     m_isOK      = true;
     m_lastError = "";
  };

 //! Normalise the sum and convert to the image type T.
 inline T normalise(U sum);

}; // end of aConvolution class description

#endif  // _A_CONVOLUTION_H