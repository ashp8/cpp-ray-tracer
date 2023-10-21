#ifndef GTFM_H
#define GTFM_H

#include "../qbLinAlg/qbVector.h"
#include "../qbLinAlg/qbMatrix.h"
#include "ray.h"

namespace qbRT{
    // Define direction flag vlaues.
    constexpr bool FWDTFORM = true;
    constexpr bool BCKTFORM = false;

    class GTform{
    public:
        GTform();
        ~GTform();

        // construction from a pair of matrices. 
        GTform(const qbMatrix2<double>&fwd, const qbMatrix2<double>&bc);

        // Function to set translation, rotation and scale components. 
        void SetTransform(const qbVector<double> &translation,
                          const qbVector<double> &rotation,
                          const qbVector<double> &scale);

        // Function to return the transform matrices.
        qbMatrix2<double> GetForward();
        qbMatrix2<double> GetBackward();

        // Function to apply the transform
        
        qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);
        qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);

        // Overload operators 
        friend GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs);
        GTform operator= (const qbRT::GTform &rhs);

        // function to print transform matrices to stdout
        void PrintMatrix(bool dirFlag);

        static void PrintVector(const qbVector<double> &vector);
    private:
        void Print(const qbMatrix2<double> &matrix); 
    private:
        qbMatrix2<double> m_fwdtfm {4, 4};
        qbMatrix2<double> m_bcktfm {4, 4};
    };
}

#endif
