#include "_seg_tools.h"
#ifdef _OPENMP
#include "omp.h"
#endif

int Create_diagonal_GH_Nclass(SegPrecisionTYPE * G,
                              SegPrecisionTYPE * H,
                              SegPrecisionTYPE ratio,
                              SEG_PARAM * segment_param)
{
  //WM - neighbours GM and dGM
  int numclass=segment_param->numb_classes;
  for(int i=0; i<segment_param->numb_classes; i++){
      for(int j=0; j<segment_param->numb_classes; j++){
          if(i!=j){
              G[i+j*numclass]=segment_param->MRF_strength;
              H[i+j*numclass]=ratio*G[i+j*numclass];
            }
          else{
              G[i+j*numclass]=0.0;
              H[i+j*numclass]=ratio*G[i+j*numclass];
            }

        }
    }

  //Print G
  if(segment_param->verbose_level>1){
      cout<<"G=" << endl;
      for (int i=0; i<numclass; i++) {
          for (int  j=0; j<numclass; j++) {
              cout<< (SegPrecisionTYPE)G[i+j*numclass] << '\t';
            }
          cout<< endl;
        }
      cout<< endl << "H=" << endl;
      for (int i=0; i<numclass; i++) {
          for (int j=0; j<numclass; j++) {
              cout<< G[i+j*numclass] << '\t';
            }
          cout<< endl;
        }
      cout<< endl;
    }

  return 1;
}


int Create_GH_5class(SegPrecisionTYPE * G,
                     SegPrecisionTYPE * H,
                     SegPrecisionTYPE ba,
                     SegPrecisionTYPE be,
                     SegPrecisionTYPE ratio,
                     SEG_PARAM * segment_param)
{
  //WM - neighbours GM and dGM
  int numclass=5;
  G[WMclass+WMclass*numclass]=0.0;
  G[GMclass+WMclass*numclass]=be;
  G[CSFclass+WMclass*numclass]=ba;
  G[dGMclass+WMclass*numclass]=be;
  G[iCSFclass+WMclass*numclass]=ba;
  //GM  - neighbours WM and CSF
  G[GMclass+GMclass*numclass]=0.0;
  G[CSFclass+GMclass*numclass]=be;
  G[dGMclass+GMclass*numclass]=ba;
  G[iCSFclass+GMclass*numclass]=ba;
  //CSF - neighbours GM
  G[CSFclass+CSFclass*numclass]=0.0;
  G[dGMclass+CSFclass*numclass]=ba;
  G[iCSFclass+CSFclass*numclass]=ba;
  //dGM - neighbours WM and iCSF
  G[dGMclass+dGMclass*numclass]=0.0;
  G[iCSFclass+dGMclass*numclass]=be;
  //iCSF - neighbours dGM
  G[iCSFclass+iCSFclass*numclass]=0.0;
  int i,j;

  //Copy to lower triangle
  for (j=0; j<numclass; j++) { for (i=1+j; i<numclass; i++) { G[j+i*numclass]=G[i+j*numclass]; } }
  //Copy G to H
  for (int i=0; i<(numclass*numclass); i++) { H[i]=ratio*G[i]; }
  //Print G
  if(segment_param->verbose_level>1){
      cout<<"G=" << endl;
      for (i=0; i<numclass; i++) {
          for (j=0; j<numclass; j++) {
              cout<< (SegPrecisionTYPE)G[i+j*numclass] << '\t';
            }
          cout<< endl;
        }
      cout<< endl << "H=" << endl;
      for (i=0; i<numclass; i++) {
          for (j=0; j<numclass; j++) {
              cout<< G[i+j*numclass] << '\t';
            }
          cout<< endl;
        }
      cout<< endl;
    }

  return 1;
}


int Create_GH_7class(SegPrecisionTYPE * G,
                     SegPrecisionTYPE * H,
                     SegPrecisionTYPE ba,
                     SegPrecisionTYPE be,
                     SegPrecisionTYPE ratio,
                     SEG_PARAM * segment_param)
{
  //WM - neighbours WMGMpv and dGM
  int numclass=7;
  G[WMclass+WMclass*numclass]=0.0;
  G[GMclass+WMclass*numclass]=ba;
  G[CSFclass+WMclass*numclass]=ba;
  G[dGMclass+WMclass*numclass]=be;
  G[iCSFclass+WMclass*numclass]=ba;
  G[WMGMpvclass+WMclass*numclass]=be;
  G[GMCSFpvclass+WMclass*numclass]=ba;
  //GM  - neighbours WMGMpv and GMCSFpv
  G[GMclass+GMclass*numclass]=0.0;
  G[CSFclass+GMclass*numclass]=ba;
  G[dGMclass+GMclass*numclass]=ba;
  G[iCSFclass+GMclass*numclass]=ba;
  G[WMGMpvclass+GMclass*numclass]=be;
  G[GMCSFpvclass+GMclass*numclass]=be;
  //CSF - neighbours GMCSFpv
  G[CSFclass+CSFclass*numclass]=0.0;
  G[dGMclass+CSFclass*numclass]=ba;
  G[iCSFclass+CSFclass*numclass]=ba;
  G[WMGMpvclass+CSFclass*numclass]=ba;
  G[GMCSFpvclass+CSFclass*numclass]=be;
  //dGM - neighbours WM and iCSF
  G[dGMclass+dGMclass*numclass]=0.0;
  G[iCSFclass+dGMclass*numclass]=be;
  G[WMGMpvclass+dGMclass*numclass]=ba;
  G[GMCSFpvclass+dGMclass*numclass]=ba;
  //iCSF - neighbours dGM
  G[iCSFclass+iCSFclass*numclass]=0.0;
  G[WMGMpvclass+iCSFclass*numclass]=ba;
  G[GMCSFpvclass+iCSFclass*numclass]=ba;
  //WMGMpv - neighbours WM and GM
  G[WMGMpvclass+WMGMpvclass*numclass]=0.0;
  G[GMCSFpvclass+WMGMpvclass*numclass]=ba;
  //GMCSFpv - neighbours GM and CSF
  G[GMCSFpvclass+GMCSFpvclass*numclass]=0.0;
  int i,j;

  //Copy to lower triangle
  for (j=0; j<numclass; j++) { for (i=1+j; i<numclass; i++) { G[j+i*numclass]=G[i+j*numclass]; } }
  //Copy G to H
  for (int i=0; i<(numclass*numclass); i++) { H[i]=ratio*G[i]; }
  //Print G
  if(segment_param->verbose_level>1){
      cout<<"G=" << endl;
      for (i=0; i<numclass; i++) {
          for (j=0; j<numclass; j++) {
              cout<< G[i+j*numclass] << '\t';
            }
          cout<< endl;
        }
      cout<< endl << "H=" << endl;
      for (i=0; i<numclass; i++) {
          for (j=0; j<numclass; j++) {
              cout<< G[i+j*numclass] << '\t';
            }
          cout<< endl;
        }
      cout<< endl;
    }


  return 1;
}

int seg_convert2binary(nifti_image *image,
                       float thresh)
{
  switch(image->datatype){
    case DT_BINARY:
      break;
    case NIFTI_TYPE_UINT8:
      seg_convert2binary_data<unsigned char>(image,thresh);
      break;
    case NIFTI_TYPE_INT8:
      seg_convert2binary_data<char>(image,thresh);
      break;
    case NIFTI_TYPE_UINT16:
      seg_convert2binary_data<unsigned short>(image,thresh);
      break;
    case NIFTI_TYPE_INT16:
      seg_convert2binary_data<short>(image,thresh);
      break;
    case NIFTI_TYPE_UINT32:
      seg_convert2binary_data<unsigned int>(image,thresh);
      break;
    case NIFTI_TYPE_INT32:
      seg_convert2binary_data<int>(image,thresh);
      break;
    case NIFTI_TYPE_FLOAT32:
      seg_convert2binary_data<float>(image,thresh);
      break;
    case NIFTI_TYPE_FLOAT64:
      seg_convert2binary_data<SegPrecisionTYPE>(image,thresh);
      break;
    default:
      printf("err\tseg_convert2binary\tThe initial image data type (%d) is not supported\n",image->datatype);
      return 1;
    }
  return 1;
}


template <class DTYPE>
int seg_convert2binary_data(nifti_image *image,
                            float thresh)
{
  // the initial array is saved and freeed
  DTYPE *initialValue = (DTYPE *)malloc(image->nvox*sizeof(DTYPE));
  memcpy(initialValue, image->data, image->nvox*sizeof(DTYPE));

  // the new array is allocated and then filled
  image->datatype = DT_BINARY;
  free(image->data);
  image->nbyper = sizeof(bool);
  image->data=(void *)calloc(image->nvox,sizeof(bool));
  bool *dataPtr = static_cast<bool *>(image->data);

  for(unsigned int i=0; i<image->nvox; i++){
      dataPtr[i] = (bool)((initialValue[i])>thresh);
    }
  free(initialValue);
  return 1;
}


int Normalize_NaN_Priors(nifti_image * Priors,
                         bool verbose)
{
  register int numel = Priors->nx*Priors->ny*Priors->nz;
  register int ups=0;
  register int good=0;
  if(verbose>0){
      cout<< "Normalizing Priors" << endl;
    }
  if(Priors->datatype==NIFTI_TYPE_FLOAT32){
      SegPrecisionTYPE * priorsptr = static_cast<SegPrecisionTYPE *>(Priors->data);
      for (int i=0; i<numel; i++) {
          float tempsum=0;
          for (int j=0; j<Priors->nt; j++) {
              int tempind=i+numel*j;
              if( priorsptr[tempind]<0.0 || priorsptr[tempind]!=priorsptr[tempind] || priorsptr[tempind]>1000 ){
                  priorsptr[tempind]=0.0;
                }
              tempsum+=priorsptr[tempind];
            }
          if (tempsum>0 && tempsum<1000) {
              for (int j=0; j<Priors->nt; j++) {
                  int tempind=i+numel*j;
                  priorsptr[tempind]=priorsptr[tempind]/tempsum;
                }
              good++;
            }
          else{
              for (int j=0; j<Priors->nt; j++) {
                  int tempind=i+numel*j;
                  priorsptr[tempind]=0.2f;
                }
              ups++;
            }
        }
    }
  else{

      printf("err\tNormalize_NaN_Priors\tWrong Image datatype\n");

    }

  if(verbose>0){
      cout<<"Priors: "<< good<<" good voxels and "<<ups<<" bad voxels" << endl;
      flush(cout);
    }

  return 1;
}

int PriorWeight_mask(float * ShortPrior,nifti_image * Priors, float * Expec,float GaussKernelSize,float RelaxFactor, int * S2L, int * L2S,ImageSize * CurrSizes,int verbose_level){

  for(int i=0; i<(CurrSizes->numclass*CurrSizes->numelmasked);i++)ShortPrior[i]=Expec[i];
  Gaussian_Filter_Short_4D(ShortPrior,S2L,L2S,GaussKernelSize,CurrSizes,CSFclass);
  float * PriorsPtr = static_cast<float *>(Priors->data);
  int currindex=0;
  for(int k=0; k<CurrSizes->numclass; k++){
      currindex=k*CurrSizes->numelmasked;
      for(int i=0; i<(CurrSizes->numelmasked);i++){
          ShortPrior[currindex]*=(1-RelaxFactor);
          ShortPrior[currindex]+=(RelaxFactor)*PriorsPtr[S2L[i]+k*CurrSizes->numel];
          currindex++;
        }
    }

  return 1;
}




int Normalize_NaN_Priors_mask(nifti_image * Priors,
                              nifti_image * Mask,
                              bool verbose)
{
  register int numel = Mask->nvox;
  register int ups=0;
  register int good=0;
  if(verbose>0){
      cout<< "Normalizing Priors" << endl;
    }
  if(Mask->datatype==DT_BINARY){
      if(Priors->datatype==NIFTI_TYPE_FLOAT32){
          SegPrecisionTYPE * priorsptr = static_cast<SegPrecisionTYPE *>(Priors->data);
          bool * brainmaskptr = static_cast<bool *> (Mask->data);

          for (int i=0; i<numel; i++) {
              if(brainmaskptr[i]){
                  float tempsum=0;
                  for (int j=0; j<Priors->nt; j++) {
                      int tempind=i+numel*j;
                      if( priorsptr[tempind]<0.0 || priorsptr[tempind]!=priorsptr[tempind] || priorsptr[tempind]>1000 ){
                          priorsptr[tempind]=0.0;
                        }
                      tempsum+=priorsptr[tempind];
                    }
                  if (tempsum>0 && tempsum<1000) {
                      for (int j=0; j<Priors->nt; j++) {
                          int tempind=i+numel*j;
                          priorsptr[tempind]=priorsptr[tempind]/tempsum;
                        }
                      good++;
                    }
                  else{
                      for (int j=0; j<Priors->nt; j++) {
                          int tempind=i+numel*j;
                          priorsptr[tempind]=1.0f/(Priors->nt);
                        }
                      ups++;

                    }
                }
              else{
                  for (int j=0; j<Priors->nt; j++) {
                      int tempind=i+numel*j;
                      priorsptr[tempind]=0;
                    }
                }
            }
        }
      else{

          printf("err\tNormalize_NaN_Priors\tWrong Image datatype\n");

        }
    }
  else{

      printf("err\tNormalize_NaN_Priors\tWrong mask datatype\n");

    }

  if(verbose>0){
      cout<<"Priors: "<< good<<" good voxels and "<<ups<<" bad voxels" << endl;
      flush(cout);
    }

  return 1;
}


int Normalize_Image_mask(nifti_image * input,
                         nifti_image * Mask,
                         ImageSize * CurrSizes,
                         bool verbose)
{
  if(input->datatype!=NIFTI_TYPE_FLOAT32){
      seg_changeDatatype<float>(input);
    }
  if(verbose>0){
      cout<< "Normalizing Input Image" << endl;
    }
  int numel=(int)(rowsize(input)*colsize(input)*depth(input));
  if(Mask->datatype!=DT_BINARY){
      seg_convert2binary(Mask,0.0f);
    }
  if(input->datatype!=NIFTI_TYPE_FLOAT32){
      seg_changeDatatype<SegPrecisionTYPE>(input);
    }
  for(int udir=0; udir<CurrSizes->usize;udir++){ // Per Multispectral Image
      bool * brainmaskptr = static_cast<bool *> (Mask->data);
      SegPrecisionTYPE * Inputptrtmp = static_cast<SegPrecisionTYPE *>(input->data);
      SegPrecisionTYPE * Inputptr=&Inputptrtmp[numel*udir];

      float tempmax=-(1e32);
      float tempmin=1e32;

      for (int i=0; i<numel; i++) {
          if(brainmaskptr[i]){
              if (Inputptr[i]<tempmin) {
                  tempmin=Inputptr[i];
                }
              if (Inputptr[i]>tempmax) {
                  tempmax=Inputptr[i];
                }
            }
        }
      CurrSizes->rescale_max[udir]=tempmax;
      CurrSizes->rescale_min[udir]=tempmin;
      if(verbose>0){
          cout << "Normalization["<<udir<<"] = ["<<tempmin<<","<<tempmax<<"]"<<endl;
        }
      Inputptr=&Inputptrtmp[numel*udir];
      brainmaskptr = static_cast<bool *> (Mask->data);
      for (int i=0; i<numel; i++) {
          if(brainmaskptr[i]>0){
              //log(number_between_0_and_1 + 1)/log(2)
              Inputptr[i]=logf((((Inputptr[i])-tempmin)/(tempmax-tempmin))+1)/0.693147181;
            }
          else{
              Inputptr[i]=0;
            }
        }
    }
  return 1;
}

int Normalize_Image(nifti_image * input,
                    ImageSize * CurrSizes,
                    bool verbose)
{
  if(input->datatype!=NIFTI_TYPE_FLOAT32){
      seg_changeDatatype<float>(input);
    }
  if(verbose>0){
      cout<< "Normalizing Input Image" << endl;
    }
  if(input->datatype==NIFTI_TYPE_FLOAT32){
      // if mask is not set up
      for(int udir=0; udir<CurrSizes->usize;udir++){ // Per Multispectral Image
          int numel=(int)(rowsize(input)*colsize(input)*depth(input));
          SegPrecisionTYPE * Inputptrtmp = static_cast<SegPrecisionTYPE *>(input->data);
          SegPrecisionTYPE * Inputptr=&Inputptrtmp[numel*udir];

          float tempmax=0;
          float tempmin=1000000.f;
          for (int i=0; i<numel; i++) {
              if (*Inputptr<tempmin) {
                  tempmin=*Inputptr;
                }
              if (*Inputptr>tempmax) {
                  tempmax=*Inputptr;
                }
              Inputptr++;
            }
          CurrSizes->rescale_max[udir]=tempmax;
          CurrSizes->rescale_min[udir]=tempmin;
          Inputptr=&Inputptrtmp[numel*udir];
          for (int i=0; i<numel; i++) {
              //log(number_between_0_and_1 + 1)/log(2)
              *Inputptr=logf((((*Inputptr)-tempmin)/(tempmax-tempmin))+1)/0.693147181;
              Inputptr++;
            }
        }
    }

  return 1;
}

int Normalize_T1_and_MV(nifti_image * T1,
                        nifti_image * Mask,
                        SegPrecisionTYPE * M,
                        SegPrecisionTYPE * V,
                        ImageSize * CurrSizes)
{

  SegPrecisionTYPE * T1ptrtmp = static_cast<SegPrecisionTYPE *>(T1->data);
  bool * brainmaskptr = static_cast<bool *>(Mask->data);
  SegPrecisionTYPE * T1ptr=T1ptrtmp;
  int numel=(int)(rowsize(T1)*colsize(T1)*depth(T1));
  float tempmax=0;
  float tempmin=100000;
  for (int i=0; i<numel; i++) {
      if(*brainmaskptr){
          if (*T1ptr<tempmin) {
              tempmin=*T1ptr;
            }
          if (*T1ptr>tempmax) {
              tempmax=*T1ptr;
            }
        }
      brainmaskptr++;
      T1ptr++;
    }
  CurrSizes->rescale_max[0]=tempmax;
  CurrSizes->rescale_min[0]=tempmin;
  T1ptr=T1ptrtmp;
  brainmaskptr = static_cast<bool *>(Mask->data);
  for (int i=0; i<numel; i++) {
      if(*brainmaskptr){
          *T1ptr=logf((((*T1ptr)-tempmin)/(tempmax-tempmin))+1)/0.693147181;
        }else{
          *T1ptr=0;
        }
      brainmaskptr++;
      T1ptr++;
    }
  for(int cl=0; cl<CurrSizes->numclass; cl++){
      M[cl]=log(1+(M[cl]-tempmin)/(tempmax-tempmin));
      V[cl]=log(1+(V[cl])/(tempmax-tempmin));
    }

  return 1;
}

int * Create_Short_2_Long_Matrix_from_NII(nifti_image * Mask,
                                          int * shortsize){
  int numel_masked=0;
  int numel = Mask->nvox;
  if(Mask->datatype==DT_BINARY){
      bool * Maskptr = static_cast<bool *> (Mask->data);
      bool * Maskptrtmp = Maskptr;
      for (int i=0; i<numel; i++, Maskptrtmp++) {
          (*Maskptrtmp)>0?numel_masked++:0;
        }
      shortsize[0]=numel_masked;

      int * Short_2_Long_Indices= new int [numel_masked]();
      int * Short_2_Long_Indices_PTR = (int *)(Short_2_Long_Indices);

      Maskptrtmp = Maskptr;
      int tempindex=0;
      for (int i=0; i<numel; i++) {
          if ((*Maskptrtmp)>0) {
              Short_2_Long_Indices_PTR[tempindex]=i;
              tempindex++;
            }
          Maskptrtmp++;
        }
      return Short_2_Long_Indices;
    }
  else {
      printf("err\tCreate_Short_2_Long_Matrix\tWrong Mask datatype\n");
      return NULL;

    }
}

int *  Create_Long_2_Short_Matrix_from_NII(nifti_image * Mask){
  int numel = Mask->nvox;
  int * Long_2_Short_Indices= new int [rowsize(Mask)*colsize(Mask)*depth(Mask)]();
  if(Mask->datatype==DT_BINARY){


      bool * Maskptr = static_cast<bool *> (Mask->data);
      bool * Maskptrtmp = Maskptr;
      int * Long_2_Short_Indices_PTR = (int *) Long_2_Short_Indices;

      Maskptrtmp = Maskptr;
      int tempindex=0;
      for (int i=0; i<numel; i++,Maskptrtmp++,Long_2_Short_Indices_PTR++) {
          if ((*Maskptrtmp)>0) {
              (*Long_2_Short_Indices_PTR)=tempindex;
              tempindex++;
            }
          else{
              (*Long_2_Short_Indices_PTR)=-1;
            }
        }
      return Long_2_Short_Indices;
    }
  else {
      cout<< "err\tCreate_Correspondace_Matrices\tWrong Mask datatype\n" << endl;
    }
  return Long_2_Short_Indices;
}


int * Create_Short_2_Long_Matrix_from_Carray(bool * Mask,
                                             int * shortsize,
                                             int nvox){
  int numel_masked=0;
  int numel = nvox;
  for (int i=0; i<numel; i++) {
      Mask[i]?numel_masked++:0;
    }
  shortsize[0]=numel_masked;

  int * Short_2_Long_Indices= new int [numel_masked]();
  int * Short_2_Long_Indices_PTR = (int *)(Short_2_Long_Indices);

  int tempindex=0;
  for (int i=0; i<numel; i++) {
      if ((Mask[i])>0) {
          Short_2_Long_Indices_PTR[tempindex]=i;
          tempindex++;
        }

    }
  return Short_2_Long_Indices;

}

int *  Create_Long_2_Short_Matrix_from_Carray(bool * Mask,
                                              int nvox){
  int * Long_2_Short_Indices= new int [nvox]();
  int * Long_2_Short_Indices_PTR = (int *) Long_2_Short_Indices;
  int tempindex=0;
  for (int i=0; i<nvox; i++,Long_2_Short_Indices_PTR++) {
      if ((Mask[i])>0) {
          (*Long_2_Short_Indices_PTR)=tempindex;
          tempindex++;
        }
      else{
          (*Long_2_Short_Indices_PTR)=-1;
        }
    }
  return Long_2_Short_Indices;

}

SegPrecisionTYPE * Create_cArray_from_Prior_mask(nifti_image * Mask,
                                                 nifti_image * Priors,
                                                 int numclass,
                                                 bool PV_ON)
{
  register int numel=(int)(rowsize(Mask)*colsize(Mask)*depth(Mask));
  register int numel_masked=0;

  bool * Maskptrtmp = static_cast<bool *> (Mask->data);;
  for (int i=0; i<numel; i++, Maskptrtmp++) {
      *Maskptrtmp?numel_masked++:0;
    }
  int pluspv=(int)(PV_ON)*2;

  SegPrecisionTYPE * Expec = new SegPrecisionTYPE [numel_masked*(numclass+pluspv)] ();
  SegPrecisionTYPE * tempExpec= (SegPrecisionTYPE *) Expec;
  SegPrecisionTYPE * PriorPTR = static_cast<SegPrecisionTYPE *>(Priors->data);
  for(int cl=0; cl<numclass;cl++){
      Maskptrtmp = static_cast<bool *> (Mask->data);;
      for (int i=numel; i--; Maskptrtmp++,PriorPTR++) {
          if(*Maskptrtmp){
              *tempExpec = *PriorPTR;
              tempExpec++;
            }
        }
    }

  return Expec;
}

SegPrecisionTYPE * Create_cArray_from_Prior(nifti_image * Priors,
                                            int numclass,
                                            bool PV_ON)
{
  register int numel=(int)(rowsize(Priors)*colsize(Priors)*depth(Priors));
  int pluspv=(int)(PV_ON)*2;
  SegPrecisionTYPE * Expec = new SegPrecisionTYPE [numel*(numclass+pluspv)] ();
  SegPrecisionTYPE * Expec_PTR= Expec;
  SegPrecisionTYPE * PriorPTR = static_cast<SegPrecisionTYPE *>(Priors->data);
  for(int cl=0; cl<numclass;cl++){
      for (int i=numel; i--; PriorPTR++,Expec_PTR++) {
          *Expec_PTR = *PriorPTR;
        }
    }
  return Expec;
}

SegPrecisionTYPE * Create_cArray_from_3D_image(nifti_image * Mask,
                                               nifti_image * SourceImage)
{
  register int numel=(int)(rowsize(Mask)*colsize(Mask)*depth(Mask));
  register int numel_masked=0;

  bool * Maskptrtmp = static_cast<bool *> (Mask->data);;
  for (int i=0; i<numel; i++, Maskptrtmp++) {
      *Maskptrtmp?numel_masked++:0;
    }

  SegPrecisionTYPE * outimage = new SegPrecisionTYPE [numel_masked] ();
  SegPrecisionTYPE * outimage_ptr= outimage;
  SegPrecisionTYPE * SourceImagePTR = static_cast<SegPrecisionTYPE *>(SourceImage->data);
  Maskptrtmp = static_cast<bool *> (Mask->data);

  for (int i=numel; i--; Maskptrtmp++,SourceImagePTR++) {
      if(*Maskptrtmp){
          *outimage_ptr = *SourceImagePTR;
          outimage_ptr++;
        }
    }


  return outimage;
}


int calcE_mask(nifti_image * T1,
               SegPrecisionTYPE * IterPrior,
               SegPrecisionTYPE * Expec,
               SegPrecisionTYPE * loglik,
               SegPrecisionTYPE * BiasField,
               SegPrecisionTYPE * Outlierness,
               SegPrecisionTYPE OutliernessThreshold,
               int * S2L,
               SegPrecisionTYPE * M,
               SegPrecisionTYPE * V,
               ImageSize * CurrSizes,
               int verbose)
{
  int numel_masked=CurrSizes->numelmasked;
  int num_class=CurrSizes->numclass;
  bool OutliernessFlag=(Outlierness==NULL)?0:1;
  SegPrecisionTYPE inv_v [max_numbclass*MaxMultispectalSize*MaxMultispectalSize]={0.0f};
  SegPrecisionTYPE inv_sqrt_V_2pi [max_numbclass]={0.0f};

  int Expec_offset [max_numbclass]={0};

  for (int cl=0; cl<num_class; cl++) {
      Expec_offset[cl]=(int) cl*numel_masked;
      if(CurrSizes->usize>1){
          matrix <double> Vmat(CurrSizes->usize,CurrSizes->usize);

          for(int j2=0; j2<CurrSizes->usize; j2++){
              for(int i2=j2; i2<CurrSizes->usize; i2++){
                  Vmat.setvalue(i2,j2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                  Vmat.setvalue(j2,i2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                }
            }
          inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI*Vmat.determinant()));
          if(verbose>1){
              cout<<endl<<"inv_sqrt_V_2pi["<< cl <<"]= "<< inv_sqrt_V_2pi[cl] << endl;
              flush(cout);
            }
          Vmat.invert();
          double cvalue=0.0f;
          bool success;
          if(verbose>1){
              cout<<"inv_V["<< cl <<"]= ";
              flush(cout);
            }
          for(int j2=0; j2<CurrSizes->usize; j2++){
              if(verbose>1){
                  if(j2!=0){
                      cout<< endl << "          ";
                    }
                }
              for(int i2=0; i2<CurrSizes->usize; i2++){
                  Vmat.getvalue(i2,j2,cvalue,success);
                  inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]=(SegPrecisionTYPE)(cvalue);
                  if(verbose>1){
                      cout<<inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]<< "\t";
                      flush(cout);
                    }
                }

            }
          if(verbose>1){
              cout<< endl;
            }
        }
      else{
          inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI*V[cl]));
          inv_v[cl]=1/V[cl];
        }
    }
  loglik[0]=0;

  //int * Expec_offset_PTR= (int *) Expec_offset;

  float logliktmp=0.0f;


#ifdef _OPENMP
  float * loglikthread = new float [omp_get_max_threads()]();
  for(int i=0; i<omp_get_max_threads(); i++)
    loglikthread[i]=0;

#pragma omp parallel for shared(Expec,loglikthread,T1,BiasField,Outlierness,IterPrior)
#endif
  for (int i=0; i<numel_masked;i++) {
      SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
      SegPrecisionTYPE T1_Bias_corr[MaxMultispectalSize];
      SegPrecisionTYPE SumExpec=0.0f;

      for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++)
        T1_Bias_corr[Multispec]=(BiasField!=NULL)?(T1_PTR[S2L[i]+Multispec*CurrSizes->numel] + BiasField[i+Multispec*numel_masked]):(T1_PTR[S2L[i]+Multispec*CurrSizes->numel]);



      //Expec_offset_PTR=Expec_offset;

      for (int cl=0; cl<num_class; cl++) {
          SegPrecisionTYPE mahal=0.0f;
          for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
              SegPrecisionTYPE tmpT1_BC_minusM=(T1_Bias_corr[Multispec] - M[cl*(CurrSizes->usize)+Multispec]);
              for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
                  mahal-=(0.5f)*(T1_Bias_corr[Multispec2] - M[cl*(CurrSizes->usize)+Multispec2])*inv_v[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]*tmpT1_BC_minusM;
                }
            }

          if(OutliernessFlag){
              Outlierness[i+Expec_offset[cl]]=(expf(mahal))/(expf(mahal)+expf(-0.5*(OutliernessThreshold*OutliernessThreshold)));
              Expec[i+Expec_offset[cl]]=IterPrior[i+Expec_offset[cl]]*Outlierness[i+Expec_offset[cl]] * expf(mahal) * inv_sqrt_V_2pi[cl];
            }
          else{
              Expec[i+Expec_offset[cl]]=IterPrior[i+Expec_offset[cl]] * expf(mahal) * inv_sqrt_V_2pi[cl];
            }
          SumExpec+=Expec[i+Expec_offset[cl]];
        }

      if (SumExpec<=0.0 || SumExpec!=SumExpec){
          for (int cl=0; cl<num_class; cl++) {
              Expec[i+Expec_offset[cl]]=(float)(1)/(float)(num_class);
            }

        }
      else{

          for (int cl=0; cl<num_class; cl++) {
              Expec[i+Expec_offset[cl]]=Expec[i+Expec_offset[cl]]/SumExpec;
            }
#ifdef _OPENMP
          loglikthread[omp_get_thread_num()]+=logf(SumExpec);
#else
          logliktmp+=logf(SumExpec);
#endif

        }
    }

#ifdef _OPENMP
  for(int i =0; i<omp_get_max_threads(); i++)
    logliktmp+=loglikthread[i];
#endif

  loglik[0]=logliktmp;
  return 1;
}


int calcE(nifti_image * T1,
          SegPrecisionTYPE * IterPrior,
          SegPrecisionTYPE * Expec,
          SegPrecisionTYPE * loglik,
          SegPrecisionTYPE * BiasField,
          SegPrecisionTYPE * Outlierness,
          SegPrecisionTYPE OutliernessThreshold,
          SegPrecisionTYPE * M,
          SegPrecisionTYPE * V,
          ImageSize * CurrSizes,
          int verbose)
{
  int numel=CurrSizes->numel;
  int num_class=CurrSizes->numclass;
  bool OutliernessFlag=(Outlierness==NULL)?0:1;


  SegPrecisionTYPE * IterPrior_PTR= (SegPrecisionTYPE *) IterPrior;
  SegPrecisionTYPE * Expec_PTR= (SegPrecisionTYPE *) Expec;
  SegPrecisionTYPE * Outlierness_PTR= (SegPrecisionTYPE *) Outlierness;
  SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
  SegPrecisionTYPE inv_v [max_numbclass*MaxMultispectalSize*MaxMultispectalSize]={0.0f};
  SegPrecisionTYPE inv_sqrt_V_2pi [max_numbclass]={0.0f};
  SegPrecisionTYPE tmpT1_BC_minusM=0;

  int Expec_offset [max_numbclass]={0};

  for (int cl=0; cl<num_class; cl++) {
      Expec_offset[cl]=(int) cl*numel;
      if(CurrSizes->usize>1){
          matrix <double> Vmat(CurrSizes->usize,CurrSizes->usize);

          for(int j2=0; j2<CurrSizes->usize; j2++){
              for(int i2=j2; i2<CurrSizes->usize; i2++){
                  Vmat.setvalue(i2,j2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                  Vmat.setvalue(j2,i2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                }
            }
          inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI)*Vmat.determinant());
          if(verbose>1){
              cout<<endl<<"inv_sqrt_V_2pi["<< cl <<"]= "<< inv_sqrt_V_2pi[cl] << endl;
              flush(cout);
            }
          Vmat.invert();
          double cvalue=0.0f;
          bool success;
          if(verbose>1){
              cout<<"inv_V["<< cl <<"]= ";
              flush(cout);
            }
          for(int j2=0; j2<CurrSizes->usize; j2++){
              if(verbose>1){
                  if(j2!=0){
                      cout<< endl << "          ";
                    }
                }
              for(int i2=0; i2<CurrSizes->usize; i2++){
                  Vmat.getvalue(i2,j2,cvalue,success);
                  inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]=(SegPrecisionTYPE)(cvalue);
                  if(verbose>1){
                      cout<<inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]<< "\t";
                      flush(cout);
                    }
                }

            }
          if(verbose>1){
              cout<< endl;
            }
        }
      else{
          inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI)* V[cl]);
          inv_v[cl]=1/V[cl];
        }
    }
  loglik[0]=0;



  float logliktmp=0.0f;
#ifdef _OPENMP
  float * loglikthread = new float [omp_get_max_threads()]();
  for(int i=0; i<omp_get_max_threads(); i++)
    loglikthread[i]=0;

#pragma omp parallel for shared(Expec,loglikthread,T1,BiasField,Outlierness,IterPrior)
#endif
  for (int i=0; i<numel;i++) {
      SegPrecisionTYPE T1_Bias_corr[MaxMultispectalSize]={0.0f};
      for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
          T1_Bias_corr[Multispec]=(BiasField!=NULL)?(T1_PTR[i+Multispec*numel] + BiasField[i+Multispec*numel]):(T1_PTR[i+Multispec*numel]);
        }
      SegPrecisionTYPE mahal=0.0f;
      SegPrecisionTYPE SumExpec=0.0f;

      //Expec_offset_PTR=Expec_offset;

      for (int cl=0; cl<num_class; cl++) {
          mahal=0.0f;
          for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
              tmpT1_BC_minusM=(T1_Bias_corr[Multispec] - M[cl*(CurrSizes->usize)+Multispec]);
              for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
                  mahal-=(0.5f)*(T1_Bias_corr[Multispec2] - M[cl*(CurrSizes->usize)+Multispec2])*inv_v[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]*tmpT1_BC_minusM;
                }
            }
          Expec_PTR[i+Expec_offset[cl]]=IterPrior_PTR[i+Expec_offset[cl]] * expf(mahal) * inv_sqrt_V_2pi[cl];
          if(OutliernessFlag){
              Outlierness_PTR[i+Expec_offset[cl]]=(expf(mahal))/(expf(mahal)+expf(-0.5*(OutliernessThreshold*OutliernessThreshold)));
            }
          SumExpec+=Expec_PTR[i+Expec_offset[cl]];
        }
      if (SumExpec<=0.0 || SumExpec!=SumExpec){
          SumExpec=0.01;
        }

      if (SumExpec<=0.0 || SumExpec!=SumExpec){
          for (int cl=0; cl<num_class; cl++) {
              Expec_PTR[i+Expec_offset[cl]]=(float)(1)/(float)(num_class);
            }
        }
      else{
          for (int cl=0; cl<num_class; cl++) {
              Expec_PTR[i+Expec_offset[cl]]=Expec_PTR[i+Expec_offset[cl]]/SumExpec;
            }
#ifdef _OPENMP
          loglikthread[omp_get_thread_num()]+=logf(SumExpec);
#else
          logliktmp+=logf(SumExpec);
#endif

        }
    }

#ifdef _OPENMP
  for(int i =0; i<omp_get_max_threads(); i++)
    logliktmp+=loglikthread[i];
#endif


  loglik[0]=logliktmp;
  return 1;
}




/*
int calcE_mask_aprox(nifti_image * T1,
                      SegPrecisionTYPE * IterPrior,
                      SegPrecisionTYPE * Expec,
                      SegPrecisionTYPE * loglik,
                      SegPrecisionTYPE * BiasField,
                      int * S2L,
                      SegPrecisionTYPE * M,
                      SegPrecisionTYPE * V,
                      ImageSize * CurrSizes,
                      int verbose)
{
    int numel_masked=CurrSizes->numelmasked;
    int num_class=CurrSizes->numclass;

    SegPrecisionTYPE * IterPrior_PTR= (SegPrecisionTYPE *) IterPrior;
    SegPrecisionTYPE * Expec_PTR= (SegPrecisionTYPE *) Expec;
    SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
    SegPrecisionTYPE SumExpec=0.0f;
    SegPrecisionTYPE expectmp=0.0f;



    SegPrecisionTYPE inv_v [max_numbclass*MaxMultispectalSize*MaxMultispectalSize]={0.0f};
    SegPrecisionTYPE inv_sqrt_V_2pi [max_numbclass]={0.0f};
    SegPrecisionTYPE newM [max_numbclass*MaxMultispectalSize]={0.0f};
    SegPrecisionTYPE T1_Bias_corr[MaxMultispectalSize]={0.0f};
    SegPrecisionTYPE tmpT1_BC_minusM=0;

    int Expec_offset [max_numbclass]={0};

    for (int cl=0; cl<num_class; cl++) {
        Expec_offset[cl]=(int) cl*numel_masked;
        if(CurrSizes->usize>1){
            matrix <double> Vmat(CurrSizes->usize,CurrSizes->usize);

            for(int j2=0; j2<CurrSizes->usize; j2++){
                for(int i2=j2; i2<CurrSizes->usize; i2++){
                    Vmat.setvalue(i2,j2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                    Vmat.setvalue(j2,i2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                }
            }
            inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI)*Vmat.determinant());
            if(verbose>1){
                cout<<endl<<"inv_sqrt_V_2pi["<< cl <<"]= "<< inv_sqrt_V_2pi[cl] << endl;
                flush(cout);
            }
            Vmat.invert();
            double cvalue;
            bool success;
            if(verbose>1){
                cout<<"inv_V["<< cl <<"]= ";
                flush(cout);
            }
            for(int j2=0; j2<CurrSizes->usize; j2++){
                if(verbose>1){
                    if(j2!=0){
                        cout<< endl << "          ";
                    }
                }
                for(int i2=0; i2<CurrSizes->usize; i2++){
                    Vmat.getvalue(i2,j2,cvalue,success);


                    inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]=(SegPrecisionTYPE)(cvalue);
                    if(verbose>1){
                        cout<<inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]<< "\t";
                        flush(cout);
                    }
                }

            }
            if(verbose>1){
                cout<< endl;
            }
        }
        else{
            inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI)* V[cl]);
            inv_v[cl]=1/V[cl];
            newM[cl]=M[cl];

        }
    }
    loglik[0]=0;
    SumExpec=0.0f;
    //int * Expec_offset_PTR= (int *) Expec_offset;
    register SegPrecisionTYPE tempvar=0.0f;
    float mahal=0.0f;
    float logliktmp=0.0f;
    for (int i=0; i<numel_masked;i++, Expec_PTR++, IterPrior_PTR++) {
        for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
            T1_Bias_corr[Multispec]=(BiasField!=NULL)?(T1_PTR[S2L[i]+Multispec*CurrSizes->numel] + BiasField[i+Multispec*numel_masked]):(T1_PTR[S2L[i]+Multispec*CurrSizes->numel]);
        }
        SumExpec=0.0f;
        expectmp=0.0f;
        mahal=0.0f;
        //Expec_offset_PTR=Expec_offset;
        for (int cl=0; cl<num_class; cl++) {
            mahal=0.0f;
            for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
                tmpT1_BC_minusM=(T1_Bias_corr[Multispec] - M[cl*(CurrSizes->usize)+Multispec]);
                for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
                    mahal-=(0.5f)*(T1_Bias_corr[Multispec2] - M[cl*(CurrSizes->usize)+Multispec2])*inv_v[cl*CurrSizes->usize*CurrSizes->usize+Multispec2+Multispec*CurrSizes->usize]*tmpT1_BC_minusM;
                }
            }
            Expec_PTR[Expec_offset[cl]]=IterPrior_PTR[Expec_offset[cl]] * (float)(EXP(mahal)) * inv_sqrt_V_2pi[cl];
            SumExpec+=Expec_PTR[Expec_offset[cl]];
        }
        if (SumExpec<=0.0 || SumExpec!=SumExpec){
            SumExpec=0.01;
        }
        logliktmp+=logf(SumExpec);



        if (SumExpec<=0.0 || SumExpec!=SumExpec){
            for (int cl=0; cl<num_class; cl++) {
                Expec_PTR[Expec_offset[cl]]=(float)(1)/(float)(num_class);
            }
        }
        else{
            logliktmp+=logf(SumExpec);
            for (int cl=0; cl<num_class; cl++) {

                Expec_PTR[Expec_offset[cl]]=Expec_PTR[Expec_offset[cl]]/SumExpec;
            }
        }
    }
    loglik[0]=logliktmp;
    return 1;
}


*/
/*
int calcE_aprox(nifti_image * T1,
                 SegPrecisionTYPE * IterPrior,
                 SegPrecisionTYPE * Expec,
                 SegPrecisionTYPE * loglik,
                 SegPrecisionTYPE * BiasField,
                 SegPrecisionTYPE * M,
                 SegPrecisionTYPE * V,
                 ImageSize * CurrSizes,
                 int verbose)
{
    int numel=CurrSizes->numel;
    int num_class=CurrSizes->numclass;

    SegPrecisionTYPE * IterPrior_PTR= (SegPrecisionTYPE *) IterPrior;
    SegPrecisionTYPE * Expec_PTR= (SegPrecisionTYPE *) Expec;
    SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
    SegPrecisionTYPE SumExpec=0.0f;
    SegPrecisionTYPE expectmp=0.0f;



    SegPrecisionTYPE inv_v [max_numbclass*MaxMultispectalSize*MaxMultispectalSize]={0.0f};
    SegPrecisionTYPE inv_sqrt_V_2pi [max_numbclass]={0.0f};
    SegPrecisionTYPE newM [max_numbclass*MaxMultispectalSize]={0.0f};
    SegPrecisionTYPE T1_Bias_corr[MaxMultispectalSize]={0.0f};
    SegPrecisionTYPE tmpT1_BC_minusM=0;

    int Expec_offset [max_numbclass]={0};

    for (int cl=0; cl<num_class; cl++) {
        Expec_offset[cl]=(int) cl*numel;
        if(CurrSizes->usize>1){
            matrix <double> Vmat(CurrSizes->usize,CurrSizes->usize);

            for(int j2=0; j2<CurrSizes->usize; j2++){
                for(int i2=j2; i2<CurrSizes->usize; i2++){
                    Vmat.setvalue(i2,j2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                    Vmat.setvalue(j2,i2,(double)(V[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]));
                }
            }
            inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI)*Vmat.determinant());
            if(verbose>1){
                cout<<endl<<"inv_sqrt_V_2pi["<< cl <<"]= "<< inv_sqrt_V_2pi[cl] << endl;
                flush(cout);
            }
            Vmat.invert();
            double cvalue;
            bool success;
            if(verbose>1){
                cout<<"inv_V["<< cl <<"]= ";
                flush(cout);
            }
            for(int j2=0; j2<CurrSizes->usize; j2++){
                if(verbose>1){
                    if(j2!=0){
                        cout<< endl << "          ";
                    }
                }
                for(int i2=0; i2<CurrSizes->usize; i2++){
                    Vmat.getvalue(i2,j2,cvalue,success);
                    inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]=(SegPrecisionTYPE)(cvalue);
                    if(verbose>1){
                        cout<<inv_v[i2+j2*CurrSizes->usize+cl*CurrSizes->usize*CurrSizes->usize]<< "\t";
                        flush(cout);
                    }
                }

            }
            if(verbose>1){
                cout<< endl;
            }
        }
        else{
            inv_sqrt_V_2pi[cl]=1/(sqrtf(2*M_PI)* V[cl]);
            inv_v[cl]=1/V[cl];
            newM[cl]=M[cl];

        }
    }
    loglik[0]=0;
    SumExpec=0.0f;
    //int * Expec_offset_PTR= (int *) Expec_offset;
    register SegPrecisionTYPE tempvar=0.0f;
    float mahal=0.0f;
    float logliktmp=0.0f;
    IterPrior_PTR= (SegPrecisionTYPE *) IterPrior;
    Expec_PTR= (SegPrecisionTYPE *) Expec;
    for (int i=0; i<numel;i++, Expec_PTR++, IterPrior_PTR++) {
        for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
            T1_Bias_corr[Multispec]=(BiasField!=NULL)?(T1_PTR[i+Multispec*numel] + BiasField[i+Multispec*numel]):(T1_PTR[i+Multispec*numel]);
        }
        SumExpec=0.0f;
        expectmp=0.0f;
        mahal=0.0f;
        //Expec_offset_PTR=Expec_offset;
        for (int cl=0; cl<num_class; cl++) {
            mahal=0.0f;
            for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
                tmpT1_BC_minusM=(T1_Bias_corr[Multispec] - M[cl*(CurrSizes->usize)+Multispec]);
                for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
                    mahal-=(0.5f)*(T1_Bias_corr[Multispec2] - M[cl*(CurrSizes->usize)+Multispec2])*inv_v[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]*tmpT1_BC_minusM;
                }
            }

            Expec_PTR[Expec_offset[cl]]=IterPrior_PTR[Expec_offset[cl]] * (float)(EXP(mahal)) * inv_sqrt_V_2pi[cl];
            SumExpec+=Expec_PTR[Expec_offset[cl]];
        }
        if (SumExpec<=0.0 || SumExpec!=SumExpec){
            SumExpec=0.01;
        }
        logliktmp+=logf(SumExpec);

        if (SumExpec<=0.0 || SumExpec!=SumExpec){
            for (int cl=0; cl<num_class; cl++) {
                Expec_PTR[Expec_offset[cl]]=(float)(1)/(float)(num_class);
            }
        }
        else{
            logliktmp+=logf(SumExpec);
            for (int cl=0; cl<num_class; cl++) {
                Expec_PTR[Expec_offset[cl]]=Expec_PTR[Expec_offset[cl]]/SumExpec;
            }
        }
    }
    loglik[0]=logliktmp;
    return 1;
}



*/
int calcM(nifti_image * T1,
          SegPrecisionTYPE * Expec,
          SegPrecisionTYPE * BiasField,
          SegPrecisionTYPE * Outlierness,
          SegPrecisionTYPE * M,
          SegPrecisionTYPE * V,
          SegPrecisionTYPE * M_MAP,
          SegPrecisionTYPE * V_MAP,
          SegPrecisionTYPE reg_factor,
          ImageSize * CurrSizes,
          int verbose)
{

  bool OutliernessFlag=(Outlierness==NULL)?0:1;

  if(verbose>0){
      cout<< "Optimising Gaussian Parameters" << endl;
      flush(cout);
    }
  int numel=CurrSizes->numel;
  int currentnum_class=CurrSizes->numclass;
  SegPrecisionTYPE * Expec_PTR = (SegPrecisionTYPE *) Expec;
  SegPrecisionTYPE * OutliernessPTR = (SegPrecisionTYPE *) Outlierness;
  SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
  SegPrecisionTYPE * BiasField_PTR= (SegPrecisionTYPE *) BiasField;
  SegPrecisionTYPE * T1_PTR2= static_cast<SegPrecisionTYPE *>(T1->data);
  SegPrecisionTYPE * BiasField_PTR2= (SegPrecisionTYPE *) BiasField;

  int Expec_offset[PV_numbclass];
  for (int cl=0; cl<currentnum_class; cl++) {
      Expec_offset[cl]=cl*numel;
    }
  SegPrecisionTYPE tempsum= (SegPrecisionTYPE) 0.0;
  SegPrecisionTYPE SumPriors= (SegPrecisionTYPE) 0.0;

  // ***********

  for (int cl=0; cl<currentnum_class; cl++) {
      // MEAN
      for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
          Expec_PTR=(SegPrecisionTYPE *) &Expec[Expec_offset[cl]];
          OutliernessPTR=(SegPrecisionTYPE *) &Outlierness[Expec_offset[cl]];
          T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
          T1_PTR =&T1_PTR[Multispec*CurrSizes->numel];
          tempsum=(SegPrecisionTYPE)0.0;
          SumPriors=(SegPrecisionTYPE)0.0;


          if(OutliernessFlag){

              if(BiasField!=NULL){
                  BiasField_PTR= &BiasField[Multispec*numel];
                  for (int i=0; i<numel; i++, Expec_PTR++,OutliernessPTR++,BiasField_PTR++) {
                      tempsum+=(*Expec_PTR) * (*OutliernessPTR)*(T1_PTR[i]+(*BiasField_PTR));
                      SumPriors+=(*Expec_PTR)*(*OutliernessPTR);
                    }
                }else{
                  for (int i=0; i<numel; i++, Expec_PTR++,OutliernessPTR++) {
                      tempsum+=(*Expec_PTR)*(*OutliernessPTR)*(T1_PTR[i]);
                      SumPriors+=(*Expec_PTR)*(*OutliernessPTR);
                    }
                }
            }
          else{

              if(BiasField!=NULL){
                  BiasField_PTR= &BiasField[Multispec*numel];
                  for (int i=0; i<numel; i++, Expec_PTR++,BiasField_PTR++) {
                      tempsum+=(*Expec_PTR) * (T1_PTR[i]+(*BiasField_PTR));
                      SumPriors+=(*Expec_PTR);
                    }
                }else{
                  for (int i=0; i<numel; i++, Expec_PTR++) {
                      tempsum+=(*Expec_PTR)*(T1_PTR[i]);
                      SumPriors+=(*Expec_PTR);
                    }
                }

            }


          if(M_MAP==NULL){
              M[cl*(CurrSizes->usize)+Multispec]=tempsum/SumPriors;
            }
          else{
              M[cl*(CurrSizes->usize)+Multispec]=(tempsum/SumPriors/powf(V[cl*(CurrSizes->usize)+Multispec],2)+M_MAP[cl*(CurrSizes->usize)+Multispec]/powf(V_MAP[cl*(CurrSizes->usize)+Multispec],2))/(1/powf(V[cl*(CurrSizes->usize)+Multispec],2)+1/powf(V_MAP[cl*(CurrSizes->usize)+Multispec],2));
            }

          for(int Multispec2=Multispec; Multispec2<CurrSizes->usize; Multispec2++) {

              T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
              T1_PTR =&T1_PTR[Multispec*CurrSizes->numel];

              T1_PTR2 = static_cast<SegPrecisionTYPE *>(T1->data);
              T1_PTR2 =&T1_PTR2[Multispec2*CurrSizes->numel];
              float tmpM=M[cl*CurrSizes->usize+Multispec];
              float tmpM2=M[cl*CurrSizes->usize+Multispec2];
              //STD
              tempsum=0;
              Expec_PTR=&Expec[Expec_offset[cl]];
              OutliernessPTR=(SegPrecisionTYPE *) &Outlierness[Expec_offset[cl]];
              if(OutliernessFlag){
                  if(BiasField!=NULL){
                      BiasField_PTR=&BiasField[Multispec*numel];
                      BiasField_PTR2=&BiasField[Multispec2*numel];
                      for (int i=0; i<numel;i++,Expec_PTR++,BiasField_PTR++,OutliernessPTR++,BiasField_PTR2++) {
                          tempsum+=(*Expec_PTR) *(*OutliernessPTR)* (T1_PTR[i]+(*BiasField_PTR)-tmpM) * (T1_PTR2[i]+(*BiasField_PTR2)-tmpM2);
                        }
                    }else{
                      for (int i=0; i<numel;i++,Expec_PTR++,OutliernessPTR++) {
                          tempsum+=(*Expec_PTR) *(*OutliernessPTR)* (T1_PTR[i]-tmpM) * (T1_PTR2[i]-tmpM2);
                        }

                    }
                }
              else{
                  if(BiasField!=NULL){
                      BiasField_PTR=&BiasField[Multispec*numel];
                      BiasField_PTR2=&BiasField[Multispec2*numel];
                      for (int i=0; i<numel;i++,Expec_PTR++,BiasField_PTR++,BiasField_PTR2++) {
                          tempsum+=(*Expec_PTR) * (T1_PTR[i]+(*BiasField_PTR)-tmpM) * (T1_PTR2[i]+(*BiasField_PTR2)-tmpM2);
                        }
                    }else{
                      for (int i=0; i<numel;i++,Expec_PTR++) {
                          tempsum+=(*Expec_PTR) * (T1_PTR[i]-tmpM) * (T1_PTR2[i]-tmpM2);
                        }

                    }
                }

              V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]=tempsum/SumPriors+0.00001f;
              V[cl*CurrSizes->usize*CurrSizes->usize+Multispec2+Multispec*CurrSizes->usize]=V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize];
              if(Multispec==Multispec2)
                V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]*=reg_factor;

            }
        }
    }

  for (int cl=0; cl<currentnum_class; cl++) {
      for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
          for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
              V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]/=reg_factor;
            }
        }
    }

  for (int cl=0; cl<currentnum_class; cl++) {
      if(verbose>0){
          if(CurrSizes->usize==1){
              cout.fill('0');
              cout<< "M["<<(int)(cl)<<"]= "<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(M[cl])<<"\tV["<<(int)(cl)<<"]="<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(V[cl])<< endl;
              flush(cout);
            }
          else{

              cout<< "M["<<(int)(cl)<<"]= ";
              for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
                  cout<< setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(M[cl*CurrSizes->usize+Multispec])<<"\t";
                }
              cout<< endl;
              flush(cout);
              cout<< "V["<<(int)(cl)<<"]= ";
              for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
                  if(Multispec>0){
                      cout<< "      ";
                    }
                  for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
                      cout<< setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(V[cl*CurrSizes->usize*CurrSizes->usize+Multispec*CurrSizes->usize+Multispec2])<<"\t";
                    }
                  cout<< endl;
                }
              cout<< endl;
              flush(cout);
            }
        }
    }

  return 1;
}




int calcM_mask(nifti_image * T1,
               SegPrecisionTYPE * Expec,
               SegPrecisionTYPE * BiasField,
               SegPrecisionTYPE * Outlierness,
               int * S2L,
               SegPrecisionTYPE * M,
               SegPrecisionTYPE * V,
               SegPrecisionTYPE * M_MAP,
               SegPrecisionTYPE * V_MAP,
               SegPrecisionTYPE reg_factor,
               ImageSize * CurrSizes,
               int verbose)
{

  if(verbose>0){
      cout<< "Optimising Gaussian Parameters" << endl;
      flush(cout);
    }
  bool OutliernessFlag=(Outlierness==NULL)?0:1;

  int numel_masked=CurrSizes->numelmasked;
  int num_class=CurrSizes->numclass;
  int Expec_offset[PV_numbclass];
  for (int cl=0; cl<num_class; cl++) {
      Expec_offset[cl]=cl*numel_masked;
    }

#ifdef _OPENMP
#pragma omp parallel for shared(T1,BiasField,Outlierness)
#endif
  // ***********
  for (int cl=0; cl<num_class; cl++) {
      int * S2L_PTR = (int *) S2L;
      SegPrecisionTYPE * Expec_PTR = (SegPrecisionTYPE *) Expec;
      SegPrecisionTYPE * OutliernessPTR = (SegPrecisionTYPE *) Outlierness;
      SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
      SegPrecisionTYPE * BiasField_PTR= (SegPrecisionTYPE *) BiasField;
      SegPrecisionTYPE tempsum= (SegPrecisionTYPE) 0.0;
      SegPrecisionTYPE SumPriors= (SegPrecisionTYPE) 0.0;
      SegPrecisionTYPE * T1_PTR2= static_cast<SegPrecisionTYPE *>(T1->data);
      SegPrecisionTYPE * BiasField_PTR2= (SegPrecisionTYPE *) BiasField;

      // MEAN
      for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
          Expec_PTR=(SegPrecisionTYPE *) &Expec[Expec_offset[cl]];
          OutliernessPTR=(SegPrecisionTYPE *) &Outlierness[Expec_offset[cl]];
          S2L_PTR = (int *) S2L;

          T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
          T1_PTR =&T1_PTR[Multispec*CurrSizes->numel];
          tempsum=(SegPrecisionTYPE)0.0;
          SumPriors=(SegPrecisionTYPE)0.0;

          if(OutliernessFlag){
              if(BiasField!=NULL){
                  BiasField_PTR= &BiasField[Multispec*numel_masked];
                  for (int i=0; i<numel_masked; i++, Expec_PTR++,OutliernessPTR++,BiasField_PTR++,S2L_PTR++) {
                      tempsum+=(*Expec_PTR)*(*OutliernessPTR)*(T1_PTR[(*S2L_PTR)]+(*BiasField_PTR));
                      SumPriors+=(*Expec_PTR)*(*OutliernessPTR);
                    }
                }else{
                  for (int i=0; i<numel_masked; i++, Expec_PTR++,S2L_PTR++) {
                      tempsum+=(*Expec_PTR)*(*OutliernessPTR)*(T1_PTR[(*S2L_PTR)]);
                      SumPriors+=(*Expec_PTR)*(*OutliernessPTR);
                    }
                }
            }
          else{
              if(BiasField!=NULL){
                  BiasField_PTR= &BiasField[Multispec*numel_masked];
                  for (int i=0; i<numel_masked; i++, Expec_PTR++,BiasField_PTR++,S2L_PTR++) {
                      tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]+(*BiasField_PTR));
                      SumPriors+=(*Expec_PTR);
                    }
                }else{
                  for (int i=0; i<numel_masked; i++, Expec_PTR++,S2L_PTR++) {
                      tempsum+=(*Expec_PTR)*(T1_PTR[(*S2L_PTR)]);
                      SumPriors+=(*Expec_PTR);
                    }
                }

            }
          if(M_MAP==NULL){
              M[cl*(CurrSizes->usize)+Multispec]=tempsum/SumPriors;
            }
          else{
              M[cl*(CurrSizes->usize)+Multispec]=(tempsum/SumPriors/powf(V[cl*(CurrSizes->usize)+Multispec],2)+M_MAP[cl*(CurrSizes->usize)+Multispec]/powf(V_MAP[cl*(CurrSizes->usize)+Multispec],2))/(1/powf(V[cl*(CurrSizes->usize)+Multispec],2)+1/powf(V_MAP[cl*(CurrSizes->usize)+Multispec],2));
            }

          for(int Multispec2=Multispec; Multispec2<CurrSizes->usize; Multispec2++) {
              S2L_PTR = (int *) S2L;

              T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
              T1_PTR =&T1_PTR[Multispec*CurrSizes->numel];

              T1_PTR2 = static_cast<SegPrecisionTYPE *>(T1->data);
              T1_PTR2 =&T1_PTR2[Multispec2*CurrSizes->numel];
              float tmpM=M[cl*CurrSizes->usize+Multispec];
              float tmpM2=M[cl*CurrSizes->usize+Multispec2];
              //STD
              tempsum=0;
              Expec_PTR=&Expec[Expec_offset[cl]];
              OutliernessPTR=(SegPrecisionTYPE *) &Outlierness[Expec_offset[cl]];
              if(BiasField!=NULL){
                  BiasField_PTR=&BiasField[Multispec*numel_masked];
                  BiasField_PTR2=&BiasField[Multispec2*numel_masked];
                  if(OutliernessFlag){
                      for (int i=0; i<numel_masked;i++,Expec_PTR++,BiasField_PTR++,OutliernessPTR++,BiasField_PTR2++,S2L_PTR++) {
                          tempsum+=(*Expec_PTR) * (*OutliernessPTR)*(T1_PTR[(*S2L_PTR)]+(*BiasField_PTR)-tmpM) * (T1_PTR2[(*S2L_PTR)]+(*BiasField_PTR2)-tmpM2);
                        }
                    }
                  else{
                      for (int i=0; i<numel_masked;i++,Expec_PTR++,BiasField_PTR++,BiasField_PTR2++,S2L_PTR++) {
                          tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]+(*BiasField_PTR)-tmpM) * (T1_PTR2[(*S2L_PTR)]+(*BiasField_PTR2)-tmpM2);
                        }
                    }
                }else{
                  for (int i=0; i<numel_masked;i++,Expec_PTR++,S2L_PTR++) {
                      tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]-tmpM) * (T1_PTR2[(*S2L_PTR)]-tmpM2);
                    }

                }
              if( (tempsum/SumPriors>0) & (!isnan(tempsum/SumPriors))){
                  V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]=tempsum/SumPriors;
                  if(Multispec2!=Multispec){
                      V[cl*CurrSizes->usize*CurrSizes->usize+Multispec2+Multispec*CurrSizes->usize]=V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize];
                    }
                  else{
                      V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]*=reg_factor;
                    }
                }
            }
        }

    }

  for (int cl=0; cl<num_class; cl++) {
      for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
          for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
              V[cl*CurrSizes->usize*CurrSizes->usize+Multispec+Multispec2*CurrSizes->usize]/=reg_factor;
            }
        }
    }

  for (int cl=0; cl<num_class; cl++) {
      if(verbose>0){
          if(CurrSizes->usize==1){
              cout.fill('0');
              cout<< "M["<<(int)(cl)<<"]= "<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(M[cl])<<"\tV["<<(int)(cl)<<"]="<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(V[cl])<< endl;
              flush(cout);
            }
          else{

              cout<< "M["<<(int)(cl)<<"]= ";
              for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
                  cout<< setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(M[cl*CurrSizes->usize+Multispec])<<"\t";
                }
              cout<< endl;
              flush(cout);
              cout<< "V["<<(int)(cl)<<"]= ";
              for(int Multispec=0; Multispec<CurrSizes->usize; Multispec++) {
                  if(Multispec>0){
                      cout<< "      ";
                    }
                  for(int Multispec2=0; Multispec2<CurrSizes->usize; Multispec2++) {
                      cout<< setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(V[cl*CurrSizes->usize*CurrSizes->usize+Multispec*CurrSizes->usize+Multispec2])<<"\t";
                    }
                  cout<< endl;
                }
              cout<< endl;
              flush(cout);
            }
        }
    }
  return 1;
}





int calcM_mask_LoAd(nifti_image * T1,
                    SegPrecisionTYPE * Expec,
                    SegPrecisionTYPE * BiasField,
                    int * S2L,
                    SegPrecisionTYPE * M,
                    SegPrecisionTYPE * V,
                    ImageSize * CurrSizes,
                    int verbose,
                    bool PVon)
{

  if(verbose>0){
      cout<< "Optimising Gaussian Parameters" << endl;
      flush(cout);
    }
  int numel_masked=CurrSizes->numelmasked;
  int currentnum_class=CurrSizes->numclass;
  int * S2L_PTR = (int *) S2L;
  SegPrecisionTYPE * Expec_PTR = (SegPrecisionTYPE *) Expec;
  SegPrecisionTYPE * T1_PTR = static_cast<SegPrecisionTYPE *>(T1->data);
  SegPrecisionTYPE * BiasField_PTR= (SegPrecisionTYPE *) BiasField;
  int Expec_offset[PV_numbclass];
  for (int cl=0; cl<currentnum_class; cl++) {
      Expec_offset[cl]=cl*numel_masked;
    }
  SegPrecisionTYPE tempsum= (SegPrecisionTYPE) 0.0;
  SegPrecisionTYPE SumPriors= (SegPrecisionTYPE) 0.0;


  for (int cl=0; cl<5; cl++) {
      Expec_PTR=(SegPrecisionTYPE *) &Expec[Expec_offset[cl]];
      BiasField_PTR= (SegPrecisionTYPE *) BiasField;
      S2L_PTR = (int *) S2L;
      tempsum=(SegPrecisionTYPE)0.0;
      SumPriors=(SegPrecisionTYPE)0.0;

      // MEAN
      if(BiasField!=NULL){
          for (int i=0; i<numel_masked; i++, Expec_PTR++,S2L_PTR++,BiasField_PTR++) {
              tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]+(*BiasField_PTR));
              SumPriors+=(*Expec_PTR);
            }
        }else{
          for (int i=0; i<numel_masked; i++, Expec_PTR++,S2L_PTR++) {
              tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]);
              SumPriors+=(*Expec_PTR);
            }
        }

      M[cl]=tempsum/SumPriors;

      //STD
      tempsum=0;
      Expec_PTR=&Expec[Expec_offset[cl]];
      BiasField_PTR=BiasField;
      S2L_PTR = (int *) S2L;
      if(BiasField!=NULL){
          for (int i=0; i<numel_masked;i++,Expec_PTR++,S2L_PTR++,BiasField_PTR++) {
              tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]+(*BiasField_PTR)-M[cl]) * (T1_PTR[(*S2L_PTR)]+(*BiasField_PTR)-M[cl]);
            }
        }else{
          for (int i=0; i<numel_masked;i++,Expec_PTR++,S2L_PTR++) {
              tempsum+=(*Expec_PTR) * (T1_PTR[(*S2L_PTR)]-M[cl]) * (T1_PTR[(*S2L_PTR)]-M[cl]);
            }

        }
      V[cl]=tempsum/SumPriors;

      if(V[cl]<0.0001 || V[cl]!=V[cl]){
          V[cl]=0.0001;
        }

      if(verbose>0){
          cout.fill('0');
          cout << "M[" << (int)(cl) << "]= " << setw(10) << setprecision(7) << left << (SegPrecisionTYPE)(M[cl]) << "\tV[" << (int)(cl) << "]=" << setw(10) << setprecision(7) <<left << (SegPrecisionTYPE)(V[cl]) << endl;
          flush(cout);
        }
    }

  if(PVon){
      M[WMGMpvclass]=(M[WMclass]*V[GMclass]+M[GMclass]*V[WMclass])/(float)(V[WMclass]+V[GMclass]);
      M[GMCSFpvclass]=(M[CSFclass]*V[GMclass]+M[GMclass]*V[CSFclass])/(float)(V[CSFclass]+V[GMclass]);
      V[WMGMpvclass]=0.5*V[WMclass]+0.5*V[GMclass];
      if(V[WMGMpvclass]<0.0003 || V[WMGMpvclass]!=V[WMGMpvclass])V[WMGMpvclass]=0.0003;
      V[GMCSFpvclass]=0.5*V[GMclass]+(0.5)*V[CSFclass];
      if(V[GMCSFpvclass]<0.0003 || V[GMCSFpvclass]!=V[GMCSFpvclass])V[GMCSFpvclass]=0.0003;
      cout<< "M["<<(int)(WMGMpvclass)<<"]= "<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(M[WMGMpvclass])<<"\tV["<<(int)(WMGMpvclass)<<"]="<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(V[WMGMpvclass])<< endl;
      cout<< "M["<<(int)(GMCSFpvclass)<<"]= "<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(M[GMCSFpvclass])<<"\tV["<<(int)(GMCSFpvclass)<<"]="<<setw(10)<<setprecision(7)<<left<<(SegPrecisionTYPE)(V[GMCSFpvclass])<< endl;
      flush(cout);
    }

  return 1;
}

int printloglik(int iter,
                SegPrecisionTYPE loglik,
                SegPrecisionTYPE oldloglik){
  if(iter>0){
      if ((loglik-oldloglik)/fabsf(oldloglik)>0 && (loglik-oldloglik)/fabsf(oldloglik)<100){
          cout<< "Loglik = " << loglik << " : Ratio = " << (loglik-oldloglik)/fabsf(oldloglik) << endl;
        }
      else{
          cout<< "Loglik = " << loglik << endl;
        }
    }
  else {
      cout<< "Initial Loglik = " << loglik << endl;
    }
  return 1;
}

int Relax_Priors(SegPrecisionTYPE * Priors,
                 SegPrecisionTYPE * Expec,
                 SegPrecisionTYPE * MRF,
                 int * S2L,
                 int * L2S,
                 float RelaxFactor,
                 SegPrecisionTYPE * G,
                 SegPrecisionTYPE ba,
                 SegPrecisionTYPE be,
                 ImageSize *  CurrSizes,
                 SEG_PARAM * segment_param){

  if(RelaxFactor<0){
      RelaxFactor=0;
      if(segment_param->verbose_level>0){
          cout<< "RelaxFactor was bellow 0 (min). Assuming RelaxFactor=0." << endl;
        }
    }

  if(RelaxFactor>1){
      RelaxFactor=1;
      if(segment_param->verbose_level>0){
          cout<< "RelaxFactor was above 1 (max). Assuming RelaxFactor=1." << endl;
        }
    }


  if(RelaxFactor>=0){
      if(segment_param->verbose_level>0){
          cout<< "Relaxing Priors with Rf = "<< RelaxFactor << endl;
          flush(cout);
        }
      Gaussian_Filter_Short_4D(Expec,S2L,L2S,2.0, CurrSizes,CSFclass);
      Relax_Priors_Share(Priors,Expec,RelaxFactor,G,be,CurrSizes);
      for(int i=0; i<(CurrSizes->numclass*CurrSizes->numelmasked);i++)MRF[i]=Priors[i];
      memcpy(Priors,Expec,CurrSizes->numelmasked*CurrSizes->numclass*sizeof(SegPrecisionTYPE));
    }

  return 1;

}

int Relax_Priors_Share(SegPrecisionTYPE * Priors,
                       SegPrecisionTYPE * Expec,
                       float RelaxFactor,
                       SegPrecisionTYPE * G,
                       SegPrecisionTYPE be,
                       ImageSize * CurrSizes){
  int numclass=CurrSizes->numclass;

  int N[PV_numbclass*PV_numbclass];
  SegPrecisionTYPE Currexpec[PV_numbclass];
  SegPrecisionTYPE Currexpec_updated[PV_numbclass];
  SegPrecisionTYPE Currexpec_sumall;
  SegPrecisionTYPE Currexpec_class;
  int Class_shift[PV_numbclass];
  // Precompute Class Shift
  for (int cl=0; cl<numclass; cl++) {
      Class_shift[cl]=cl*CurrSizes->numelmasked;
    }

  //Find neighbouring rules
  for(int i=0; i<numclass; i++){
      for(int j=0; j<numclass; j++){
          N[i+j*numclass]=(G[i+j*numclass]<=be)?1:0;
        }
    }

  for (int i=0; i<CurrSizes->numelmasked;i++) {
      //Copy current expec for all classes
      for (int cl=0; cl<numclass; cl++) {
          Currexpec[cl]=(1-RelaxFactor)*Expec[i+Class_shift[cl]]+(RelaxFactor)*Priors[i+Class_shift[cl]];
        }
      //Compute relaxed expec
      Currexpec_sumall=0;
      for (int cl=0; cl<numclass; cl++) {
          Currexpec_updated[cl]=0;
          Currexpec_class=Currexpec[cl];
          for (int cl2=0; cl2<numclass; cl2++) {
              Currexpec_updated[cl]+=Currexpec_class*Currexpec[cl2]*double(N[cl+cl2*numclass]);
            }
          Currexpec_sumall+=Currexpec_updated[cl];
        }
      Currexpec_sumall=Currexpec_sumall==0?1:Currexpec_sumall;
      //Copy current expec back all classes
      for (int cl=0; cl<numclass; cl++) {
          Expec[i+Class_shift[cl]]=Currexpec_updated[cl]/Currexpec_sumall;
        }

    }
  return 1;
}

int Gaussian_Filter_Short_4D(SegPrecisionTYPE * ShortData,
                             int * S2L,
                             int * L2S,
                             SegPrecisionTYPE gauss_std,
                             ImageSize * CurrSizes,
                             int class_with_CSF){

  int kernelsize=0;
  int kernelsizemin=(int)floorf(gauss_std*3.0);
  int kernelsizemax=(int)ceilf(gauss_std*3.0);

  if((kernelsizemin/2.0)==(double)(kernelsizemin/2) && kernelsizemin!=kernelsizemax){ // Which one is odd? kernelsizemin or kernelsizemax?
      kernelsize=kernelsizemax;}
  else if((kernelsizemax/2.0)==(double)(kernelsizemax/2) && kernelsizemin!=kernelsizemax){
      kernelsize=kernelsizemin;}
  else{
      kernelsize=kernelsizemin+1;}

  int kernelshift=(int)floorf(kernelsize/2);
  SegPrecisionTYPE GaussKernel [100]= {0};

  for(int i=0; i<kernelsize; i++){
      float kernelvalue=expf((float)(-0.5*powf((i-kernelshift)/gauss_std, 2)))/(sqrtf(2*3.14159265*powf(gauss_std, 2)));
      GaussKernel[i]=kernelvalue;
    }

  SegPrecisionTYPE * Buffer= new SegPrecisionTYPE [CurrSizes->numel]();
  SegPrecisionTYPE * LongData= new SegPrecisionTYPE [CurrSizes->numel]();


  int shiftdirection[3];
  shiftdirection[0]=1;
  shiftdirection[1]=(int)CurrSizes->xsize;
  shiftdirection[2]=(int)CurrSizes->xsize*(int)CurrSizes->ysize;
  int dim_array[3];
  dim_array[0]=(int)CurrSizes->xsize;
  dim_array[1]=(int)CurrSizes->ysize;
  dim_array[2]=(int)CurrSizes->zsize;


  //Outside the mask is considered Pure CSF
  int outsiderangevalue[10];
  for(int i=0; i<10; i++){
      outsiderangevalue[i]=0;
    }
  outsiderangevalue[class_with_CSF]=1;

  for(int curr4d=0; curr4d<CurrSizes->numclass; curr4d++){ //For Each Class
      int current_4dShift_short=curr4d*CurrSizes->numelmasked;
      for(int index=0;index<CurrSizes->numelmasked;index++){ //Copy Class to Buffer in LongFormat
          Buffer[S2L[index]]=ShortData[index+current_4dShift_short];
        }


      int xyzpos[3];
      for(int currentdirection=0;currentdirection<3;currentdirection++){ //Blur Buffer along each direction
          int index=0;
          for(xyzpos[2]=0;xyzpos[2]<(int)CurrSizes->zsize;xyzpos[2]++){
              for(xyzpos[1]=0;xyzpos[1]<(int)CurrSizes->ysize;xyzpos[1]++){
                  for(xyzpos[0]=0;xyzpos[0]<(int)CurrSizes->xsize;xyzpos[0]++){
                      SegPrecisionTYPE tmpvalue=0.0f;
                      SegPrecisionTYPE tmpkernelsum=0.0f;
                      LongData[index]=0.0f;
                      if(L2S[index]>=0){
                          for(int shift=((xyzpos[currentdirection]<kernelshift)?-xyzpos[currentdirection]:-kernelshift);shift<=((xyzpos[currentdirection]>=(dim_array[currentdirection]-kernelshift))?(int)dim_array[currentdirection]-xyzpos[currentdirection]-1:kernelshift) ; shift++){
                              tmpvalue+=(L2S[index+shift*shiftdirection[currentdirection]]==-1)?GaussKernel[shift+kernelshift]*outsiderangevalue[curr4d]:GaussKernel[shift+kernelshift]*Buffer[index+shift*shiftdirection[currentdirection]];
                              tmpkernelsum+=GaussKernel[shift+kernelshift];
                            }
                          LongData[index]=tmpvalue/tmpkernelsum;
                        }
                      index++;
                    }
                }
            }
          if(currentdirection<2){
              for(int index2=0;index2<CurrSizes->numel;index2++){
                  Buffer[index2]=LongData[index2];
                }
            }
        }

      for(int index=0;index<CurrSizes->numelmasked;index++){ //Copy Class to Buffer in LongFormat
          ShortData[index+current_4dShift_short]=LongData[S2L[index]];
        }


    }
  delete [] LongData;
  delete [] Buffer;
  return 1;
}

int Gaussian_Filter_4D(SegPrecisionTYPE * LongData,
                       SegPrecisionTYPE gauss_std,
                       ImageSize * CurrSizes){

  int kernelsize=0;
  int kernelsizemin=(int)floorf(gauss_std*4.0);
  int kernelsizemax=(int)ceilf(gauss_std*4.0);

  if((kernelsizemin/2.0)==(double)(kernelsizemin/2) && kernelsizemin!=kernelsizemax){ // Which one is odd? kernelsizemin or kernelsizemax?
      kernelsize=kernelsizemax;}
  else if((kernelsizemax/2.0)==(double)(kernelsizemax/2) && kernelsizemin!=kernelsizemax){
      kernelsize=kernelsizemin;}
  else{
      kernelsize=kernelsizemin+1;}

  int kernelshift=(int)floorf(kernelsize/2);

  SegPrecisionTYPE GaussKernel [200]= {0};

  for(int i=0; i<kernelsize; i++){
      GaussKernel[i]=expf((float)(-0.5*powf((i-kernelshift)/gauss_std, 2)))/(sqrtf(2*3.14159265*powf(gauss_std, 2)));
    }


  SegPrecisionTYPE * Buffer= new SegPrecisionTYPE [CurrSizes->numel]();



  int shiftdirection[3];
  shiftdirection[0]=1;
  shiftdirection[1]=(int)CurrSizes->xsize;
  shiftdirection[2]=(int)CurrSizes->xsize*(int)CurrSizes->ysize;
  int dim_array[3];
  dim_array[0]=(int)CurrSizes->xsize;
  dim_array[1]=(int)CurrSizes->ysize;
  dim_array[2]=(int)CurrSizes->zsize;


  for(int curr4d=0; curr4d<CurrSizes->tsize; curr4d++){ //For Each Class

      int current_4dShift_short=curr4d*CurrSizes->numel;
      SegPrecisionTYPE * longdataptr=&LongData[current_4dShift_short];
      for(int index=0;index<CurrSizes->numel;index++){ //Copy Class to Buffer in LongFormat
          Buffer[index]=longdataptr[index];
        }


      int xyzpos[3];
      for(int currentdirection=0;currentdirection<3;currentdirection++){ //Blur Buffer along each direction
          int index=0;
          SegPrecisionTYPE * longdataptr2=&longdataptr[0];
          for(xyzpos[2]=0;xyzpos[2]<(int)CurrSizes->zsize;xyzpos[2]++){
              for(xyzpos[1]=0;xyzpos[1]<(int)CurrSizes->ysize;xyzpos[1]++){
                  xyzpos[0]=0;
                  int kernelshiftminus=((xyzpos[currentdirection]<kernelshift)?-xyzpos[currentdirection]:-kernelshift);
                  int kernelshiftmplus=kernelshift;
                  for(xyzpos[0]=0;xyzpos[0]<(int)CurrSizes->xsize;xyzpos[0]++){

                      if(xyzpos[currentdirection]<=kernelshift){
                          kernelshiftminus=((xyzpos[currentdirection]<kernelshift)?-xyzpos[currentdirection]:-kernelshift);
                        }
                      if((xyzpos[currentdirection]>=(dim_array[currentdirection]-kernelshift))){
                          kernelshiftmplus=(int)dim_array[currentdirection]-xyzpos[currentdirection]-1;
                        }

                      SegPrecisionTYPE * GaussKernelptr=&GaussKernel[kernelshiftminus+kernelshift];
                      SegPrecisionTYPE * Bufferptr=&Buffer[index+kernelshiftminus*shiftdirection[currentdirection]];
                      SegPrecisionTYPE tmpvalue=0.0f;
                      SegPrecisionTYPE tmpkernelsum=0.0f;

                      for(int shift=kernelshiftminus;shift<=kernelshiftmplus ; shift++, GaussKernelptr++,Bufferptr+=shiftdirection[currentdirection]){
                          SegPrecisionTYPE GaussKernelvar=(*GaussKernelptr);
                          tmpvalue+=GaussKernelvar*(*Bufferptr);
                          tmpkernelsum+=GaussKernelvar;
                        }

                      (*longdataptr2)=tmpvalue/tmpkernelsum;

                      index++;
                      longdataptr2++;
                    }
                }
            }
          if(currentdirection<2){
              for(int index2=0;index2<CurrSizes->numel;index2++){
                  Buffer[index2]=longdataptr[index2];
                }
            }
        }
    }

  delete [] Buffer;
  return 0;
}

SegPrecisionTYPE * Gaussian_Filter_4D_inside_mask(SegPrecisionTYPE * LongData,
                                                  bool * mask,
                                                  SegPrecisionTYPE gauss_std,
                                                  ImageSize * CurrSizes){

  int kernelsize=0;
  int kernelsizemin=(int)floorf(gauss_std*3.0);
  int kernelsizemax=(int)ceilf(gauss_std*3.0);

  if((kernelsizemin/2.0)==(double)(kernelsizemin/2) && kernelsizemin!=kernelsizemax){ // Which one is odd? kernelsizemin or kernelsizemax?
      kernelsize=kernelsizemax;}
  else if((kernelsizemax/2.0)==(double)(kernelsizemax/2) && kernelsizemin!=kernelsizemax){
      kernelsize=kernelsizemin;}
  else{
      kernelsize=kernelsizemin+1;}

  int kernelshift=(int)floorf(kernelsize/2);
  SegPrecisionTYPE GaussKernel [100]= {0};

  for(int i=0; i<kernelsize; i++){
      float kernelvalue=expf((float)(-0.5*powf((i-kernelshift)/gauss_std, 2)))/(sqrtf(2*3.14159265*powf(gauss_std, 2)));
      GaussKernel[i]=kernelvalue;
    }

  SegPrecisionTYPE * Buffer= new SegPrecisionTYPE [CurrSizes->numel]();



  int shiftdirection[3];
  shiftdirection[0]=1;
  shiftdirection[1]=(int)CurrSizes->xsize;
  shiftdirection[2]=(int)CurrSizes->xsize*(int)CurrSizes->ysize;
  int dim_array[3];
  dim_array[0]=(int)CurrSizes->xsize;
  dim_array[1]=(int)CurrSizes->ysize;
  dim_array[2]=(int)CurrSizes->zsize;



  for(int curr4d=0; curr4d<CurrSizes->numclass; curr4d++){ //For Each Class
      int current_4dShift_short=curr4d*CurrSizes->numel;
      for(int index=0;index<CurrSizes->numel;index++){ //Copy Class to Buffer in LongFormat
          Buffer[index]=LongData[index+current_4dShift_short];
        }


      int xyzpos[3];
      for(int currentdirection=0;currentdirection<3;currentdirection++){ //Blur Buffer along each direction
          int index=0;
          for(xyzpos[2]=0;xyzpos[2]<(int)CurrSizes->zsize;xyzpos[2]++){
              for(xyzpos[1]=0;xyzpos[1]<(int)CurrSizes->ysize;xyzpos[1]++){
                  for(xyzpos[0]=0;xyzpos[0]<(int)CurrSizes->xsize;xyzpos[0]++){
                      SegPrecisionTYPE tmpvalue=0.0f;
                      SegPrecisionTYPE tmpkernelsum=0.0f;
                      LongData[index]=0.0f;
                      if(mask[index]>0){
                          for(int shift=((xyzpos[currentdirection]<kernelshift)?-xyzpos[currentdirection]:-kernelshift);shift<=((xyzpos[currentdirection]>=(dim_array[currentdirection]-kernelshift))?(int)dim_array[currentdirection]-xyzpos[currentdirection]-1:kernelshift) ; shift++){
                              tmpvalue+=GaussKernel[shift+kernelshift]*Buffer[index+shift*shiftdirection[currentdirection]];
                              tmpkernelsum+=GaussKernel[shift+kernelshift];
                            }
                          LongData[index]=tmpvalue/tmpkernelsum;
                        }
                      else{
                          if(curr4d==2){
                              LongData[index]=1;
                            }
                          else{
                              LongData[index]=0;
                            }
                        }
                      index++;
                    }
                }
            }
          if(currentdirection<2){
              for(int index2=0;index2<CurrSizes->numel;index2++){
                  Buffer[index2]=LongData[index2];
                }
            }
        }
    }
  return Buffer;
}

int Convert_to_PV(nifti_image * T1,
                  SegPrecisionTYPE * BiasField,
                  SegPrecisionTYPE * ShortPrior,
                  SegPrecisionTYPE * Expec,
                  SegPrecisionTYPE * MRF,
                  SegPrecisionTYPE * M,
                  SegPrecisionTYPE * V,
                  int * S2L,
                  int * L2S,
                  ImageSize * CurrSizes,
                  SEG_PARAM * segment_param){
  if(segment_param->verbose_level>0){
      cout<< "Covert to Explicit PV modeling" << endl;
    }
  Gaussian_Filter_Short_4D(Expec,S2L,L2S,1.0,CurrSizes,CSFclass);
  Gaussian_Filter_Short_4D(MRF,S2L,L2S,1.0,CurrSizes,CSFclass);
  Convert_WM_and_GM_to_PV(T1,BiasField,ShortPrior,Expec,S2L,M,V,CurrSizes);
  CurrSizes->numclass=7;
  for(int i=0; i<(CurrSizes->numclass*CurrSizes->numelmasked);i++){
      MRF[i]=1.0f;
    }
  return 1;
}

int Sulci_and_gyri_correction(SegPrecisionTYPE * MRF_Beta,
                              SegPrecisionTYPE * ShortPrior,
                              SegPrecisionTYPE * Expec,
                              SegPrecisionTYPE *MRF,
                              int * S2L,
                              int * L2S,
                              ImageSize *CurrSizes){

  // Deep Sulci ->  Seed=WM+WMGMpv+dGM+iCSF
  cout<< "Sucli and Gyri correction" << endl;
  bool * Seed_Mask= new bool [CurrSizes->numelmasked]();
  SegPrecisionTYPE * SpeedFunc= new SegPrecisionTYPE [CurrSizes->numelmasked]();
  SegPrecisionTYPE * wSulci= new SegPrecisionTYPE [CurrSizes->numelmasked]();
  SegPrecisionTYPE * wGyri= new SegPrecisionTYPE [CurrSizes->numelmasked]();

  for(int i=0; i<CurrSizes->numelmasked;i++){
      Seed_Mask[i]=(Expec[i+WMclass*CurrSizes->numelmasked]+
                    Expec[i+WMGMpvclass*CurrSizes->numelmasked]+
                    Expec[i+dGMclass*CurrSizes->numelmasked]+
                    Expec[i+iCSFclass*CurrSizes->numelmasked])>0.5f;
      SpeedFunc[i]=(Expec[i+CSFclass*CurrSizes->numelmasked]+
                    Expec[i+GMCSFpvclass*CurrSizes->numelmasked])*2;
    }

  FMM(Seed_Mask, SpeedFunc, wSulci,30, L2S, S2L, CurrSizes);
  TransformGeoTime(wSulci,30, L2S, S2L, CurrSizes);

  for(int i=0; i<CurrSizes->numelmasked;i++){
      Seed_Mask[i]=(Expec[i+CSFclass*CurrSizes->numelmasked]+
                    Expec[i+GMCSFpvclass*CurrSizes->numelmasked])>0.5f;
      SpeedFunc[i]=(Expec[i+WMclass*CurrSizes->numelmasked]+
                    Expec[i+WMGMpvclass*CurrSizes->numelmasked]+
                    Expec[i+dGMclass*CurrSizes->numelmasked]+
                    Expec[i+iCSFclass*CurrSizes->numelmasked])*2;
    }

  FMM(Seed_Mask, SpeedFunc, wGyri,30, L2S, S2L, CurrSizes);
  TransformGeoTime(wGyri,30, L2S, S2L, CurrSizes);


  float sumed_all=0;
  float wSulci_tmp=0;
  float wGyri_tmp=0;
  float MRFbeta_tmp=0;

  for(int i=0; i<CurrSizes->numelmasked;i++){
      wSulci_tmp=wSulci[i];
      wGyri_tmp=wGyri[i];
      MRFbeta_tmp=(1-wSulci_tmp)*(1-wGyri_tmp);
      MRF_Beta[i]=MRFbeta_tmp;
      sumed_all=0;
      if((wSulci_tmp+wGyri_tmp)>0){
          Expec[i+WMGMpvclass*CurrSizes->numelmasked]=Expec[i+WMGMpvclass*CurrSizes->numelmasked]+wGyri[i]*Expec[i+GMclass*CurrSizes->numelmasked];
          Expec[i+GMCSFpvclass*CurrSizes->numelmasked]=Expec[i+GMCSFpvclass*CurrSizes->numelmasked]+wSulci[i]*Expec[i+GMclass*CurrSizes->numelmasked];
          Expec[i+GMclass*CurrSizes->numelmasked]=Expec[i+GMclass*CurrSizes->numelmasked]*(MRFbeta_tmp);

          for(int c=0;c<7;c++){
              sumed_all+=Expec[i+c*CurrSizes->numelmasked];
            }
          if(sumed_all>0){
              for(int c=0;c<7;c++){
                  Expec[i+c*CurrSizes->numelmasked]=Expec[i+c*CurrSizes->numelmasked]/sumed_all;
                }
            }else{
              for(int c=0;c<7;c++){
                  Expec[i+c*CurrSizes->numelmasked]=1.0/7.0;
                }

            }
        }

    }
  Gaussian_Filter_Short_4D(Expec,S2L,L2S,1.0, CurrSizes,CSFclass);

  for(int i=0; i<CurrSizes->numelmasked;i++){
      for(int c=0;c<7;c++){
          ShortPrior[i+c*CurrSizes->numelmasked]=Expec[i+c*CurrSizes->numelmasked];
          MRF[i+c*CurrSizes->numelmasked]=Expec[i+c*CurrSizes->numelmasked];
        }
    }

  delete [] Seed_Mask;
  delete [] SpeedFunc;
  delete [] wSulci;
  delete [] wGyri;
  return 1;

}

int Convert_WM_and_GM_to_PV(nifti_image * T1,
                            SegPrecisionTYPE * BiasField,
                            SegPrecisionTYPE * ShortPrior,
                            SegPrecisionTYPE * Expec,
                            int * S2L,
                            SegPrecisionTYPE * M,
                            SegPrecisionTYPE * V,
                            ImageSize * CurrSizes){

  int WMindex=WMclass*CurrSizes->numelmasked;
  int GMindex=GMclass*CurrSizes->numelmasked;
  int CSFindex=CSFclass*CurrSizes->numelmasked;
  int dGMindex=dGMclass*CurrSizes->numelmasked;
  int iCSFindex=iCSFclass*CurrSizes->numelmasked;
  int WMGMpvindex=WMGMpvclass*CurrSizes->numelmasked;
  int GMCSFpvindex=GMCSFpvclass*CurrSizes->numelmasked;

  float averageFC_WMGM=0;
  float averageFCtmp_WMGM=0;
  float averageFC_GMCSF=0;
  float averageFCtmp_GMCSF=0;
  float currentT1=0;
  int count1=0;
  int count2=0;

  SegPrecisionTYPE * T1ptrtmp = static_cast<SegPrecisionTYPE *>(T1->data);
  for (int i=0; i<CurrSizes->numelmasked;i++){
      currentT1=T1ptrtmp[S2L[i]]+BiasField[i];

      averageFCtmp_WMGM=(currentT1-M[GMclass])/(M[WMclass]-M[GMclass]);

      if(averageFCtmp_WMGM<1 && averageFCtmp_WMGM>0){
          averageFC_WMGM+=averageFCtmp_WMGM;
          count1++;
        }

      averageFCtmp_GMCSF=(currentT1-M[CSFclass])/(M[GMclass]-M[CSFclass]);

      if(averageFCtmp_GMCSF<1 && averageFCtmp_GMCSF>0){
          averageFC_GMCSF+=averageFCtmp_GMCSF;
          count2++;
        }
    }

  averageFC_WMGM=(count1>0)?averageFC_WMGM/(float)(count1):0.5;
  averageFC_GMCSF=(count2>0)?averageFC_GMCSF/(float)(count2):0.5;


  cout<< "avr_WMGMfc=" << averageFC_WMGM << endl;
  cout<< "avr_GMCSFfc=" << averageFC_GMCSF << endl;

  for (int i=0; i<CurrSizes->numelmasked;i++,WMindex++,GMindex++,CSFindex++,dGMindex++,iCSFindex++,WMGMpvindex++,GMCSFpvindex++) {
      //Copy current expec for all classes
      ShortPrior[WMindex]=(ShortPrior[WMindex]*Expec[WMindex]);
      Expec[WMindex]=ShortPrior[WMindex];
      ShortPrior[GMindex]=(ShortPrior[GMindex]*Expec[GMindex]);
      Expec[GMindex]=ShortPrior[GMindex];
      ShortPrior[CSFindex]=(ShortPrior[CSFindex]*Expec[CSFindex]);
      Expec[CSFindex]=ShortPrior[CSFindex];
      ShortPrior[dGMindex]=(ShortPrior[dGMindex]*Expec[dGMindex]);
      Expec[dGMindex]=ShortPrior[dGMindex];
      ShortPrior[iCSFindex]=(ShortPrior[iCSFindex]*Expec[iCSFindex]);
      Expec[iCSFindex]=ShortPrior[iCSFindex];
      ShortPrior[WMGMpvindex]=sqrtf(ShortPrior[WMindex]*ShortPrior[GMindex]);
      Expec[WMGMpvindex]=(ShortPrior[WMGMpvindex]==ShortPrior[WMGMpvindex])?ShortPrior[WMGMpvindex]:0;
      ShortPrior[WMGMpvindex]=Expec[WMGMpvindex];
      ShortPrior[GMCSFpvindex]=sqrtf(ShortPrior[CSFindex]*ShortPrior[GMindex]);
      Expec[GMCSFpvindex]=(ShortPrior[GMCSFpvindex]==ShortPrior[GMCSFpvindex])?ShortPrior[GMCSFpvindex]:0;
      ShortPrior[GMCSFpvindex]=Expec[GMCSFpvindex];
    }



  M[WMGMpvclass]=(averageFC_WMGM*M[WMclass]+(1-averageFC_WMGM)*M[GMclass]);
  M[GMCSFpvclass]=(averageFC_GMCSF*M[GMclass]+(1-averageFC_GMCSF)*M[CSFclass]);
  V[WMGMpvclass]=sqrtf(averageFC_WMGM*averageFC_WMGM*pow(V[WMclass],2)+(1-averageFC_WMGM)*(1-averageFC_WMGM)*V[GMclass]);
  V[GMCSFpvclass]=sqrtf(averageFC_GMCSF*averageFC_GMCSF*pow(V[GMclass],2)+(1-averageFC_GMCSF)*(1-averageFC_GMCSF)*V[CSFclass]);

  return 1;
}



nifti_image * Copy_ShortExpec_to_Result(nifti_image * T1,
                                        SegPrecisionTYPE * Expec,
                                        SegPrecisionTYPE * BiasField,
                                        SegPrecisionTYPE * BiasFieldCoefs,
                                        int * S2L,
                                        nifti_image * Priors,
                                        SEG_PARAM * segment_param,
                                        SegPrecisionTYPE * M,
                                        ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(Priors);
  if(segment_param->flag_PV_model){

      SegPrecisionTYPE * T1ptrtmp = static_cast<SegPrecisionTYPE *>(T1->data);

      Result->dim[0]=4;
      Result->dim[4]=6;
      Result->datatype=DT_FLOAT32;
      Result->cal_max=1;
      nifti_set_filenames(Result,segment_param->filename_out,0,0);
      nifti_update_dims_from_array(Result);
      nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
      Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
      SegPrecisionTYPE * Result_PTR = static_cast<SegPrecisionTYPE *>(Result->data);
      for(unsigned int i=0; i<Result->nvox; i++){Result_PTR[i]=0;}

      int Short_2_Long_Indices_tmp = 0;
      int class_nvox=Result->nx*Result->ny*Result->nz;
      SegPrecisionTYPE * Resultdata= static_cast<SegPrecisionTYPE *>(Result->data);
      SegPrecisionTYPE * Expec_tmp = new SegPrecisionTYPE [CurrSizes->numclass]();
      SegPrecisionTYPE Expec_tmp_sum=0;
      SegPrecisionTYPE Fractional_content=0;

      if(BiasField!=NULL){
          for(int i=0; i<CurrSizes->numelmasked; i++){
              Short_2_Long_Indices_tmp=S2L[i];
              for(int currclass=0; currclass<CurrSizes->numclass;currclass++){
                  Expec_tmp[currclass]=Expec[i+currclass*CurrSizes->numelmasked];
                }
              float classthreshold=0.1;
              Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=Expec_tmp[WMclass]>classthreshold?Expec_tmp[WMclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=Expec_tmp[GMclass]>classthreshold?Expec_tmp[GMclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=Expec_tmp[CSFclass]>classthreshold?Expec_tmp[CSFclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(dGMclass)*class_nvox]=Expec_tmp[dGMclass]>classthreshold?Expec_tmp[dGMclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(iCSFclass)*class_nvox]=Expec_tmp[iCSFclass]>classthreshold?Expec_tmp[iCSFclass]:0;


              // Estimating WM/GM fractional content from the T1 bias corrected data
              if(Expec_tmp[WMGMpvclass]>classthreshold){
                  if(((Expec_tmp[WMclass])<(Expec_tmp[WMGMpvclass])) & (Expec_tmp[GMclass]<(Expec_tmp[WMGMpvclass]))){
                      Expec_tmp_sum=Expec_tmp[WMclass]+Expec_tmp[WMGMpvclass]+Expec_tmp[GMclass];
                      Fractional_content=(M[WMclass]-(T1ptrtmp[Short_2_Long_Indices_tmp]+BiasField[i]))/(M[WMclass]-M[GMclass]);
                      Fractional_content=(Fractional_content<0)?0:Fractional_content;
                      Fractional_content=(Fractional_content>1)?1:Fractional_content;
                      Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=(1-Fractional_content)/Expec_tmp_sum;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=(Fractional_content)/Expec_tmp_sum;
                    }
                  else if(Expec_tmp[WMclass]>Expec_tmp[GMclass]){
                      Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=1;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=0;
                    }
                  else{
                      Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=0;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=1;
                    }
                }

              // Estimating CSF/GM fractional content from the T1 bias corrected data
              if(Expec_tmp[GMCSFpvclass]>classthreshold){
                  if((Expec_tmp[CSFclass]<(Expec_tmp[GMCSFpvclass])) & (Expec_tmp[GMclass]<(Expec_tmp[GMCSFpvclass]))){
                      Expec_tmp_sum=Expec_tmp[CSFclass]+Expec_tmp[GMCSFpvclass]+Expec_tmp[GMclass];
                      Fractional_content=(M[CSFclass]-(T1ptrtmp[Short_2_Long_Indices_tmp]+BiasField[i]))/(M[CSFclass]-M[GMclass]);
                      Fractional_content=(Fractional_content<0)?0:Fractional_content;
                      Fractional_content=(Fractional_content>1)?1:Fractional_content;
                      Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=(1-Fractional_content)/Expec_tmp_sum;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=(Fractional_content)/Expec_tmp_sum;
                    }
                  else if(Expec_tmp[CSFclass]>Expec_tmp[GMclass]){
                      Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=1;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=0;
                    }
                  else{
                      Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=0;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=1;
                    }
                }

              // Normalizing the fractional contents
              Expec_tmp_sum=0;
              for(int currclass=0; currclass<non_PV_numclass;currclass++){
                  Expec_tmp_sum+=Resultdata[Short_2_Long_Indices_tmp+(currclass)*class_nvox];
                }
              for(int currclass=0; currclass<non_PV_numclass;currclass++){
                  Resultdata[Short_2_Long_Indices_tmp+(currclass)*class_nvox]=Resultdata[Short_2_Long_Indices_tmp+(currclass)*class_nvox]/Expec_tmp_sum;
                }

            }
        }
      else{

          for(int i=0; i<CurrSizes->numelmasked; i++){
              Short_2_Long_Indices_tmp=S2L[i];
              for(int currclass=0; currclass<CurrSizes->numclass;currclass++){
                  Expec_tmp[currclass]=Expec[i+currclass*CurrSizes->numelmasked];
                }
              float classthreshold=0.1;
              Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=Expec_tmp[WMclass]>classthreshold?Expec_tmp[WMclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=Expec_tmp[GMclass]>classthreshold?Expec_tmp[GMclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=Expec_tmp[CSFclass]>classthreshold?Expec_tmp[CSFclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(dGMclass)*class_nvox]=Expec_tmp[dGMclass]>classthreshold?Expec_tmp[dGMclass]:0;
              Resultdata[Short_2_Long_Indices_tmp+(iCSFclass)*class_nvox]=Expec_tmp[iCSFclass]>classthreshold?Expec_tmp[iCSFclass]:0;


              // Estimating WM/GM fractional content from the T1 data
              if(Expec_tmp[WMGMpvclass]>classthreshold){
                  if(((Expec_tmp[WMclass])<(Expec_tmp[WMGMpvclass])) & (Expec_tmp[GMclass]<(Expec_tmp[WMGMpvclass]))){
                      Expec_tmp_sum=Expec_tmp[WMclass]+Expec_tmp[WMGMpvclass]+Expec_tmp[GMclass];
                      Fractional_content=(M[WMclass]-(T1ptrtmp[Short_2_Long_Indices_tmp]))/(M[WMclass]-M[GMclass]);
                      Fractional_content=(Fractional_content<0)?0:Fractional_content;
                      Fractional_content=(Fractional_content>1)?1:Fractional_content;
                      Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=(1-Fractional_content)/Expec_tmp_sum;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=(Fractional_content)/Expec_tmp_sum;
                    }
                  else if(Expec_tmp[WMclass]>Expec_tmp[GMclass]){
                      Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=1;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=0;
                    }
                  else{
                      Resultdata[Short_2_Long_Indices_tmp+(WMclass)*class_nvox]=0;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=1;
                    }
                }

              // Estimating CSF/GM fractional content from the T1 data
              if(Expec_tmp[GMCSFpvclass]>classthreshold){
                  if((Expec_tmp[CSFclass]<Expec_tmp[GMCSFpvclass]) & (Expec_tmp[GMclass]<Expec_tmp[GMCSFpvclass])){
                      Expec_tmp_sum=Expec_tmp[CSFclass]+Expec_tmp[GMCSFpvclass]+Expec_tmp[GMclass];
                      Fractional_content=(M[CSFclass]-(T1ptrtmp[Short_2_Long_Indices_tmp]))/(M[CSFclass]-M[GMclass]);
                      Fractional_content=(Fractional_content<0)?0:Fractional_content;
                      Fractional_content=(Fractional_content>1)?1:Fractional_content;
                      Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=(1-Fractional_content)/Expec_tmp_sum;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=(Fractional_content)/Expec_tmp_sum;
                    }
                  else if(Expec_tmp[CSFclass]>Expec_tmp[GMclass]){
                      Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=1;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=0;
                    }
                  else{
                      Resultdata[Short_2_Long_Indices_tmp+(CSFclass)*class_nvox]=0;
                      Resultdata[Short_2_Long_Indices_tmp+(GMclass)*class_nvox]=1;
                    }
                }

              // Normalizing the fractional contents
              Expec_tmp_sum=0;
              for(int currclass=0; currclass<non_PV_numclass;currclass++){
                  Expec_tmp_sum+=Resultdata[Short_2_Long_Indices_tmp+(currclass)*class_nvox];
                }
              for(int currclass=0; currclass<non_PV_numclass;currclass++){
                  Resultdata[Short_2_Long_Indices_tmp+(currclass)*class_nvox]=Resultdata[Short_2_Long_Indices_tmp+(currclass)*class_nvox]/Expec_tmp_sum;
                }



            }
          delete [] Expec_tmp;


        }
    }
  else{
      Result->dim[0]=4;
      Result->dim[4]=(CurrSizes->numclass);
      Result->datatype=DT_FLOAT32;
      Result->cal_max=1;
      nifti_set_filenames(Result,segment_param->filename_out,0,0);
      nifti_update_dims_from_array(Result);
      nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
      Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
      SegPrecisionTYPE * Result_PTR = static_cast<SegPrecisionTYPE *>(Result->data);
      for(unsigned int i=0; i<Result->nvox; i++){Result_PTR[i]=0;}

      int * S2L_PRT = (int *) S2L;
      SegPrecisionTYPE * Resultdata= static_cast<SegPrecisionTYPE *>(Result->data);


      int class_nvox=CurrSizes->numel;
      for(int currclass=0; currclass<CurrSizes->numclass;currclass++){

          SegPrecisionTYPE * Resultdata_class = &Resultdata[(currclass)*class_nvox];
          SegPrecisionTYPE * Expec_PTR = &Expec[(currclass)*CurrSizes->numelmasked];
          S2L_PRT= (int *) S2L;

          for(int i=0; i<CurrSizes->numelmasked; i++,S2L_PRT++,Expec_PTR++){
              Resultdata_class[*S2L_PRT]=*Expec_PTR;
            }
        }
    }
  return Result;
}

bool * binarise_image(SegPrecisionTYPE * SingleImage,
                      SegPrecisionTYPE Threshold,
                      ImageSize * CurrSizes){

  bool * Result = new bool [CurrSizes->numelmasked];

  for(int i=0; i<CurrSizes->numelmasked; i++){
      Result[i]=(SingleImage[i]>Threshold);
    }
  return Result;
}

nifti_image * Copy_Single_ShortImage_to_Result(SegPrecisionTYPE * SingleImage,
                                               int * Short_2_Long_Indices,
                                               nifti_image * Sourceimage,
                                               char * filename,
                                               ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(Sourceimage);
  nifti_set_filenames(Result,filename,0,0);
  Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * Result_PTR = static_cast<SegPrecisionTYPE *>(Result->data);
  for(unsigned int i=0; i<Result->nvox; i++){Result_PTR[i]=0;}

  int * Short_2_Long_Indices_PRT = (int *) Short_2_Long_Indices;
  SegPrecisionTYPE * Resultdata= static_cast<SegPrecisionTYPE *>(Result->data);

  SegPrecisionTYPE * SingleImage_PTR =SingleImage;
  Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;

  for(int i=0; i<CurrSizes->numelmasked; i++,Short_2_Long_Indices_PRT++,SingleImage_PTR++){
      Resultdata[*Short_2_Long_Indices_PRT]=(SegPrecisionTYPE)(*SingleImage_PTR);
    }
  return Result;
}



nifti_image * Copy_BiasCorrected_to_Result_mask(SegPrecisionTYPE * BiasField,
                                                int * Short_2_Long_Indices,
                                                nifti_image * T1,
                                                char * filename,
                                                ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(T1);
  Result->dim[0]=4;
  Result->dim[4]=1;
  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);
  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
  Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * Resultdata = static_cast<SegPrecisionTYPE *>(Result->data);
  SegPrecisionTYPE * T1data = static_cast<SegPrecisionTYPE *>(T1->data);
  for(unsigned int i=0; i<Result->nvox; i++){Resultdata[i]=0;}

  int * Short_2_Long_Indices_PRT = (int *) Short_2_Long_Indices;

  Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;
  SegPrecisionTYPE to_resize=0;
  if(BiasField!=NULL){
      for(int i=0; i<CurrSizes->numelmasked; i++,Short_2_Long_Indices_PRT++){
          to_resize=exp((BiasField[i]+T1data[*Short_2_Long_Indices_PRT])*0.693147181)-1;
          Resultdata[*Short_2_Long_Indices_PRT]=(to_resize*(CurrSizes->rescale_max[0]-CurrSizes->rescale_min[0])+CurrSizes->rescale_min[0]);
        }
    }else{
      for(int i=0; i<CurrSizes->numelmasked; i++,Short_2_Long_Indices_PRT++){
          to_resize=exp((T1data[*Short_2_Long_Indices_PRT])*0.693147181)-1;
          Resultdata[*Short_2_Long_Indices_PRT]=(to_resize*(CurrSizes->rescale_max[0]-CurrSizes->rescale_min[0])+CurrSizes->rescale_min[0]);
        }
    }
  return Result;
}

nifti_image * Copy_BiasCorrected_to_Result(SegPrecisionTYPE * BiasField,
                                           nifti_image * T1,
                                           char * filename,
                                           ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(T1);
  Result->dim[0]=4;
  Result->dim[4]=1;
  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);
  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
  Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * Resultdata = static_cast<SegPrecisionTYPE *>(Result->data);
  SegPrecisionTYPE * T1data = static_cast<SegPrecisionTYPE *>(T1->data);
  for(unsigned int i=0; i<Result->nvox; i++){Resultdata[i]=0;}
  SegPrecisionTYPE to_resize=0;
  if(BiasField!=NULL){
      for(int i=0; i<CurrSizes->numel; i++){
          to_resize=exp((BiasField[i]+T1data[i])*0.693147181)-1;
          Resultdata[i]=(to_resize*(CurrSizes->rescale_max[0]-CurrSizes->rescale_min[0])+CurrSizes->rescale_min[0]);
        }
    }else{
      for(int i=0; i<CurrSizes->numel; i++){
          to_resize=exp((T1data[i])*0.693147181)-1;
          Resultdata[i]=(to_resize*(CurrSizes->rescale_max[0]-CurrSizes->rescale_min[0])+CurrSizes->rescale_min[0]);
        }
    }
  return Result;
}



nifti_image * Copy_Expec_to_Result_Neonate_mask(SegPrecisionTYPE * Expec,
                                                int * Short_2_Long_Indices,
                                                int * Long_2_Short_Indices,
                                                nifti_image * T1,
                                                float * BiasField,
                                                float * M,
                                                char * filename,
                                                ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(T1);
  Result->dim[0]=4;
  Result->dim[4]=6;
  Result->dim[5]=1;
  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);
  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
  Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * Resultdata = static_cast<SegPrecisionTYPE *>(Result->data);

  SegPrecisionTYPE * T1ptrtmp = static_cast<SegPrecisionTYPE *>(T1->data);
  for(unsigned int i=0; i<Result->nvox; i++){Resultdata[i]=0;}

  int * Short_2_Long_Indices_PRT = (int *) Short_2_Long_Indices;

  int class_nvox=Result->nx*Result->ny*Result->nz;

  Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;
  for(int currclass=0; currclass<6;currclass++){
      SegPrecisionTYPE * Resultdata_class = &Resultdata[(currclass)*class_nvox];
      SegPrecisionTYPE * Expec_PTR = &Expec[(currclass)*CurrSizes->numelmasked];
      Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;
      for(int i=0; i<CurrSizes->numelmasked; i++,Short_2_Long_Indices_PRT++,Expec_PTR++){
          Resultdata_class[(*Short_2_Long_Indices_PRT)]=(*Expec_PTR);
        }
    }


  int xyzpos[3]={0};
  int distance=4;
  Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;
  float Fractional_content=0;
  int biggestclass=-1;
  float biggestclass_prob=-1;
  int biggestclass2=-1;
  float biggestclass2_prob=-1;
  int neigh_index=0;

  for(int i=0; i<CurrSizes->numelmasked; i++,Short_2_Long_Indices_PRT++){
      if(Expec[(6)*CurrSizes->numelmasked+i]>0.1){
          biggestclass=-1;
          biggestclass_prob=0.1;
          biggestclass2=-2;
          biggestclass2_prob=0.1;
          for(xyzpos[2]=-distance;xyzpos[2]<distance;xyzpos[2]++){
              for(xyzpos[1]=-distance;xyzpos[1]<distance;xyzpos[1]++){
                  for(xyzpos[0]=-distance;xyzpos[0]<distance;xyzpos[0]++){
                      neigh_index=Long_2_Short_Indices[(*Short_2_Long_Indices_PRT)+xyzpos[0]+xyzpos[1]*CurrSizes->xsize+xyzpos[2]*CurrSizes->xsize*CurrSizes->ysize];
                      if(neigh_index>0 && neigh_index<CurrSizes->numel){
                          for(int neigh_class=1; neigh_class<6;neigh_class++){
                              if(Expec[neigh_index+(neigh_class)*CurrSizes->numelmasked]>biggestclass_prob){
                                  if(biggestclass!=biggestclass2){
                                      biggestclass2_prob=biggestclass_prob;
                                      biggestclass2=biggestclass;
                                    }
                                  biggestclass_prob=Expec[neigh_index+(neigh_class)*CurrSizes->numelmasked];
                                  biggestclass=neigh_class;
                                }
                              if(Expec[neigh_index+(neigh_class)*CurrSizes->numelmasked]>biggestclass2_prob && Expec[neigh_index+(neigh_class)*CurrSizes->numelmasked]<biggestclass2_prob){
                                  if(biggestclass!=neigh_class){
                                      biggestclass2_prob=Expec[neigh_index+(neigh_class)*CurrSizes->numelmasked];
                                      biggestclass2=neigh_class;
                                    }
                                }
                            }
                        }
                    }
                }
            }

          if(biggestclass>0 && biggestclass2>0){
              Fractional_content=(M[biggestclass]-(T1ptrtmp[(*Short_2_Long_Indices_PRT)]+BiasField[i]))/(M[biggestclass]-M[biggestclass2]);
              Fractional_content=(Fractional_content<0)?0:Fractional_content;
              Fractional_content=(Fractional_content>1)?1:Fractional_content;
              Resultdata[(*Short_2_Long_Indices_PRT)+(biggestclass)*class_nvox]=(1-Fractional_content);
              Resultdata[(*Short_2_Long_Indices_PRT)+(biggestclass2)*class_nvox]=(Fractional_content);
              for(int otherclasses=0;otherclasses<6;otherclasses++){
                  if(otherclasses!=biggestclass && otherclasses!=biggestclass2){
                      Resultdata[(*Short_2_Long_Indices_PRT)+(otherclasses)*class_nvox]=0;
                    }
                }
            }
          else{
              for(int otherclasses=0;otherclasses<6;otherclasses++){
                  Resultdata[(*Short_2_Long_Indices_PRT)+(otherclasses)*class_nvox]=0;
                }
              Resultdata[(*Short_2_Long_Indices_PRT)+(2)*class_nvox]=1;
            }
        }
    }


  Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;
  float sumexp=0;

  for(int i=0; i<CurrSizes->numel; i++){
      if(Long_2_Short_Indices[i]>0){
          sumexp=0;
          for(int currclass=0; currclass<6;currclass++){
              if((Resultdata[i+currclass*CurrSizes->numel])>0.01){
                  sumexp+=Resultdata[i+currclass*CurrSizes->numel];
                }
            }
          if(sumexp>0){
              for(int currclass=0; currclass<6;currclass++){
                  if((Resultdata[i+currclass*CurrSizes->numel])>0.01){
                      Resultdata[i+currclass*CurrSizes->numel]=Resultdata[i+currclass*CurrSizes->numel]/sumexp;
                    }
                  else{
                      Resultdata[i+currclass*CurrSizes->numel]=0;
                    }
                }
            }
        }
    }

  return Result;
}

nifti_image * Copy_Expec_to_Result_mask(SegPrecisionTYPE * Expec,
                                        int * Short_2_Long_Indices,
                                        nifti_image * T1,
                                        char * filename,
                                        ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(T1);
  Result->dim[0]=4;
  Result->dim[4]=CurrSizes->numclass;
  Result->dim[5]=1;
  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);
  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
  Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * Resultdata = static_cast<SegPrecisionTYPE *>(Result->data);
  for(unsigned int i=0; i<Result->nvox; i++){Resultdata[i]=0;}

  int * Short_2_Long_Indices_PRT = (int *) Short_2_Long_Indices;

  int class_nvox=Result->nx*Result->ny*Result->nz;

  Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;
  for(int currclass=0; currclass<CurrSizes->numclass;currclass++){

      SegPrecisionTYPE * Resultdata_class = &Resultdata[(currclass)*class_nvox];
      SegPrecisionTYPE * Expec_PTR = &Expec[(currclass)*CurrSizes->numelmasked];
      Short_2_Long_Indices_PRT= (int *) Short_2_Long_Indices;

      for(int i=0; i<CurrSizes->numelmasked; i++,Short_2_Long_Indices_PRT++,Expec_PTR++){
          Resultdata_class[Short_2_Long_Indices[i]]=*Expec_PTR;
        }
    }
  return Result;
}


nifti_image * Copy_Expec_to_Result(SegPrecisionTYPE * Expec,
                                   nifti_image * T1,
                                   char * filename,
                                   ImageSize * CurrSizes){

  nifti_image * Result = nifti_copy_nim_info(T1);
  Result->dim[0]=4;
  Result->dim[4]=CurrSizes->numclass;
  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);
  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);
  Result->data = (void *) calloc(Result->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * Resultdata = static_cast<SegPrecisionTYPE *>(Result->data);
  for(unsigned int i=0; i<Result->nvox; i++){Resultdata[i]=0;}
  int class_nvox=Result->nx*Result->ny*Result->nz;

  for(int currclass=0; currclass<CurrSizes->numclass;currclass++){

      SegPrecisionTYPE * Resultdata_class = &Resultdata[(currclass)*class_nvox];
      SegPrecisionTYPE * Expec_PTR = &Expec[(currclass)*CurrSizes->numel];

      for(int i=0; i<CurrSizes->numel; i++,Expec_PTR++){
          Resultdata_class[i]=*Expec_PTR;
        }
    }
  return Result;
}


nifti_image * Copy_single_image_to_Result(bool * Mask,
                                          nifti_image * Original,
                                          char * filename){

  nifti_image * Result = nifti_copy_nim_info(Original);
  Result->dim[0]=4;
  Result->dim[4]=1;

  Result->datatype=DT_INT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);

  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);

  Result->data = (void *) calloc(Result->nvox, sizeof(int));

  int * Resultdata = static_cast<int *>(Result->data);

  bool * Expec_PTR = static_cast<bool *>(Mask);

  for(unsigned int i=0; i<Result->nvox; i++,Expec_PTR++,Resultdata++){
      *Resultdata=(int)(*Expec_PTR);
    }

  return Result;
}


nifti_image * Copy_single_image_to_Result(float * W,
                                          nifti_image * Original,
                                          char * filename){

  nifti_image * Result = nifti_copy_nim_info(Original);
  Result->dim[0]=4;
  Result->dim[4]=1;

  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);

  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);

  Result->data = (void *) calloc(Result->nvox, sizeof(float));

  float * Resultdata = static_cast<float *>(Result->data);

  float * Expec_PTR = static_cast<float *>(W);

  for(unsigned int i=0; i<Result->nvox; i++,Expec_PTR++,Resultdata++){
      *Resultdata=(float)(*Expec_PTR);
    }

  return Result;
}

nifti_image * Copy_single_image_to_Result(double * W,
                                          nifti_image * Original,
                                          char * filename){

  nifti_image * Result = nifti_copy_nim_info(Original);
  Result->dim[0]=4;
  Result->dim[4]=1;

  Result->datatype=DT_FLOAT32;
  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);

  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);

  Result->data = (void *) calloc(Result->nvox, sizeof(float));

  float * Resultdata = static_cast<float *>(Result->data);

  double * Expec_PTR = static_cast<double *>(W);

  for(unsigned int i=0; i<Result->nvox; i++,Expec_PTR++,Resultdata++){
      *Resultdata=(float)(*Expec_PTR);
    }

  return Result;
}

nifti_image * Copy_single_image_to_Result(int * Image,
                                          nifti_image * Original,
                                          char * filename){

  nifti_image * Result = nifti_copy_nim_info(Original);
  Result->dim[0]=4;
  Result->dim[4]=1;

  Result->datatype=DT_INT32;

  Result->cal_max=1;
  nifti_set_filenames(Result,filename,0,0);
  nifti_update_dims_from_array(Result);

  nifti_datatype_sizes(Result->datatype,&Result->nbyper,&Result->swapsize);

  Result->data = (void *) calloc(Result->nvox, sizeof(int));

  int * Resultdata = static_cast<int *>(Result->data);
  int * Image_PTR = Image;

  for(unsigned int i=0; i<Result->nvox; i++,Image_PTR++,Resultdata++){
      *Resultdata=(int)(*Image_PTR);
    }

  return Result;
}


int quickSort(int *arr, int elements) {

  int  piv, beg[300], end[300], i=0, L, R, swap ;

  beg[0]=0; end[0]=elements;
  while (i>=0) {
      L=beg[i]; R=end[i]-1;
      if (L<R) {
          piv=arr[L];
          while (L<R) {
              while (arr[R]>=piv && L<R) R--; if (L<R) arr[L++]=arr[R];
              while (arr[L]<=piv && L<R) L++; if (L<R) arr[R--]=arr[L];
            }
          arr[L]=piv; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
          if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
              swap=beg[i];
              beg[i]=beg[i-1];
              beg[i-1]=swap;
              swap=end[i];
              end[i]=end[i-1];
              end[i-1]=swap;
            }
        }
      else {
          i--;
        }
    }
  return 1;}


int quickSort(float *arr, int elements) {

  float  piv;
  int beg[300], end[300], i=0, L, R, swap ;

  beg[0]=0; end[0]=elements;
  cout << elements<<endl;

  while (i>=0) {
      L=beg[i]; R=end[i]-1;
      if (L<R) {
          piv=arr[L];
          cout <<"part1= "<< L << "," <<arr[L] << " ... " <<R << "," <<arr[R]<<endl;
          while (L<R) {
              while (arr[R]>=piv && L<R) R--; if (L<R) arr[L++]=arr[R];
              while (arr[L]<=piv && L<R) L++; if (L<R) arr[R--]=arr[L];
            }
          cout <<"part2= "<< L << "," <<arr[L] << " ... " <<R << "," <<arr[R]<<endl;
          arr[L]=piv; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
          cout <<i<<endl;
          if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
              swap=beg[i];
              beg[i]=beg[i-1];
              beg[i-1]=swap;
              swap=end[i];
              end[i]=end[i-1];
              end[i-1]=swap;
            }
          cout <<i<<endl;
        }
      else {
          i--;
        }
    }
  return 1;
}


int * quickSort_order(int *arr, int elements) {

  int  piv,piv_index, beg[300], end[300], i=0, L, R, swap ;

  int * order=new int [elements];
  for(i=0;i<elements; i++){
      order[i]=i;
    }

  beg[0]=0; end[0]=elements;
  while (i>=0) {
      L=beg[i]; R=end[i]-1;
      if (L<R) {
          piv=arr[L];
          piv_index=order[L];
          while (L<R) {
              while (arr[R]>=piv && L<R) R--;
              if (L<R) {
                  arr[L]=arr[R];
                  order[L++]=order[R];
                }
              while (arr[L]<=piv && L<R) L++;
              if (L<R) {
                  arr[R]=arr[L];
                  order[R--]=order[L];
                }
            }

          arr[L]=piv;order[L]=piv_index; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
          if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
              swap=beg[i];
              beg[i]=beg[i-1];
              beg[i-1]=swap;
              swap=end[i];
              end[i]=end[i-1];
              end[i-1]=swap;
            }
        }
      else {
          i--;
        }
    }
  return order;}


int * quickSort_order(float *arr, int elements) {

  float  piv;
  int piv_index, beg[300], end[300], i=0, L, R, swap ;
  int * order = new int [elements];
  for(int index=0;index<elements; index++){
      order[index]=index;
    }
  beg[0]=0; end[0]=elements;
  int step=0;
  while (i>=0) {
      L=beg[i]; R=end[i]-1;
      if (L<R) {
          step++;
          if(step==100){
              cout << "R , L = "<<R<<" , "<<L<<" -> "<<arr[L]<<" , "<<arr[R]<<endl;
              step=0;
            }
          piv=arr[L];
          piv_index=order[L];
          while (L<R) {
              while (arr[R]>=piv && L<R){
                  R--;
                }
              if (L<R) {
                  arr[L]=arr[R];
                  order[L++]=order[R];
                }
              while (arr[L]<=piv && L<R){
                  L++;
                }
              if (L<R) {
                  arr[R]=arr[L];
                  order[R--]=order[L];
                }
            }
          arr[L]=piv;order[L]=piv_index; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
          if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
              swap=beg[i];
              beg[i]=beg[i-1];
              beg[i-1]=swap;
              swap=end[i];
              end[i]=end[i-1];
              end[i-1]=swap;
            }
        }
      else {
          i--;
        }
    }
  return order;
}




void MaxHeapify(float * a,int i,int n)
{
    int l,r,lr;
    float t;
    l=2*i+1;
    r=2*i+2;
    if((l<=n)&&(a[l]>a[i]))lr=l;
    else lr=i;
    if((r<=n)&&(a[r]>a[lr]))lr=r;
    if(lr!=i)
    {
        t=a[i];
        a[i]=a[lr];
        a[lr]=t;
        MaxHeapify(a,lr,n);
    }
}

void BuildMaxHeap(float * a,int n)
{
    int i;
    for(i=(n/2);i>=0;i--)
    MaxHeapify(a,i,n);
}

void HeapSort(float * a,int n)
{
    int i;
    float t;
    BuildMaxHeap(a,n);
    for(i=n;i>0;i--)
    {
        t=a[0];
        a[0]=a[i];
        a[i]=t;
        n--;
        MaxHeapify(a,0,n);
    }
}



nifti_image * Get_Bias_Corrected(float * BiasField,
                                 nifti_image * T1,
                                 char * filename,
                                 ImageSize * CurrSizes){

  nifti_image * BiasCorrected = nifti_copy_nim_info(T1);
  BiasCorrected->dim[0]=4;
  BiasCorrected->dim[4]=CurrSizes->usize;
  BiasCorrected->datatype=DT_FLOAT32;
  BiasCorrected->cal_max=(CurrSizes->rescale_max[0]);

  nifti_set_filenames(BiasCorrected,filename,0,0);
  nifti_update_dims_from_array(BiasCorrected);
  nifti_datatype_sizes(BiasCorrected->datatype,&BiasCorrected->nbyper,&BiasCorrected->swapsize);
  BiasCorrected->data = (void *) calloc(BiasCorrected->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * BiasCorrected_PTR = static_cast<SegPrecisionTYPE *>(BiasCorrected->data);
  SegPrecisionTYPE * T1data = static_cast<SegPrecisionTYPE *>(T1->data);
  for(int multispec=0;multispec<CurrSizes->usize;multispec++){

      BiasCorrected_PTR = static_cast<SegPrecisionTYPE *>(BiasCorrected->data);
      BiasCorrected_PTR = &BiasCorrected_PTR[multispec*BiasCorrected->nvox];

      T1data = static_cast<SegPrecisionTYPE *>(T1->data);
      T1data = &T1data[multispec*BiasCorrected->nvox];

      for( unsigned int i=0; i<BiasCorrected->nvox; i++){
          BiasCorrected_PTR[i]=0;
        }

      float to_resize=0;

      for(int i=0; i<CurrSizes->numel; i++){
          to_resize=exp((BiasField[i]+T1data[i])*0.693147181)-1;
          BiasCorrected_PTR[i]=(to_resize*(CurrSizes->rescale_max[multispec]-CurrSizes->rescale_min[multispec])+CurrSizes->rescale_min[multispec]);
        }
    }
  return BiasCorrected;
}


nifti_image * Get_Bias_Corrected_mask(float * BiasFieldCoefs,
                                      nifti_image * T1,
                                      char * filename,
                                      ImageSize * CurrSizes,
                                      int biasOrder){

  int UsedBasisFunctions=(int)((biasOrder+1) * (biasOrder+2)/2 *(biasOrder+3)/3);

  nifti_image * BiasCorrected = nifti_copy_nim_info(T1);
  BiasCorrected->dim[0]=4;
  BiasCorrected->dim[4]=CurrSizes->usize;
  BiasCorrected->datatype=DT_FLOAT32;
  BiasCorrected->cal_max=(CurrSizes->rescale_max[0]);

  nifti_set_filenames(BiasCorrected,filename,0,0);
  nifti_update_dims_from_array(BiasCorrected);
  nifti_datatype_sizes(BiasCorrected->datatype,&BiasCorrected->nbyper,&BiasCorrected->swapsize);
  BiasCorrected->data = (void *) calloc(BiasCorrected->nvox, sizeof(SegPrecisionTYPE));
  SegPrecisionTYPE * BiasCorrected_PTR = static_cast<SegPrecisionTYPE *>(BiasCorrected->data);
  SegPrecisionTYPE * T1data = static_cast<SegPrecisionTYPE *>(T1->data);
  float BiasField=0;
  SegPrecisionTYPE currxpower[maxallowedpowerorder];
  SegPrecisionTYPE currypower[maxallowedpowerorder];
  SegPrecisionTYPE currzpower[maxallowedpowerorder];
  float xpos=0.0f;
  float ypos=0.0f;
  float zpos=0.0f;
  SegPrecisionTYPE not_point_five_times_dims_x=(0.5f*(SegPrecisionTYPE)CurrSizes->xsize);
  SegPrecisionTYPE not_point_five_times_dims_y=(0.5f*(SegPrecisionTYPE)CurrSizes->ysize);
  SegPrecisionTYPE not_point_five_times_dims_z=(0.5f*(SegPrecisionTYPE)CurrSizes->zsize);
  SegPrecisionTYPE inv_not_point_five_times_dims_x=1.0f/(0.5f*(SegPrecisionTYPE)CurrSizes->xsize);
  SegPrecisionTYPE inv_not_point_five_times_dims_y=1.0f/(0.5f*(SegPrecisionTYPE)CurrSizes->ysize);
  SegPrecisionTYPE inv_not_point_five_times_dims_z=1.0f/(0.5f*(SegPrecisionTYPE)CurrSizes->zsize);
  int ind=0;

  for(int multispec=0;multispec<CurrSizes->usize;multispec++){

      BiasCorrected_PTR = static_cast<SegPrecisionTYPE *>(BiasCorrected->data);
      BiasCorrected_PTR = &BiasCorrected_PTR[multispec*CurrSizes->numel];
      T1data = static_cast<SegPrecisionTYPE *>(T1->data);
      T1data = &T1data[multispec*CurrSizes->numel];

      float * BiasFieldCoefs_multispec = &BiasFieldCoefs[multispec*UsedBasisFunctions];


      for(unsigned int i=0; i<BiasCorrected->nvox; i++){
          BiasCorrected_PTR[i]=0;
        }

      float to_resize=0;
      int index_full=0;
      for (int iz=0; iz<CurrSizes->zsize; iz++) {
          for (int iy=0; iy<CurrSizes->ysize; iy++) {
              for (int ix=0; ix<CurrSizes->xsize; ix++) {
                  BiasField=0.0f;
                  xpos=(((SegPrecisionTYPE)ix-not_point_five_times_dims_x)*inv_not_point_five_times_dims_x);
                  ypos=(((SegPrecisionTYPE)iy-not_point_five_times_dims_y)*inv_not_point_five_times_dims_y);
                  zpos=(((SegPrecisionTYPE)iz-not_point_five_times_dims_z)*inv_not_point_five_times_dims_z);
                  get_xyz_pow_int(xpos, ypos, zpos, currxpower, currypower, currzpower, biasOrder);
                  ind=0;
                  for(int order=0; order<=biasOrder; order++){
                      for(int xorder=0; xorder<=order; xorder++){
                          for(int yorder=0; yorder<=(order-xorder); yorder++){
                              int zorder=order-yorder-xorder;
                              BiasField-=BiasFieldCoefs_multispec[ind]*currxpower[xorder]*currypower[yorder]*currzpower[zorder];
                              ind++;
                            }
                        }
                    }

                  to_resize=exp((BiasField+T1data[index_full])*0.693147181)-1;
                  BiasCorrected_PTR[index_full]=(to_resize*(CurrSizes->rescale_max[multispec]-CurrSizes->rescale_min[multispec])+CurrSizes->rescale_min[multispec]);
                  index_full++;
                }
            }
        }
    }
  return BiasCorrected;
}

char * seg_norm_4D_GNCC(nifti_image * BaseImage,nifti_image * NCC,int numberordered,ImageSize * CurrSizes,int verbose){

  LabFusion_datatype * NCCptr = static_cast<LabFusion_datatype *>(NCC->data);
  LabFusion_datatype * BaseImageptr = static_cast<LabFusion_datatype *>(BaseImage->data);

  LabFusion_datatype BaseMean=0.0f;
  LabFusion_datatype BaseSTD=0.0f;


  LabFusion_datatype bufferMean=0.0f;
  LabFusion_datatype bufferSTD=0.0f;


  // CALC MEAN AND STD OF THE BASE
  if (verbose>0){
      cout << "Calculating NCC"<<endl;
      cout << "Local Mean and STD of the base image"<<endl;
      flush(cout);
    }
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      BaseMean+=BaseImageptr[i];

    }
  BaseMean=BaseMean/(BaseImage->nx*BaseImage->ny*BaseImage->nz);
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      BaseSTD+=(BaseImageptr[i]-BaseMean)*(BaseImageptr[i]-BaseMean);
    }
  BaseSTD=sqrtf(BaseSTD/(BaseImage->nx*BaseImage->ny*BaseImage->nz));
  // Calc Mean
  int realt=CurrSizes->numclass;


  // CALC NCC FOR EACH
  if (verbose>0){
      cout << "Local Mean and STD of the Template images"<<endl;
      flush(cout);
    }

  LabFusion_datatype * NCCval= new LabFusion_datatype [NCC->nt];
  for(int currlable=0;currlable<NCC->nt; currlable++){
      NCCval[currlable]=0;
      bufferMean=0;
      bufferSTD=0;
      float * currNCCptr=&NCCptr[currlable*BaseImage->nx*BaseImage->ny*BaseImage->nz];

      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          bufferMean+=currNCCptr[i];
        }
      bufferMean=bufferMean/(BaseImage->nx*BaseImage->ny*BaseImage->nz);
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          bufferSTD+=(currNCCptr[i]-bufferMean)*(currNCCptr[i]-bufferMean);
        }
      bufferSTD=sqrtf(bufferSTD/(BaseImage->nx*BaseImage->ny*BaseImage->nz));
      NCCval[currlable]=0;
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          NCCval[currlable]+=((currNCCptr[i]-bufferMean)*(BaseImageptr[i]-BaseMean));
        }
      NCCval[currlable]=NCCval[currlable]/((bufferSTD*BaseSTD)+0.0000001)/(BaseImage->nx*BaseImage->ny*BaseImage->nz);
      if (verbose>0){
          cout << currlable+1 << "/" << NCC->nt<<" - GNCC= "<< NCCval[currlable]<<endl;
          flush(cout);
        }
    }

  CurrSizes->numclass=realt;


  char * NCC_ordered=new char [numberordered];

  if (verbose>0){
      cout << "Used Labels after sorting the GNCC"<<endl;
    }

  int * ordertmp=quickSort_order(&NCCval[0],NCC->nt);
  for(int lable_order=0;lable_order<numberordered;lable_order++){
      NCC_ordered[lable_order]=(char)ordertmp[NCC->nt-lable_order-1];
      if (verbose>0){
          cout << (int)NCC_ordered[lable_order]+1 << "/" << numberordered<<endl;
        }
    }


  return NCC_ordered;
}


float seg_norm3GNCC(nifti_image * BaseImage,nifti_image * Template,nifti_image * Mask,int verbose){

  LabFusion_datatype * Templateptr = static_cast<LabFusion_datatype *>(Template->data);
  LabFusion_datatype * BaseImageptr = static_cast<LabFusion_datatype *>(BaseImage->data);

  bool * Maskptr=NULL;
  int Maskcount=0;
  bool usemask=false;
  if (Mask!=NULL){
      Maskptr = static_cast<bool * >(Mask->data);
      usemask=true;
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          Maskcount+=Maskptr[i];
        }
    }

  LabFusion_datatype BaseMean=0.0f;
  LabFusion_datatype BaseSTD=0.0f;


  LabFusion_datatype bufferMean=0.0f;
  LabFusion_datatype bufferSTD=0.0f;


  // CALC MEAN AND STD OF THE BASE
  if (verbose>0){
      cout << "Calculating NCC"<<endl;
      cout << "Local Mean and STD of the base image"<<endl;
      flush(cout);
    }


  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){

      if(usemask){BaseMean+=(Maskptr[i])?BaseImageptr[i]:0;}
      else{BaseMean+=BaseImageptr[i];}
    }

  if(usemask){BaseMean=BaseMean/Maskcount;}
  else{BaseMean=BaseMean/(BaseImage->nx*BaseImage->ny*BaseImage->nz);}

  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      if(usemask){BaseSTD+=(Maskptr[i])?((BaseImageptr[i]-BaseMean)*(BaseImageptr[i]-BaseMean)):0;}
      else{BaseSTD+=(BaseImageptr[i]-BaseMean)*(BaseImageptr[i]-BaseMean);}
    }
  if(usemask){BaseSTD=sqrtf(BaseSTD/Maskcount);}
  else{BaseSTD=sqrtf(BaseSTD/(BaseImage->nx*BaseImage->ny*BaseImage->nz));}
  // Calc Mean
  // CALC NCC FOR EACH
  if (verbose>0){
      cout << "Local Mean and STD of the Template images"<<endl;
      flush(cout);
    }

  LabFusion_datatype NCCval=0;

  bufferMean=0;
  bufferSTD=0;

  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      if(usemask){bufferMean+=(Maskptr[i])?Templateptr[i]:0;}
      else{bufferMean+=Templateptr[i];}
    }
  if(usemask){bufferMean=bufferMean/Maskcount;}
  else{bufferMean=bufferMean/(BaseImage->nx*BaseImage->ny*BaseImage->nz);}
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      if(usemask){bufferSTD+=(Maskptr[i])?((Templateptr[i]-bufferMean)*(Templateptr[i]-bufferMean)):0;}
      else{bufferSTD+=(Templateptr[i]-bufferMean)*(Templateptr[i]-bufferMean);}
    }
  if(usemask){BaseSTD=sqrtf(bufferSTD/Maskcount);}
  else{BaseSTD=sqrtf(bufferSTD/(BaseImage->nx*BaseImage->ny*BaseImage->nz));}

  NCCval=0;
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      if(usemask){NCCval+=(Maskptr[i])?((Templateptr[i]-bufferMean)*(BaseImageptr[i]-BaseMean)):0;}
      else{NCCval+=((Templateptr[i]-bufferMean)*(BaseImageptr[i]-BaseMean));}

    }

  if(usemask){NCCval=NCCval/((bufferSTD*BaseSTD)+0.0000001)/(Maskcount);}
  else{NCCval=NCCval/((bufferSTD*BaseSTD)+0.0000001)/(BaseImage->nx*BaseImage->ny*BaseImage->nz);}

  return NCCval;
}





char * seg_norm4ROINCC(nifti_image * LableImage,nifti_image * BaseImage,nifti_image * NCC,int numberordered,ImageSize * CurrSizes,int DilSize, int verbose){

  LabFusion_datatype * NCCptr = static_cast<LabFusion_datatype *>(NCC->data);
  bool * LableImageptr = static_cast<bool *>(LableImage->data);
  LabFusion_datatype * BaseImageptr = static_cast<LabFusion_datatype *>(BaseImage->data);
  bool * ROIarea=new bool [BaseImage->nx*BaseImage->ny*BaseImage->nz];

  LabFusion_datatype BaseMean=0.0f;
  LabFusion_datatype BaseSTD=0.0f;
  LabFusion_datatype bufferMean=0.0f;
  LabFusion_datatype bufferSTD=0.0f;

  // CALC MEAN AND STD OF THE BASE
  if (verbose>0){
      cout << "Calculating ROI from Lables"<<endl;
      flush(cout);
    }
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      ROIarea[i]=false;
    }



  int ROIsize=0;
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      bool ROItmp=false;
      for(int currlable=0;currlable<NCC->nt; currlable++){
          if(LableImageptr[i+currlable*BaseImage->nx*BaseImage->ny*BaseImage->nz]){
              ROItmp=true;
            }
        }
      if(ROItmp==true){
          ROIsize++;
          ROIarea[i]=true;
        }
    }

  int dim_array[3];
  dim_array[0]=(int)BaseImage->nx;
  dim_array[1]=(int)BaseImage->ny;
  dim_array[2]=(int)BaseImage->nz;
  Dillate(ROIarea,DilSize,dim_array,verbose);


  // CALC MEAN AND STD OF THE BASE
  if (verbose>0){
      cout << "Calculating NCC"<<endl;
      cout << "Local Mean and STD of the base image"<<endl;
      flush(cout);
    }
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      if(ROIarea[i]){
          BaseMean+=BaseImageptr[i];
        }
    }
  BaseMean=BaseMean/(ROIsize);
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      if(ROIarea[i]){
          BaseSTD+=(BaseImageptr[i]-BaseMean)*(BaseImageptr[i]-BaseMean);
        }
    }
  BaseSTD=sqrtf(BaseSTD/(ROIsize));
  // Calc Mean
  int realt=CurrSizes->numclass;


  // CALC NCC FOR EACH
  if (verbose>0){
      cout << "Local Mean and STD of the Template images"<<endl;
      flush(cout);
    }

  LabFusion_datatype * NCCval= new LabFusion_datatype [NCC->nt];
  for(int currlable=0;currlable<NCC->nt; currlable++){
      NCCval[currlable]=0;
      float * currNCCptr=&NCCptr[currlable*BaseImage->nx*BaseImage->ny*BaseImage->nz];
      bufferMean=0;
      bufferSTD=0;
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          if(ROIarea[i]){
              bufferMean+=currNCCptr[i];
            }
        }
      bufferMean=bufferMean/(ROIsize);
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          if(ROIarea[i]){
              bufferSTD+=(currNCCptr[i]-bufferMean)*(currNCCptr[i]-bufferMean);
            }
        }
      bufferSTD=sqrtf(bufferSTD/(ROIsize));
      NCCval[currlable]=0;
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          if(ROIarea[i]){
              NCCval[currlable]+=((currNCCptr[i]-bufferMean)*(BaseImageptr[i]-BaseMean));
            }
        }
      NCCval[currlable]=NCCval[currlable]/((bufferSTD*BaseSTD)+0.0000001)/(ROIsize);
      if (verbose>0){
          cout << currlable+1 << "/" << NCC->nt<<" - ROINCC= "<< NCCval[currlable]<<endl;
          flush(cout);
        }
    }

  CurrSizes->numclass=realt;


  char * NCC_ordered=new char [numberordered];

  if (verbose>0){
      cout << "Used Labels after sorting the ROINCC"<<endl;
    }

  int * ordertmp=quickSort_order(&NCCval[0],NCC->nt);
  for(int lable_order=0;lable_order<numberordered;lable_order++){
      NCC_ordered[lable_order]=(char)ordertmp[NCC->nt-lable_order-1];
      if (verbose>0){
          cout << (int)NCC_ordered[lable_order]+1 << "/" << numberordered<<endl;
        }
    }


  return NCC_ordered;
}


char * seg_norm4MLLNCC(nifti_image * BaseImage, nifti_image * LNCC,float distance,int levels, int numberordered,ImageSize * CurrSizes,int verbose){

  LabFusion_datatype * LNCCptr = static_cast<LabFusion_datatype *>(LNCC->data);
  LabFusion_datatype * BaseImageptr = static_cast<LabFusion_datatype *>(BaseImage->data);
  char * LNCC_ordered=NULL;
  char * LNCC_ordered_save=NULL;


  int numbordered_level_old=LNCC->nt;

  for(int curlevel=levels; curlevel;curlevel--){

      if(curlevel==levels){
          LNCC_ordered_save=new char [numbordered_level_old*BaseImage->nx*BaseImage->ny*BaseImage->nz];
          if(LNCC_ordered_save == NULL){
              fprintf(stderr,"* Error when alocating LNCC_ordered_save in function seg_norm4MLLNCC");
              exit(-1);
            }

          for(int cl=0;cl<numbordered_level_old; cl++){
              for(int cl_index=0;cl_index<BaseImage->nx*BaseImage->ny*BaseImage->nz; cl_index++){
                  LNCC_ordered_save[cl_index+cl*(BaseImage->nx*BaseImage->ny*BaseImage->nz)]=cl;
                }
            }
        }


      float distance_level=distance*pow(2,(curlevel-1));
      int numbordered_level=(curlevel*numberordered)<=LNCC->nt?(curlevel*numberordered):LNCC->nt;


      LabFusion_datatype * BaseMean=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
      if(BaseMean == NULL){
          fprintf(stderr,"* Error when alocating BaseMean in function seg_norm4LNCC");
          exit(-1);
        }
      LabFusion_datatype * BaseSTD=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
      if(BaseSTD == NULL){
          fprintf(stderr,"* Error when alocating BaseSTD in function seg_norm4LNCC");
          exit(-1);
        }

      // CALC MEAN AND STD OF THE BASE
      if (verbose>0){
          cout << "Calculating LNCC at level "<<curlevel<< " ( kernel size = "<<distance_level<<" , number templates = "<<numbordered_level<<" )"<<endl;
          cout << "Local Mean and STD of the base image"<<endl;
          flush(cout);
        }
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          BaseMean[i]=BaseImageptr[i];
          BaseSTD[i]=BaseImageptr[i]*BaseImageptr[i];
        }
      // Calc Mean
      int realt=CurrSizes->numclass;
      CurrSizes->numclass=1;
      Gaussian_Filter_4D(BaseMean,(float)(distance_level),CurrSizes);
      Gaussian_Filter_4D(BaseSTD,(float)(distance_level),CurrSizes);

      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          BaseSTD[i]=BaseSTD[i]-BaseMean[i]*BaseMean[i];
        }

      // CALC LNCC FOR EACH
      if (verbose>0){
          cout << "Local Mean and STD of the Template images"<<endl;
          flush(cout);
        }
      int currlable=0;

#ifdef _OPENMP
#pragma omp parallel for shared(BaseImageptr, BaseSTD, BaseMean, LNCC,BaseImage,stderr, verbose,cout,LNCCptr,CurrSizes,distance_level)
#endif

      for(currlable=0;currlable<LNCC->nt; currlable++){
          LabFusion_datatype * bufferMean=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
          if(bufferMean == NULL){
              fprintf(stderr,"* Error when alocating bufferMean in function seg_norm4LNCC");
              exit(-1);
            }
          LabFusion_datatype * bufferSTD=new LabFusion_datatype [ BaseImage->nx * BaseImage->ny * BaseImage->nz ];
          if(bufferSTD == NULL){
              fprintf(stderr,"* Error when alocating bufferSTD in function seg_norm4LNCC");
              exit(-1);
            }
          LabFusion_datatype * bufferDATA=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
          if(bufferDATA == NULL){
              fprintf(stderr,"* Error when alocating bufferDATA in function seg_norm4LNCC");
              exit(-1);
            }

          if (verbose>0){
              cout << currlable+1 << "/" << LNCC->nt<<"\n";
              flush(cout);
            }
          LabFusion_datatype * currLNCCptr=&LNCCptr[currlable*BaseImage->nx*BaseImage->ny*BaseImage->nz];
          for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
              bufferDATA[i]=currLNCCptr[i]*BaseImageptr[i];
              bufferMean[i]=currLNCCptr[i];
              bufferSTD[i]=currLNCCptr[i]*currLNCCptr[i];
            }

          // Calc Mean
          Gaussian_Filter_4D(bufferMean,(float)(distance_level),CurrSizes);
          Gaussian_Filter_4D(bufferSTD,(float)(distance_level),CurrSizes);
          Gaussian_Filter_4D(bufferDATA,(float)(distance_level),CurrSizes);
          for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
              bufferSTD[i]=bufferSTD[i]-bufferMean[i]*bufferMean[i];
              currLNCCptr[i]=(bufferDATA[i]-BaseMean[i]*bufferMean[i])/(sqrt(bufferSTD[i]*BaseSTD[i])+0.0000001);
              currLNCCptr[i]=currLNCCptr[i]>0?currLNCCptr[i]:0;
            }
          delete [] bufferSTD;
          delete [] bufferMean;
          delete [] bufferDATA;
        }

      delete [] BaseSTD;
      delete [] BaseMean;

      CurrSizes->numclass=realt;
      LNCC_ordered=new char [numbordered_level*BaseImage->nx*BaseImage->ny*BaseImage->nz];
      if(LNCC_ordered == NULL){
          fprintf(stderr,"* Error when alocating LNCC_ordered in function seg_norm4LNCC");
          exit(-1);
        }


      if (verbose>0){
          cout << "Sorting"<<endl;
        }

#ifdef _OPENMP
#pragma omp parallel for default(none) \
  shared(LNCC,LNCCptr,CurrSizes,numbordered_level,LNCC_ordered,numbordered_level_old,LNCC_ordered_save)
#endif
      for(int i=0; i<LNCC->nx*LNCC->ny*LNCC->nz;i++){
          LabFusion_datatype LNCCvalue_tmp[1000];
          char old_sort[1000];;
          for(int currlable=0;currlable<LNCC->nt; currlable++){
              LNCCvalue_tmp[currlable]=LNCCptr[i+currlable*LNCC->nx*LNCC->ny*LNCC->nz];
            }

          for(int currlable=0;currlable<numbordered_level_old; currlable++){
              old_sort[currlable]=LNCC_ordered_save[i+currlable*LNCC->nx*LNCC->ny*LNCC->nz];
            }

          int * ordertmp=quickSort_order(&LNCCvalue_tmp[0],LNCC->nt);

          int label_order_index=0;
          for(int lable_order=0;lable_order<LNCC->nt;lable_order++){
              char cur_LNCC_ordered_label=(char)ordertmp[LNCC->nt-lable_order-1];
              for(int currlable=0;currlable<numbordered_level_old; currlable++){
                  if(cur_LNCC_ordered_label==old_sort[currlable]){
                      LNCC_ordered[i+label_order_index*LNCC->nx*LNCC->ny*LNCC->nz]=cur_LNCC_ordered_label;
                      label_order_index++;
                      currlable=numbordered_level_old;
                    }
                }
              if((label_order_index)>=numbordered_level){
                  lable_order=LNCC->nt;
                }

            }
          delete [] ordertmp;

        }

      if(curlevel>1){
          numbordered_level_old=numbordered_level;
          delete [] LNCC_ordered_save;
          LNCC_ordered_save=new char [numbordered_level_old*LNCC->nx*LNCC->ny*LNCC->nz];
          if(LNCC_ordered_save == NULL){
              fprintf(stderr,"* Error when alocating LNCC_ordered_save in function seg_norm4MLLNCC");
              exit(-1);
            }
          for(int cl=0;cl<numbordered_level_old*LNCC->nx*LNCC->ny*LNCC->nz; cl++){
              LNCC_ordered_save[cl]=LNCC_ordered[cl];
            }
          delete [] LNCC_ordered;
        }

      if (verbose>0){
          cout << "Finished sorting"<< endl;
          flush(cout);
        }
    }

  return LNCC_ordered;
}

/* *************************************************************** */


char * seg_norm4LNCC(nifti_image * BaseImage, nifti_image * LNCC,float distance,int numberordered,ImageSize * CurrSizes,int verbose){

  LabFusion_datatype * LNCCptr = static_cast<LabFusion_datatype *>(LNCC->data);
  LabFusion_datatype * BaseImageptr = static_cast<LabFusion_datatype *>(BaseImage->data);
  char * LNCC_ordered=NULL;
  LabFusion_datatype * BaseMean=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
  if(BaseMean == NULL){
      fprintf(stderr,"* Error when alocating BaseMean in function seg_norm4LNCC");
      exit(-1);
    }
  LabFusion_datatype * BaseSTD=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
  if(BaseSTD == NULL){
      fprintf(stderr,"* Error when alocating BaseSTD in function seg_norm4LNCC");
      exit(-1);
    }

  // CALC MEAN AND STD OF THE BASE
  if (verbose>0){
      cout << "Calculating LNCC"<<endl;
      cout << "Local Mean and STD of the base image"<<endl;
      flush(cout);
    }
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      BaseMean[i]=BaseImageptr[i];
      BaseSTD[i]=BaseImageptr[i]*BaseImageptr[i];
    }
  // Calc Mean
  int realt=CurrSizes->numclass;
  CurrSizes->numclass=1;
  Gaussian_Filter_4D(BaseMean,(float)(distance),CurrSizes);
  Gaussian_Filter_4D(BaseSTD,(float)(distance),CurrSizes);

  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      BaseSTD[i]=BaseSTD[i]-BaseMean[i]*BaseMean[i];
    }

  // CALC LNCC FOR EACH
  if (verbose>0){
      cout << "Local Mean and STD of the Template images"<<endl;
      flush(cout);
    }

#ifdef _OPENMP
#pragma omp parallel for shared(BaseImageptr, BaseSTD, BaseMean, LNCC,BaseImage,stderr, verbose,cout,LNCCptr,CurrSizes,distance)
#endif

  for(int currlable=0;currlable<LNCC->nt; currlable++){
      LabFusion_datatype * bufferMean=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
      if(bufferMean == NULL){
          fprintf(stderr,"* Error when alocating bufferMean in function seg_norm4LNCC");
          exit(-1);
        }
      LabFusion_datatype * bufferSTD=new LabFusion_datatype [ BaseImage->nx * BaseImage->ny * BaseImage->nz ];
      if(bufferSTD == NULL){
          fprintf(stderr,"* Error when alocating bufferSTD in function seg_norm4LNCC");
          exit(-1);
        }
      LabFusion_datatype * bufferDATA=new LabFusion_datatype [BaseImage->nx*BaseImage->ny*BaseImage->nz];
      if(bufferDATA == NULL){
          fprintf(stderr,"* Error when alocating bufferDATA in function seg_norm4LNCC");
          exit(-1);
        }
      //for(int currlable=0;currlable<3; currlable++){
      if (verbose>0){
          cout << currlable+1 << "/" << LNCC->nt<<"\n";
          flush(cout);
        }
      LabFusion_datatype * currLNCCptr=&LNCCptr[currlable*BaseImage->nx*BaseImage->ny*BaseImage->nz];
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          bufferDATA[i]=currLNCCptr[i]*BaseImageptr[i];
          bufferMean[i]=currLNCCptr[i];
          bufferSTD[i]=currLNCCptr[i]*currLNCCptr[i];
        }

      // Calc Mean
      Gaussian_Filter_4D(bufferMean,(float)(distance),CurrSizes);
      Gaussian_Filter_4D(bufferSTD,(float)(distance),CurrSizes);
      Gaussian_Filter_4D(bufferDATA,(float)(distance),CurrSizes);
      for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
          bufferSTD[i]=bufferSTD[i]-bufferMean[i]*bufferMean[i];
          currLNCCptr[i]=(bufferDATA[i]-BaseMean[i]*bufferMean[i])/(sqrt(bufferSTD[i]*BaseSTD[i])+0.0000001);
          currLNCCptr[i]=currLNCCptr[i]>0?currLNCCptr[i]:0;
        }
      delete [] bufferSTD;
      delete [] bufferMean;
      delete [] bufferDATA;
    }
  delete [] BaseSTD;
  delete [] BaseMean;


  // cout << "Filtering LNCC"<< endl;
  CurrSizes->numclass=realt;
  //  Gaussian_Filter_4D(LNCCptr,(float)(distance),CurrSizes);

  LNCC_ordered=new char [numberordered*BaseImage->nx*BaseImage->ny*BaseImage->nz];
  if(LNCC_ordered == NULL){
      fprintf(stderr,"* Error when alocating LNCC_ordered in function seg_norm4LNCC");
      exit(-1);
    }


  if (verbose>0){
      cout << "Sorting LNCC"<<endl;
    }

#ifdef _OPENMP
#pragma omp parallel for default(none) \
  shared(LNCC,BaseImage,LNCCptr,CurrSizes,numberordered,LNCC_ordered)
#endif
  for(int i=0; i<BaseImage->nx*BaseImage->ny*BaseImage->nz;i++){
      LabFusion_datatype * LNCCvalue_tmp = new LabFusion_datatype [LNCC->nt];
      for(int currlable=0;currlable<LNCC->nt; currlable++){
          LNCCvalue_tmp[currlable]=LNCCptr[i+currlable*BaseImage->nx*BaseImage->ny*BaseImage->nz];
        }
      int * ordertmp=quickSort_order(&LNCCvalue_tmp[0],LNCC->nt);
      for(int lable_order=0;lable_order<numberordered;lable_order++){
          LNCC_ordered[i+lable_order*BaseImage->nx*BaseImage->ny*BaseImage->nz]=(char)ordertmp[LNCC->nt-lable_order-1];
        }
      delete [] ordertmp;
      delete [] LNCCvalue_tmp;
    }
  if (verbose>0){
      cout << "Finished sorting LNCC"<< endl;
      flush(cout);
    }

  return LNCC_ordered;
}

/* *************************************************************** */



template <class NewTYPE, class DTYPE>
int seg_changeDatatype1(nifti_image *image)
{
  // the initial array is saved and freeed
  DTYPE *initialValue = (DTYPE *)malloc(image->nvox*sizeof(DTYPE));
  memcpy(initialValue, image->data, image->nvox*sizeof(DTYPE));

  // the new array is allocated and then filled
  if(sizeof(NewTYPE)==sizeof(unsigned char)) image->datatype = NIFTI_TYPE_UINT8;
  else if(sizeof(NewTYPE)==sizeof(float)) image->datatype = NIFTI_TYPE_FLOAT32;
  else if(sizeof(NewTYPE)==sizeof(double)) image->datatype = NIFTI_TYPE_FLOAT64;
  else{
      fprintf(stderr,"[NiftyReg ERROR] seg_changeDatatype\tOnly change to unsigned char, float or double are supported\n");
      exit(1);
    }
  free(image->data);
  image->nbyper = sizeof(NewTYPE);
  image->data = (void *)calloc(image->nvox,sizeof(NewTYPE));
  NewTYPE *dataPtr = static_cast<NewTYPE *>(image->data);
  if(sizeof(NewTYPE)==sizeof(unsigned char)){
      for(unsigned int i=0; i<image->nvox; i++) dataPtr[i] = (unsigned char)(round(initialValue[i]));
    }
  else{
      for(unsigned int i=0; i<image->nvox; i++) dataPtr[i] = (NewTYPE)(initialValue[i]);
    }


  free(initialValue);
  return 1;
}
/* *************************************************************** */
template <class NewTYPE>
int seg_changeDatatype(nifti_image *image)
{
  switch(image->datatype){
    case DT_BINARY:
      seg_changeDatatype1<NewTYPE,bool>(image);
      break;
    case NIFTI_TYPE_UINT8:
      seg_changeDatatype1<NewTYPE,unsigned char>(image);
      break;
    case NIFTI_TYPE_INT8:
      seg_changeDatatype1<NewTYPE,char>(image);
      break;
    case NIFTI_TYPE_UINT16:
      seg_changeDatatype1<NewTYPE,unsigned short>(image);
      break;
    case NIFTI_TYPE_INT16:
      seg_changeDatatype1<NewTYPE,short>(image);
      break;
    case NIFTI_TYPE_UINT32:
      seg_changeDatatype1<NewTYPE,unsigned int>(image);
      break;
    case NIFTI_TYPE_INT32:
      seg_changeDatatype1<NewTYPE,int>(image);
      break;
    case NIFTI_TYPE_FLOAT32:
      seg_changeDatatype1<NewTYPE,float>(image);
      break;
    case NIFTI_TYPE_FLOAT64:
      seg_changeDatatype1<NewTYPE,double>(image);
      break;
    default:
      fprintf(stderr,"[NiftyReg ERROR] seg_changeDatatype\tThe initial image data type (%d) is not supported\n",image->datatype);
      exit(1);
    }
  return 1;
}
/* *************************************************************** */
template int seg_changeDatatype<unsigned char>(nifti_image *);
template int seg_changeDatatype<float>(nifti_image *);
template int seg_changeDatatype<double>(nifti_image *);
/* *************************************************************** */


/* *************************************************************** */
template <class DTYPE>
void seg_mat44_mul(mat44 *mat,
                   DTYPE *in,
                   DTYPE *out)
{
  out[0]=mat->m[0][0]*in[0] + mat->m[0][1]*in[1] + mat->m[0][2]*in[2] + mat->m[0][3];
  out[1]=mat->m[1][0]*in[0] + mat->m[1][1]*in[1] + mat->m[1][2]*in[2] + mat->m[1][3];
  out[2]=mat->m[2][0]*in[0] + mat->m[2][1]*in[1] + mat->m[2][2]*in[2] + mat->m[2][3];
  return;
}
template void seg_mat44_mul<float>(mat44 *, float*, float*);
template void seg_mat44_mul<double>(mat44 *, double*, double*);
/* *************************************************************** */
template<class SourceTYPE, class FieldTYPE>
void Resample_NN_with_weights(  nifti_image *sourceImage,
                                nifti_image *deformationField,
                                nifti_image *resultImage,
                                nifti_image *resultImageWeights,
                                int *mask,
                                float bgValue)
{
  // The resampling scheme is applied along each time
  SourceTYPE *sourceIntensityPtr = static_cast<SourceTYPE *>(sourceImage->data);
  SourceTYPE *resultIntensityPtr = (resultImage!=NULL)?static_cast<SourceTYPE *>(resultImage->data):NULL;
  FieldTYPE * resultWeightsPtr = (resultImageWeights!=NULL)?static_cast<FieldTYPE *>(resultImageWeights->data):NULL;
  FieldTYPE *deformationFieldPtrX = static_cast<FieldTYPE *>(deformationField->data);

  int targetVoxelNumber = (resultImage!=NULL)?(resultImage->nx*resultImage->ny*resultImage->nz):(resultImageWeights->nx*resultImageWeights->ny*resultImageWeights->nz);
  //int targetVoxelNumber_x = (resultImage!=NULL)?(resultImage->nx):(resultImageWeights->nx);
  //int targetVoxelNumber_y = (resultImage!=NULL)?(resultImage->ny):(resultImageWeights->ny);
  //int targetVoxelNumber_z = (resultImage!=NULL)?(resultImage->nz):(resultImageWeights->nz);

  FieldTYPE *deformationFieldPtrY = &deformationFieldPtrX[targetVoxelNumber];
  FieldTYPE *deformationFieldPtrZ = &deformationFieldPtrY[targetVoxelNumber];

  int *maskPtr = (mask!=NULL)?&mask[0]:NULL;
  mat44 *sourceIJKMatrix;
  if(sourceImage->sform_code>0)
    sourceIJKMatrix=&(sourceImage->sto_ijk);
  else sourceIJKMatrix=&(sourceImage->qto_ijk);


  SourceTYPE *resultIntensity = (resultIntensityPtr!=NULL)?&resultIntensityPtr[0]:NULL;
  FieldTYPE *resultWeights = (resultWeightsPtr!=NULL)?&resultWeightsPtr[0]:NULL;
  SourceTYPE *sourceIntensity = &sourceIntensityPtr[0];

  FieldTYPE xBasis[2], yBasis[2], zBasis[2], relative;
  int a, b, c, Y, Z, previous[3], index;
  SourceTYPE *zPointer, *xyzPointer;
  FieldTYPE world[3], position[3];
#ifdef _OPENMP
#pragma omp parallel for default(none) \
  private(index, world, position, previous, xBasis, yBasis, zBasis, relative, \
  a, b, c, Y, Z, zPointer, xyzPointer) \
  shared(sourceIntensity, resultIntensity,resultWeights, targetVoxelNumber, \
  deformationFieldPtrX, deformationFieldPtrY, deformationFieldPtrZ, maskPtr, \
  sourceIJKMatrix, sourceImage, bgValue)
#endif // _OPENMP
  for(index=0;index<targetVoxelNumber; index++){
      if(maskPtr==NULL || maskPtr[index]>-1){
          world[0]=(FieldTYPE) deformationFieldPtrX[index];
          world[1]=(FieldTYPE) deformationFieldPtrY[index];
          world[2]=(FieldTYPE) deformationFieldPtrZ[index];

          /* real -> voxel; source space */
          seg_mat44_mul(sourceIJKMatrix, world, position);
          if( position[0]>=0.f && position[0]<(FieldTYPE)(sourceImage->nx-1) && position[1]>=0.f && position[1]<(FieldTYPE)(sourceImage->ny-1) && position[2]>=0.f && position[2]<(FieldTYPE)(sourceImage->nz-1) ){
              previous[0] = (int)position[0];
              previous[1] = (int)position[1];
              previous[2] = (int)position[2];
              // basis values along the x axis
              relative=position[0]-(FieldTYPE)previous[0];
              if(relative<0) relative=0.0; // rounding error correction
              xBasis[0]= (FieldTYPE)(1.0-relative);
              xBasis[1]= relative;
              // basis values along the y axis
              relative=position[1]-(FieldTYPE)previous[1];
              if(relative<0) relative=0.0; // rounding error correction
              yBasis[0]= (FieldTYPE)(1.0-relative);
              yBasis[1]= relative;
              // basis values along the z axis
              relative=position[2]-(FieldTYPE)previous[2];
              if(relative<0) relative=0.0; // rounding error correction
              zBasis[0]= (FieldTYPE)(1.0-relative);
              zBasis[1]= relative;
              int neighindex=0;
              for(c=0; c<2; c++){
                  Z= previous[2]+c;
                  zPointer = &sourceIntensity[Z*sourceImage->nx*sourceImage->ny];
                  for(b=0; b<2; b++){
                      Y= previous[1]+b;
                      xyzPointer = &zPointer[Y*sourceImage->nx+previous[0]];
                      for(a=0; a<2; a++){
                          if(resultIntensity!=NULL)
                            resultIntensity[index+targetVoxelNumber*neighindex]=(SourceTYPE)(*xyzPointer);
                          if(resultWeights!=NULL)
                            resultWeights[index+targetVoxelNumber*neighindex]=(float)(xBasis[a]*yBasis[b]*zBasis[c]);
                          xyzPointer++;
                          neighindex++;
                        }
                    }
                }
            }
          else {
              for(int neighindex=0; neighindex<8; neighindex++){
                  if(resultIntensity!=NULL)
                    resultIntensity[index+targetVoxelNumber*neighindex]=(SourceTYPE)(round(bgValue));
                  if(resultWeights!=NULL)
                    resultWeights[index+targetVoxelNumber*neighindex]=(SourceTYPE)(round(bgValue));
                }
            }
        }
    }

  return;
}

template void Resample_NN_with_weights<unsigned char,float>(nifti_image *sourceImage,nifti_image *deformationField,nifti_image *resultImage,nifti_image *resultImageWeights,int *mask,float bgValue);


int get_all_files_and_folders_in_dir (string dir, vector<string> &files , vector<string> &folders)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }

  while ((dirp = readdir(dp)) != NULL) {
      if(dirp->d_name[0]!='.'){
          if(dirp->d_type==8){
              files.push_back(dir+string("/")+string(dirp->d_name));
            }
          else{
              folders.push_back(dir+string("/")+string(dirp->d_name));
            }
        }
    }
  closedir(dp);
  return 0;
}
int get_all_files_that_match_string (string dir, vector<string> &files , string string_to_match)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }

  while ((dirp = readdir(dp)) != NULL) {
      if(dirp->d_name[0]!='.'){
          if(dirp->d_type==8){
              string curstring=dirp->d_name;
              if(curstring.find(string_to_match)>=0){
                  files.push_back(dir+string("/")+string(dirp->d_name));
                }
            }
        }
    }
  closedir(dp);
  return 0;
}
int get_all_files_that_match_2_strings(string dir, vector<string> &files , string string_to_match, string string_to_match2)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }
  while ((dirp = readdir(dp)) != NULL) {
      if(dirp->d_name[0]!='.'){
          if(dirp->d_type==8){
              string curstring=dirp->d_name;
              if((bool)(curstring.find(string_to_match)!=string::npos) & (bool)(curstring.find(string_to_match2)!=string::npos)){
                  files.push_back(dir+string("/")+string(dirp->d_name));
                }
            }
          //            else{
          //                folders.push_back(dir+string("/")+string(dirp->d_name));
          //            }
        }
    }
  closedir(dp);
  return 0;
}
int get_all_files_in_dir_without_extension(string dir, vector<string> &files)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }
  while ((dirp = readdir(dp)) != NULL) {
      if(dirp->d_name[0]!='.'){
          if(dirp->d_type==8){
              string tmpstring=dir+string("/")+string(dirp->d_name);
              tmpstring.erase(tmpstring.find_first_of(".",tmpstring.find_last_of("/")),tmpstring.length());
              files.push_back(tmpstring);
            }
        }
    }
  closedir(dp);
  return 0;
}
float * getHeatWij(float * DistanceMatrix,int size_matrix, float temperature){
  float * UpdatedDistanceMatrix= new float [size_matrix*size_matrix];

  for(int i=0; i<size_matrix; i++){
      for(int j=0; j<size_matrix; j++){
          UpdatedDistanceMatrix[i*size_matrix+j]=expf(-((float)DistanceMatrix[i*size_matrix+j])/temperature);
        }
    }
  return UpdatedDistanceMatrix;
}
float * getNN(float * DistanceMatrix,int size_matrix,int sizeneig){
  float * UpdatedDistanceMatrix= new float [size_matrix*size_matrix];
  float * currcosts= new float [size_matrix];
  int * ranking;
  for(int i=0; i<size_matrix; i++){
      for(int j=0; j<size_matrix; j++){
          currcosts[j]=(float)DistanceMatrix[j+i*size_matrix];
        }
      ranking=quickSort_order(currcosts,size_matrix);
      for(int j=0; j<((sizeneig+1)>size_matrix?size_matrix:(sizeneig+1)); j++){
          UpdatedDistanceMatrix[i*size_matrix+ranking[j]]=(float)currcosts[j];
        }
      if((sizeneig+1)<size_matrix){
          for(int j=(sizeneig); j<size_matrix; j++){
              UpdatedDistanceMatrix[i*size_matrix+ranking[j]]=(float)100000.0f;
            }
        }
      delete [] ranking;
    }
  return UpdatedDistanceMatrix;
}
