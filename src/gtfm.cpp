#include "../include/gtfm.h"

qbRT::GTform::GTform(){
    m_fwdtfm.SetToIdentity();
    m_bcktfm.SetToIdentity();
}

qbRT::GTform::~GTform(){
}

// Construct a pair of matrix
qbRT::GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck){
    if((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) ||
       (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4)){
        throw std::invalid_argument("cannot construct GTform, inputs are not all 4x4");
    }
    m_fwdtfm = fwd;
    m_bcktfm = bck;
}

void qbRT::GTform::SetTransform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale){
    // Define a matrix for each componet of the transform
    qbMatrix2<double> translationMatrix {4, 4};
    qbMatrix2<double> rotationMatrixX {4, 4};
    qbMatrix2<double> rotationMatrixY {4, 4};
    qbMatrix2<double> rotationMatrixZ {4, 4};
    qbMatrix2<double> scaleMatrix {4, 4};
    
    // set these to identity 
    translationMatrix.SetToIdentity();
    rotationMatrixX.SetToIdentity();
    rotationMatrixY.SetToIdentity();
    rotationMatrixZ.SetToIdentity();
    scaleMatrix.SetToIdentity();

    // Populate these with appropriate values 
    translationMatrix.SetElement(0, 3, translation.GetElement(0));
    translationMatrix.SetElement(1, 3, translation.GetElement(1));
    translationMatrix.SetElement(2, 3, translation.GetElement(2));

    rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

    rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
    rotationMatrixY.SetElement(0, 2, -sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 0, sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

    rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
    rotationMatrixX.SetElement(1, 2, sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 1, -sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));


    // Scale Matrix
    scaleMatrix.SetElement(0, 0, scale.GetElement(0));
    scaleMatrix.SetElement(1, 1, scale.GetElement(1));
    scaleMatrix.SetElement(2, 2, scale.GetElement(2));

    // combine to give the final forward transform matrix
    m_fwdtfm = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY
        * rotationMatrixZ;

    // combine to give the final backward transform matrix
    m_bcktfm = m_fwdtfm;
    m_bcktfm.Inverse();
}

// function to return the transform matrix
qbMatrix2<double> qbRT::GTform::GetForward(){
    return m_fwdtfm;
}

qbMatrix2<double> qbRT::GTform::GetBackward(){
    return m_bcktfm;
}

// function to apply the transform
qbRT::Ray qbRT::GTform::Apply(const qbRT::Ray &inputRay, bool dirFlag){
    // Create an output object
    qbRT::Ray outputRay;
    if(dirFlag){
        outputRay.m_point1 = this->Apply(inputRay.m_point1, qbRT::FWDTFORM);
        outputRay.m_point2 = this->Apply(inputRay.m_point2, qbRT::FWDTFORM);
        outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
    }else{
        outputRay.m_point1 = this->Apply(inputRay.m_point1, qbRT::BCKTFORM);
        outputRay.m_point2 = this->Apply(inputRay.m_point2, qbRT::BCKTFORM);
        outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
    }

    return outputRay;
}



// # In this place last time
