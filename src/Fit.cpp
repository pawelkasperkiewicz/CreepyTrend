#include <RcppArmadillo.h>
#include <omp.h>
using namespace Rcpp;
// [[Rcpp::plugins(openmp)]]
// [[Rcpp::depends(RcppArmadillo)]]


//' @export
// [[Rcpp::export]]
List Fit(const arma::colvec & x, const arma::colvec & y, int l, int cores) {

  int k; arma::colvec coef; arma::colvec fitted; arma::colvec constant(x.n_rows);
  constant.fill(1);
  arma::mat egzog(x.n_rows, 2);
  egzog.col(0) = x; egzog.col(1) = constant;

  k = x.n_rows - l + 1;

  arma::colvec Y(k*l);
  arma::colvec X(k*l);
  arma::uvec ids;
  arma::uvec IDs;
  omp_set_num_threads(12);
  #pragma omp parallel for shared(egzog, x, X, Y, k) private(ids, IDS)
  for (int i=0; i<k; i++){

    ids = arma::linspace<arma::uvec>(i, i+l-1, l);
    IDs = arma::linspace<arma::uvec>(i*l, (l*(i+1))-1, l);

    coef = arma::solve(egzog.rows(ids), y.rows(ids));
    Y.elem(IDs) = egzog.rows(ids)*coef;
    X.elem(IDs) = x.rows(ids);
  }


  return List::create(Named("y") = Y,
                      Named("x") = X);
}

