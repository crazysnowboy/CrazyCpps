
##--------------module x.i---------------------
set(PTHON_I_TEMPLATE
"%module pyCrazyCPP
 %{
#define SWIG_FILE_WITH_INIT
#include \"cmake_generated/headers.h\"
 %}

%include \"swig/numpy.i\"

%init %{
  import_array()\;
%}


%apply (double* IN_ARRAY2,int DIM1, int DIM2) {(double* mat,int rows,int cols)}


%rename (NumpyData_Python2CPP) myNumpyData_Python2CPP\;
%inline %{
            void myNumpyData_Python2CPP(double* mat, int rows, int cols, crazy::DMatrix &DMat)
            {
                NumpyData_Python2CPP(mat, rows, cols,DMat)\;

            }
        %}
%rename (Image_Python2CPP) myImage_Python2CPP\;
%inline %{
            void myImage_Python2CPP(double* mat, int rows, int cols,int c,crazy::ImageMatrix &ImageMat)
            {
                Image_Python2CPP(mat, rows, cols,c,ImageMat)\;

            }
        %}

%apply (double* ARGOUT_ARRAY1, int DIM1) {(double* mat,int length)}

%include cmake_generated/incs_for_wrap.i

%clear (double* mat,int rows,int cols)\;")
