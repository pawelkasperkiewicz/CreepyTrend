#include <RcppArmadillo.h>
//#include <omp.h>
using namespace Rcpp;
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppArmadillo)]]


//' @export
// [[Rcpp::export]]
arma::rowvec Agg(const arma::colvec& X, const arma::colvec& Y){

  int n = arma::max(X);
  arma::colvec y(n);

  arma::uvec I;
  arma::uvec F;
  //omp_set_num_threads(12);
  //#pragma omp parallel for shared(X, Y, y) private(I, F)
  for(int i=0; i<n; i++){
    I = i;
    F = arma::find(X == i+1);
    y.elem(I) = arma::mean(Y.rows(F));
    }

  return y;

}
