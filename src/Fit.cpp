#include <RcppArmadillo.h>
 #include <omp.h>
using namespace Rcpp;
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppArmadillo)]]


//' @export
// [[Rcpp::export]]
List Fit(const arma::colvec & x, const arma::colvec & y, int l, int cores) {

  int k; arma::colvec coef; arma::colvec fitted;

  k = x.n_rows - l + 1;

  arma::colvec Y(k*l);
  arma::colvec X(k*l);

  #pragma omp parallel for scheulde(auto)
  for (int i=0; i<k; i++){

    arma::uvec ids = arma::linspace<arma::uvec>(i, i+l-1, l);
    arma::uvec IDs = arma::linspace<arma::uvec>(i*l, (l*(i+1))-1, l);

    coef = arma::solve(x.elem(ids), y.elem(ids));
    Y.elem(IDs) = x.elem(ids)*coef;
    X.elem(IDs) = x.elem(ids);
  }

  return List::create(Named("y") = Y,
                      Named("x") = X);
}

