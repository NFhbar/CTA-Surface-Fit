#include "cutresiduals.h"


CutResiduals::CutResiduals(QObject *parent) :
    QObject(parent)
{
}

CutResiduals::~CutResiduals()
{

}

void CutResiduals::process()
{

   arma::uvec min = find(Residuals.col(2) < Cut(0));
   arma::uvec max = find(Residuals.col(2) > Cut(1));

   int nop  = Residuals.n_rows;
   int rowsmin = min.n_rows;  
   min.insert_rows(rowsmin,max);
   rowsmin = min.n_rows;
   int totalrow = nop-(rowsmin);
   int np = D.n_rows;
   CutPoints.set_size(rowsmin,3);
   ResidualCut.set_size(totalrow,3);
   CutData.set_size(np,4);


   int rowPCut = 0;
   int rowRCut = 0;
   for(int i=0; i<nop; i++)
   {
       if(Residuals(i,2) < Cut(0) || Residuals(i,2) > Cut(1))
       {
           CutPoints(rowPCut,0) = Residuals(i,0);
           CutPoints(rowPCut,1) = Residuals(i,1);
           CutPoints(rowPCut,2) = Residuals(i,2);
           rowPCut = rowPCut + 1;
       }

       else
       {
           ResidualCut(rowRCut,0) = Residuals(i,0);
           ResidualCut(rowRCut,1) = Residuals(i,1);
           ResidualCut(rowRCut,2) = Residuals(i,2);
           rowRCut = rowRCut + 1;
       }
   }



   CutData.zeros();
   for(int i=0; i<np; i++)
   {
               CutData(i,0) = D(i,0);
               CutData(i,1) = D(i,1);
               CutData(i,2) = D(i,2);
    }



   for(int i=0; i<rowsmin; i++)
   {
       CutData(min(i),3) = 1;
   }

}

//===============================SLOTS==========================================//
//==============================================================================//

void CutResiduals::ListenCut(arma::vec cut)
{
    Cut = cut;
}

void CutResiduals::ListenResiduals(arma::mat r)
{
    Residuals = r;
}

void CutResiduals::ListenData(arma::mat d)
{
    D = d;
}
