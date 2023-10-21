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


qbVector<double> qbRT::GTform::Apply(const qbVector<double> &inputVector, bool dirFlag){
    const std::vector<double> tempData {
        inputVector.GetElement(0),
        inputVector.GetElement(1),
        inputVector.GetElement(2), 1.0};
    qbVector<double> tempVector {tempData};
    
    qbVector<double> resultVector;
    if(dirFlag){
        resultVector = m_fwdtfm * tempVector;
    }else{
        resultVector = m_bcktfm * tempVector;
    }

    qbVector<double> outPutVector {std::vector<double> {
        resultVector.GetElement(0), 
        resultVector.GetElement(1), 
        resultVector.GetElement(2)}};
    return outPutVector;
}




// Overload Operators
namespace qbRT{
    qbRT::GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs){
        // form the product of the two forward transform
        qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

        // compute backward transform as the inverse of the forward transform
        qbMatrix2<double> bckResult = fwdResult;
        bckResult.Inverse();

        qbRT::GTform finalResult (fwdResult, bckResult);
        return finalResult;
    }
};

qbRT::GTform qbRT::GTform::operator= (const qbRT::GTform &rhs){
    // make sure not to assign self
    if(this != &rhs){
        m_fwdtfm = rhs.m_fwdtfm;
        m_bcktfm = rhs.m_bcktfm;
    }
    return *this;
}

// Function to Print the transform Matrix to stdout
//
void qbRT::GTform::PrintMatrix(bool dirFlag){
    if(dirFlag)
        Print(m_fwdtfm);
    else
        Print(m_bcktfm);
}

void qbRT::GTform::Print(const qbMatrix2<double> &matrix){
    int nRows = matrix.GetNumRows();
    int nCols = matrix.GetNumCols();

    for(int row = 0; row < nRows; ++row){
        for(int col = 0; col < nCols; ++col){
            std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row,col) << " ";
        }
        std::cout << std::endl;
    };
};

void qbRT::GTform::PrintVector(const qbVector<double> &vector){
    int nRows = vector.GetNumDims();
    for(int row = 0; row < nRows; ++row){
        std::cout << std::fixed << std::setprecision(3) << vector.GetElement(row) << std::endl;
    }
}
